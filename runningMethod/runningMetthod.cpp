#include <iostream>
#include <vector>
#include <format>
#include "matrixModule.hpp"

using namespace std;

int main(){

size_t N = 5; //размерность векторов
vector<double> f(N), c(N), l(N), r(N), p(N), q(N), x(N); //вектора 
vector<vector<double>> matrix; // переменная матрицы

matrixFile(matrix,"matrix.txt"); // считываем матрицу из файла

// заполнение векторов+
for(size_t k = 0; k < N; k++)
{   f[k] = matrix[k][N];
    
    if(k > 0){
    l[k] = matrix[k][k - 1]; 
    }

    c[k] = matrix[k][k];

    if(k < N - 1){
    r[k] = matrix[k][k + 1];    
    }

    p[k] = 0;  q[k] = 0; x[k] = 0;
}

// вывод векторов
cout << "Вектор f: " << endl;
arrayPrint(f); 

cout << "Вектор c: " << endl;
arrayPrint(c); 

cout << "Вектор l: " << endl;
arrayPrint(l);

cout << "Вектор r: " << endl;
arrayPrint(r); 

// вычисление и вывод векторов p и q
p[0] = f[0] / c[0];
q[0] = r[0] / c[0];

for(size_t k = 1; k < N; k++)
{
    p[k] = (f[k] - l[k] * p[k - 1]) / (c[k] - l[k] * q[k - 1]);
    q[k] = r[k] / (c[k] - l[k]  * q[k - 1]);
}

cout << "Вектор p: " << endl;
arrayPrint(p);

cout << "Вектор q: " << endl;
arrayPrint(q); 

// вычисление и вывод x
x[N - 1] = p[N - 1];
for(size_t k = N - 2; k > 0; k--)
{
    x[k] = p[k] - q[k] * x[k + 1];
}

cout << "Вектор x: " << endl;
arrayPrint(x); 

}