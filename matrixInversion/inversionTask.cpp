#include <iostream>
#include <format>
#include <cmath>
#include "matrixModule.hpp"

using namespace std;

int main(){
    // массивы
    size_t N = 0; // размерность
    vector<vector<double>> A;
    vector<vector<double>> L;
    vector<vector<double>> Y;
    vector<vector<double>> AInv;

    matrixFile(A, "matrix.txt"); // записываем матрицу из файла
    N = A[0].size(); // задаём размер для переменной 

    // выделяем память под строки
    L.resize(N); Y.resize(N);
    AInv.resize(N);

    // выделяем память под столбцы
    for(size_t i = 0; i < N; i++){
    L[i].resize(N); Y[i].resize(N);
    AInv[i].resize(N);  
    } 

    // вывод матрицы A:
    cout << format("Ваша матрица А: \n");
    matrixPrint(A);

    // заполнение матрицы L
    L[0][0] = pow(A[0][0], 0.5);

    for(size_t i = 1; i <= N - 1; i++){
        L[i][0] = A[i][0] / L[0][0];
    }

    double sqSum;
    double pairSum;
    for(size_t k = 1; k <= N - 1; k++){
        sqSum = 0.0;
      for(size_t m = 0; m <= k - 1; m++){
        sqSum = sqSum + L[k][m] * L[k][m];
      }  
      L[k][k] = pow(A[k][k] - sqSum, 0.5);

    if(k <= N-1){
       for(size_t i = k + 1; i <= N - 1; i++){
        pairSum = 0.0;
        for(size_t m = 0; m <= k - 1; m++){
           pairSum = pairSum + L[i][m] * L[k][m]; 
       } L[i][k] = (A[i][k] - pairSum) / L[k][k];}
    } } 

    // вывод матрицы L
    cout << format("Ваша матрица L: \n");
    matrixPrint(L);

    // этап 2
    // заполнение матрицы Y
    for (size_t i = 0; i <= N - 1; i++) {
        for (size_t j = 0; j <= N - 1; j++) {
            if (j > i) {
                Y[i][j] = 0;
            } else if (j == i) {
             Y[i][j] = 1 / L[i][i];
            } else {
                Y[i][j] = 0.0;
             for (size_t m = j; m <= i - 1; m++) {
                    Y[i][j] = Y[i][j]  + L[i][m] * Y[m][j];
                }
            Y[i][j] = Y[i][j] / (-L[i][i]);
        } } }

    // вывод матрицы Y
    cout << format("Ваша матрица Y: \n");
    matrixPrint(Y);

    // вычисление матрицы обратной к A
    for (size_t i = 0; i <= N - 1; i++) {
        for (size_t j = 0; j <= N - 1; j++){
            AInv[i][j] = 0;
           for(size_t m = 0; m <= N - 1; m++){
            AInv[i][j] = AInv[i][j] + Y[m][i] * Y[m][j]; 
           } } }
    
    // вывод матрицы обратной к А
    cout << format("Ваша обратная матрица A: \n");
    matrixPrint(AInv);

    return 0;
}

// g++ inversionTask.cpp matrixModule.cpp -o task.exe --std=c++20
// ./task