#include "vector.h"

namespace gameTheoryAndOperationsResearch {
    // Произведение вектора на матрицу
    // Функция умножает вектор на матрицу и записывает результат в выходной вектор
    void gameTheoryAndOperationsResearch_vector::product_vector_matrix(double *v, double **matr, double* v_out, int n, int m)
    {
        for (int i = 0; i < m; i++)
        {
            v_out[i] = 0; // Инициализация i-го элемента выходного вектора
            for (int j = 0; j < n; j++)
                v_out[i] += v[j] * matr[j][i]; // Умножение элементов вектора на элементы матрицы и суммирование
        }
    }

    // Произведение матрицы на вектор
    // Функция умножает матрицу на вектор и записывает результат в выходной вектор
    void gameTheoryAndOperationsResearch_vector::product_matrix_vector(double **matr, double *v,  double* v_out, int n, int m)
    {
        for (int i = 0; i < n; i++)
        {
            v_out[i] = 0; // Инициализация i-го элемента выходного вектора
            for (int j = 0; j < m; j++)
                v_out[i] += v[j] * matr[i][j]; // Умножение элементов строки матрицы на элементы вектора и суммирование
        }
    }

    // Произведение вектор на вектор - на выходе число (скалярное произведение)
    // Функция вычисляет скалярное произведение двух векторов
    double gameTheoryAndOperationsResearch_vector::product_vector_vector(double *v1, double *v2, int n)
    {
        double rez = 0; // Инициализация результата
        for (int i = 0; i < n; i++)
            rez += v1[i] * v2[i]; // Умножение соответствующих элементов двух векторов и суммирование
        return rez; // Возвращаем полученное скалярное произведение
    }
}
