#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 257

int main() {
    char buffer[BUFFER];

    typedef struct {
        int game_id;
        int max_r, max_g, max_b;
    } game_t;

    game_t games[100];
    int i = 0;

    FILE *fp = fopen("../data/2_1.txt", "r");
    if (fp == NULL) {
        perror("Error occured while opening .txt");
        return 1;
    }
    while (!feof(fp)) {
        if (fgets(buffer, BUFFER - 1, fp)) {
            games[i].game_id = 0;
            games[i].max_r = 0;
            games[i].max_g = 0;
            games[i].max_b = 0;
            int id_flag = 0;
            int color_flag = 0;
            char sep[5] = " ,;:";
            char *istr;
            istr = strtok(buffer, sep);
            int last_num = 0;
            while (istr != NULL) {
                if (strcmp(istr, "\n") == 0) {
                    id_flag = 3;
                }
                if (id_flag == 2) {
                    if (color_flag == 1) {
                        if ((strcmp(istr, "red") == 0 || strcmp(istr, "red\n") == 0) &&
                            last_num > games[i].max_r) {
                            games[i].max_r = last_num;
                        }
                        if ((strcmp(istr, "green") == 0 || strcmp(istr, "green\n") == 0) &&
                            last_num > games[i].max_g) {
                            games[i].max_g = last_num;
                        }
                        if ((strcmp(istr, "blue") == 0 || strcmp(istr, "blue\n") == 0) &&
                            last_num > games[i].max_b) {
                            games[i].max_b = last_num;
                        }
                        color_flag = 0;
                        last_num = 0;
                    }
                    if (color_flag == 0 && atoi(istr) > 0) {
                        last_num = atoi(istr);
                        color_flag = 1;
                    }
                }

                if (id_flag == 1) {
                    id_flag = 2;
                    games[i].game_id = atoi(istr);
                }

                if (strcmp(istr, "Game") == 0 && id_flag == 0) {
                    id_flag = 1;
                }

                if (id_flag == 3) {
                    id_flag = 2;
                }
                istr = strtok(NULL, sep);
            }
            i++;
        }
    }

    fclose(fp);
    int sum = 0;
    for (int j = 0; j < 100; ++j) {
        if (games[j].max_r <= 12 && games[j].max_g <= 13 && games[j].max_b <= 14) {
            sum += games[j].game_id;
            printf("ID:%d R:%d G:%d B:%d\n", games[j].game_id, games[j].max_r, games[j].max_g,
                   games[j].max_b);
        }
    }
    printf("Sum of IDs: %d\n", sum);
    return 0;
}
