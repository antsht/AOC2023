#include <stdio.h>
#include <string.h>

#define ASCII_ZERO 48
#define ASCII_NINE 57
#define BUFFER 257

int main() {
    long int total = 0;
    char buffer[BUFFER];

    FILE* fp = fopen("../data/data2.txt", "r");
    if (fp == NULL) {
        perror("Error occured while opening data2.txt");
        return 1;
    }
    while (!feof(fp)) {
        if (fgets(buffer, BUFFER - 1, fp)) {
            int first_digit = -1, last_digit = -1, i = 0;
            int res = 0;

            while (buffer[i] != '\0') {
                switch (buffer[i]) {
                    case 'o':
                        if (strncmp(&buffer[i], "one", 3) == 0) buffer[i] = '1';
                        break;
                    case 't':
                        if (strncmp(&buffer[i], "two", 3) == 0)
                            buffer[i] = '2';
                        else if (strncmp(&buffer[i], "three", 5) == 0)
                            buffer[i] = '3';
                        break;
                    case 'f':
                        if (strncmp(&buffer[i], "four", 4) == 0)
                            buffer[i] = '4';
                        else if (strncmp(&buffer[i], "five", 4) == 0)
                            buffer[i] = '5';
                        break;
                    case 's':
                        if (strncmp(&buffer[i], "six", 3) == 0)
                            buffer[i] = '6';
                        else if (strncmp(&buffer[i], "seven", 5) == 0)
                            buffer[i] = '7';
                        break;
                    case 'e':
                        if (strncmp(&buffer[i], "eight", 5) == 0) buffer[i] = '8';
                        break;
                    case 'n':
                        if (strncmp(&buffer[i], "nine", 4) == 0) buffer[i] = '9';
                        break;
                }
                if (buffer[i] >= ASCII_ZERO && buffer[i] <= ASCII_NINE) {
                    if (first_digit == -1) {
                        first_digit = buffer[i];
                    }
                    last_digit = buffer[i];
                }
                i++;
            }

            res = (first_digit - ASCII_ZERO) * 10 + (last_digit - ASCII_ZERO);
            total += res;
        }
    }

    fclose(fp);
    printf("%ld", total);
    return 0;
}
