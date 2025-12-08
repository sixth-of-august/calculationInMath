#include <iostream>
#include <format>
#include "matrixModule.hpp"

using namespace std;

int main(){

    char fileName[] = "matrix.txt";
    vector<vector<double>> B; // матрица для хранения значений
    size_t N; // размер исходной матрицы

    //заполняем матрицу с файла 
    matrixFile(B, fileName);

    N = B[0].size(); //задаём переменной размер матрицы

    // создаём расширенную матрицу
    for(size_t i = 0; i < N; i++){
        B[i].resize(2 * N);
        // заполняем правую часть единичной матрицей
        for(size_t j = N; j < 2 * N; j++){
        if(j == N + i){
        B[i][j] = 1.0;  // 1.0 на диагонали, 0.0 иначе
    } } }
    
    // выводим расширенную матрицу на экран
    cout << format("Ваша расширенная матрица: \n");
    matrixPrint(B);
    
    // пересчёт по методу Жордана-Гаусса
    for(size_t k = 0; k <= N - 1; k++){
        /* методом прямоугольника пересчитываем все элементы
        правее ведущего столбца и не в ведущей строке*/
        for(size_t i = 0; i <= N - 1; i++){
            for(size_t j = k + 1; j <= 2 * N - 1; j++){
                if(i != k){
                    B[i][j] = (B[i][j] * B[k][k] - B[k][j] * B[i][k]) / B[k][k];
                } } }
            
        // обнуляем все элементы ведущего столбца (кроме ведущего элемента)
        for(size_t i = 0; i <= N - 1; i++){
            if(i != k){
                B[i][k] = 0;
            } } 

        // делим ведущую строку на ведущий элемент
        for(size_t j = 2 * N - 1; j > k; j--){
            B[k][j] = B[k][j] / B[k][k];
       }
       B[k][k] = 1; // делаем элементы на главной диагонале еденичными

        cout << format("Ваша матрица на {}-ой иттерации: \n", k + 1);
       matrixPrint(B);
    }

    return 0;
}

// g++ stageMethodTask.cpp matrixModule.cpp -o newTask.exe --std=c++20
// ./newTask