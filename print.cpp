#include "print.h"

namespace gameTheoryAndOperationsResearch {
    // Метод print_vector выводит вектор на экран
    void gameTheoryAndOperationsResearch_print::print_vector(std::ostream& out, char * str, double *p, int n)
    {
        out.precision(3); // Устанавливаем точность вывода чисел
        out << str << ": "; // Выводим строку-метку для вектора

        for (int i = 0; i < n; i++)
            out << p[i] << " "; // Выводим элементы вектора через пробел
        out << std::endl; // Переходим на новую строку после вывода всех элементов
    }
}
