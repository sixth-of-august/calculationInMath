#include <iostream> // библиотека для хранения потока
#include <vector> // библиотека для хранения вектора

#pragma once

/** @brief процедура считывания матрицы из файла
 * @param matrix считываемая матрицаъ
 * @param fileName имя открываемого файла
 */
void matrixFile(std::vector<std::vector<double>> &matrix, char fileName[]);

void arrayFile(std::vector<double> &array, char fileName[]);

/** @brief процедура вывода матрицы на экран
 * @param matrix выводимая матрица на экран
 */
void matrixPrint(const std::vector<std::vector<double>> matrix);

/** @brief процедура вывода вектора на экран
 *  @param array выводимый вектор на экран
 */
void arrayPrint(const std::vector<double> array);

/** @brief процедура выделения памяти под матрицу
 * @param matrix матрица, для выделения памяти
 * @param cols количество столбцов
 * @param rows количество строк
 */
void resizeMatrix(std::vector<std::vector<double>> &matrix, size_t cols, size_t rows);