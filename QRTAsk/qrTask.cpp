#include <iostream>
#include <format>
#include <cmath>
#include <vector>
#include "matrixModule.hpp"

using namespace std;

int main() {
    int N = 0; 

    // задаём матрицы для работы
    vector<vector<double>> A;
    vector<vector<double>> Q;
    vector<vector<double>> R;

    matrixFile(A, "matrix.txt");
    N = A.size(); // записываем размерность из файла

     // выделяем память под строки
    A.resize(N); Q.resize(N);
    R.resize(N);

    // выделяем память под столбцы
    for(size_t i = 0; i <= N - 1; i++){
    A[i].resize(N); Q[i].resize(N);
    R[i].resize(N);  
    } 

    for (size_t t = 0; t <= 300; t++) {
        // копирование A в Q, инициализация R нулями
        for (size_t i = 0; i <= N - 1; i++) {
            for (size_t j = 0; j <= N - 1; j++) {
                Q[i][j] = A[i][j];
                R[i][j] = 0;
            } }

        // QR-разложение
        double SQsum;
        for (size_t j = 0; j <= N - 1; j++) {
            SQsum = 0;
            for (size_t m = 0; m <= N - 1; m++) {
                SQsum = SQsum + pow(Q[m][j], 2);
            }
            R[j][j] = pow(SQsum, 0.5);

            for (size_t i = 0; i <= N - 1; i++) {
                Q[i][j] = Q[i][j] / R[j][j];
            }

            for (size_t k = j + 1; k <= N - 1; k++) {
                for (size_t m = 0; m <= N - 1; m++) {
                    R[j][k] = R[j][k] + Q[m][j] * Q[m][k];
                }
                for (size_t i = 0; i <= N - 1; i++) {
                    Q[i][k] = Q[i][k] - Q[i][j] * R[j][k];
                } } }

        for (size_t i = 0; i <= N - 1; i++) {
            for (size_t j = 0; j <= N - 1; j++) {
                A[i][j] = 0;
                for (size_t k = 0; k <= N - 1; k++) {
                    A[i][j] = A[i][j] + R[i][k] * Q[k][j];
                } } }

        // выводим результаты каждой иттерации
        cout << format("Итерация {}:\n", t);
        cout << "Q =\n"; matrixPrint(Q);
        cout << "R =\n"; matrixPrint(R);
        cout << "A =\n"; matrixPrint(A);
    }

    return 0;
}

//g++ qrTask.cpp matrixModule.cpp -o task.exe --std=c++20
// ./task