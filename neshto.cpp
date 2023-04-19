#include <iostream>
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

    ~Item () {
        delete[] name;
    }
};

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

    void resize(const bool increase) {
        try {
            if (increase) {
                size_t itemAmount = sizeof(*getItems()) / sizeof(Item);
                Item* newItems = new Item[itemAmount + 1];

                for (size_t i = 0; i < itemAmount; ++i) {
                    newItems[i] = this->items[i];
                }
                free();

                this->items = newItems;
            }
        }
        catch (bad_alloc ba) {
            throw ba;
        }
    }

    void addItem(const Item item) {
        if (find(item.getName()) > -1) {
            size_t itemAmount = sizeof(*getItems()) / sizeof(Item);
            resize();

            this->items[itemAmount] = item;
        }
    }

    bool removeItem(const char* name) {
        if (find(name) > -1) {

        }
    }
};

int main()
{
    Item b;
    Item a = b;

    return 0;
}
