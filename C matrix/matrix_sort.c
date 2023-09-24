#include <stdio.h>
#include <stdlib.h>

int **marix_init(int const *row, int const *column);
void mem_clear(int **matrix, int const *row);

void fill_matrix(int **matrix, int const *row, int const *column);
void output(int **matrix, int const *row, int const *column);
void swap_values(int *first_value, int *second_value);
void sort_matrix(int **matrix, int const *row, int const *column);

int main() {
    int row = 2;
    int column = 4;

    int **matrix = marix_init(&row, &column);
    fill_matrix(matrix, &row, &column);

    output(matrix, &row, &column);
    printf("\n");

    sort_matrix(matrix, &row, &column);
    output(matrix, &row, &column);

    mem_clear(matrix, &row);
    return 0;
}

int **marix_init(int const *row, int const *column) {
    int **matrix = calloc(*row, sizeof(int*));
    for (int i = 0; i < *row; i++) {
        matrix[i] = calloc(*column, sizeof(int));
    }
    return matrix;
}

void mem_clear(int **matrix, int const *row) {
    for (int i = 0; i < *row; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void fill_matrix(int **matrix, int const *row, int const *column) {
    int x = 8;
    for (int i = 0; i < *row; i++) {
        for(int j = 0; j < *column; j++){
            matrix[i][j] = x;
            x--;
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

void swap_values(int *first_value, int *second_value) {
    int tmp_value = *first_value;
    *first_value = *second_value;
    *second_value = tmp_value;
}

void sort_matrix(int **matrix, int const *row, int const *column) {
    // Сортировка справа налево
    int is_sorted = 0;

    while (!is_sorted)
    {
        is_sorted = 1;
        for (int i = 0; i < *row; i++) {
            for (int j = 1; j < *column; j++) {
                if (matrix[i][j - 1] > matrix[i][j]) {
                    swap_values(&matrix[i][j - 1], &matrix[i][j]);
                    is_sorted = 0;
                }
            }
            if (i != *row - 1) {
                if (matrix[i][*column - 1] > matrix[i + 1][0]) {
                    swap_values(&matrix[i][*column - 1], &matrix[i + 1][0]);
                    is_sorted = 0;
                }

            }
        } 
    }
    
}