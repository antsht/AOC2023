#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char buffer[25000];


void read_data_from_file(char * filename);
int hash(char * str);

typedef struct {
    char name[10];
    int value;
} card_t;

typedef struct {
    card_t cards[1000];
    int len;
} box_t;

box_t hashmap[256];

void add_or_update_card(card_t card);
void remove_card(card_t card);
void print_hash_map();
long int calc_focusing_power();

int main()
{
    read_data_from_file("15.txt");
    print_hash_map();
    printf("Focusing power = %ld", calc_focusing_power());
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
    while(!feof (fp)) 
    {
        if (fgets(buffer, 25000, fp))
        {
          char sep [10]=",";
            char *istr;
            istr = strtok (buffer,sep);

            
            while (istr != NULL)
            {   
                card_t card;
                int namelen = 0;
                while (istr[namelen] != '-' && istr[namelen] != '=' && istr[namelen] != '\0' && istr[namelen] != '\n')
                {
                    card.name[namelen] = istr[namelen];
                    namelen++;
                }
                card.name[namelen] = '\0';
                if (istr[namelen] == '-')
                {
                    remove_card(card);
                }
                if (istr[namelen] == '=')
                {
                    card.value = istr[namelen+1] - 48;
                    add_or_update_card(card);
                }


                istr = strtok (NULL,sep);
            }
        }          
        
    }  
   
    fclose(fp);
    return;
}

int hash(char * str)
{
    int hash = 0;
    int i = 0;
    while (str[i] != '\0' && str[i] != '\n')
    {
        hash = ((hash + str[i++]) * 17) % 256; 
    }
    return hash;
}

void add_or_update_card(card_t card)
{    
    int h = hash(card.name);
    //printf("ADD | Str=%s Hash=%d Val= %d\n", card.name, h, card.value);
    int exists = 0;
    for(int i = 0; i < hashmap[h].len; ++i)
    {
        if (strcmp(hashmap[h].cards[i].name, card.name) == 0)
        {
            hashmap[h].cards[i].value = card.value;
            exists = 1;
        }

    }
    if (exists == 0)
    {
        strcpy(hashmap[h].cards[hashmap[h].len].name,card.name);
        hashmap[h].cards[hashmap[h].len].value = card.value;
        hashmap[h].len++;
    }
}
void remove_card(card_t card)
{
    int h = hash(card.name);
    //printf("REM | Str=%s Hash=%d\n", card.name, h);
    for(int i = 0; i < hashmap[h].len; ++i)
    {
        if (strcmp(hashmap[h].cards[i].name, card.name) == 0)
            strcpy(hashmap[h].cards[i].name, "\0");
    }
}

void print_hash_map()
{
    for (int i = 0; i < 256; ++i)
    {
        if (hashmap[i].len > 0)
        {
            printf("\nBox %d:\n", i);
            for (int n = 0; n < hashmap[i].len; ++n)
            {
                if (hashmap[i].cards[n].name[0] != '\0')
                    printf("Card %d: name=%s | val=%d\n", n, hashmap[i].cards[n].name, hashmap[i].cards[n].value);
            }
        }
    }
}


long int calc_focusing_power()
{
    long int total_power = 0;
    for (int i = 0; i < 256; ++i)
    {
        if (hashmap[i].len > 0)
        {
            //printf("\nBox %d:\n", i);
            int card_num = 1;
            for (int n = 0; n < hashmap[i].len; ++n)
            {
                if (hashmap[i].cards[n].name[0] != '\0')
                {
                    total_power = total_power + (i + 1) * card_num * hashmap[i].cards[n].value;
                    ++card_num;
                }
            }
        }
    }
    return total_power;
}