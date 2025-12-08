#include <vector>
#pragma once

/**
 * @brief процедура дифференцирования
 * @param variable вектор коэффициентов
 */
void dx(std::vector<double> &variable);


/**
 * @brief вычисление значения в точке X
 * @param variable вектор коэффициентов
 * @param x точка, в которой вычисляется значение
 * @return результат вычисления по формуле
 */
void printEqualation(std::vector<double> const &variable);


/**
 * @brief вычисление значения в точке X
 * @param variable вектор коэффициентов
 * @param x точка, в которой вычисляется значение
 * @return результат вычисления по формуле
 */
double fx(std::vector<double> const &variable, double x);


/**
 * @brief метод хорд для нахождения корня на интервале
 * @param variable вектор коэффициентов
 * @param a нижняя граница интервала
 * @param b верхняя граница интервала
 * @param eps точность
 * @return значение корня
 */
double chords(std::vector<double> const &variable, double a, double b, double eps);


/**
 * @brief метод касательных 
 * @param variable вектор коэффициентов
 * @param a нижняя граница интервала
 * @param b верхняя граница интервала
 * @param eps точность
 * @return значение корня
 */
double tangents(std::vector<double> const &variable, double a, double b, double eps);


/**
 * @brief комбинированный метод для вычислений  
 * @param variable вектор коэффициентов
 * @param a нижняя граница интервала
 * @param b верхняя граница интервала
 * @param eps точность
 * @return значение корня
 */
double combined(std::vector<double> const &variable, double a, double b, double eps);