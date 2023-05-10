#include <iostream>
#pragma warning(disable:4996)

using namespace std;

class CarPart {
    unsigned ID;
    char* name;
    char* description;

public:
    unsigned getID(void) const {
        return this->ID;
    }

    const char* getName(void) const {
        return this->name;
    }

    const char* getDescription(void) const {
        return this->description;
    }

    void setID(const unsigned ID) {
        this->ID = ID;
    }

    void setStr(char* destStr, const char* name) {
        try {
            char* newName = new char[strlen(name) + 1];
            strcpy(newName, name);
            if (destStr != name && destStr) {
                delete[] destStr;
            }
            destStr = newName;
        }
        catch (bad_alloc ba) {
            throw ba;
        }
    }

    void setName(const char* name) {
        setStr(this->name, name);
    }

    void setDescription(const char* description) {
        setStr(this->description, description);
    }

    CarPart() : ID(0), name(nullptr), description(nullptr) {};

    ~CarPart() {
        delete[] this->name;
        delete[] this->description;
    }

    CarPart(const unsigned ID, const char* name, const char* description) {
        setID(ID);
        setName(name);
        setDescription(description);
    }

    CarPart& operator=(const CarPart& carPart) {
        setID(carPart.getID());
        setName(carPart.getName());
        setDescription(carPart.getDescription());
        return *this;
    }

    friend ostream& operator<<(ostream& os, const CarPart& cp) {
        os << '(' << tire.getID() << ") by " << tire.getName() << " - " << tire.getDescription();
        return os;
    }
};

class Tire : public CarPart {
protected:
    float width;
    float profile;
    float diameter;

public:
    float getWidth(void) const {
        return this->width;
    }

    float getProfile(void) const {
        return this->profile;
    }

    float getDiameter(void) const {
        return this->diameter;
    }

    void setWidth(const float width) {
        if (width < 155 || width > 365) {
            throw logic_error("Invalid width.");
        }
        this->width = width;
    }

    void setProfile(const float profile) {
        if (profile < 30 || profile > 80) {
            throw logic_error("Invalid profile.");
        }
        this->profile = profile;
    }

    void setDiameter(const float diameter) {
        if (diameter < 13 || diameter > 21) {
            throw logic_error("Invalid diameter.");
        }
        this->diameter = diameter;
    }

    Tire() : width(0), profile(0), diameter(0) {};

    Tire(const unsigned ID, const char* name, const char* description, const float width, const float profile, const float diameter)
        : CarPart(ID, name, description) {
        setWidth(width);
        setProfile(profile);
        setDiameter(diameter);
    }

    friend ostream& operator<<(ostream& os, const Tire& tire) {
        os << (const CarPart&)tire;
        os << " - " << tire.getWidth() << '/' << tire.getProfile() << 'R' << tire.getDiameter();
        return os;
    }
};

class Engine : public CarPart {
    float horsePower = 0;

public:
    float getHorsePower(void) const {
        return this->horsePower;
    }

    void setHorsePower(const float horsePower) {
        if (horsePower < 0) {
            throw logic_error("Horsepower cannot be negative.");
        }
        this->horsePower = horsePower;
    }

    Engine() = default;

    Engine(const unsigned ID, const char* name, const char* description, const float horsePower)
        : CarPart(ID, name, description) {
        setHorsePower(horsePower);
    }

    friend ostream& operator<<(ostream& os, const Engine& engine) {
        os << (const CarPart&)engine;
        os << " - " << engine.getDescription() << " - " << engine.getHorsePower() << " hp";
        return os;
    }
};

class Accumulator : public CarPart {
    float capacity;
    unsigned batteryID;

public:
    float getCapacity(void) const {
        return this->capacity;
    }

    unsigned getBatteryID(void) const {
        return this->batteryID;
    }

    void setCapacity(const float capacity) {
        if (capacity < 0) {
            throw logic_error("Capacity cannot be negative.");
        }
        this->capacity = capacity;
    }

    void setBatteryID(const unsigned batteryID) {
        this->batteryID = batteryID;
    }

    Accumulator() : capacity(0), batteryID(0) {};

    Accumulator(const unsigned ID, const char* name, const char* description, const float capacity, const unsigned batteryID)
        : CarPart(ID, name, description) {
        setCapacity(capacity);
        setBatteryID(batteryID);
    }

    friend ostream& operator<<(ostream& os, const Accumulator& accum) {
        cout << '(' << accum.getID() << ") by " << accum.getName() << " - " << accum.getDescription() << " - " << accum.getCapacity() << " Ah";
        return os;
    }
};

class insufficient_fuel_error : public logic_error {
public:
    insufficient_fuel_error(const char* message) : logic_error(message) {}
};

class FuelTank {
    double capacity;
    double fuel;

    void setCapacity(const double capacity) {
        if (capacity < 0) {
            throw logic_error("Capacity cannot be negative.");
        }
        this->capacity = capacity;
    }

    void setFuel(const double fuel) {
        if (fuel < 0) {
            throw logic_error("Fuel cannot be negative.");
        }
        else if (fuel > capacity) {
            throw logic_error("Fuel cannot be more than the capacity, that's dangerous.");
        }
        this->fuel = fuel;
    }

public:
    FuelTank() = default;

    double getCapacity(void) const {
        return this->capacity;
    }

    double getFuel(void) const {
        return this->fuel;
    }

    FuelTank(const double capacity) {
        setCapacity(capacity);
        setFuel(capacity);
    }

    void use(const double fuelToUse) {
        if (this->fuel - fuelToUse < 0) {
            throw insufficient_fuel_error("insufficient_fuel_error");
        }
        setFuel(this->fuel - fuelToUse);
    }

    void fill(const double fuelToFill) {
        if (this->fuel + fuelToFill > this->capacity) {
            setFuel(capacity);
            return;
        }
        setFuel(this->fuel + fuelToFill);
    }
};

class Car {
    FuelTank fuelTank;
    Engine engine;
    Tire tires[4];
    Accumulator accumulator;
    double drivenKilometers;
    float weigth;

public:
    Engine getEngine(void) const {
        return this->engine;
    }

    float getWeigth(void) const {
        return this->weigth;
    }

    void setWeigth(const float weigth) {
        this->weigth = weigth;
    }

    Car() = default;

    Car(const FuelTank ft, const Engine eng, const Tire trs[4], const Accumulator acc, const double dk, const float w) {
        if (sizeof(trs) < 4) {
            throw logic_error("Too few tires.");
        }

        this->fuelTank = ft.getCapacity();
        this->engine = eng;
        for (size_t i = 0; i < 4; ++i) {
            this->tires[i] = trs[i];
        }
        this->accumulator = acc;
        this->drivenKilometers = dk;
        this->weigth = w;
    }

    bool drive(const double kilometers) {
        if (kilometers > this->fuelTank.getFuel()) {
            return false;
        }

        this->drivenKilometers += kilometers;
        this->fuelTank.use(kilometers);
        return true;
    }
};

Car* dragRace(Car* car1, Car* car2) {
    if (!(*car1).drive(0.4) && !(*car2).drive(0.4)) {
        return nullptr;
    }
    else if ((*car1).drive(0.4) && !(*car2).drive(0.4)) {
        return car1;
    }
    else if (!(*car1).drive(0.4) && (*car2).drive(0.4)) {
        return car2;
    }
    else {
        if ((*car1).getWeigth() / (*car1).getEngine().getHorsePower() > (*car2).getWeigth() / (*car2).getEngine().getHorsePower()) {
            return car1;
        }
        else {
            return car2;
        }
    }
}

int main()
{
    return 0;
}
