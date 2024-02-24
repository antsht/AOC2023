#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char buffer[256];

#define MAPSIZE 110

typedef struct {
    char type;
    int v_from_left;
    int v_from_right;
    int v_from_top;
    int v_from_bottom;
} map_point_t;

map_point_t map[MAPSIZE][MAPSIZE];

typedef struct {
    int row;
    int col;
    char dir;
    int active;
} beam_t;

beam_t beams[1000];
int cnt_beams = 0;

void read_data_from_file(char* filename);
void draw_map();
void draw_energy_map();
int count_energy();
int move_light_beam_from_point(int curr_beam);
int calc_from_point(int r, int c, char dir);

int main() {
    read_data_from_file("16.txt");

    // draw_map();
    // draw_energy_map();
    int max_energy = 0;
    for (int r = 0; r < MAPSIZE; r++) {
        int res = calc_from_point(r, -1, 'r');
        if (res > max_energy) {
            max_energy = res;
        }
    }

    for (int r = 0; r < MAPSIZE; r++) {
        int res = calc_from_point(r, MAPSIZE, 'l');
        if (res > max_energy) {
            max_energy = res;
        }
    }

    for (int c = 0; c < MAPSIZE; c++) {
        int res = calc_from_point(-1, c, 'd');
        if (res > max_energy) {
            max_energy = res;
        }
    }

    for (int c = 0; c < MAPSIZE; c++) {
        int res = calc_from_point(MAPSIZE, c, 'u');
        if (res > max_energy) {
            max_energy = res;
        }
    }

    printf("Result: %d", max_energy);
    return 0;
}

void read_data_from_file(char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error occured while opening input file");
        return;
    }

    int r = 0;
    while (!feof(fp)) {
        if (fgets(buffer, 256, fp)) {
            for (int c = 0; c < MAPSIZE; ++c) {
                map[r][c].type = buffer[c];
                map[r][c].v_from_left = 0;
                map[r][c].v_from_right = 0;
                map[r][c].v_from_top = 0;
                map[r][c].v_from_bottom = 0;
            }
        }

        r++;
    }

    fclose(fp);
    return;
}

void draw_map() {
    printf("\nMap\n");
    for (int r = 0; r < MAPSIZE; ++r) {
        for (int c = 0; c < MAPSIZE; ++c) {
            printf("%c", map[r][c].type);
        }
        printf("\n");
    }
    printf("\n");
}

void draw_energy_map() {
    printf("\nEnergized Map\n");
    for (int r = 0; r < MAPSIZE; ++r) {
        for (int c = 0; c < MAPSIZE; ++c) {
            if (map[r][c].v_from_bottom || map[r][c].v_from_top || map[r][c].v_from_left ||
                map[r][c].v_from_right) {
                printf("#");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int move_light_beam_from_point(int n) {
    // move beam to right direction
    switch (beams[n].dir) {
        case 'r':
            beams[n].col++;
            break;
        case 'l':
            beams[n].col--;
            break;
        case 'u':
            beams[n].row--;
            break;
        case 'd':
            beams[n].row++;
            break;
    }
    // disable beam if pass maps border
    if (beams[n].row < 0 || beams[n].col < 0 || beams[n].row >= MAPSIZE || beams[n].col >= MAPSIZE) {
        beams[n].active = 0;
        return 0;
    }

    int r = beams[n].row;
    int c = beams[n].col;
    // check and mark visited points
    switch (beams[n].dir) {
        case 'r':
            if (map[r][c].v_from_left) {
                beams[n].active = 0;
                return 0;
            }

            map[r][c].v_from_left = 1;
            break;
        case 'l':
            if (map[r][c].v_from_right) {
                beams[n].active = 0;
                return 0;
            }
            map[r][c].v_from_right = 1;
            break;
        case 'u':
            if (map[r][c].v_from_bottom) {
                beams[n].active = 0;
                return 0;
            }
            map[r][c].v_from_bottom = 1;
            break;
        case 'd':
            if (map[r][c].v_from_top) {
                beams[n].active = 0;
                return 0;
            }
            map[r][c].v_from_top = 1;
            break;
    }

    switch (map[r][c].type) {
        case '.':
            break;
        case '\\':
            switch (beams[n].dir) {
                case 'r':
                    beams[n].dir = 'd';
                    break;
                case 'l':
                    beams[n].dir = 'u';
                    break;
                case 'u':
                    beams[n].dir = 'l';
                    break;
                case 'd':
                    beams[n].dir = 'r';
                    break;
            }
            break;
        case '/':
            switch (beams[n].dir) {
                case 'r':
                    beams[n].dir = 'u';
                    break;
                case 'l':
                    beams[n].dir = 'd';
                    break;
                case 'u':
                    beams[n].dir = 'r';
                    break;
                case 'd':
                    beams[n].dir = 'l';
                    break;
            }
            break;

        case '|':
            switch (beams[n].dir) {
                case 'r':
                case 'l':
                    beams[n].dir = 'u';
                    beams[cnt_beams].row = beams[n].row;
                    beams[cnt_beams].col = beams[n].col;
                    beams[cnt_beams].dir = 'd';
                    beams[cnt_beams].active = 1;
                    cnt_beams++;
                    break;
                case 'u':
                case 'd':
                    break;
            }
            break;

        case '-':
            switch (beams[n].dir) {
                case 'u':
                case 'd':
                    beams[n].dir = 'l';
                    beams[cnt_beams].row = beams[n].row;
                    beams[cnt_beams].col = beams[n].col;
                    beams[cnt_beams].dir = 'r';
                    beams[cnt_beams].active = 1;
                    cnt_beams++;
                    break;
                case 'r':
                case 'l':
                    break;
            }
            break;
    }

    return 0;
}

int count_energy() {
    // printf("\nTotal energy\n");
    int sum = 0;
    for (int r = 0; r < MAPSIZE; ++r) {
        for (int c = 0; c < MAPSIZE; ++c) {
            if (map[r][c].v_from_bottom || map[r][c].v_from_top || map[r][c].v_from_left ||
                map[r][c].v_from_right) {
                sum++;
            }
        }
    }

    return sum;
}

int calc_from_point(int r, int c, char dir) {
    for (int row = 0; row < MAPSIZE; ++row) {
        for (int col = 0; col < MAPSIZE; ++col) {
            map[row][col].v_from_bottom = 0;
            map[row][col].v_from_top = 0;
            map[row][col].v_from_left = 0;
            map[row][col].v_from_right = 0;
        }
    }

    beam_t start_beam;

    start_beam.row = r;
    start_beam.col = c;
    start_beam.dir = dir;
    start_beam.active = 1;
    beams[0] = start_beam;
    cnt_beams = 1;
    int have_active_beams = 1;
    while (have_active_beams) {
        have_active_beams = 0;
        for (int n = 0; n < cnt_beams; ++n) {
            if (beams[n].active) {
                have_active_beams = 1;
                move_light_beam_from_point(n);
            }
        }
    }

    // draw_energy_map();
    return count_energy();
}