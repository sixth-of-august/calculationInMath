// включённые библиотеки в проекте
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

// пользовательский модуль для работы с матрицами
# include "matrixModule.h"

int main(){

double **matrix; // переменная для главной матрицы
// переменные для LU-матриц и XY - векторов
double **lMatrix, **uMatrix, *xArray, *yArray;
int N = 0; // размерность матрицы

// считываем размерность матрицы
puts("Введите размерность матрицы: ");
scanf("%d", &N);

matrix = init_matr(N, N + 1); // выделяем память под главную  матрицу
lMatrix = init_matr(N, N); // выделяем память под матрицу L
uMatrix = init_matr(N, N); // выделяем память под матрицу U
xArray = malloc((N) * sizeof(double)); // выделяем память под вектор X
yArray = malloc((N) * sizeof(double)); // выделяем память под вектор Y

// считываем главную матрицу из файла
matrix = matrixReadFile("matrix.txt", N, N + 1);
// заполняем единицами диагональ матрицы uMatrix
for(int i = 0; i < N; i++){
    uMatrix[i][i] = 1;
}
// первый этап
// записываем первый столбец L
for(int i = 0; i < N; i++){
    lMatrix[i][0] = matrix[i][0];
}

// записываем первую строку U
for(int i = 1; i < N; i++){
    uMatrix[0][i] = matrix[0][i] / lMatrix[0][0];
}

// пересчитываем остальные слои
for(int i = 1; i < N; i++){
    for(int j = i; j < N; j++){
        // вычисление нижнего столбца L
        lMatrix[j][i] = matrix[j][i];
        for(int k = 0; k < i; k++){ // суммируем предыдущие столбцы
            lMatrix[j][i] = lMatrix[j][i] - (lMatrix[j][k] * uMatrix[k][i]);
        } }

    // вычисление верхней строки для U
    if(i < N){
        for(int j = i + 1; j < N; j++){
            uMatrix[i][j] = matrix[i][j]; // заполняем столбцы правее диагонали
            for(int k = 0; k < i; k++){ // суммирование предыдущих строк
                uMatrix[i][j] = uMatrix[i][j] - (lMatrix[i][k] * uMatrix[k][j]); 
            } // деление элемента на ведущую диагональ 
            uMatrix[i][j] = uMatrix[i][j] / lMatrix[i][i]; 
        } } }

// вывод матриц на экран
puts("Главная матрица: "); print_matr(matrix, N, N + 1);
puts("Матрица L: "); print_matr(lMatrix, N, N);
puts("Матрица U: "); print_matr(uMatrix, N, N);

//второй этап - вычисляем yArray
yArray[0] = matrix[0][N] / lMatrix[0][0];

for(int i = 1; i < N; i++){
    yArray[i] = matrix[i][N];
    for(int j = 0; j < i; j++){
        yArray[i] = yArray[i] - (lMatrix[i][j] * yArray[j]);
    } yArray[i] = yArray[i] / lMatrix[i][i];
}

// третий этап - вычисляем xArray
xArray[N - 1] = yArray[N - 1];

for(int i = N - 1; i >= 0; i--){
    xArray[i] = yArray[i];
    for(int j = i + 1; j < N; j++){
        xArray[i] = xArray[i] - (uMatrix[i][j] * xArray[j]);
    } }

// вывод значений на экран
// вывод вектора Y
puts("Вектор Y: ");
for(int i = 0; i < N; i++){
    printf("%6.2lf", yArray[i]);
} puts("\n");

// вывод вектора X
puts("Вектор X: ");
for(int i = 0; i < N; i++){
    printf("%6.2lf", xArray[i]);
}

// освобождаем память из переменных
matrix_free(matrix, N); matrix_free(uMatrix, N); matrix_free(lMatrix, N);
free(xArray); free(yArray);

// помечаем указатели NULL
matrix = NULL; uMatrix = NULL; lMatrix = NULL;
xArray = NULL; yArray = NULL;

/* действия в консоли -- 
 создаём программу с подключённым модулем
  gcc holetsky.c -o holetsky
  
  запускаем исполняемый файл
  ./holetsky  */
}
