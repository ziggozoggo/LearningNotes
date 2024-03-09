/*
* Хранение квадратной матрицы в виде одномерного массива
*/

#include <stdio.h>
#include <stdlib.h>

int get_matrix_element(int *matrix, int row, int col, int side_size);

int main () {
  int matrix[] = {
    0, 0, 0,
    3, 3, 3,
    0, 3, 0
  };

  int side_size = 3;

  for (int i = 0; i < side_size; ++i) {
    for (int j = 0; j < side_size; ++j) {
      printf("%d ", get_matrix_element(&matrix, i, j, side_size));
    }
    printf("\n");
  }

}

int get_matrix_element(int *matrix, int row, int col, int side_size) {
  return matrix[row * side_size + col];
}

