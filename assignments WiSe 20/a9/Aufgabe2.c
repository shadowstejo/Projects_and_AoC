/*
 * 	Stephan Jokiel
 * 	Maxine Rahlfes
*/

#include "base.h"

struct Matrix {
    int rows; // number of rows
    int cols; // number of columns
    double **data; // a pointer to an array of n_rows pointers to rows; a row is an array of n_cols doubles

};
typedef struct Matrix Matrix;

/**
Creates a zero-initialized matrix of rows and columns matrix.
@param[in] n_rows number of rows
@param[in] n_cols number of columns
@return a pointer to an array of n_rows pointers to rows; a row is an array of n_cols doubles 
*/
Matrix *new_matrix(int n_rows, int n_cols) {

    require("valid matrix", n_rows > 0 && n_cols > 0);

    Matrix *m;
    m = xmalloc(sizeof(Matrix));                            //Speicher für Matrix
    double **data = xmalloc(n_rows * sizeof(double *));         //Speicher für rows data

    //printf("size of data %d, %p\n", n_rows * sizeof(double*), data //test
    //printf("size of Matrix %d, %p\n", sizeof(Matrix), m);         // test

    ensure("Memory available", data != NULL && m != NULL);

    m->rows = n_rows;
    m->cols = n_cols;
    m->data = data;

    for (int r = 0; r < m->rows; r++) {
        data[r] = xmalloc(n_cols * sizeof(double));             //Speicher für cols
        //printf("size of row: %d; data[r]: %p\n", n_cols * sizeof(double), data[r]);//test

        for (int c = 0; c < m->cols; c++) {
            //printf("r: %d; c: %d; pointer: %p\n", r, c, &(data[r][c]));  //test
            m->data[r][c] = 0.0;
        }

    }

    return m;
}

/**
Creates a zero-initialized matrix of rows and columns matrix.
@param[in] data an array of doubles, ordered row-wise
@param[in] n_rows number of rows
@param[in] n_cols number of columns
@return a pointer to an array of n_rows pointers to rows; a row is an array of n_cols doubles 
*/
Matrix *copy_matrix(double *data, int n_rows, int n_cols) {
    require("valid matrix", data != NULL && n_rows > 0 && n_cols > 0);

    Matrix *m = new_matrix(n_rows, n_cols);

    for (int r = 0; r < n_rows; r++) {
        for (int c = 0; c < n_cols; c++) {
            m->data[r][c] = data[r * n_cols + c];
        }
    }
    return m;
}

/**
Print a matrix.
@param[in] m the matrix to print
*/
void print_matrix(Matrix *m) {
    require_not_null(m);

    for (int r = 0; r < m->rows; r++) {
        for (int c = 0; c < m->cols; c++) {
            printf("%.1f",m->data[r][c]);
            printc(' ');
        }
        println();
    }
}


/**
Transpose a matrix.
@param[in] a the first operand
@return a new matrix whose elements are transposed
*/
Matrix *transpose_matrix(/*in*/ Matrix *a) {
    int new_cols = a->rows;
    int new_rows = a->cols;
    Matrix *m = new_matrix(new_rows, new_cols);

    for (int r = 0; r < new_rows; r++) {
        for (int c = 0; c < new_cols; c++) {
            m->data[r][c] = a->data[c][r];
        }
    }
    return m;
}

/**
Multiplies two matrices.
@param[in] a the first operand
@param[in] b the second operand
@return a new matrix that is the result of the multiplication of a * b
*/
Matrix *mul_matrices(/*in*/ Matrix *a, /*in*/ Matrix *b) {
    require("valid matrix multiolication", a->cols == b->rows);
    require_not_null(a);
    require_not_null(b);

    int result_m_rows = a->rows;
    int result_m_cols = b->cols;
    double new_ele = 0;
    Matrix *result_m = new_matrix(result_m_rows, result_m_cols);

    for (int c = 0; c < result_m_cols; c++) {
        for (int r = 0; r < result_m_rows; r++) {
            for (int i = 0; i < a->cols; i++) {
                new_ele += a->data[r][i] * b->data[i][c];
                //printf("das Element an Position(%d, %d) lautet: %f\n", r, c, new_ele);
            }
            result_m->data[r][c] = new_ele;
            new_ele = 0;
        }
    }
    assert("correct result-matrix", result_m->rows == a->rows && result_m->cols == b->cols);
    return result_m;
}

/**
Free a matrix.
@param[in] m the matrix to free
*/
void free_matrix(Matrix *m) {
    for (int r = 0; r < m->rows; r++) {
        free(m->data[r]);
    }
    free(m->data);
    free(m);
}

void matrix_test(void) {
    printf("Create empty matrix: \n");
    Matrix *m0 = new_matrix(3, 2);
    print_matrix(m0);

    printf("Copy matrix data from double[]\n");
    double a[] = {
            1, 2, 3,
            4, 5, 6,
            7, 8, 9};
    Matrix *m1 = copy_matrix(a, 3, 3);
    printf("m1:\n");
    print_matrix(m1);


    double a2[] = {
            1, 2, 3, 3.5,
            4, 5, 6, 7};
    Matrix *m2 = copy_matrix(a2, 2, 4);
    printf("m2:\n");
    print_matrix(m2);


    printf("Transpose: m2\n");
    Matrix *m2t = transpose_matrix(m2);
    print_matrix(m2t);


    double a3[] = {
            1, 2,
            3, 4,
            5, 6,
            7, 8};
    Matrix *m3 = copy_matrix(a3, 4, 2);
    printf("m3:\n");
    print_matrix(m3);

    printf("Multiplie m3 * m3t\n");
    Matrix *m3t = transpose_matrix(m3);
    printf("m3t:\n");
    print_matrix(m3t);

    Matrix *m4 = mul_matrices(m3, m3t);
    printf("m4:\n");
    print_matrix(m4);

    free_matrix(m0);
    free_matrix(m1);
    free_matrix(m2);
    free_matrix(m2t);
    free_matrix(m3);
    free_matrix(m3t);
    free_matrix(m4);
}

int main(void) {
    report_memory_leaks(true);
    matrix_test();
    return 0;
}
