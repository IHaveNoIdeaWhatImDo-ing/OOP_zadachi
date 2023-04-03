#include <iostream>

using namespace std;

const int MAX_SIZE = 128;

void strCopy(char* str1, const char* str2)
{
	size_t i = 0;

	while (str1[i] != '\0' && str2[i] != '\0') {
		str1[i] = str2[i++];
	}
}

class Teacher
{
private:
	char* name = new char[MAX_SIZE];
	unsigned short age;
	unsigned short experience;

public:
	char* getName(void) const {
		return this->name;
	}

	unsigned short getAge(void) const {
		return this->age;
	}

	unsigned short getExperience(void) const {
		return this->experience;
	}

	void setName(const char* name) {
		strCopy(this->name, name);
	}

	void setAge(const unsigned short age) {
		this->age = age;
	}

	void setExperience(const unsigned short experience) {
		this->experience = experience;
	}

	Teacher(const char* name, const unsigned short age, const unsigned short experience)
	{
		strCopy(this->name, name);
		this->age = age;
		this->experience = experience;
	}

	Teacher(const Teacher& tchr) {
		strCopy(this->name, tchr.getName());
		this->age = tchr.getAge();
		this->experience = tchr.getExperience();
	}
	
	~Teacher () {
		delete[] this->name;
	}
};

int main()
{
	Teacher teacher("Bai Ganyo", 35, 10);
	Teacher teacherCopy = teacher;

	return 0;
}
