#include <iostream>
#include <fstream>
#pragma warning(disable:4996)

using namespace std;

class Item
{
private:
    char* name;
    unsigned availability;
    float price;

public:
    const char* getName(void) const {
        return this->name;
    }

    unsigned getAvailability(void) const {
        return this->availability;
    }

    float getPrice(void) const {
        return this->price;
    }

    void setName(const char* name) {
        try {
            if (this->name != name) {
                char* newName = new char[strlen(name) + 1];
                strcpy(newName, name);
                delete[] this->name;
                this->name = newName;
            }
        }
        catch (bad_alloc ba) {
            throw ba;
        }
    }

    void setAvailability(const unsigned availability) {
        this->availability = availability;
    }

    void setPrice(const float price) {
        this->price = price;
    }

    Item() = default;

    Item(const char* name, const unsigned availability, const float price) {
        setName(name);
        this->availability = availability;
        this->price = price;
    }

    Item(const Item& item) {
        setName(item.getName());
        this->availability = item.getAvailability();
        this->price = item.getPrice();
    }

    Item& operator=(const Item& item) {
        setName(item.getName());
        this->availability = item.getAvailability();
        this->price = item.getPrice();

        return *this;
    }

    ~Item() {
        delete[] name;
    }
};

template <class T>
void mySwap(T& el1, T& el2) {
    T temp = el1;
    el1 = el2;
    el2 = temp;
}

class ShoppingCart
{
private:
    Item* items;

    void free(void) {
        delete[] items;
    }

    void copyFrom(const Item* scart) {
        try {
            size_t itemAmount = sizeof(*scart) / sizeof(Item);
            Item* newItems = new Item[itemAmount];

            for (size_t i = 0; i < itemAmount; ++i) {
                newItems[i] = scart[i];
            }
            free();

            this->items = newItems;
        }
        catch (bad_alloc ba) {
            throw ba;
        }
    }

public:
    const Item* getItems(void) const {
        return this->items;
    }

    ShoppingCart() = default;

    ~ShoppingCart() {
        free();
    }

    ShoppingCart(const Item* items) {
        copyFrom(items);
    }

    ShoppingCart(const ShoppingCart& scart) {
        copyFrom(scart.getItems());
    }

    ShoppingCart& operator=(const ShoppingCart& scart) {
        copyFrom(scart.getItems());
        return *this;
    }

    int find(const char* name) {
        int amount = sizeof(*getItems()) / sizeof(Item);

        for (int i = 0; i < amount; ++i) {
            if (!strcmp(name, this->items[i].getName())) {
                return i;
            }
        }
        return -1;
    }

    void resizeUp(void) {
        try {
            size_t itemAmount = sizeof(*getItems()) / sizeof(Item);
            Item* newItems = new Item[itemAmount + 1];

            for (size_t i = 0; i < itemAmount; ++i) {
                newItems[i] = this->items[i];
            }
            free();

            this->items = newItems;
        }
        catch (bad_alloc ba) {
            throw ba;
        }
    }

    void resizeDown(const char* name) {
        try {
            size_t itemAmount = sizeof(*getItems()) / sizeof(Item);
            Item* newItems = new Item[itemAmount - 1];

            for (size_t i = 0, counter = 0; i < itemAmount; ++i) {
                newItems[counter] = this->items[i];
                if (strcmp(newItems[counter].getName(), name)) {
                    ++counter;
                }
            }
            free();

            this->items = newItems;
        }
        catch (bad_alloc ba) {
            throw ba;
        }
    }

    void addItem(const Item item) {
        if (find(item.getName()) > -1) {
            size_t itemAmount = sizeof(*getItems()) / sizeof(Item);
            resizeUp();

            this->items[itemAmount] = item;
        }
    }

    bool removeItem(const char* name) {
        if (find(name) > -1) {
            resizeDown(name);
            return true;
        }
        return false;
    }

    size_t itemsCount(void) {
        return (sizeof(*getItems()) / sizeof(Item));
    }

    bool exists(const char* name) {
        return find(name) > 0;
    }

    bool isEmpty(bool) {
        return !itemsCount();
    }

    float getPriceOf(const char* name) {
        size_t itemsAmount = itemsCount();

        for (size_t i = 0; i < itemsAmount; ++i) {
            if (!strcmp(this->items[i].getName(), name)) {
                return this->items[i].getPrice();
            }
        }

        return 0;
    }

    float totalPrice(void) {
        float total = 0;
        size_t itemsAmount = itemsCount();

        for (size_t i = 0; i < itemsAmount; ++i) {
            total += this->items[i].getPrice();
        }

        return total;
    }

    void sortByName(void) {
        size_t itemsAmount = itemsCount();

        for (size_t i = 0; i < itemsAmount - 1; ++i) {
            for (size_t a = i + 1; i < itemsAmount; ++a) {
                if (strcmp(this->items[i].getName(), this->items[a].getName()) > 1) {
                    mySwap(this->items[i], this->items[a]);
                }
            }
        }
    }

    bool save(const char* fpath) {
        ofstream streamWriter(fpath, ios::trunc);
        size_t itemsAmount = itemsCount();

        if (streamWriter.is_open()) {
            for (size_t i = 0; i < itemsAmount; ++i) {
                streamWriter << (this->items[i].getName()) << ' ' << (this->items[i].getAvailability()) << ' ' << (this->items[i].getPrice()) << '\n';
            }
        }

        streamWriter.close();
    }
};

int main()
{
    Item b;
    Item a = b;

    return 0;
}
