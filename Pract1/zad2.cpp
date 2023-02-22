#include <iostream>

using namespace std;

int main()
{
    int N, amount = 0;
    do {
        cout << "Enter the amount of whole numbers: ";
        cin >> N;
    } while (N <= 0);
    
    char letter;
    cout << "Enter anascii character: ";
    cin >> letter;
    
    cout << "Enter the whole numbers: ";
    int* arr = new int[N];
    for (int i = 0; i < N; ++i)
    {
        cin >> arr[i];
        if (arr[i] > letter) amount++;
    }
    
    cout << '\n' << "The amount of numbers larger than the letter's ascii code is " << amount;
    
    delete[] arr;

    return 0;
}
