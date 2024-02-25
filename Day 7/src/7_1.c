#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_7.h"

int main() {
    char buffer[257];
    hand_t hands[1000];
    read_hands_from_file("../data/7.txt", hands, buffer);
    sort_asc(hands, 1000);
    long total = 0;
    for (int i = 0; i < 1000; ++i) {
        total += hands[i].bet * (i + 1);
        printf("Row #%d: %d Total: %ld\n", i + 1, hands[i].bet * (i + 1), total);
    }

    return 0;
}