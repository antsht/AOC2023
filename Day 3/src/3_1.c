#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MATRIX_SIZE 142

int main() {
    char buffer[MATRIX_SIZE];
    char schematic[MATRIX_SIZE][MATRIX_SIZE];
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            schematic[i][j] = '.';
        }
    }

    FILE* fp = fopen("../data/3_1.txt", "r");
    if (fp == NULL) {
        perror("Error occured while opening .txt");
        return 1;
    }
    int row = 1;
    while (!feof(fp)) {
        if (fgets(buffer, MATRIX_SIZE-1, fp)) {
            for (int col = 1; col < MATRIX_SIZE; ++col) {
                schematic[row][col] = buffer[col - 1];
            }
            ++row;
        }
    }
    for (int i = 1; i < 141; ++i) {
        for (int j = 1; j < 141; ++j) {
            printf("%c", schematic[i][j]);
        }
        printf("\n");
    }
    int in_number_flag = 0;
    int has_adj_symbol = 0;
    int current_number = 0;
    int sum = 0;
    for (int i = 1; i < 141; ++i) {
        for (int j = 1; j < 141; ++j) {
            if (isdigit(schematic[i][j])) {
                if (in_number_flag == 1) {
                    current_number = current_number * 10 + schematic[i][j] - 48;
                }
                if (in_number_flag == 0) {
                    in_number_flag = 1;
                    current_number = schematic[i][j] - 48;
                }
                if (!isdigit(schematic[i][j - 1]) && schematic[i][j - 1] != '.') has_adj_symbol = 1;
                if (!isdigit(schematic[i][j + 1]) && schematic[i][j + 1] != '.') has_adj_symbol = 1;
                if (!isdigit(schematic[i - 1][j - 1]) && schematic[i - 1][j - 1] != '.') has_adj_symbol = 1;
                if (!isdigit(schematic[i - 1][j]) && schematic[i - 1][j] != '.') has_adj_symbol = 1;
                if (!isdigit(schematic[i - 1][j + 1]) && schematic[i - 1][j + 1] != '.') has_adj_symbol = 1;
                if (!isdigit(schematic[i + 1][j - 1]) && schematic[i + 1][j - 1] != '.') has_adj_symbol = 1;
                if (!isdigit(schematic[i + 1][j]) && schematic[i + 1][j] != '.') has_adj_symbol = 1;
                if (!isdigit(schematic[i + 1][j + 1]) && schematic[i + 1][j + 1] != '.') has_adj_symbol = 1;
            } else {
                if (in_number_flag == 1 && has_adj_symbol == 1) {
                    sum += current_number;
                }
                has_adj_symbol = 0;
                in_number_flag = 0;
                current_number = 0;
            }
        }
    }
    printf("\n\n%d\n\n", sum);
    fclose(fp);

    return 0;
}
