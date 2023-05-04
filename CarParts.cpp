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
            strcpy(newName, destStr);
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
            throw "Invalid width.";
        }
        this->width = width;
    }

    void setProfile(const float profile) {
        if (profile < 30 || profile > 80) {
            throw "Invalid profile.";
        }
        this->profile = profile;
    }

    void setDiameter(const float diameter) {
        if (diameter < 13 || diameter > 21) {
            throw "Invalid diameter.";
        }
        this->diameter = diameter;
    }

    Tire(const unsigned ID, const char* name, const char* description,  const float width, const float profile, const float diameter)
        : CarPart(ID, name, description), width(0), profile(0), diameter(0) {
        setWidth(width);
        setProfile(profile);
        setDiameter(diameter);
    }
    
    friend ostream& operator<<(ostream& os, const Tire& tire) {
        cout << '(' << tire.getID() << ") by " << tire.getName() << " - " << tire.getDescription() << " - " << tire.getWidth() << '/' << tire.getProfile() << 'R' << tire.getDiameter();
        return os;
    }
 };

class Engine : public CarPart {
    float horsePower;

public:
    float getHorsePower(void) const {
        return this->horsePower;
    }

    void setHorsePower(const float horsePower) {
        if (horsePower < 0) {
            throw "Horsepower cannot be negative.";
        }
        this->horsePower = horsePower;
    }

    Engine(const unsigned ID, const char* name, const char* description, const float horsePower)
        : CarPart(ID, name, description), horsePower(0) {
        setHorsePower(horsePower);
    }

    friend ostream& operator<<(ostream& os, const Engine& engine) {
        cout << '(' << engine.getID() << ") by " << engine.getName() << " - " << engine.getDescription() << " - " << engine.getHorsePower() << " hp";
        return os;
    }
};

class Accummulator : public CarPart {
    float capacity;
    unsigned batteryID;

public:
    float getCapacity(void) const {
        return this->capacity;
    }

    float getBatteryID(void) const {
        return this->batteryID;
    }

    void setCapacity(const float capacity) {
        if (capacity < 0) {
            throw "Capacity cannot be negative.";
        }
        this->capacity = capacity;
    }

    void setBatteryID(const unsigned batteryID) {
        this->batteryID = batteryID;
    }

    Accummulator(const unsigned ID, const char* name, const char* description, const float capacity, const unsigned batteryID)
        : CarPart(ID, name, description), capacity(0) {
        setCapacity(capacity);
        setBatteryID(batteryID);
    }

    friend ostream& operator<<(ostream& os, const Accummulator& accum) {
        cout << '(' << accum.getID() << ") by " << accum.getName() << " - " << accum.getDescription() << " - " << accum.getCapacity() << " Ah";
        return os;
    }
};

class FuelTank {
    float capacity;
    float fuel;

public:
    float getCapacity(void) const {
        return this->capacity;
    }

    float getFuel(void) const {
        return this->fuel;
    }

    void setCapacity(const float capacity) {
        if (capacity < 0) {
            throw "Capacity cannot be negative.";
        }
        this->capacity = capacity;
    }

    void setFuel(const unsigned batteryID) {
        if (fuel < 0) {
            throw "Fuel cannot be negative.";
        }
        else if (fuel > capacity) {
            throw "Fuel cannot be more than the capacity, that's dangerous.";
        }
        this->fuel = fuel;
    }
};

int main()
{
    return 0;
}
