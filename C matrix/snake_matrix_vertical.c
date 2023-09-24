#include <stdio.h>
#include <stdlib.h>

int **marix_init(int const *row, int const *column);
void mem_clear(int **matrix, int const *row);

void fill_matrix(int **matrix, int const *row, int const *column);
void output(int **matrix, int const *row, int const *column);

int main() {
    int row = 4;
    int column = 2;

    int **matrix = marix_init(&row, &column);
    fill_matrix(matrix, &row, &column);

    output(matrix, &row, &column);
    printf("\n");

    // Вертикальная змейка (первое движение - вниз, смещение слева направо)
    
    // Инициализация начального положения;
    // int dir_h = 0; // Горизонталь: 1 вправо, -1 влево, 0 - нет смещения
    int dir_v = -1; // Вертикаль: 1 вверх, -1 вниз, 0 - нет смещения

    int top = 0;
    int left = 0;
    int bottom = row - 1;
    int right = column - 1;

    while (left <= right)
    {
        if (dir_v == -1) {
            for (int j = top; j <= bottom; j++) {
                int res = matrix[j][left];
                printf("%02d ", res);
            }
            left++;
            if (left > right)
                break;
            dir_v = 1;
        }
        if (dir_v == 1) {
            for (int j = bottom; j >= top; j--) {
                int res = matrix[j][left];
                printf("%02d ", res);

            }
            left++;
            if (left > right)
                break;
            dir_v = -1;
        }
    }
    
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
    int x = 0;
    for (int i = 0; i < *row; i++) {
        for(int j = 0; j < *column; j++){
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