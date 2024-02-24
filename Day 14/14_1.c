#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char buffer[256];

#define ROWS 10
#define COLS 10

char map[ROWS][COLS];


void read_data_from_file(char * filename);
void draw_map();
void move_O_to_north();
long count_load();

int main()
{
    read_data_from_file("14t.txt");
    //for (int n = 0; n < maps_cnt; ++n)
    //    draw_map(n);
    draw_map();


    move_O_to_north();
    draw_map();

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
                    map[row][col] = map[row - 1][col];
                    map[--row][col] = 'O';
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

