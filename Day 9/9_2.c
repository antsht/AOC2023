#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char buffer[256];

#define COL_COUNT 21 
#define ROWS_COUNT 200

typedef struct {
    long long data[COL_COUNT];
    long long prediction;
    long long history;
} record_t;    

record_t records[ROWS_COUNT];

void read_data_from_file(char * filename);

long long calculate_next(long long * data_row, int data_row_length);

long long calculate_prev(long long * data_row, int data_row_length);

int main()
{
    read_data_from_file("9.txt");
    long long sum = 0;
    for (int i = 0; i < ROWS_COUNT; ++i)
    {
        records[i].history = calculate_prev(records[i].data, COL_COUNT);

        sum += records[i].history;
        
    }

    printf("Sum: %lld", sum);

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
        
    int i = 0; 
    while(!feof (fp)) {
    if (fgets(buffer, 256, fp))
        {
            char sep [2]=" ";
            char *istr;
            istr = strtok (buffer,sep);
            for (int col = 0; col < COL_COUNT; ++col)
            {
                records[i].data[col] = atoi(istr);
                istr = strtok (NULL,sep); 
                printf("%lld ", records[i].data[col]);
            }
            printf("\n");
            long long next = calculate_next(records[i].data, COL_COUNT);
            printf("Next value: %lld\n", next);
            i++;            
            //getchar();
        }
    }

    fclose(fp);
    return;
}



long long calculate_next(long long * data_row, int data_row_length)
{
    int all_zeroes = 1;
    for (int i = 0; i < data_row_length; ++i)
        if (data_row[i] != 0)
            all_zeroes = 0;
    if (all_zeroes)
        return 0;
    int new_length = data_row_length - 1;
    long long * new_data_row = malloc(new_length * sizeof(long long));
    for (int i = 0; i < new_length; ++i)
        new_data_row[i] = data_row[i+1] - data_row[i];
    int next = data_row[data_row_length - 1] + calculate_next(new_data_row, new_length);
    free(new_data_row);
    return next;
}

long long calculate_prev(long long * data_row, int data_row_length)
{
    int all_zeroes = 1;
    for (int i = 0; i < data_row_length; ++i)
        if (data_row[i] != 0)
            all_zeroes = 0;
    if (all_zeroes)
        return 0;
    int new_length = data_row_length - 1;
    long long * new_data_row = malloc(new_length * sizeof(long long));
    for (int i = 0; i < new_length; ++i)
        new_data_row[i] = data_row[i+1] - data_row[i];
    int prev = data_row[0] - calculate_prev(new_data_row, new_length);
    free(new_data_row);
    return prev;
}