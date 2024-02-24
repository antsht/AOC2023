#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char buffer[256];

#define ROWS 100
#define COLS 100

char map[ROWS][COLS];

char map_tmp[100000][ROWS][COLS];
long tmp_cnt = 1;


void read_data_from_file(char * filename);
void draw_map();
void move_O_to_north();
void move_O_to_west();
void move_O_to_south();
void move_O_to_east();
long count_load();
void savemap();
int compare_arrays(long n);

int main()
{
    read_data_from_file("14.txt");
    //for (int n = 0; n < maps_cnt; ++n)
    //    draw_map(n);
    draw_map();
        if (compare_arrays(0) == 1)
        printf("Full cycle on %d steps\n\n", 0);
    
    int c_found = 0;
    for (long i = 0; i < 1000000000; ++i)
    {
        if (((i + 1) % 10000) == 0)
        {
            printf("%ld of 100000 \n\n", (i + 1) / 10000);
            draw_map();
        }
        move_O_to_north();
        move_O_to_west();
        move_O_to_south();
        move_O_to_east();
        savemap();
        if (c_found == 0)
        {
            for (int n = 0; n < tmp_cnt - 1 ; ++n)
            {
                if (c_found == 0 && compare_arrays(n) == 1)
                {
                    printf("Full cycle on %ld %ld steps\n\n", i+1, i+1-n);
                    getchar();
                    c_found = i+1-n;
                    i = 1000000000 - (1000000000-i) % c_found;
                }
            }
        }
        
    }
    printf("\n\nTotal Load: %ld\n\n", count_load());

    return 0;
}


void read_data_from_file(char * filename)
{
    FILE * fp = fopen(filename, "r");
    if(fp==NULL)
    {
        perror("Error occured while opening input file");
        return;
    }
        
    int r = 0;
    while(!feof (fp)) 
    {
        if (fgets(buffer, 256, fp))
        {
            for (int c = 0; c < COLS; ++c)
            {
                map[r][c] = buffer[c];
                map_tmp[0][r][c] = buffer[c];
            }
        }          
        
        r++;
    }  
   
    fclose(fp);
    return;
}


void draw_map()
{
    printf("Map\n");
    for (int r = 0; r < ROWS; ++r)
    {
        for (int c = 0; c <COLS; ++c)
        {
            printf("%c", map[r][c]);
        }
        printf("\n");
    }    
    printf("\n");
}

void move_O_to_north() {
    for (int col = 0; col < COLS; col++) {
        for (int row = 0; row < ROWS; row++) {
            if (map[row][col] == 'O') {
                // Move 'O' upwards until it reaches a border or '#'
                while (row > 0 && (map[row - 1][col] == '.')) {
                    map[row][col] = '.';
                    map[--row][col] = 'O';
                }
            }
        }
    }
}

void move_O_to_east() {
    for (int row = 0; row < ROWS; row++) {
        for (int col = COLS - 1; col >= 0; col--) {
            if (map[row][col] == 'O') {
                while (col < COLS - 1 && (map[row][col + 1] == '.')) {
                    map[row][col] = '.';
                    map[row][++col] = 'O';
                }
            }
        }
    }
}
void move_O_to_south() {
    for (int col = 0; col < COLS; col++) {
        for (int row = ROWS - 1; row >= 0; row--) {
            if (map[row][col] == 'O') {
                while (row < ROWS - 1 && (map[row + 1][col] == '.')) {
                    map[row][col] = '.';
                    map[++row][col] = 'O';
                }
            }
        }
    }
}

void move_O_to_west() {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (map[row][col] == 'O') {
                while (col > 0 && (map[row][col - 1] == '.')) {
                    map[row][col] = '.';
                    map[row][--col] = 'O';
                }
            }
        }
    }
}

long count_load()
{
    long sum = 0;
    for (int r = 0; r < ROWS; ++r)
    {
        for (int c = 0; c <COLS; ++c)
        {
            if (map[r][c] == 'O')
            {
                sum += (ROWS - r);
            }
        }
    }   
    return sum; 
}

int compare_arrays(long n) {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (map[row][col] != map_tmp[n][row][col]) {
                // If any element is different, arrays are not equal
                return 0;
            }
        }
    }
    return 1;
}

void savemap()
{
    for (int r = 0; r < ROWS; ++r)
    {
        for (int c = 0; c <COLS; ++c)
        {
            map_tmp[tmp_cnt][r][c] = map[r][c];
        }
    }   
    tmp_cnt++;
    return; 
}