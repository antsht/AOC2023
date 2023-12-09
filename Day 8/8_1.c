#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char buffer[256];

#define DIR_COUNT 263 
#define MAPS_COUNT 762

int directions[DIR_COUNT] = {1, 2, 2, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 2, 1, 2, 2, 2, 1, 2, 2, 1, 2, 2, 2, 1, 2, 2, 1, 2, 2, 2, 1, 1, 2, 2, 2, 1, 2, 2, 1, 2, 1, 2, 2, 2, 1, 2, 2, 1, 2, 2, 2, 1, 1, 2, 1, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 1, 1, 2, 1, 2, 1, 2, 2, 2, 1, 2, 2, 1, 2, 2, 1, 2, 2, 1, 2, 1, 2, 2, 2, 1, 2, 2, 1, 2, 2, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 2, 1, 2, 1, 1, 2, 1, 2, 2, 1, 2, 1, 2, 1, 2, 2, 1, 2, 2, 2, 1, 1, 1, 2, 2, 1, 2, 2, 2, 1, 1, 2, 2, 1, 2, 1, 2, 1, 2, 2, 2, 1, 2, 1, 2, 2, 2, 1, 1, 2, 1, 1, 1, 2, 2, 2, 1, 1, 1, 2, 2, 1, 1, 2, 1, 1, 2, 2, 1, 1, 2, 1, 2, 2, 2, 1, 2, 1, 2, 2, 1, 2, 2, 1, 1, 2, 2, 1, 2, 1, 1, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 1, 2, 2, 2, 1, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 1, 2, 2, 1, 2, 2, 2, 1, 1, 2, 1, 2, 1, 1, 2, 1, 1, 2, 2, 2, 2};


typedef struct {
    int point;
    int l_dest;    
    int r_dest;
    char point_c[3];
    char l_dest_c[3];
    char r_dest_c[3];
} map_t;    

map_t maps[MAPS_COUNT];

void read_maps_from_file(char * filename);
int get_dir_index(char dir_c[3]);
int a_in_b(int a[6], int b[6]);

int main()
{
    read_maps_from_file("C:\\c_pr\\8.txt");
    int tmp_index = 0;
    for( int i = 0; i < MAPS_COUNT; ++i)
    {
        maps[i].l_dest = get_dir_index(maps[i].l_dest_c);
        maps[i].r_dest = get_dir_index(maps[i].r_dest_c);
        //printf("Point: %d ( %d , %d )\n", maps[i].point, maps[i].l_dest,maps[i].r_dest);
    }


    int current_point[6] = {1, 22, 71, 242, 383, 710};
    int end_point[6] = {323, 399, 423, 492, 657, 762};
    long long steps = 0;
    int matches = a_in_b(current_point,end_point);
    while ( matches != 6)
    {
        for(int i = 0; i < 6; ++i)
        {
            //printf("%d:%d ", i+1,current_point[i] );
        if (directions[steps % DIR_COUNT] == 1)
            current_point[i] = maps[current_point[i] - 1].l_dest;
        if (directions[steps % DIR_COUNT] == 2)
            current_point[i] = maps[current_point[i] - 1].r_dest;
        }
        steps++;
        matches = a_in_b(current_point,end_point);
        if (matches > 2)
            printf("\n Matches: %d Steps: %ld\n",matches, steps);

    }
    printf("Steps: %lld", steps);
    return 0;
}

int a_in_b(int a[6], int b[6])
{
    int matches = 0;
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            if (a[i] == b[j])
                matches++;
        }
    }
    return matches;
}

int get_dir_index(char dir_c[3])
{
    for( int i = 0; i < MAPS_COUNT; ++i)
    {
        if (strncmp(dir_c, maps[i].point_c, 3) == 0)
            return maps[i].point;
    }
    return 0;
}

void read_maps_from_file(char * filename)
{
    FILE * fp = fopen(filename, "r");
    if(fp==NULL)
        {
            perror("Error occured while opening input file");
            return;
        }
        
    int i = 0; 
    while(!feof (fp)) {
    if (fgets(buffer, 256, fp))
        {
            char sep [2]=" ";
            char *istr;
            istr = strtok (buffer,sep);
            maps[i].point = atoi(istr);
            istr = strtok (NULL,sep); 
            maps[i].point_c[0] = istr[0];            
            maps[i].point_c[1] = istr[1];
            maps[i].point_c[2] = istr[2];  
            
            istr = strtok (NULL,sep); 
            maps[i].l_dest_c[0] = istr[0];            
            maps[i].l_dest_c[1] = istr[1];
            maps[i].l_dest_c[2] = istr[2];  
            
            istr = strtok (NULL,sep); 
            maps[i].r_dest_c[0] = istr[0];            
            maps[i].r_dest_c[1] = istr[1];
            maps[i].r_dest_c[2] = istr[2];  

            i++;            
            //getchar();
        }
    }

    fclose(fp);
    return;
}