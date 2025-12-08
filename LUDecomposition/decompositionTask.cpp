#include <iostream>
#include <format>
#include "matrixModule.hpp"

using namespace std;

int main(){
    // массивы
    size_t N = 0; // размерность
    vector<vector<double>> A;
    vector<vector<double>> L;
    vector<vector<double>> U;
    vector<vector<double>> Y;
    vector<vector<double>> X;
    vector<vector<double>> AInv;

    matrixFile(A, "matrix.txt"); // записываем матрицу из файла
    N = A[0].size(); // задаём размер для переменной 

    // выделяем память под строки
    L.resize(N); U.resize(N);
    Y.resize(N); X.resize(N);
    AInv.resize(N);

    // выделяем память под столбцы
    for(size_t i = 0; i < N; i++){
    L[i].resize(N); U[i].resize(N);
    Y[i].resize(N); X[i].resize(N);
    AInv[i].resize(N);  
    } 

    // вывод матрицы A:
    cout << format("Ваша матрица А: \n");
    matrixPrint(A);

    // первичное заполнение матриц A, L, U 
    for(size_t i = 0; i <= N - 1; i++){
        for(size_t j = 0; j <= N - 1; j++){
            L[i][j] = 0;

            if(i == j){
                U[i][j] = 1;
            } else {
            U[i][j] = 0;
        } } }

    // вычисление матриц L и U
    for(size_t i = 0; i <= N - 1; i++){
        L[i][0] = A[i][0];
    }

    for(size_t j = 1; j <= N - 1; j++){
        U[0][j] = A[0][j] / L[0][0];
    }

    for(size_t k = 1; k <= N - 1; k++){
        for(size_t i = k; i <= N - 1; i++){
            L[i][k] = A[i][k];
            for(size_t m = 0; m <= k-1; m++){
                L[i][k] = L[i][k] - L[i][m] * U[m][k];
            } }

    if(k <= N - 2){
        for(size_t j = k + 1; j <= N - 1; j++){
            U[k][j] = A[k][j];
    for(size_t m = 0; m <= k - 1; m++){
        U[k][j] = U[k][j] - L[k][m] * U[m][j];
    } 
    U[k][j] = U[k][j] / L[k][k];
    } } }

    // вывод матриц на экран
    cout << format("Ваша матрица L: \n");
    matrixPrint(L);
    cout << format("Ваша матрица U: \n");
    matrixPrint(U);

    // вычисление матрицы Y
    cout << "Вычисление и вывод матрицы Y\n";
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
        if (j > i) {
            Y[i][j] = 0;
        } else if (j == i) {
            Y[i][j] = 1 / L[i][i];
        } else {
            Y[i][j] = 0;
            for (size_t m = j; m <= i - 1; m++) {
                Y[i][j] = Y[i][j] - L[i][m] * Y[m][j]; }
            Y[i][j] = Y[i][j] / L[i][i];
    } } }

    // вывод матрицы Y на экран    
    cout << format("Ваша матрица Y: \n");
    matrixPrint(Y);

 // вычисление матрицы X
    for(int i = N - 1; i >= 0; i--){ 
        for(int j = N - 1; j >= 0; j--) {
        if (j < i) {
            X[i][j] = 0;
        } else if (j == i) {
            X[i][j] = 1;
        } else {
            X[i][j] = 0;
            for (size_t m = i + 1; m <= j; m++) {
                X[i][j] = X[i][j] - U[i][m] * X[m][j];
     } } } }

    // вывод матрицы X
    cout << format("Ваша матрица X: \n");
    matrixPrint(X);

    // вычисление матрицы AInv
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
          AInv[i][j] = 0;
          for (size_t m = 0; m < N; m++) {
            AInv[i][j] = AInv[i][j] + X[i][m] * Y[m][j];
        } } }

    cout << format("Ваша матрица AInv: \n");
    matrixPrint(AInv);   

}
