#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char buffer[256];

#define COLS_COUNT 142 
#define ROWS_COUNT 142

typedef struct {
    int m_up;
    int m_down;
    int m_left;
    int m_right;
    char * symbol;
    int visited;
} map_node_t;    

typedef struct {
    int row;
    int col;
} point_t; 

point_t start_point;
point_t current_point1;
point_t current_point2;

map_node_t map[ROWS_COUNT][COLS_COUNT];

void read_data_from_file(char * filename);
void draw_map();
point_t make_move(point_t point_from);
void print_point_data(point_t point);
int steps = 1;

int main()
{
    read_data_from_file("10.txt");
    
    current_point1 = make_move(start_point);
    current_point2 = make_move(start_point);

    do {
        current_point1 = make_move(current_point1);
        current_point2 = make_move(current_point2);
        steps++;
        //draw_map();
        //getchar();
    } while (current_point2.row != 0 && current_point2.col != 0);
    //draw_map();
    //printf("\n\nSteps: %d \n\n", steps);
    unsigned int inside_flag = 0;
    int inside_cnt = 0;
    for (int r = 1; r < ROWS_COUNT - 1; ++r)
    {
        inside_flag = 0;
        for (int c = 1; c < COLS_COUNT - 1; ++c)
        {
            if (map[r][c].visited)
                if (inside_flag == 0)
                    inside_flag = 1;
                else
                    inside_flag = 0;
            else
            {
                    map[r][c].symbol = ".";
                    if (inside_flag == 1)
                        {
                            map[r][c].symbol = "*";
                            inside_cnt++;
                        }
            }
        }
    }
    draw_map();
    printf("Inside: %d", inside_cnt);

    return 0;
}

/*
| is a vertical pipe connecting north and south.
- is a horizontal pipe connecting east and west.
L is a 90-degree bend connecting north and east.
J is a 90-degree bend connecting north and west.
7 is a 90-degree bend connecting south and west.
F is a 90-degree bend connecting south and east.
. is ground; there is no pipe in this tile.
S is the starting position of the animal; there is a pipe on this tile, but your sketch doesn't show what shape the pipe has.
*/
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
                //map[r][c].symbol = buffer[c];
                map[r][c].visited = 0;
                switch (buffer[c])
                {
                    case '.':
                        map[r][c].m_up = 0;
                        map[r][c].m_down = 0;
                        map[r][c].m_left = 0;
                        map[r][c].m_right = 0;                       
                        map[r][c].symbol = "░";
                        break;
                    case '|':
                        map[r][c].m_up = 1;
                        map[r][c].m_down = 1;
                        map[r][c].m_left = 0;
                        map[r][c].m_right = 0;                        
                        map[r][c].symbol = "│";
                        break;
                    case '-':
                        map[r][c].m_up = 0;
                        map[r][c].m_down = 0;
                        map[r][c].m_left = 1;
                        map[r][c].m_right = 1;
                        map[r][c].symbol = "─";
                        break;
                    case 'L':
                        map[r][c].m_up = 1;
                        map[r][c].m_down = 0;
                        map[r][c].m_left = 0;
                        map[r][c].m_right = 1;
                        map[r][c].symbol = "└";
                        break;
                    case 'J':
                        map[r][c].m_up = 1;
                        map[r][c].m_down = 0;
                        map[r][c].m_left = 1;
                        map[r][c].m_right = 0;
                        map[r][c].symbol = "┘";
                        break;
                    case '7':
                        map[r][c].m_up = 0;
                        map[r][c].m_down = 1;
                        map[r][c].m_left = 1;
                        map[r][c].m_right = 0;
                        map[r][c].symbol = "┐";
                        break;
                    case 'F':
                        map[r][c].m_up = 0;
                        map[r][c].m_down = 1;
                        map[r][c].m_left = 0;
                        map[r][c].m_right = 1;
                        map[r][c].symbol = "┌";
                        break;
                    case 'S':
                        start_point.row = r;
                        start_point.col = c;                        
                        map[r][c].visited = 1;
                        map[r][c].symbol = "S";
                        break;
                }

            }
            r++;            
            //getchar();
        }
        if (map[start_point.row][start_point.col - 1].m_right == 1)
            map[start_point.row][start_point.col].m_left = 1;
        if (map[start_point.row][start_point.col + 1].m_left == 1)
            map[start_point.row][start_point.col].m_right = 1;
        if (map[start_point.row - 1][start_point.col].m_down == 1)
            map[start_point.row][start_point.col].m_up = 1;
        if (map[start_point.row + 1][start_point.col].m_up == 1)
            map[start_point.row][start_point.col].m_down = 1;
    }

    fclose(fp);
    return;
}


void draw_map()
{
    for (int r = 0; r < ROWS_COUNT; ++r)
    {
        for (int c = 0; c < COLS_COUNT; ++c)
        {
            if (!map[r][c].visited)
                printf("%s", map[r][c].symbol);
            else
                printf("\033[38:5:9m%s\033[38:5:15m", map[r][c].symbol);
        }
        printf("\n");
    }
}

point_t make_move(point_t point_from)
{
    point_t next_point;
    next_point.row = 0;
    next_point.col = 0;

    if (map[point_from.row][point_from.col].m_up == 1 && map[point_from.row - 1][point_from.col].visited == 0)
    {
        next_point.row = point_from.row - 1;
        next_point.col = point_from.col;
        map[next_point.row][next_point.col].visited = 1;
    }
    else if (map[point_from.row][point_from.col].m_down == 1 && map[point_from.row + 1][point_from.col].visited == 0)
    {
        next_point.row = point_from.row + 1;
        next_point.col = point_from.col;
        map[next_point.row][next_point.col].visited = 1;
    }
    else if (map[point_from.row][point_from.col].m_right == 1 && map[point_from.row][point_from.col+1].visited == 0)
    {
        next_point.row = point_from.row;
        next_point.col = point_from.col + 1;
        map[next_point.row][next_point.col].visited = 1;
    }
    else if (map[point_from.row][point_from.col].m_left == 1 && map[point_from.row][point_from.col-1].visited == 0)
    {
        next_point.row = point_from.row;
        next_point.col = point_from.col - 1;
        map[next_point.row][next_point.col].visited = 1;
    }
    //printf("Step: %d \n", steps);
    //print_point_data(point_from);
    //print_point_data(next_point);
    return next_point;
}


void print_point_data(point_t point)
{
    printf("___________\n");
    printf("Point r: %d c: %d\n", point.row, point.col);
    printf("*%d*\n", map[point.row][point.col].m_up);    
    printf("%d*%d\n", map[point.row][point.col].m_left, map[point.row][point.col].m_right);
    printf("*%d*\n", map[point.row][point.col].m_down);
    printf("___________\n");

}