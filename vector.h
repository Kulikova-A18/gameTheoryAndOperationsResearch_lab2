#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <iomanip>
#include <fstream>

namespace gameTheoryAndOperationsResearch {
    class gameTheoryAndOperationsResearch_vector
    {
        public:
            void product_vector_matrix(double *, double**, double*, int, int);
            void product_matrix_vector(double **, double*,  double*, int, int);
            double product_vector_vector(double *, double*, int);
    };
}
#endif // VECTOR_H
