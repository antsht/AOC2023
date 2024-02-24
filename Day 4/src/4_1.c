#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CARDS_AMOUNT 203
#define WIN_AMOUNT 10
#define ELF_AMOUNT 25

int strtoarray(int *dest_array, char *str);

int main() {
    char buffer[256];

    typedef struct {
        int card_id;
        int win_values[WIN_AMOUNT];
        int elf_values[ELF_AMOUNT];
    } card_t;

    card_t cards[CARDS_AMOUNT];
    int ind = 0;

    FILE *fp = fopen("../data/4.txt", "r");
    if (fp == NULL) {
        perror("Error occured while opening 4.txt");
        return 1;
    }
    while (!feof(fp)) {
        if (fgets(buffer, 256, fp)) {
            char sep[10] = ":|\n";
            char *istr;
            istr = strtok(buffer, sep);
            int part = 1;
            while (istr != NULL) {
                if (part == 3) {
                    part = 4;
                    strtoarray(cards[ind].elf_values, istr);
                }
                if (part == 2) {
                    part = 3;
                    strtoarray(cards[ind].win_values, istr);
                }
                if (part == 1) {
                    part = 2;
                    cards[ind].card_id = atoi(istr);
                }
                istr = strtok(NULL, sep);
            }
            ind++;
        }
    }

    fclose(fp);
    int sum_total = 0;
    int card_count = 0;
    for (int c = 0; c < CARDS_AMOUNT; ++c) {
        for (int i = 0; i < WIN_AMOUNT; ++i) {
            for (int j = 0; j < ELF_AMOUNT; ++j) {
                if (cards[c].win_values[i] == cards[c].elf_values[j]) ++card_count;
            }
        }
        if (card_count > 0) sum_total += pow(2, card_count - 1);
    }

    printf("\n\nResult: %d\n\n", sum_total);

    return 0;
}

int strtoarray(int *dest_array, char *str) {
    int i = 0;
    int ch = 0;

    int num = 0;
    while (str[ch] != '\0' && str[ch] != '\n') {
        if (isdigit(str[ch])) {
            num = str[ch] - 48;
            ++ch;
        }
        if (isdigit(str[ch])) {
            num = num * 10 + (str[ch] - 48);
            ++ch;
        }
        dest_array[i] = num;
        ++i;
        if (str[ch] != '\0') ++ch;
    }
    return 0;
}