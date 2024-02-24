#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char buffer[256];

typedef struct {
    int hand_id;
    int hand[5];
    int bet;
    long rank;
} hand_t;

hand_t hands[1000];

void read_hands_from_file(char *filename, hand_t hands[1000]);
int calculate_main_rank(int hand[5]);
void sort_desc(hand_t hands[], int length);
void sort_asc(hand_t hands[], int length);

int main() {
    read_hands_from_file("7.txt", hands);
    sort_asc(hands, 1000);
    long total = 0;
    for (int i = 0; i < 1000; ++i) {
        total += hands[i].bet * (i + 1);
    }
    printf("Row #%d: %d Total: %ld\n", 1000, hands[999].bet * (1000), total);
    return 0;
}

void read_hands_from_file(char *filename, hand_t hands[1000]) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error occured while opening input file");
        return;
    }

    int i = 0;
    while (!feof(fp)) {
        if (fgets(buffer, 256, fp)) {
            char sep[2] = " ";
            char *istr;
            istr = strtok(buffer, sep);
            for (int j = 0; j < 5; ++j) {
                switch (istr[j]) {
                    case 'T':
                        hands[i].hand[j] = 10;
                        break;
                    case 'J':
                        hands[i].hand[j] = 1;
                        break;
                    case 'Q':
                        hands[i].hand[j] = 11;
                        break;
                    case 'K':
                        hands[i].hand[j] = 12;
                        break;
                    case 'A':
                        hands[i].hand[j] = 13;
                        break;
                    default:
                        hands[i].hand[j] = istr[j] - 48;
                }
            }
            istr = strtok(NULL, sep);
            hands[i].bet = atoi(istr);
            hands[i].hand_id = i + 1;

            // printf("Hand #%d: %d %d %d %d %d Bet: %d\n", hands[i].hand_id, hands[i].hand[0],
            // hands[i].hand[1], hands[i].hand[2], hands[i].hand[3], hands[i].hand[4], hands[i].bet );

            // printf("Main rank: %ld\n", hands[i].rank);
            char rank_str[12] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '\0'};
            sprintf(rank_str, "%d%.2d%.2d%.2d%.2d%.2d", calculate_main_rank(hands[i].hand), hands[i].hand[0],
                    hands[i].hand[1], hands[i].hand[2], hands[i].hand[3], hands[i].hand[4]);
            printf("%s\n", rank_str);
            hands[i].rank = atol(rank_str);
            i++;
            // getchar();
        }
    }

    fclose(fp);
    return;
}

int calculate_main_rank(int hand[5]) {
    int cnt_cards[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int cnt_matches[6] = {0, 0, 0, 0, 0, 0};

    for (int i = 0; i < 5; ++i) {
        cnt_cards[hand[i]]++;
    }
    for (int i = 2; i < 14; ++i) {
        cnt_matches[cnt_cards[i]]++;
    }
    int jokers = cnt_cards[1];

    int index_max = 0;
    for (int i = 1; i < 6; ++i) {
        if (cnt_matches[i] > 0) {
            index_max = i;
        }
    }
    if (jokers > 0) {
        printf("J: %d Matches: %d %d %d %d %d\n", jokers, cnt_matches[1], cnt_matches[2], cnt_matches[3],
               cnt_matches[4], cnt_matches[5]);
        // cnt_matches[index_max] -= jokers;
        cnt_matches[index_max + jokers] += 1;
        cnt_matches[index_max] -= 1;
        int i = 1;
        /*while (jokers > 0)
        {
            if (cnt_matches[i]>0)
            {
               cnt_matches[i]--;
               jokers--;
            }
            else
            {
                i++;
            }
        }*/
        printf("J: %d Matches: %d %d %d %d %d\n", jokers, cnt_matches[1], cnt_matches[2], cnt_matches[3],
               cnt_matches[4], cnt_matches[5]);
    }

    /*
    for (int i = 1; i < 6; ++i)
    {
        printf("%d card mathes: %d\n", i, cnt_matches[i]);
    }
    */

    if (cnt_matches[5] == 1) return 7;
    if (cnt_matches[4] == 1) return 6;
    if (cnt_matches[3] == 1 && cnt_matches[2] == 1) return 5;
    if (cnt_matches[3] == 1 && cnt_matches[1] == 2) return 4;
    if (cnt_matches[2] == 2) return 3;
    if (cnt_matches[2] == 1 && cnt_matches[1] == 3) return 2;
    if (cnt_matches[1] == 5) return 1;

    /*if (cnt_matches[4] == 1 && jokers == 1) return 7;
    if (cnt_matches[3] == 1 && jokers == 2) return 7;
    if (cnt_matches[3] == 1 && jokers == 1) return 6;
    if (cnt_matches[2] == 2 && jokers == 1) return 5;

    if (cnt_matches[2] == 1 && jokers == 1) return 4;
    if (cnt_matches[2] == 1 && jokers == 2) return 6;
    if (cnt_matches[2] == 1 && jokers == 3) return 7;

    if (cnt_matches[1] == 5 && jokers == 1) return 2;
    if (cnt_matches[1] == 5 && jokers == 2) return 4;
    if (cnt_matches[1] == 5 && jokers == 3) return 6;
    if (cnt_matches[1] == 5 && jokers == 4) return 7;

    if (jokers == 5) return 7;*/

    return 0;
}

void sort_desc(hand_t hands[], int length) {
    hand_t tmp;
    int swap = 1;
    while (swap) {
        swap = 0;
        for (int i = 0; i < length - 1; ++i) {
            if (hands[i].rank < hands[i + 1].rank) {
                tmp = hands[i];
                hands[i] = hands[i + 1];
                hands[i + 1] = tmp;
                swap = 1;
            }
        }
    }
    return;
}

void sort_asc(hand_t hands[], int length) {
    hand_t tmp;
    int swap = 1;
    while (swap) {
        swap = 0;
        for (int i = 0; i < length - 1; ++i) {
            if (hands[i].rank > hands[i + 1].rank) {
                tmp = hands[i];
                hands[i] = hands[i + 1];
                hands[i + 1] = tmp;
                swap = 1;
            }
        }
    }
    return;
}