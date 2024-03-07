#include "braun_robinson.h"

#include "maxmin.h"

#include <memory.h>
#include <cmath>

namespace gameTheoryAndOperationsResearch {
    gameTheoryAndOperationsResearch::gameTheoryAndOperationsResearch_maxmin _braun_robinson_maxmin;

    // Классичекий метод Брауна-Робинсона для матрицы игры
    void gameTheoryAndOperationsResearch_braun_robinson::braun_robinson(
            double **pM, double *p, double *q, int n, int m, double& vmin, double& vmax, std::ostream & fout)
    {
        int *pX = new int[n];           // Частоты по строкам
        int *pY = new int[m];           // Частоты по столбцам
        int k = 1;                      // Общее число выбора строк и столбцов
        double *pV1 = new double[n];    // Суммарный выигрыш 1-го игрока
        double *pV2 = new double[m];    // Суммарный выигрыш 2-го игрока

        for (int i = 0; i < n; i++)
           pV1[i] = pX[i] = 0;
        for (int i = 0; i < m; i++)
           pV2[i] = pY[i] = 0;

        fout << std::fixed << std::setprecision(2);

        int iMax, iMin;

        fout << "N" << std::setprecision(0) << std::left << std::setw(25)
            << " | selection A" << std::left << std::setw(15)
            << " | selection B" << std::left << std::setw(15)
            << " | Winning A" << std::left << std::setw(15)
            << " | Winning B" << std::left << std::setw(15)
            << " | max" << std::left << std::setw(15)
            << " | min" << std::left << std::setw(15)
            << " | e" << std::endl;

        // Первые ходы по минмаксу и максимину
        _braun_robinson_maxmin.max_min(pM, n, m, iMax);
        _braun_robinson_maxmin.min_max(pM, n, m, iMin);

        iMin = iMax = 0;

        double vminmax = 9e99,
               vmaxmin = -9e99;

        do
        {
            fout << std::setprecision(0) << std::left << std::setw(5) << k << " | "
                << "  x" << std::left << std::setw(5) << (iMax + 1) << " | " << " y" << std::setw(5) << (iMin + 1) << " | [";

            // Выигрыш 1-го игрока
            for (int i = 0; i < n; i++) {
                pV1[i] += pM[i][iMin];
                fout << std::right << std::setw(5) << pV1[i];

                if (i != n - 1)
                    fout << ", ";
                else
                    fout << "]  |  [";

           }

           // Проигрыш 2-го игрока
           for (int i = 0; i < m; i++)
           {
                pV2[i] += pM[iMax][i];

                fout << std::setw(5) << pV2[i];

                if (i != m - 1)
                    fout << ", ";
                else
                    fout << "] | ";
           }


           double min = 9e99; // Выбор второго игрока

           for (int i = 0; i < m; i++) {
               if (pV2[i] < min) {
                   min = pV2[i];
                   iMin = i;
               }
           }

           pY[iMin]++;
           vmin = min / k; // Нижняя цена игры

           if (vmin > vmaxmin)
               vmaxmin = vmin;

           // Выбор первого игрока
           double max = -9e99;

           for (int i = 0; i < n; i++) {
               if (pV1[i] > max) {
                   max = pV1[i];
                   iMax = i;
               }
           }

           pX[iMax]++;
           vmax = max / k; // Верхняя цена игры

           if (vmax < vminmax)
               vminmax = vmax;

           k++;

           fout << std::setprecision(3) << std::setw(6) << vmax << " | "
                << std::setw(6) << vmin << "  | " << fabs(vminmax - vmaxmin) << std::endl;

        } while (fabs(vminmax - vmaxmin) > 0.1); // Условие остановки

        vmin = vminmax; vmax = vmaxmin;

        // Расчет оценок вероятностей
        for (int i = 0; i < n; i++)
           p[i] = (double)pX[i] / (k);
        for (int i = 0; i < m; i++)
           q[i] = (double)pY[i] / (k);

        delete[]pX;
        delete[]pY;
        delete[]pV1;
        delete[]pV2;
    }
}
