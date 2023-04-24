#include <iostream>
#pragma warning(disable:4996)

using namespace std;

class String
{
private:
    char* str = nullptr;

public:
    void setStr(const char* str) {
        try {
            char* newStr = new char[strlen(str) + 1];
            strcpy(newStr, str);

            if (this->str != str && this->str) {
                delete[] this->str;
            }
            this->str = newStr;
        }
        catch (bad_alloc ba) {
            throw ba;
        }
    }

    const char* getStr(void) const {
        return str;
    }

    String() = default;

    ~String() {
        delete[] this->str;
    }

    String(const char* str) {
        setStr(str);
    }

    String(const String& str) {
        setStr(str.getStr());
    }

    String& operator=(const String& str) {
        setStr(str.getStr());
        return *this;
    }

    String& operator=(const char* str) {
        setStr(str);
        return *this;
    }

    String operator+(const String& str) {
        String newObj;

        try {
            char* newStr = new char[strlen(str.getStr()) + strlen(this->str) + 1];
            strcpy(newStr, this->str);
            strcpy(newStr + strlen(this->str), str.getStr());

            newObj.setStr(newStr);
        }
        catch (bad_alloc ba) {
            throw ba;
        }

        return newObj;
    }

    String operator+(const char* str) {
        String newObj;

        try {
            char* newStr = new char[strlen(str) + strlen(this->str) + 1];
            strcpy(newStr, this->str);
            strcpy(newStr + strlen(this->str), str);

            newObj.setStr(newStr);
        }
        catch (bad_alloc ba) {
            throw ba;
        }

        return newObj;
    }

    String& operator+=(const String& str) {
        *this = *this + str;
        return *this;
    }

    String& operator+=(const char* str) {
        *this = *this + str;
        return *this;
    }

    bool comp(size_t pos, const char* str) {
        size_t len = strlen(str);

        for (size_t i = 0; i < len; ++i) {
            if (!this->str[pos + i] || this->str[pos + i] != str[i]) {
                return false;
            }
        }
        return true;
    }

    // не работят
    // https://cplusplus.com/reference/string/string/
    size_t find(const char* str) {
        size_t count = strlen(this->str) - strlen(str);

        for (size_t i = 0; i < count; ++i) {
            if (comp(i, str)) {
                return true;
            }
        }
        return false;
    }

    size_t rfind(const char* str) {
        size_t count = strlen(this->str) - strlen(str);

        for (size_t i = count; i >= 0; --i) {
            if (comp(i, str)) {
                return true;
            }
        }
        return false;
    }
};

int main()
{
    String a("abca");
    String b = a + " " + a;
    String c = b;
    c += " abca";

    cout << a.find("ca");
    //cout << a.getStr() << '\n' << b.getStr() << '\n' << c.getStr() << '\n';
}
