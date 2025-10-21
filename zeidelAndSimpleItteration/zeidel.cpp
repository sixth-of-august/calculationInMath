#include <iostream>
#include <vector>
#include <math.h>
#include <format>
#include "matrixModule.hpp"

using namespace std;

int main(){

    const double e = 0.0000001; // объявление константы для точности вычислений

    vector<vector<double>> aMatrix; // главная матрица
    vector<double> xArray;
    vector<double> cArray; 
    vector<double> xxArray;
    char fileName[] = "matrix.txt"; // имя файла с которого будет загружатся матрица
    size_t count = 0;
    size_t N = 0; // размер матриц и векторов

    matrixFile(aMatrix, fileName); // считываем матрицу из файла
    cArray.resize(N);

    N = aMatrix.size(); // запоминаем размер матрицы

    for(size_t i = 0; i < N; i++){ // записываем сврбродные коэфиценты
        cArray.push_back(aMatrix[i][N]);
    }

    resizeMatrix(aMatrix, N, N); // создаём квадратную матрицу
    xArray.resize(N); xxArray.resize(N); // выделяем размер под массивы

    cout << "Ваша исходная матрица: " << endl;
    matrixPrint(aMatrix); // выводим систему уравнений на экран

    cout << "Свободные коэфиценты: " << endl;
    arrayPrint(cArray);

    size_t k = 0; // заводим переменную k
    for(size_t i = 0; i < N; i++){
        xArray[i] = 0; // заполняем массив 0-ями
    }

while(count <= N){

    cout << format("Иттерация {}: ", k) << endl;
    arrayPrint(xArray); // выводим результаты иттерации

    k = k + 1; for(size_t i = 0; i < N; i++){ // заполняем массив xx
        xxArray[i] = cArray[i];
        for(size_t j = 0; j < N; j++){
            if(j < i){
                xxArray[i] = xxArray[i] - aMatrix[i][j] * xxArray[j];
            } else if(j > i){
                xxArray[i] = xxArray[i] - aMatrix[i][j] * xArray[j];
            }}
     xxArray[i] = xxArray[i] / aMatrix[i][i]; }

    for(size_t i = 0; i < N; i++){
        if(fabs(xArray[i] - xxArray[i]) < e){
            count = count + 1;
        } xArray[i] = xxArray[i];
    } }

    return 0;
}