#include "matrix.h"

Matrix matTran(Matrix a) {
    Matrix c = {0, 0, NULL};
    if (a.mat != NULL) {
        c = matCreate(a.cols, a.rows);
        for (int i = 0; i < c.rows; i++) {
            for (int j = 0; j < c.cols; j++) {
                c.mat[i][j] = a.mat[j][i];
            }
        }
    }
    return c;
}

Matrix arrayToMatrix(double *arr, int arr_i, int arr_j) {
    Matrix a = {0, 0, NULL};
    int arr_len = sizeof(arr);
    if (arr_len % arr_i == 0 && arr_len % arr_j == 0) {
        a = matCreate(arr_i, arr_j);
        for (int i = 0, cnt = 0; i < arr_i; i++) {
            for (int j = 0; j < arr_j; j++, cnt++) {
                a.mat[i][j] = arr[cnt];
            }
        }
    }
    return a;
}

Matrix matCreate(int rows, int cols) {
    Matrix a;
    a.cols = cols;
    a.rows = rows;
    (a.mat) = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) (a.mat[i]) = (double *)malloc(cols * sizeof(double *));
    return a;
}

bool matEqual(Matrix a, Matrix b) {
    bool res = true;
    if ((a.cols == b.cols && a.rows == b.rows))
        for (int i = 0; i < a.rows && res; i++)
            for (int j = 0; j < a.cols && res; j++) res = (a.mat)[i][j] == (b.mat)[i][j];
    else
        res = false;
    return res;
}

Matrix matSum(Matrix a, Matrix b) {
    Matrix c;
    c.cols = b.cols;
    c.rows = b.rows;
    (c.mat) = (double **)malloc(c.rows * sizeof(double *));
    for (int i = 0; i < c.rows; i++) (c.mat[i]) = (double *)malloc(c.cols * sizeof(double *));
    for (int i = 0; i < c.rows; i++)
        for (int j = 0; j < c.cols; j++) c.mat[i][j] = a.mat[i][j] + b.mat[i][j];
    return c;
}

Matrix matSub(Matrix a, Matrix b) {
    Matrix c;
    c.cols = b.cols;
    c.rows = b.rows;
    (c.mat) = (double **)malloc(c.rows * sizeof(double *));
    for (int i = 0; i < c.rows; i++) (c.mat[i]) = (double *)malloc(c.cols * sizeof(double *));
    for (int i = 0; i < c.rows; i++)
        for (int j = 0; j < c.cols; j++) c.mat[i][j] = a.mat[i][j] - b.mat[i][j];
    return c;
}

Matrix matMul(Matrix a, Matrix b) {
    Matrix c = {0, 0, NULL};
    if (a.cols == b.rows && a.mat != NULL && b.mat != NULL) {
        c = matCreate(a.rows, b.cols);
        for (int i = 0; i < a.rows; i++) {
            for (int j = 0; j < b.cols; j++) {
                c.mat[i][j] = 0;
                for (int k = 0; k < a.cols; k++) {
                    c.mat[i][j] += a.mat[i][k] * b.mat[k][j];
                }
            }
        }
    }
    return c;
}

Matrix matByNum(Matrix a, double k) {
    Matrix c = {a.rows, a.cols, NULL};
    if (a.mat != NULL) {
        c = matCreate(a.rows, a.cols);
        for (int i = 0; i < a.rows; i++) {
            for (int j = 0; j < a.cols; j++) {
                c.mat[i][j] = a.mat[i][j] * k;
            }
        }
    }
    return c;
}

Matrix matMinor(Matrix a, int x, int y) {
    Matrix b = matCreate(a.rows - 1, a.cols - 1);
    for (int i = 0, bi = 0; i < a.rows; i++) {
        if (i == x) continue;
        for (int j = 0, bj = 0; j < a.cols; j++) {
            if (j == y) continue;
            b.mat[bi][bj] = a.mat[i][j];
            bj++;
        }
        bi++;
    }
    return b;
}

double matDet(Matrix a) {
    if (a.cols != a.rows) return NAN;  // Возвращаем NaN для несовместимых размеров
    if (a.cols == 1) return a.mat[0][0];
    if (a.cols == 2) return a.mat[0][0] * a.mat[1][1] - a.mat[0][1] * a.mat[1][0];

    double d = 0;
    int sign = 1;
    for (int i = 0; i < a.cols; i++) {
        Matrix minor = matMinor(a, 0, i);
        d += sign * a.mat[0][i] * matDet(minor);
        sign = -sign;
        matRemove(minor);
    }
    return d;
}

Matrix matCompl(Matrix a) {
    Matrix b = matCreate(0, 0);
    if (a.cols != a.rows)
        b.mat = NULL;
    else {
        b = matCreate(a.cols, a.rows);
        for (int i = 0; i < a.cols; i++) {
            for (int j = 0; j < a.rows; j++) {
                Matrix minor = matMinor(a, i, j);
                b.mat[i][j] = pow(-1, i + j) * matDet(minor);
                matRemove(minor);
            }
        }
    }
    return b;
}

Matrix matInv(Matrix a) { return matByNum(matTran(matCompl(a)), (1 / matDet(a))); }

double matTrace(Matrix a) {
    double s = 0;
    if (a.cols == a.rows)
        for (int i = 0; i < a.cols; i++) s += (a.mat)[i][i];
    else
        s = NAN;
    return s;
}

int printMatrix(Matrix a) {
    int res = true;
    if (a.mat != NULL) {
        for (int i = 0; i < a.rows; i++) {
            for (int j = 0; j < a.cols; j++) {
                printf("%.1lf ", a.mat[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("Error: incorrect input\n");
        res = false;
    }
    return res;
}

int matRemove(Matrix a) {
    int res = true;
    if (a.mat == NULL) res = false;
    for (int i = 0; i < a.rows; i++) free(a.mat[i]);
    free(a.mat);
    return res;
}
