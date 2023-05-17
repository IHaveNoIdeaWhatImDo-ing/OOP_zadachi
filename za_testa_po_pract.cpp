#include <iostream>
#pragma warning(disable:4996)

using namespace std;

class Car
{
    char brand[31];
    char model[31];
    char registry[9];

public:
    const char* getBrand(void) const {
        return this->brand;
    }

    const char* getModel(void) const {
        return this->model;
    }

    const char* getRegistry(void) const {
        return this->registry;
    }

    void setBrand(const char brand[31]) {
        strcpy(this->brand, brand);
    }

    void setModel(const char model[31]) {
        strcpy(this->model, model);
    }

    // Car() = delete;
    Car() = default;

    Car(char brand[31], char registry[9]) {
        setBrand(brand);
        strcpy(this->registry, registry);
    }

    Car(char brand[31], char model[31], char registry[9]) {
        setBrand(brand);
        setModel(model);
        strcpy(this->registry, registry);
    }

    bool operator==(const Car& car) {
        return !strcmp(getBrand(),    car.getBrand()) &&
               !strcmp(getModel(),    car.getModel()) &&
               !strcmp(getRegistry(), car.getRegistry());
    }

    bool operator!=(const Car& car) {
        return !(*this == car);
    }

    Car& operator=(const Car& car) {
        setBrand(car.getBrand());
        setModel(car.getModel());
        strcpy(this->registry, car.getRegistry());
    }
};

class Parking
{
    Car* cars;
    size_t size;

    Car breakConst(const Car car) const {
        return car;
    }

public:
    const size_t length(void) const {
        return this->size;
    }

    Car* getCars(void) const {
        return this->cars;
    }

    bool dupeCars(const Car* cars, size_t size) {
        for (size_t i = 0; i < size - 1; ++i) {
            for (size_t j = i + 1; j < size; ++j) {
                if (breakConst(cars[i]) != cars[j]) {
                    return false;
                }
            }
        }
    }

    void setCars(Car* cars) {
        if (!dupeCars(cars, sizeof(cars))) {
            try {
                if (this->cars != cars) {
                    delete[] this->cars;
                    this->cars = cars;
                    this->size = sizeof(cars);
                }
            }
            catch (bad_alloc ba) {
                throw ba;
            }
        }
    }

    Parking() = default;

    Parking(const Parking& parking) {
        setCars(parking.getCars());
        this->size = parking.length();
    }

    ~Parking() {
        delete[] cars;
    }

    Parking operator+(const Car& car) {
        for (size_t i = 0; i < this->size; ++i) {
            if (this->cars[i] == car) {
                throw logic_error("Car already exists.");
            }
        }

        try {
            Car* newCars = new Car[size + 1];
            for (size_t i = 0; i < size; ++i) {
                newCars[i] = this->cars[i];
            }
            newCars[size] = car;
            delete[] this->cars;
            this->cars = newCars;
            this->size++;

            return *this;
        }
        catch (bad_alloc ba) {
            throw ba;
        }
    }

    Parking operator+=(const Car& car) {
        return *this + car;
    }


};

int main()
{
    std::cout << "Hello World!\n";
}
