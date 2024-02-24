#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

char buffer[256];

#define COLS_COUNT 140 
#define ROWS_COUNT 140

typedef struct {
    int is_star;
    int distance;
} galaxy_node_t;    

typedef struct {
    int row;
    int col;
} star_t; 


galaxy_node_t galaxy[COLS_COUNT][ROWS_COUNT];

galaxy_node_t expanded_galaxy[200][200];
star_t stars[1000];
int stars_cnt=0;

void read_data_from_file(char * filename);
void draw_galaxy_map();
void count_empty_rows_cols();
void fill_expanded_galaxy();
void draw_expanded_galaxy_map();
void count_stars();
long long calc_distance(star_t star1, star_t star2);

int stars_in_row[ROWS_COUNT];
int stars_in_col[COLS_COUNT];

int empty_rows_cnt = 0;
int empty_cols_cnt = 0;

int exp_rows = ROWS_COUNT;
int exp_cols = COLS_COUNT;

int main()
{
    read_data_from_file("11.txt");
    
    //draw_galaxy_map();
    count_empty_rows_cols();
    printf("Rows to expand: %d Cols to expand: %d\n", empty_rows_cnt, empty_cols_cnt);
    exp_rows += empty_rows_cnt;
    exp_cols += empty_cols_cnt;
    
    printf("Rows in expanded: %d Cols in expanded: %d\n", exp_rows, exp_cols);

    fill_expanded_galaxy();
    
    //draw_expanded_galaxy_map();
    count_stars();
    long long distance_sum = 0;
    for (int s1 = 0; s1 < stars_cnt - 1; ++s1)
    {
        for (int s2 = s1; s2 < stars_cnt; ++s2)
        {
            distance_sum += calc_distance(stars[s1], stars[s2]);
        }
    }
    
    printf("Stars: %d\n", stars_cnt);
    
    printf("Sum of distances: %lld\n", distance_sum);

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
    while(!feof (fp)) {
    if (fgets(buffer, 256, fp))
        {
            for (int c = 0; c < COLS_COUNT; ++c)
            {
                galaxy[r][c].distance = 1;
                switch (buffer[c])
                {
                    case '.':
                        galaxy[r][c].is_star = 0;
                        break;
                    case '#':
                        galaxy[r][c].is_star = 1;
                        break;
                }

            }
            r++;            
            //getchar();
        }
    }

    fclose(fp);
    return;
}


void draw_galaxy_map()
{
    for (int r = 0; r < ROWS_COUNT; ++r)
    {
        for (int c = 0; c < COLS_COUNT; ++c)
        {
            if (galaxy[r][c].is_star)
                printf("*");
            else
                printf(".");
        }
        printf("\n");
    }
}

void draw_expanded_galaxy_map()
{
    for (int r = 0; r < exp_cols; ++r)
    {
        for (int c = 0; c < exp_cols; ++c)
        {
            if (expanded_galaxy[r][c].is_star)
                printf("*");
            else            
                printf(".");
        }
        printf("\n");
    }
}

void count_empty_rows_cols()
{
    for (int r = 0; r < ROWS_COUNT; ++r)
    {
        for (int c = 0; c < COLS_COUNT; ++c)
        {
            if (galaxy[r][c].is_star)
                {
                    stars_in_row[r]++;
                    stars_in_col[c]++;
                }
        }
    }
    for (int r = 0; r < ROWS_COUNT; ++r)
    {
        if (stars_in_row[r] == 0)
            empty_rows_cnt++;
    }
    for (int c = 0; c < COLS_COUNT; ++c)
    {
        if (stars_in_col[c] == 0)
            empty_cols_cnt++;
    }
}

void fill_expanded_galaxy()
{
    int s_row = 0;
    int s_col = 0;
    int t_row = 0;
    int t_col = 0;

    while (s_row < ROWS_COUNT)
    {
        while (s_col < COLS_COUNT)
        {
            expanded_galaxy[t_row][t_col].is_star = galaxy[s_row][s_col].is_star;
            expanded_galaxy[t_row][t_col].distance = 1;
            if (stars_in_col[s_col] == 0)
            {
                expanded_galaxy[t_row][t_col+1].is_star = 0;
                expanded_galaxy[t_row][t_col+1].distance = 999999;
            }
            if (stars_in_row[s_row] == 0)
            {
                expanded_galaxy[t_row+1][t_col].is_star = 0;
                expanded_galaxy[t_row+1][t_col].distance = 999999;
            }
            if (stars_in_col[s_col] == 0)
                t_col++;  
            t_col++;
            s_col++;          
        }
        s_col = 0;
        t_col = 0;
        if (stars_in_row[s_row] == 0)
            t_row++;   
        t_row++;
        s_row++;
    }
}

void count_stars()
{
    for (int r = 0; r < exp_cols; ++r)
    {
        for (int c = 0; c < exp_cols; ++c)
        {
            if (expanded_galaxy[r][c].is_star)
            {
                //printf("r %d c %d \n",r,c);
                stars[stars_cnt].row = r;
                stars[stars_cnt].col = c;
                stars_cnt++;
            }
        }
    }
}

long long calc_distance(star_t star1, star_t star2)
{
    long long distance = 0;
    if (star1.row == star2.row && star1.col == star2.col)
        return 0;
    if (star1.row <= star2.row)
    {
        for (int t = star1.row; t < star2.row; t++)
            distance += expanded_galaxy[t][star1.col].distance;
    }
    else
    {
        for (int t = star2.row; t < star1.row; t++)
            distance += expanded_galaxy[t][star1.col].distance;
    }
    if (star1.col <= star2.col)
    {
    for (int t = star1.col; t < star2.col; t++)
        distance += expanded_galaxy[star1.row][t].distance;
    }
    else
    {
    for (int t = star2.col; t < star1.col; t++)
        distance += expanded_galaxy[star1.row][t].distance;
    }

    //printf("Star1: %d %d Star2: %d %d Dist: %lld\n", star1.row, star1.col, star2.row, star2.col, distance );
    return distance;
}