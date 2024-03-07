#include <iostream>
#include <iomanip>
#include <fstream>

#include "maxmin.h"
#include "vector.h"
#include "print.h"
#include "braun_robinson.h"
#include "analytical_inverse_matrix_method.h"

#include "main.define.h"

namespace gameTheoryAndOperationsResearch {
    void _gameTheoryAndOperationsResearch_readfile() {
        std::string line;std::ifstream in(gameTheoryAndOperationsResearch_filename);
        while (std::getline(in, line))
            std::cout << line << std::endl;
    }

    void _gameTheoryAndOperationsResearch_deletefile() {
        std::remove(gameTheoryAndOperationsResearch_filename);
    }

    gameTheoryAndOperationsResearch::gameTheoryAndOperationsResearch_analytical_inverse_matrix_method _gameTheoryAndOperationsResearch_analytical_inverse_matrix_method;
    gameTheoryAndOperationsResearch::gameTheoryAndOperationsResearch_braun_robinson _gameTheoryAndOperationsResearch_braun_robinson;
    gameTheoryAndOperationsResearch::gameTheoryAndOperationsResearch_maxmin _gameTheoryAndOperationsResearch_maxmin;
    gameTheoryAndOperationsResearch::gameTheoryAndOperationsResearch_print _gameTheoryAndOperationsResearch_print;
    gameTheoryAndOperationsResearch::gameTheoryAndOperationsResearch_vector _gameTheoryAndOperationsResearch_vector;

    int _main(int argc, char* argv[])
    {
        // Удаляем файл
        _gameTheoryAndOperationsResearch_deletefile();

        // Выделяем память под матрицу a размером n x m
        double **a = new double *[n];

        for (int i = 0; i < n; i++)
            a[i] = new double[m];

        int i;

        std::ofstream fout(gameTheoryAndOperationsResearch_filename);

        // Инициализируем матрицу a:
        //      17   4   9
        //      0    16  9
        //      12   2   19

        a[0][0] = 17;       a[0][1] = 4;        a[0][2] = 9;
        a[1][0] = 0;        a[1][1] = 16;       a[1][2] = 9;
        a[2][0] = 12;       a[2][1] = 2;        a[2][2] = 19;

        // Вычисляем min max и max min
        fout << "min max (options):    " << _gameTheoryAndOperationsResearch_maxmin.min_max(a, n, m, i) << std::endl;
        fout << "max min (options):    " << _gameTheoryAndOperationsResearch_maxmin.max_min(a, n, m, i) << std::endl;
        fout << std::endl;

        // Выделяем память под векторы p и q
        double *p = new double[n];
        double *q = new double[m];
        double F1, F2;

        // Применяем метод Брауна-Робинсона
        _gameTheoryAndOperationsResearch_braun_robinson.braun_robinson(a, p, q, n, m, F1, F2, fout);

        fout << std::endl << "[Braun Robinson]" << std::endl;

        fout << "F1:    " << F1 << std::endl
             << "F2:   " << F2 << std::endl
             << "Fsr:  " << (F1 + F2) / 2 << std::endl;

        // Печатаем векторы p и q
        _gameTheoryAndOperationsResearch_print.print_vector(fout, (char *)"P", p, n);
        _gameTheoryAndOperationsResearch_print.print_vector(fout, (char *)"Q", q, m);

        fout << std::endl << "[analytics (inverse matrix)]" << std::endl;

        // Выделяем память под матрицу c размером n x m
        double **c = new double *[n];

        for (int i = 0; i < n; i++)
            c[i] = new double[m];

        // Получаем обратную матрицу
        _gameTheoryAndOperationsResearch_analytical_inverse_matrix_method.matrix_inverse_matrix(a, c, n);

        // Создаем вектор u из всех единиц
        double * u = new double[n];

        for (int i = 0;
             i < n; i++) u[i] = 1;

        // Вычисляем v и обновляем векторы p и q
        double *r1 = new double[n]; // Вектор для промежуточных вычислений

        _gameTheoryAndOperationsResearch_vector.product_vector_matrix(u, c, r1, n, n);
        double v = _gameTheoryAndOperationsResearch_vector.product_vector_vector(r1, u, n);

        _gameTheoryAndOperationsResearch_vector.product_vector_matrix(u, c, p, n, n);

        for (int i = 0; i < n; i++)
            p[i] /= v;

        _gameTheoryAndOperationsResearch_vector.product_matrix_vector(c, u, q, n, m);

        for (int i = 0; i < n; i++)
            q[i] /= v;

        fout << "v: " << 1 / v << std::endl;

        // Печатаем обновленные векторы p и q
        _gameTheoryAndOperationsResearch_print.print_vector(fout, (char *)"P", p, n);
        _gameTheoryAndOperationsResearch_print.print_vector(fout, (char *)"Q", q, m);

        // Считываем файл
        _gameTheoryAndOperationsResearch_readfile();
        return 0;
    }
}

int main(int argc, char* argv[])
{
    gameTheoryAndOperationsResearch::_main(argc, argv);
    return 0;
}
