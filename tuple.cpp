#include <iostream>

using namespace std;

template <class T>
class Tuple
{
    T* items;
    size_t size;

    void setItems(const T* items, const size_t size) {
        if (items) {
            try {
                T* newItems = new T[size];
                for (size_t i = 0; i < size; ++i) {
                    newItems[i] = items[i];
                }
                if (this->items) {
                    delete[] this->items;
                }
                this->items = newItems;
                this->size = size;
                return;
            }
            catch (const bad_alloc& ba) {
                throw ba;
            }
        }
        throw "Invalid items.";
    }

public:
    const T* getItems(void) const {
        return items;
    }

    size_t getSize(void) const {
        return size;
    }

    Tuple() : items(nullptr), size(0) {}

    Tuple(const T* items, const size_t size) {
        setItems(items, size);
    }

    Tuple(const Tuple& t) {
        setItems(t.getItems(), t.getSize());
    }

    Tuple& operator=(const Tuple& t) {
        setItems(t.getItems(), t.getSize());
    }

    T operator[](const size_t index) {
        if (index < size) {
            return this->getItems()[i];
        }
    }

    ~Tuple() {
        delete[] items;
    }
};

int main()
{
    std::cout << "Hello World!\n";
}
