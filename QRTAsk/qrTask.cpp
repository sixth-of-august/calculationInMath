#include <iostream>
#include <format>
#include <cmath>
#include <vector>
#include "matrixModule.hpp"

using namespace std;

int main() {
    size_t n; 

    // задаём матрицы для работы
    vector<vector<double>> A(n, vector<double>(n));
    vector<vector<double>> Q(n, vector<double>(n));
    vector<vector<double>> R(n, vector<double>(n));

    matrixFile(A, "matrix.txt");
    n = A.size(); // записываем размерность из файла

    for (size_t t = 0; t <= 300; t++) {
        // копирование A в Q, инициализация R нулями
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                Q[i][j] = A[i][j];
                R[i][j] = 0;
            } }

        // QR-разложение
        double SQsum;
        for (size_t j = 0; j < n; j++) {
            SQsum = 0;
            for (size_t m = 0; m < n; m++) {
                SQsum = SQsum + pow(Q[m][j], 2);
            }
            R[j][j] = pow(SQsum, 0.5);

            for (size_t i = 0; i < n; i++) {
                Q[i][j] = Q[i][j] / R[j][j];
            }

            for (size_t k = j + 1; k < n; k++) {
                for (size_t m = 0; m < n; m++) {
                    R[j][k] = R[j][k] + Q[m][j] * Q[m][k];
                }
                for (size_t i = 0; i < n; i++) {
                    Q[i][k] = Q[i][k] - Q[i][j] * R[j][k];
                } } }

        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                A[i][j] = 0;
                for (size_t k = 0; k < n; k++) {
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