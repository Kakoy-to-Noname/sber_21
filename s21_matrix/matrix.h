#include "my_math.h"
#include <stdbool.h>
#include <stdio.h>

// #include "/data_structs.h"

// typedef struct Tensor {
//     int n;
//     void *ptr;
// }

typedef struct Matrix {
    int rows;
    int cols;
    double **mat;
} Matrix;

typedef struct matSpace {
    int cnt;
    Matrix *space;
} MatrixSpace;

typedef union MatFunc {
    Matrix (*opBinary) (Matrix , Matrix);
    Matrix (*opUnary) (Matrix);
    Matrix (*getMinor) (Matrix, int, int);
    Matrix (*scalMul) (Matrix, double);
    bool (*opEq) (Matrix, Matrix);
    double (*matExtr) (Matrix);
} MatFunc;


Matrix matSum(Matrix a, Matrix b);
Matrix matSub(Matrix a, Matrix b);
Matrix matMul(Matrix a, Matrix b);
Matrix matByNum(Matrix a, double k);
bool matEqual(Matrix a, Matrix b);

Matrix matTran(Matrix a);
Matrix matMinor(Matrix a, int i, int j);
Matrix matCompl(Matrix a);
double matDet(Matrix a);
Matrix matInv(Matrix a);
double matTrace(Matrix a);

int printMatrix(Matrix a);
Matrix matCreate(int rows, int cols);
Matrix arrayToMatrix(double *arr, int i, int j);
int matRemove(Matrix a);