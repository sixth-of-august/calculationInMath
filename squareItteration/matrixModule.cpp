#include <iostream> // библиотека для хранения потока
#include <vector> // библиотека для хранения вектора
#include <fstream> // библиотека для хранения потока файлов
#include <cmath> // библиотека математических формул 
#include <format> // библиотека для работы с форматом вывода  
#include "matrixModule.hpp" // заголовочный файл

using namespace std;

/** @brief процедура считывания матрицы из файла
 * @param matrix считываемая матрицаъ
 * @param fileName имя открываемого файла
 */
void matrixFile(vector<vector<double>> &matrix, char fileName[]){ 
    ifstream openFile(fileName); // открываем файл для чтения
    int rows = 0, cols = 0;
    string line;

    while(getline(openFile, line)){
     rows++;
    } // считаем количество строк
    cols = rows++; // приравниваем кол-во столбцов к кол-ву строк
    // и увеличиваем количество строк (для расширенной матрицы)

    openFile.clear(); // сбрасываем позицию в файле
    openFile.seekg(0); // переходим к началу файла

    resizeMatrix(matrix, cols, rows); // выделяем память под матрицу

    for(size_t i = 0; i < cols; i++){
        for(size_t j = 0; j < rows; j++){
        openFile >> matrix[i][j]; // записываем символы из файла
    } }

    openFile.close(); // закрываем файл
}

/** @brief процедура вывода матрицы на экран
 * @param matrix выводимая матрица на экран
 */
void matrixPrint(const vector<vector<double>> matrix){
      for(size_t i = 0; i < matrix.size(); i++){
        for(size_t j = 0; j < matrix[i].size(); j++){
        cout << format("{:.3}", matrix[i][j]) << "\t"; // выводим пробел между элементами матрицы
    } cout << endl; }
}

/** @brief процедура вывода вектора на экран
 *  @param array выводимый вектор на экран
 */
void arrayPrint(const vector<double> array){
    for(size_t i = 0; i < array.size(); i++){
    cout << format("{:.3}", array[i]) << "\t"; } 
    cout << endl;}

/** @brief процедура выделения памяти под матрицу
 * @param matrix матрица, для выделения памяти
 * @param cols количество столбцов
 * @param rows количество строк
 */
void resizeMatrix(vector<vector<double>> &matrix, size_t cols, size_t rows){
    // устанавливаем количество столбцов
    matrix.resize(cols);

    // устанавливаем размерность для строк
    for(size_t i = 0; i < cols; i++){
    matrix[i].resize(rows);
    } // выделаяем память под каждую строку
}
