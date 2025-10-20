#include <iostream> // библиотека для хранения потока
#include <vector> // библиотека для хранения вектора

#pragma once

using namespace std;

/** @brief процедура считывания матрицы из файла
 * @param matrix считываемая матрицаъ
 * @param fileName имя открываемого файла
 */
void matrixFile(vector<vector<double>> &matrix, char fileName[]);

/** @brief процедура вывода матрицы на экран
 * @param matrix выводимая матрица на экран
 */
void matrixPrint(const vector<vector<double>> matrix);

/** @brief процедура вывода вектора на экран
 *  @param array выводимый вектор на экран
 */
void arrayPrint(const vector<double> array);

/** @brief процедура выделения памяти под матрицу
 * @param matrix матрица, для выделения памяти
 * @param cols количество столбцов
 * @param rows количество строк
 */
void resizeMatrix(vector<vector<double>> &matrix, size_t cols, size_t rows);