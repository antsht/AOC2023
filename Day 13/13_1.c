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

map_t maps[100];
int maps_cnt = 0;


void read_data_from_file(char * filename);
void draw_map(int n);
int find_max_v_m_line(int map_n);
int find_max_h_m_line(int map_n);
int cmp2rows(int map_n, int r1, int r2);
int cmp2cols(int map_n, int c1, int c2);


int main()
{
    read_data_from_file("13.txt");
    for (int n = 0; n < maps_cnt; ++n)
        draw_map(n);
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