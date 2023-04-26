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

    char* getStr(void) const {
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

    String operator+(const String& str) {
        return *this + str.getStr();
    }

    String& operator+=(const char* str) {
        *this = *this + str;
        return *this;
    }

    String& operator+=(const String& str) {
        return *this += str.getStr();
    }

    friend ostream& operator<<(ostream& os, const String& str) {
        if (str.str) {
            os << str.getStr();
        }
        else {
            os << "NULL";
        }
        return os;
    }

    friend istream& operator>>(istream& is, String& str) {
        char* temp = new char[128];
        is.getline(temp, strlen(temp));
        str.setStr(temp);
        delete[] temp;

        return is;
    }

    String(String&& str) noexcept {
        this->str = str.getStr();
        str.str = nullptr;
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

    int find(const char* str) {
        int count = strlen(this->str) - strlen(str);

        for (int i = 0; i < count; ++i) {
            if (comp(i, str)) {
                return i;
            }
        }
        return -1;
    }

    int rfind(const char* str) {
        size_t count = strlen(this->str) - strlen(str);

        for (int i = count; i >= 0; --i) {
            if (comp(i, str)) {
                return i;
            }
        }
        return -1;
    }

    String substr(const size_t index, const size_t length) {
        try {
            char* newStr = new char[length + 1];

            for (size_t i = 0; i < length; ++i) {
                newStr[i] = this->str[index + i];
            }
            newStr[length] = '\0';

            return String(newStr);
        }
        catch (bad_alloc ba) {
            throw ba;
        }
        catch (out_of_range ofr) {
            throw ofr;
        }
    }

    short compare(const char* str) {
        size_t i = 0;

        while (this->str[i] != '\0' && str[i] != '\0') {
            if (this->str[i] < str[i]) {
                return -1;
            }
            else if (this->str[i] > str[i]) {
                return 1;
            }
            ++i;
        }

        if (strlen(this->str) == strlen(str)) {
            return 0;
        }
        else if (strlen(this->str) < strlen(str)) {
            return -1;
        }
        else {
            return 1;
        }
    }
};

int main()
{
    //String a("a");
    //String b = a + " " + a;
    //String c = b;
    //c += " a";

    //cout << a.find("ba") << ' ' << a.rfind("ba") << '\n';
    //cout << a.getStr() << '\n' << b.getStr() << '\n' << c.getStr() << '\n';
    //cout << a.substr(4, 7).getStr() << '\n';

    String a("neshto tam");
    String b(move(a));

    cout << "b = " << b << '\n'
         << "a = " << a;
}
