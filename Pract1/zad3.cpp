#include <iostream>

using namespace std;

void transpose (int**& matrix, int& N, int& M)
{
    int** new_mat = new int*[M];
    for (int x = 0; x < M; ++x)
    {
        new_mat[x] = new int[N];
        for (int y = 0; y < N; ++y)
        {
            new_mat[x][y] = matrix[y][x];
        }
    }
    
    for (int i = 0; i < N; ++i)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = new_mat;
    
    int temp = N;
    N = M;
    M = temp;
}

int main()
{
    int N, M;
    do {
        cout << "Enter the dimensions of the matrix: ";
        cin >> N >> M;
    } while (N <= 0 || M <= 0);
    
    int** matrix = new int*[N];
    for (int i = 0; i < N; ++i)
    {
        matrix[i] = new int[M];
        cout << "Enter the elements of row " << i + 1 << '\n';
        for (int a = 0; a < M; ++a)
        {
            cin >> matrix[i][a];
        }
    }
    
    cout << '\n';
    for (int i = 0; i < N; ++i)
    {
        for (int a = 0; a < M; ++a)
        {
            cout << matrix[i][a] << ' ';
        }
        cout << '\n';
    }
    
    transpose(matrix, N, M);
    
    cout << '\n';
    for (int i = 0; i < N; ++i)
    {
        for (int a = 0; a < M; ++a)
        {
            cout << matrix[i][a] << ' ';
        }
        delete[] matrix[i];
        cout << '\n';
    }
    delete[] matrix;

    return 0;
}
