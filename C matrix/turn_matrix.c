#include <stdio.h>
#include <stdlib.h>

// https://www.youtube.com/watch?v=IdZlsG6P17w
// rotate matrix 90 degreed

int **matrix_init(int *row, int *column);
void mem_free(int **matrix, int *row);
void test_data_init(int **matrix, int *row, int *column);
void matrix_output(int **matrix, int *row, int *column);
void swap_values(int *first_value, int *second_value);
void matrix_square_transpose(int **matrix, int *row, int *column);
void matrix_square_flip_horiz(int **matrix, int *row, int *column);

int main() {
    int row = 3;
    int column = 3;

    

    int **matrix = matrix_init(&row, &column);
    test_data_init(matrix, &row, &column);
    matrix_output(matrix, &row, &column);

    // Step 1: Transpose
    matrix_square_transpose(matrix, &row, &column);
    printf("\n");
    matrix_output(matrix, &row, &column);

    // Step 2: Flip Horizontally
    // swap( matrix[i][j], matrix[i][row - 1 - j])
    matrix_square_flip_horiz(matrix, &row, &column);
    printf("\n");
    matrix_output(matrix, &row, &column);


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

void matrix_output(int **matrix, int *row, int *column) {
    for (int i = 0; i < *row; i++) {
        for (int j = 0; j < *column; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void swap_values(int *first_value, int *second_value) {
    int tmp = *first_value;
    *first_value = *second_value;
    *second_value = tmp;
}

void matrix_square_transpose(int **matrix, int *row, int *column) {
    for (int i = 0; i < *row; i++) {
        for (int j = i; j < *column; j++) {
            swap_values(&matrix[i][j], &matrix[j][i]);
        }
    }
}

void matrix_square_flip_horiz(int **matrix, int *row, int *column) {
    for (int i = 0; i < *row; i++) {
        for (int j = 0; j < (*column / 2); j++) {
            swap_values(&matrix[i][j], &matrix[i][*row - 1 - j]);
        }
    }
}