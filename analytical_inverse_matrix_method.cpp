#include "analytical_inverse_matrix_method.h"

#include <memory.h>
#include <cmath>

namespace gameTheoryAndOperationsResearch {
    // [функции для аналитического метода обратной матрицы]

    // Функция для вычисления определителя матрицы
    double gameTheoryAndOperationsResearch_analytical_inverse_matrix_method::determinant_matrix(double **p, int n)
    {
        if (n == 1)
            return p[0][0]; // Если размер матрицы равен 1, возвращаем элемент

        if (n == 2)
            return p[0][0] * p[1][1] - p[0][1] * p[1][0]; // Если размер матрицы равен 2, используем формулу для определителя 2x2 матрицы

        else
        {
            double **p2 = new double *[n - 1]; // Создаем временную матрицу меньшего размера
            for (int i = 0; i < n - 1; i++)
                p2[i] = new double[n - 1];

            int zn = 1; // Знак определителя
            double Det = 0; // Инициализируем определитель

            for (int k = 0; k < n; k++, zn *= -1)
            {
                if (p[0][k] == 0)
                    continue; // Пропускаем нулевые элементы
                for (int i = 1; i < n; i++)
                    for (int j = 0; j < n; j++)
                    {
                        if (j < k)
                            p2[i - 1][j] = p[i][j]; // Заполняем временную матрицу
                        if (j > k)
                            p2[i - 1][j - 1] = p[i][j]; // Заполняем временную матрицу
                    }
                Det += zn * p[0][k] * determinant_matrix(p2, n - 1); // Рекурсивно вычисляем определитель
            }

            for (int i = 0; i < n - 1; i++)
                delete[] p2[i]; // Освобождаем память временной матрицы

            delete[] p2; // Освобождаем память временной матрицы

            return Det; // Возвращаем определитель
        }
    }

    // Функция для вычисления обратной матрицы для матрицы
    void gameTheoryAndOperationsResearch_analytical_inverse_matrix_method::matrix_inverse_matrix(double **p, double **pObr, int n)
    {
        double Det = 0;

        // Если размер матрицы равен 2, используем простую формулу для нахождения обратной матрицы
        if (n == 2)
        {
            Det = p[0][0] * p[1][1] - p[0][1] * p[1][0];
            pObr[0][0] = p[1][1];
            pObr[0][1] = p[1][0] * -1;
            pObr[1][0] = p[0][1] * -1;
            pObr[1][1] = p[0][0];
        }
        else
        {
            double **p2 = new double *[n - 1]; // Создаем временную матрицу меньшего размера

            for (int i = 0; i < n - 1; i++)
                p2[i] = new double[n - 1];

            int zn = 1; // Знак определителя
            Det = 0;

            // Вычисляем обратную матрицу методом алгебраических дополнений
            for (int k0 = 0; k0 < n; k0++)
            {
                for (int k = 0; k < n; k++)
                {
                    if ((k + k0) % 2)
                        zn = -1;
                    else
                        zn = 1;

                    for (int i = 0; i < n; i++)
                        for (int j = 0; j < n; j++)
                        {
                            if (i > k0)
                            {
                                if (j < k)
                                    p2[i - 1][j] = p[i][j];
                                if (j > k)
                                    p2[i - 1][j - 1] = p[i][j];
                            }
                            if (i < k0)
                            {
                                if (j < k)
                                    p2[i][j] = p[i][j];
                                if (j > k)
                                    p2[i][j - 1] = p[i][j];
                            }
                        }

                    double opr = determinant_matrix(p2, n - 1);
                    pObr[k0][k] = zn * opr;

                    if (k0 == 0)
                        Det += p[k0][k] * pObr[k0][k];

                }
            }

            // Освобождаем память временной матрицы
            for (int i = 0; i < n - 1; i++)
                delete[] p2[i];

            delete[] p2;

        }

        // Транспонируем матрицу обратной матрицы
        for (int i = 0; i < n - 1; i++)
            for (int j = i + 1; j < n; j++) {
                double buf = pObr[i][j];
                pObr[i][j] = pObr[j][i];
                pObr[j][i] = buf;
            }

        // Делим все элементы обратной матрицы на определитель и округляем значения
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                pObr[i][j] /= Det;
                if (fabs(pObr[i][j]) < 1e-9)
                    pObr[i][j] = 0;
            }
    }
}
