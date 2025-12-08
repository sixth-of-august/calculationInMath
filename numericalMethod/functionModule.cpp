#include <cmath>
#include <vector>
#include <format>
#include <iostream>
#include "functionModule.hpp"

using namespace std;

/**
 * @brief процедура дифференцирования
 * @param variable вектор коэффициентов
 */
void dx(vector<double> &variable){
    variable[0] = variable[1]; // меняем свободный коэффициент
    for(size_t i = 2; i < variable.size(); i++){
    // дифференцирцем переменные и перезаписываем их
        variable[i - 1] = variable[i] * (i); 
    }

    // уменьшаем количество элементов
    variable.resize(variable.size() - 1);
}


/**
 * @brief вычисление значения в точке X
 * @param variable вектор коэффициентов
 * @param x точка, в которой вычисляется значение
 * @return результат вычисления по формуле
 */
double fx(vector<double> const &variable, double x){
    double result = variable[0];
    for(size_t i = 1; i < variable.size(); i++){
        result += variable[i] * pow(x, i);
    } return result;}


/**
 * @brief выводит полином в читабельном виде
 * @param variable вектор коэффициентов
 */
void printEqualation(vector<double> const &variable){
    for(size_t i = variable.size() - 1; i > 0; i--){
    cout << format("({})x^{} + ", variable[i], i);
} cout << format("({})", variable[0]);
}


/**
 * @brief метод хорд для нахождения корня на интервале
 * @param variable вектор коэффициентов
 * @param a нижняя граница интервала
 * @param b верхняя граница интервала
 * @param eps точность
 * @return значение корня
 */
double chords(vector<double> const &variable, double a, double b, double eps){
    double cNew = (a * fx(variable, b) - b * fx(variable, a)) / (fx(variable, b) - fx(variable, a));
    double cOld;
    do {
        // оперделяем половину интервала в которой находится корень и сужаем интервал
        if (fx(variable, a) * fx(variable, cNew) < 0) {
            b = cNew;
        } else {
            a = cNew;
        }
        cOld = cNew;

        // обновляем приближение
        cNew = (a * fx(variable, b) - b * fx(variable, a)) / (fx(variable, b) - fx(variable, a));
    } while (fabs(cNew - cOld) >= eps);
    return cNew;
}


/**
 * @brief метод касательных 
 * @param variable вектор коэффициентов
 * @param a нижняя граница интервала
 * @param b верхняя граница интервала
 * @param eps точность
 * @return значение корня
 */
double tangents(vector<double> const &variable, double a, double b, double eps){
    // вычисляем первую и вторую производные полинома
    vector<double> dx1 = variable; dx(dx1);
    vector<double> dx2 = dx1; dx(dx2);

    double dNew;
    if (fx(variable, a) * fx(dx2, a) > 0) {
        dNew = a - fx(variable, a) / fx(dx1, a); // подставляем a
    } else if (fx(variable, b) * fx(dx2, b) > 0) {
        dNew = b - fx(variable, b) / fx(dx1, b);  // подставляем b
    } else {
        return (a + b) / 2;
    }

    double dOld;
    do {
        dOld = dNew;

        // пересчитываем значение
        if (fx(variable, a) * fx(dx2, a) > 0) {
            a = dNew;
                    dNew = a - fx(variable, a) / fx(dx1, a);
        } else if (fx(variable, b) * fx(dx2, b) > 0) {
            b = dNew;
            dNew = b - fx(variable, b) / fx(dx1, b);
        }
    } while (fabs(dNew - dOld) >= eps);
    return dNew;
}

/**
 * @brief комбинированный метод для вычислений  
 * @param variable вектор коэффициентов
 * @param a нижняя граница интервала
 * @param b верхняя граница интервала
 * @param eps точность
 * @return значение корня
 */
double combined(vector<double> const &variable, double a, double b, double eps){
    vector<double> dx1 = variable; dx(dx1);
    vector<double> dx2 = dx1; dx(dx2);
    
    do {
        double c = (a * fx(variable, b) - b * fx(variable, a)) / (fx(variable, b) - fx(variable, a));

        if (fx(variable, a) * fx(dx2, a) > 0) {
            double d = a - fx(variable, a) / fx(dx1, a);
            a = d;  b = c;  
        
        } else if (fx(variable, b) * fx(dx2, b) > 0) {
            double d = b - fx(variable, b) / fx(dx1, b);
            b = d; a = c;
        }
    } while (fabs(b - a) >= 2 * eps);
    return (a + b) / 2; // возвращаем среднее значение
}