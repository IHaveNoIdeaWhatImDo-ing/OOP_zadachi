#include <iostream>

using namespace std;

struct Student
{
    char name[31];
    unsigned short facNum;
};

void initStudent (Student& st)
{
    cout << "Enter the the student's name: ";
    cin.getline(st.name, 30);
    
    cout << "Enter the the student's faculty number: ";
    cin >> st.facNum;
}

void printStudent (Student& st)
{
    cout << "The student's name is: " << st.name << " and his faculty number is: " << st.facNum<< '.';
}

int main()
{
    Student st  = { "Gosho", 10 };
    
    Student *pSt = &st;
    
    const Student* pCSt = &st;
    pCSt++;
    
    Student* const cPSt = &st;
    (*cPSt).facNum = 69;
    
    const Student* const cpCSt = &st;
    
    Student& refSt = st;
    refSt.facNum = 420;
    
    const Student& refCSt = st;
    
    return 0;
}
