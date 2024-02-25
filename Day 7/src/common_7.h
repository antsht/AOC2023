#ifndef COMMON_7_H
#define COMMON_7_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int hand_id;
    int hand[5];
    int bet;
    long rank;
} hand_t;

void read_hands_from_file(char *filename, hand_t hands[1000], char *buffer);
int calculate_main_rank(const int hand[5]);
/*void sort_desc(hand_t hands[], int length);*/
void sort_asc(hand_t hands[], int length);

#endif