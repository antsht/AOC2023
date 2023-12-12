#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uthash.h"

char buffer[256];

#define MAX_REC_COUNT 1000
#define MAX_COL 31
#define MAX_MAP_COL 7

char records[MAX_REC_COUNT][MAX_COL];
char rawmap[MAX_REC_COUNT][30];
int map[MAX_REC_COUNT][MAX_MAP_COL];
int rec_cnt = 0;
int permutations[MAX_REC_COUNT];
char tmprecords[100000][MAX_COL];
int cur_matches_cnt;

struct string_entry {
    char str[MAX_COL];    
    UT_hash_handle hh;
};

struct string_entry *strings = NULL;

void read_records_from_file(char * filename);
void print_records();
void generate_strings(char* current, int target_length, int current_length, int row_n);

void generate_strings_optimized(char* current, int target_length, int current_length, int row_n);
int strpatcmp(char * pattern, char * strtocompare);
void clear_tmp();
int check_perm(char * strtocheck);

int main()
{
    read_records_from_file("12.txt");
    //print_records();

    //init counter
    for (int i = 0; i < MAX_REC_COUNT; ++i)
    {    
        permutations[i] = 0;
    }
    
    long sum = 0;
    
    for (int row_n = 0; row_n < MAX_REC_COUNT; ++row_n)
    {
        int i = 0;
        while (records[row_n][i] != 0)
        {    
            i++;
        }

        int curr_templ_len = i;
        
        char tmp[30];
        i = 0;    
        int j = 0;
        while (map[row_n][i] != -1)
        {
            for (int t = 0; t < map[row_n][i]; t++)
                {
                tmp[j] = '#';
                j++;
                }
                tmp[j] = '.';
                j++;
                i++;
        }
        tmp[j-1] = '\0';

        
        printf("base case template %d: %s\n", row_n + 1, tmp);
        int target_length = curr_templ_len;  
        char current[curr_templ_len + 1];
        strcpy(current, tmp);
        
        //clear_tmp();
        cur_matches_cnt = 0;
        generate_strings_optimized(current, target_length, strlen(tmp), row_n);
        sum += permutations[row_n];
        printf("Perm %d: %d Running sum: %ld\n", row_n + 1, permutations[row_n], sum);
            struct string_entry *current_entry, *tmp1;
    HASH_ITER(hh, strings, current_entry, tmp1) 
    {
    HASH_DEL(strings, current_entry);
    free(current_entry);
    }
    
    printf("Sum: %ld\n", sum);

}

    return 0;
}


void read_records_from_file(char * filename)
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
            for (int j = 0; j < strlen(istr); ++j)
            {
                records[i][j] = istr[j];
                records[i][j+1] = 0; 
            }
            istr = strtok (NULL,sep); 
            strcpy(rawmap[i], istr);        
            i++;            
            //getchar();
        }
    }
    rec_cnt = i;
    for (int j = 0; j < MAX_REC_COUNT; ++j)
    {
        char sep [2]=",";
        char *istr;
        istr = strtok (rawmap[j], sep);
        i = 0;
        while (istr != NULL)
        {                
            map[j][i] = atoi(istr);                    
            istr = strtok(NULL,sep);
            i++;  
        }
        map[j][i] = -1;
    }

    fclose(fp);
    return;
}

void print_records()
{
    for(int i = 0; i < rec_cnt; ++i)
    {
        int j = 0;
        while (records[i][j] == '.' || records[i][j] == '?' || records[i][j] == '#')
        {
            printf("%c", records[i][j]);
            j++;
        }
        printf("  -  ");
        j = 0;
        while (map[i][j] != -1)
        {
            printf("%d ", map[i][j]);
            j++;
        }        
        printf("\n");
    }
    return;
}

void generate_strings_optimized(char* current, int target_length, int current_length, int row_n) {
    if (current_length == target_length) {
        //printf("%s\n", current);
        if (strpatcmp(records[row_n], current) == 1)
            {   
                permutations[row_n]++;
                printf("%s\n", current);
            }
        return;
    }

    // Store the positions of '.' in the string
    int dot_positions[current_length + 2];
    int dot_count = 0;
    dot_positions[dot_count++] = -1;
    for (int i = 0; i < current_length; i++) {
        if (current[i] == '.') {
            dot_positions[dot_count++] = i;
        }
    }
    dot_positions[dot_count++] = current_length;

    // Only iterate over the positions where '.' can be inserted
    for (int i = 0; i < dot_count; i++) {
        // Insert '.' at the current position
        if (dot_positions[i] != current_length) {
            memmove(current + dot_positions[i] + 2, current + dot_positions[i] + 1, current_length - dot_positions[i]);
            current[dot_positions[i] + 1] = '.';
            current[current_length + 1] = '\0';
        } else {
            current[current_length] = '.';
            current[current_length + 1] = '\0';
        }

        struct string_entry *s;
        HASH_FIND_STR(strings, current, s);
        if (s == NULL) {
            // The string is not in the hash table, so add it
            s = malloc(sizeof(struct string_entry));
            strcpy(s->str, current);
            HASH_ADD_STR(strings, str, s);

            // Make the recursive call
            generate_strings_optimized(current, target_length, current_length + 1, row_n);
        }

        // Remove the inserted '.'
        if (dot_positions[i] != current_length) {
            memmove(current + dot_positions[i] + 1, current + dot_positions[i] + 2, current_length - dot_positions[i]);
            current[current_length] = '\0';
        } else {
            current[current_length] = '\0';
        }
    }
}

void generate_strings(char* current, int target_length, int current_length, int row_n) {
    if (current_length == target_length) {
        //printf("%s\n", current);
        if (strpatcmp(records[row_n], current) == 1)
            if (check_perm(current) == 0)
                {
                    permutations[row_n]++;
                    strcpy(tmprecords[cur_matches_cnt], current);
                    cur_matches_cnt++;
                }

        return;
    }

    for (int i = 0; i < current_length; i++) {
        if (current[i] == '.' || i == 0 || i == current_length - 1) {
            char new_string[target_length + 1];
            if (i == current_length - 1)
            {            
            strcpy(new_string, current);
            new_string[i+1] = '.';
            new_string[i+2] = '\0';
            }
            else
            {
            strncpy(new_string, current, i);
            new_string[i] = '.';
            strcpy(new_string + i + 1, current + i);

            }
            generate_strings(new_string, target_length, current_length + 1, row_n);
        }
    }
}

int strpatcmp(char * pattern, char * strtocompare)
{
    int res = 1;
    int i = 0;
    while (pattern[i] != '\0' && strtocompare[i] != '\0')
    {
        if (strtocompare[i] != pattern[i] && pattern[i] != '?')
            return 0;
        i++;
    }
    return res;
}

void clear_tmp()
{
    for (int i = 0; i < 100000; ++i)
        tmprecords[i][0] = '\0';
    return;
}

int check_perm(char * strtocheck)
{
    for (int i = 0; i < cur_matches_cnt; i++)
        if (strcmp(tmprecords[i], strtocheck) == 0)
            return 1;
    return 0;
}