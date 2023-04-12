#include <iostream>
#pragma warning(disable:4996)

using namespace std;

class String
{
private:
    char* str;

public:
    const char* getString(void) const {
        return str;
    }

    void setString(const char* str) {
        if (this->str != str) {
            try {
                char* temp = new char[strlen(str) + 1];
                delete[] (this->str);
                (this->str) = temp;
                strcpy(this->str, str);
            }
            catch (std::bad_alloc& ba) {
                cout << "Allocation error.\n";
                throw ba;
            }
        }
    }

    String() = default;

    ~String (){
        delete[] str;
    }

    String(const char* str) {
        setString(str);
    }

    String(const String& str) {
        setString(str.getString());
    }

    String& operator=(const String& str) {
        setString(str.getString());
        return *this;
    }

    char operator[](const size_t i) {
        return *(this->str + i);
    }

    String operator+(const String& str) {
        String newObj;

        try {
            char* newStr = new char[strlen(this->str) + strlen(str.getString()) + 1];

            strcpy(newStr, this->str);
            strcpy(newStr + strlen(this->str), str.getString());

            newObj.setString(newStr);
        }
        catch (std::bad_alloc ba) {
            throw ba;
        }

        return newObj;
    }

    String& operator+=(const String& str) {
        *this = *this + str;
        return *this;
    }

    bool operator==(const String& str) {
        return strcmp(getString(), str.getString());
    }

    bool operator!=(const String& str) {
        return !(*this == str);
    }

    bool operator<(const String& str) {
        return strcmp(getString(), str.getString());
    }

    bool operator>(const String& str) {
        return strcmp(getString(), str.getString());
    }

    bool operator<=(const String& str) {
        return strcmp(getString(), str.getString()) == -1 || !(*this == str);
    }

    bool operator>=(const String& str) {
        return (*this == str) == 1 || !(*this == str);
    }

    size_t length(void) {
        size_t i = 0;
        while ((*this)[i++] != '\0');
        return --i;
    }

    bool empty(void) {
        return !(*this).length();
    }

    void clear(void) {
        setString("");
    }

    const char* c_str(void) {
        return getString();
    }

    String& append(const char chr) {
        char* str = new char[(*this).length() + 2];
        str[(*this).length()] = chr;
        setString(str);
    }

    short compare(const String& str) {
        return strcmp(getString(), str.getString());
    }
};

int main()
{
    String a("abc");
    String b("def");
    String d = a + b;

    cout << d.getString();
}
