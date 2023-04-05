#include <iostream>
#include <fstream>

using namespace std;

char fpath[] = "C:\\Users\\grade\\Desktop\\squares.dat";
const unsigned MAX_SQUARES = 100;

struct Point
{
    double X;
    double Y;
};

struct Square
{
    double sideLength;
    Point lowerLeftPoint;

    double getArea(void) const {
        return sideLength * sideLength;
    }
};

Square squares[MAX_SQUARES];

void readFromFile(void)
{
    ifstream streamReader(fpath, ios::binary);

    if (streamReader.is_open()) {
        streamReader.read((char*)&squares, sizeof(squares));
    }
    else {
        cout << "Unexpected error occured.";
        return;
    }

    streamReader.close();
}

template <typename T>
void mySwap(T& el1, T& el2)
{
    T temp = el1;
    el1 = el2;
    el2 = temp;
}

void sortSquares(void)
{
    for (int i = 0; i < MAX_SQUARES - 1; ++i) {
        for (int a = i; a < MAX_SQUARES; ++a) {
            if (squares[i].getArea() > squares[a].getArea()) {
                mySwap(squares[i], squares[a]);
            }
            else if (squares[i].getArea() == squares[a].getArea()) {
                if  (squares[i].lowerLeftPoint.X > squares[a].lowerLeftPoint.X) {
                    mySwap(squares[i], squares[a]);
                }
                else if (squares[i].lowerLeftPoint.X == squares[a].lowerLeftPoint.X) {
                    if  (squares[i].lowerLeftPoint.Y >  squares[a].lowerLeftPoint.Y) {
                        mySwap(squares[i], squares[a]);
                    }
                }
            }
        }
    }
}

void writeToFile(const double area)
{
    char ofpath[] = "C:\\Users\\grade\\Desktop\\squares-output.txt";
    ofstream streamWriter(ofpath, ios::app);

    if (streamWriter.is_open()) {
        for (size_t i = 0; i < MAX_SQUARES; ++i) {
            if (area <= squares[i].getArea()) {
                streamWriter << '(' << squares[i].lowerLeftPoint.X << ", " << squares[i].lowerLeftPoint.Y << "), ("
                             << squares[i].lowerLeftPoint.X + squares[i].sideLength << ", "
                             << squares[i].lowerLeftPoint.Y + squares[i].sideLength << ")\n";
            }
        }
    }
    else {
        cout << "Unexpected error occured.";
        return;
    }

    streamWriter.close();
}

int main()
{
    //readFromFile();

    Square square1{ 12, {5, 2} };
    squares[0] = square1;

    Square square2{ 12, {5, -3} };
    squares[1] = square2;

    Square square3{ 4, {23, 65} };
    squares[2] = square3;

    Square square4{ 16, {-432, -342} };
    squares[3] = square4;

    sortSquares();

    double input;
    do {
        cout << "Enter a positive real number: ";
        cin >> input;
    } while (input < 0);
    
    writeToFile(input);

    return 0;
}
