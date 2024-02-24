#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CARDS_AMOUNT 203
#define WIN_AMOUNT 10
#define ELF_AMOUNT 25

int strtoarray(int *dest_array, int dest_array_length, char *str);

int main() {
    char buffer[256];

    typedef struct {
        int card_id;
        int win_values[WIN_AMOUNT];
        int elf_values[ELF_AMOUNT];
        int matches;
        int cards;
    } card_t;

    card_t cards[CARDS_AMOUNT];
    int i = 0;

    FILE *fp = fopen("4.txt", "r");
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
            // Выделение последующих частей
            while (istr != NULL) {
                // printf("Str: %s\n", istr);
                if (part == 3) {
                    part = 4;
                    strtoarray(cards[i].elf_values, ELF_AMOUNT, istr);
                    // printf ("%s\n", istr);
                }
                if (part == 2) {
                    part = 3;
                    strtoarray(cards[i].win_values, WIN_AMOUNT, istr);

                    // printf ("%s | ", istr);
                }
                if (part == 1) {
                    part = 2;
                    cards[i].card_id = atoi(istr);

                    // printf ("Card %d: ", cards[i].card_id);
                }
                // Выделение очередной части строки
                istr = strtok(NULL, sep);
            }
            // printf("\nID: %d 1th win num: %d  10th win num: %d   1th elf num: %d  25th elf num: %d\n",
            // cards[i].card_id, cards[i].win_values[0],
            // cards[i].win_values[9],cards[i].elf_values[0],cards[i].elf_values[24]);
            cards[i].matches = 0;
            cards[i].cards = 1;
            // getchar();
            i++;
        }
    }

    fclose(fp);
    int sum_total = 0;
    int card_count = 0;
    for (int c = 0; c < CARDS_AMOUNT; ++c) {
        card_count = 0;
        for (int i = 0; i < WIN_AMOUNT; ++i) {
            for (int j = 0; j < ELF_AMOUNT; ++j) {
                if (cards[c].win_values[i] == cards[c].elf_values[j]) ++card_count;
            }
        }
        cards[c].matches = card_count;
    }

    for (int i = 0; i < CARDS_AMOUNT - 1; ++i) {
        for (int j = i + 1; j <= i + cards[i].matches; ++j) {
            if (j < CARDS_AMOUNT) cards[j].cards += cards[i].cards;
        }
    }
    long int total_cards = 0;
    for (int i = 0; i < CARDS_AMOUNT; ++i) {
        total_cards += cards[i].cards;
        printf("ID: %d matches: %d Cards: %d\n", i, cards[i].matches, cards[i].cards);
    }
    printf("Total: %ld\n", total_cards);
    return 0;
}

int strtoarray(int *dest_array, int dest_array_length, char *str) {
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
        // printf("Dest num: %d, Str: %s\n", dest_array[i], str);
        ++i;
        if (str[ch] != '\0') ++ch;
    }
    return 0;
}