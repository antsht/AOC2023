#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char buffer[256];

#define MAXROWS 20
#define MAXCOLS 20

typedef struct {
    int data[MAXROWS][MAXCOLS];
    int rows;
    int cols;
} map_t;

map_t maps[150];
int maps_cnt = 0;


void read_data_from_file(char * filename);
void draw_map(int n);
int find_max_v_m_line(int map_n);
int find_max_h_m_line(int map_n);
int compare_2_rows(int map_n, int r1, int r2);
int compare_2_cols(int map_n, int c1, int c2);
int check_mirror_columns(int map_n, int col);
int check_mirror_rows(int map_n, int row);


int main()
{
    read_data_from_file("13.txt");

    long sum = 0;
    long sum_new = 0;
    for (int n = 0; n < maps_cnt; ++n)
    {
        draw_map(n);
        int result_mirror;
        int res_r = 0;
        int res_c = 0;
        for (int i = 0; i < maps[n].cols - 1; ++i)
        {
            result_mirror = check_mirror_columns(n, i);
            
            if (result_mirror == 1)
            {
                printf("Map %d: checking mirror column %d: res = %d\n", n, i + 1, result_mirror);
                sum += (i + 1);
                res_c = i;
            }

        }
        for (int i = 0; i < maps[n].rows - 1; ++i)
        {
            result_mirror = check_mirror_rows(n, i);
            
            if (result_mirror == 1)
            {
                printf("Map %d: checking mirror row %d: res = %d\n", n, i + 1, result_mirror);
                sum +=  (i + 1) * 100;
                res_r = i;
            }
        }
        int exit_flag = 0;
        for (int r = 0; r <= maps[n].rows; ++r)
        {
            if (exit_flag)
                break;
            for (int c = 0; c < maps[n].cols; ++c)
            {
                if (exit_flag)
                   break;

                maps[n].data[r][c] = maps[n].data[r][c] ^ 1;
                /////
                for (int i = 0; i < maps[n].cols - 1; ++i)
                {
                    result_mirror = check_mirror_columns(n, i);
                    if (result_mirror == 1 && i != res_c)
                    {
                        draw_map(n);      
                        printf("Inverted R: %d C: %d\n", r, c);                  
                        printf("Map %d: checking mirror column %d: res = %d\n", n, i + 1, result_mirror);
                        sum_new += (i + 1);
                        exit_flag = 1;
                    }

                }
                for (int i = 0; i < maps[n].rows - 1; ++i)
                {
                    result_mirror = check_mirror_rows(n, i);
                    if (result_mirror == 1 && i != res_r)
                    {
                        draw_map(n);          
                        printf("Inverted R: %d C: %d\n", r, c);                    
                        printf("Map %d: checking mirror row %d: res = %d\n", n, i + 1, result_mirror);
                        sum_new += (i + 1) * 100;
                        exit_flag = 1;
                    }
                }

                /////
                maps[n].data[r][c] = maps[n].data[r][c] ^ 1;

            }
        }
        if (exit_flag == 0 && res_c > 0)
        {
            sum_new += res_c + 1 ;
        }
        if (exit_flag == 0 && res_r > 0)
        {
            sum_new += (res_r + 1) * 100;
        }


    }

    printf("Total sum: %ld\n", sum);
    printf("Total new sum: %ld\n", sum_new);
    

    //NOT FINISHED YET
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
        
    int n = 0;
    maps[0].rows = 0;
    maps[0].cols = 0;
    while(!feof (fp)) 
    {
        if (fgets(buffer, 256, fp))
        {
            
            if (strlen(buffer) < 2)
            {
                n++;
                maps[n].rows = 0;
                maps[n].cols = 0;
            }
            else
            {
                
                int c = 0;
                while (buffer[c] != '\0' && buffer[c] != '\n')
                {
                    maps[n].data[maps[n].rows][c] = (buffer[c] == '.') ? 0 : 1;
                    c++;
                }
                maps[n].rows++;
                maps[n].cols = c;
            }          
            //getchar();
        }
    }  
    maps_cnt = n + 1;
    fclose(fp);
    return;
}


