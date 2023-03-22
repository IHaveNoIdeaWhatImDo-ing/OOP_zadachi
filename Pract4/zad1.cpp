#include <iostream>
#include <fstream>

using namespace std;

void strCopy(char arr[30], const char* ptr)
{
    int i = 0;
    while (ptr[i] != '\0' && i < 30) arr[i] = ptr[i++];
}

class Teacher
{
private:
    char name[30];
    unsigned age;
    unsigned experience;

public:
    const char* getName() const
    {
        return name;
    }

    unsigned getAge() const
    {
        return age;
    }

    unsigned getexperience() const
    {
        return experience;
    }

    void setName(const char* newName)
    {
        strCopy(this->name, newName);
    }

    void setAge(const unsigned newAge)
    {
        this->age = newAge;
    }

    void setExperience(const unsigned newExperience)
    {
        this->experience = newExperience;
    }
};

int main()
{
    return 0;
}
