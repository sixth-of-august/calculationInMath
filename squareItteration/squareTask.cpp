#include <iostream>
#include <vector>
#include <math.h>
#include "matrixModule.hpp"

using namespace std;

int main(){
vector<vector<double>> matrixA; // обьявили матрицу из векторов
vector<vector<double>> matrixL; // обьявляем нижнюю труегольную матрицу
vector<vector<double>> matrixU; // транспонированная матрица L
vector<double> bArray; // вектор B
vector<double> xArray; // вектор X
vector<double> yArray; // вектор Y
size_t N = 0.0; // переменная для хранения размера матрицы

// cчитываем расширенную матрицу из файла
matrixFile(matrixA, "matrix.txt");
N = matrixA.size(); // запоминаем размерность

// считываем свободные коэфиценты из расширенной матрицы в вектор
for(size_t i = 0; i < N; i++){
    bArray.push_back(matrixA[i][N]);
}

// превращаем расширенную матрицу в квадратную и выделяем память под остальные матрицы
resizeMatrix(matrixA, N, N);
resizeMatrix(matrixL, N, N);
resizeMatrix(matrixU, N, N);
yArray.resize(N);
xArray.resize(N);

cout << "Ваша матрица: " << endl;
// выводим на экран квадратную матрицу
matrixPrint(matrixA); cout << endl;

cout << "Вектор свободных коэфицентов: " << endl;
// выводим на экран вектор bArray
arrayPrint(bArray); cout << endl;

// заполняем матрицу L
matrixL[0][0] = sqrt(matrixA[0][0]);

for(size_t i = 1; i < N; i++){
    matrixL[i][0] = matrixA[i][0] / matrixL[0][0];
}

for(size_t k = 1; k < N; k++){
    double sqSum = 0.0;
    for(size_t m = 0; m < k; m++){
        sqSum = sqSum + powf(matrixL[k][m], 2.0); 
    }

    matrixL[k][k] = sqrt(matrixA[k][k] - sqSum);
    
    if(k < N){
        for(size_t i = k + 1; i < N; i++){
            double pairSum = 0.0;
            for(size_t m = 0; m < k; m++){
                pairSum = pairSum + matrixL[i][m] * matrixL[k][m];
            }
            matrixL[i][k] = (matrixA[i][k] - pairSum) / matrixL[k][k];
        } } } 

    for(size_t i = 0; i < N; i++){
        for(size_t j = 0; j < N; j++){
        matrixU[i][j] = matrixL[j][i];
    } }
     
    cout << "Ваша матрица L: " << endl;
    // выводим на экран матрицу L
    matrixPrint(matrixL); cout << endl;
    
    cout << "Ваша матрица U: " << endl;
    // выводим на экран транспонированную матрицу L
    matrixPrint(matrixU); cout << endl;
    
    // вычисление вектора Y
    yArray[0] = bArray[0] / matrixL[0][0];
    for(int i = 1; i < N; i++){
        yArray[i] = bArray[i];
        
        for(int m = 0; m < i; m++){
            yArray[i] = yArray[i] - matrixL[i][m]  * yArray[m];
        }
        yArray[i] = yArray[i] / matrixL[i][i]; }
  
    cout << "Вектор Y: " << endl;
    // выводим на экран вектор yArray
    arrayPrint(yArray); cout << endl;

    // вычисляем вектор X
    xArray[N - 1] = yArray[N - 1] / matrixU[N - 1][N - 1];
    for(int i = N - 2; i >= 0; i--){
        xArray[i] = yArray[i];
        for(size_t m = i + 1; m < N; m++){
            xArray[i] = xArray[i] - matrixU[i][m] * xArray[m];
        }
    xArray[i] = xArray[i] / matrixU[i][i];}

    cout << "Вектор X: " << endl;
    // выводим на экран вектор yArray
    arrayPrint(xArray); cout << endl;   

    /* действия в консоле 
    сохдаём исполняемый  файл
    g++ squareTask.cpp matrixModule.cpp -o program -std=c++20
    
    запускаем файл для работы
    ./program
    */

}