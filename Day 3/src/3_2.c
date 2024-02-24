#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define ASCII_ZERO 48
#define MATRIX_SIZE 142

int get_number_in_position(char matrix[MATRIX_SIZE][MATRIX_SIZE], int row, int col);
int check_adj_number(char matrix[MATRIX_SIZE][MATRIX_SIZE], int row, int col, int *num1, int *num2, int *cnt);

int main() {
    long int total = 0;
    char buffer[MATRIX_SIZE];
    char schematic[MATRIX_SIZE][MATRIX_SIZE];
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            schematic[i][j] = '.';
        }
    }
    FILE *fp = fopen("3a.txt", "r");
    if (fp == NULL) {
        perror("Error occured while opening 1.txt");
        return 1;
    }
    int row = 1;
    while (!feof(fp)) {
        if (fgets(buffer, MATRIX_SIZE, fp)) {
            for (int col = 1; col < MATRIX_SIZE - 1; ++col) {
                schematic[row][col] = buffer[col - 1];
            }
            ++row;
        }
    }
    int sum = 0;
    for (int i = 1; i < MATRIX_SIZE - 1; ++i) {
        for (int j = 1; j < MATRIX_SIZE - 1; ++j) {
            if (schematic[i][j] == '*') {
                int num1 = 0, num2 = 0;
                int cnt = 0;
                int tmp_num;
                check_adj_number(schematic, i, j - 1, &num1, &num2, &cnt);
                check_adj_number(schematic, i, j + 1, &num1, &num2, &cnt);
                check_adj_number(schematic, i - 1, j - 1, &num1, &num2, &cnt);
                check_adj_number(schematic, i - 1, j, &num1, &num2, &cnt);
                check_adj_number(schematic, i - 1, j + 1, &num1, &num2, &cnt);
                check_adj_number(schematic, i + 1, j - 1, &num1, &num2, &cnt);
                check_adj_number(schematic, i + 1, j, &num1, &num2, &cnt);
                check_adj_number(schematic, i + 1, j + 1, &num1, &num2, &cnt);
                if (cnt == 2) sum += num1 * num2;
                cnt = 0;
                num1 = 0;
                num2 = 0;
            }
        }
    }
    printf("\n\n%d\n\n", sum);
    fclose(fp);

    return 0;
}

int get_number_in_position(char matrix[MATRIX_SIZE][MATRIX_SIZE], int row, int col) {
    while (isdigit(matrix[row][col - 1])) col--;
    int number = matrix[row][col] - ASCII_ZERO;
    while (isdigit(matrix[row][col + 1])) {
        col++;
        number = number * 10 + matrix[row][col] - ASCII_ZERO;
    }
    return number;
}

int check_adj_number(char matrix[MATRIX_SIZE][MATRIX_SIZE], int row, int col, int *num1, int *num2,
                     int *cnt) {
    if (isdigit(matrix[row][col])) {
        int tmp_num = get_number_in_position(matrix, row, col);
        if (tmp_num != *num1 && tmp_num != *num2) {
            *cnt = *cnt + 1;
            if (*num1 == 0)
                *num1 = tmp_num;
            else if (*num2 == 0)
                *num2 = tmp_num;
        }
    }
    return 0;
}