#include "maxmin.h"

namespace gameTheoryAndOperationsResearch {
    // Метод max_min находит максимум из минимальных значений по строкам
    double gameTheoryAndOperationsResearch_maxmin::max_min(double **Matr, int n, int m, int& iMax)
    {
        double min;
        double max = 0;

        for (int i = 0; i < n; i++)
        {
            min = Matr[i][0];

            // Находим минимальное значение в текущей строке
            for (int j = 1; j < m; j++)
                if (min > Matr[i][j])
                    min = Matr[i][j];

            // Сравниваем минимальное значение с максимальным
            if (max < min) {
                max = min;
                iMax = i; // Сохраняем индекс строки с максимальным минимальным значением
            }

        }
        return max; // Возвращаем максимальное из минимальных значений
    }

    // Метод min_max находит минимум из максимальных значений по столбцам
    double gameTheoryAndOperationsResearch_maxmin::min_max(double **Matr, int n, int m, int& iMin)
    {
        double min = 9e99; // Инициализация переменной min большим значением
        double max;

        for (int j = 0; j < m; j++)
        {
            max = Matr[0][j];

            // Находим максимальное значение в текущем столбце
            for (int i = 1; i < n; i++)
                if (max < Matr[i][j])
                    max = Matr[i][j];

            // Сравниваем максимальное значение с минимальным
            if (max < min) {
                min = max;
                iMin = j; // Сохраняем индекс столбца с минимальным максимальным значением
            }
        }
        return min; // Возвращаем минимум из максимальных значений
    }
}
