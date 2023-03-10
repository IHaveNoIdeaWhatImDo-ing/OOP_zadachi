#include <iostream>

using namespace std;

int smaller (int a, int b)
{
    return (a > b ? b : a);
}

int smallerConst (const int a, const int b)
{
    return (a > b ? b : a);
}

int smallerByPointer (int* a, int* b)
{
    return (*a > *b ? *b : *a);
}

int smallerByRef (int& a, int& b)
{
    return (a > b ? b : a);
}

int main()
{
    int a = 5, b = 6;
    
    cout << "Smaller by pointer: " << smallerByPointer(&a, &b) << '\n'
         << "Smaller by reference: " << smallerByRef(a, b);

    return 0;
}
