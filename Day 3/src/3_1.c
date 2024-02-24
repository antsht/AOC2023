#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main() {
    long int total = 0;
    char buffer[142];
    char schematic[142][142];
    for (int i = 0; i < 142; ++i) {
        for (int j = 0; j < 142; ++j) {
            schematic[i][j] = '.';
        }
    }

    FILE* fp = fopen("3_1.txt", "r");
    if (fp == NULL) {
        perror("Error occured while opening 1.txt");
        return 1;
    }
    int row = 1;
    while (!feof(fp)) {
        if (fgets(buffer, 142, fp)) {
            for (int col = 1; col < 141; ++col) {
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
                    // printf("Current: %d  Sum: %d", current_number, sum);
                    // getchar();
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
