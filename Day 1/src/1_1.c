#include <stdio.h>
#include <string.h>

#define ASCII_ZERO 48
#define ASCII_NINE 57
#define BUFFER 257

int main() {
    long int total = 0;
    char buffer[BUFFER];

    FILE* fp = fopen("../data/data.txt", "r");
    if (fp == NULL) {
        perror("Error occured while opening 1.txt");
        return 1;
    }
    while (!feof(fp)) {
        if (fgets(buffer, BUFFER - 1, fp)) {
            int digit_s = -1, digit_e = -1, i = 0;
            int res = 0;

            while (buffer[i] != '\0') {
                if (buffer[i] >= ASCII_ZERO && buffer[i] <= ASCII_NINE) {
                    if (digit_s == -1) {
                        digit_s = buffer[i];
                    }
                    digit_e = buffer[i];
                }
                i++;
            }

            res = (digit_s - ASCII_ZERO) * 10 + (digit_e - ASCII_ZERO);
            total += res;
        }
    }

    fclose(fp);
    printf("%ld", total);
    return 0;
}