void draw_map(int n)
{
    printf("Map %d:\n__________\n", n);
    for (int r = 0; r < maps[n].rows; ++r)
    {
        for (int c = 0; c < maps[n].cols; ++c)
        {
                printf("%d ", maps[n].data[r][c]);
        }
        printf("\n");
    }    
    printf("\n");
}

int compare_2_rows(int map_n, int r1, int r2) {
    // Check if the map number is valid
    if (map_n < 0 || map_n >= maps_cnt) {
        fprintf(stderr, "Invalid map number\n");
        return 0; // Return an error code or handle it as appropriate
    }

    // Check if the row numbers are valid
    if (r1 < 0 || r1 >= maps[map_n].rows || r2 < 0 || r2 >= maps[map_n].rows) {
        fprintf(stderr, "Invalid row numbers\n");
        return 0; // Return an error code or handle it as appropriate
    }

    // Compare the two rows
    for (int col = 0; col < maps[map_n].cols; col++) {
        if (maps[map_n].data[r1][col] != maps[map_n].data[r2][col]) {
            return 0; // Rows are not equal
        }
    }

    return 1; // Rows are equal
}

int compare_2_cols(int map_n, int c1, int c2) {
    // Check if the map number is valid
    if (map_n < 0 || map_n >= maps_cnt) {
        fprintf(stderr, "Invalid map number\n");
        return 0; // Return an error code or handle it as appropriate
    }

    // Check if the column numbers are valid
    if (c1 < 0 || c1 >= maps[map_n].cols || c2 < 0 || c2 >= maps[map_n].cols) {
        fprintf(stderr, "Invalid column numbers\n");
        return 0; // Return an error code or handle it as appropriate
    }

    // Compare the two columns
    for (int row = 0; row < maps[map_n].rows; row++) {
        if (maps[map_n].data[row][c1] != maps[map_n].data[row][c2]) {
            return 0; // Columns are not equal
        }
    }

    return 1; // Columns are equal
}

int check_mirror_columns(int map_n, int col) {
    // Check if the map number is valid
    if (map_n < 0 || map_n >= maps_cnt) {
        fprintf(stderr, "Invalid map number\n");
        return 0; // Return an error code or handle it as appropriate
    }

    // Check if the column index is valid
    if (col < 0 || col >= maps[map_n].cols) {
        fprintf(stderr, "Invalid column index\n");
        return 0; // Return an error code or handle it as appropriate
    }

    // Iterate over the columns to the left and right
    for (int offset = 1; (col - offset + 1) >= 0 && (col + offset) < maps[map_n].cols; offset++) {
        int left_col = col - offset + 1;
        int right_col = col + offset;

        // Check if the columns are mirrors
        if (!compare_2_cols(map_n, left_col, right_col)) {
            return 0; // Columns are not mirrors
        }
    }

    return 1; // Columns are mirrors
}

int check_mirror_rows(int map_n, int row) {
    // Check if the map number is valid
    if (map_n < 0 || map_n >= maps_cnt) {
        fprintf(stderr, "Invalid map number\n");
        return 0; // Return an error code or handle it as appropriate
    }

    // Check if the row index is valid
    if (row < 0 || row >= maps[map_n].rows) {
        fprintf(stderr, "Invalid row index\n");
        return 0; // Return an error code or handle it as appropriate
    }

    // Iterate over the rows above and below
    for (int offset = 1; (row - offset + 1) >= 0 && (row + offset) < maps[map_n].rows; offset++) {
        int above_row = row - offset + 1;
        int below_row = row + offset;

        // Check if the rows are mirrors
        if (!compare_2_rows(map_n, above_row, below_row)) {
            return 0; // Rows are not mirrors
        }
    }

    return 1; // Rows are mirrors
}