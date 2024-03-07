#ifndef ANALYTICAL_INVERSE_MATRIX_METHOD_H
#define ANALYTICAL_INVERSE_MATRIX_METHOD_H

#include <iostream>
#include <iomanip>
#include <fstream>

namespace gameTheoryAndOperationsResearch {
    class gameTheoryAndOperationsResearch_analytical_inverse_matrix_method
    {
        public:
            double determinant_matrix(double**, int);
            void matrix_inverse_matrix(double**, double**, int);
    };
}

#endif // ANALYTICAL_INVERSE_MATRIX_METHOD_H
