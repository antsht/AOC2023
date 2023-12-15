#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char buffer[25000];

int hashes[10000];
int hashes_cnt = 0;
long hashes_sum = 0;

void read_data_from_file(char * filename);
int hash(char * str);

int main()
{
    read_data_from_file("15.txt");
    printf("Hashes cnt: %d\n\n", hashes_cnt);
    for (int i = 0; i < hashes_cnt; i++)
    {
        printf("Hash[%d] = %d\n", i, hashes[i]);
        hashes_sum += hashes[i]; 
    }
    

    printf("Sum = %ld\n", hashes_sum);
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
                hashes[hashes_cnt] = hash(istr);
                hashes_cnt++;
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