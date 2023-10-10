#include <stdio.h>
#include <stdlib.h>

// Вариант поворота произвольной матрицы M x N с выводом на печать

int **matrix_init(int *row, int *column);
void mem_free(int **matrix, int *row);
void test_data_init(int **matrix, int *row, int *column);
void output(int **matrix, int const *row, int const *column);
void rotate_output(int **matrix, int const *row, int const *column);

int main(){
    int row = 2;
    int column = 3;
    int **matrix = matrix_init(&row, &column);
    test_data_init(matrix, &row, &column);
    
    printf("Matrix before turn:\n");
    output(matrix, &row, &column);

    printf("Matrix after turn:\n");
    rotate_output(matrix, &row, &column);

    mem_free(matrix, &row);

    return 0;
}

int **matrix_init(int *row, int *column) {
    int **matrix = calloc(*row, sizeof(int*));
    for (int i = 0; i < *row; i++) {
        matrix[i] = calloc(*column, sizeof(int));
    }
    return matrix;
}

void mem_free(int **matrix, int *row) {
    for (int i = 0; i < *row; i++) {
        free(matrix[i]);
    } 
    free(matrix);
}

void test_data_init(int **matrix, int *row, int *column) {
    int x = 1;
    for (int i = 0; i < *row; i++) {
        for (int j = 0; j < *column; j++) {
            matrix[i][j] = x;
            x++;
        }
    }
}

void output(int **matrix, int const *row, int const *column) {
    for (int i = 0; i < *row; i++) {
        for (int j = 0; j < *column; j++) {
            printf("%02d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void rotate_output(int **matrix, int const *row, int const *column) {
    for (int j = 0; j < *column; j++) {
        for (int i = *row - 1; i >= 0; i--) {
            printf("%02d ", matrix[i][j]);
        }
        printf("\n");
    }
}