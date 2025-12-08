#include <iostream>
#include <vector>
#include <format>
#include "functionModule.hpp"

using namespace std;

int main(){

   //для проверки: 2x3 − 3x2 + 4x + 5 = 0

    int degree; // переменная ответственная за высшую степень в уравнении
    vector<double> variable;
    const double eps = 0.000001; // переменная для точности вычислений

    cout << "Введите высшую степень x: ";
    cin >> degree; degree++;
    variable.resize(degree);

    // записываем свободные коэффициенты
    for(int i = degree - 1; i > 0; i--){
        cout << format("Введите коэфициент для степени x{}:\n", i);
        cin >> variable[i];
    }   
    cout << format("Введите свободный от x коэффициент:\n" );
    cin >> variable[0];

    cout << format("Метод хорд на интервале [-1; 1] с точностью 0.000001: {}\n", chords(variable, -1, 1, eps));
    cout << format("Метод касательных на интервале [-1; 1] с точностью 0.000001: {}\n", tangents(variable, -1, 1, eps));
    cout << format("Комбинированный метод на интервале [-1; 1] с точностью 0.000001: {}\n", combined(variable, -1, 1, eps));
    return 0;
}

// g++ numericalTask.cpp functionModule.cpp -o task.exe --std=c++20
// ./task