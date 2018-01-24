#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>
#include <cstdio>
#include <omp.h>

using std::ostream;

class Matrix
{
  public:
    double          A[4][4];

    void            TransformPoint(const double *ptIn, double *ptOut);
    static Matrix   ComposeMatrices(const Matrix &, const Matrix &);
    void            Print(ostream &o);
};

#endif
