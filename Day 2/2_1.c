#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char buffer[256];

    typedef struct {
        int game_id;
        int max_r, max_g, max_b;
    } game_t;

    game_t games[100]; 
    int i = 0;

    FILE * fp = fopen("2_1.txt", "r");
    if(fp==NULL)
        {
            perror("Error occured while opening 1.txt");
            return 1;
        }
    while(!feof (fp)) {
    if (fgets(buffer, 256, fp))
        {
            games[i].game_id = 0;
            games[i].max_r = 0;
            games[i].max_g = 0;
            games[i].max_b = 0;
            int id_flag = 0;
            int color_flag = 0;
            char sep [10]=" ,;:";
            char *istr;
            istr = strtok (buffer,sep);
            int last_num = 0;
            // Выделение последующих частей
            while (istr != NULL)
            {
                // Вывод очередной выделенной части
                //printf ("%s\n",istr);
                if (strcmp(istr,"\n") == 0)
                {
                    id_flag = 3;
                }
                


                if (id_flag == 2)
                {

                    if (color_flag == 1)
                    {
                        //printf ("Lastcolor: %s Lastnum: %d\n",istr, last_num);
                        if ((strcmp(istr,"red") == 0 || strcmp(istr,"red\n") == 0) && last_num > games[i].max_r)
                        {
                            games[i].max_r = last_num;
                        }
                        if ((strcmp(istr,"green") == 0 || strcmp(istr,"green\n") == 0) && last_num > games[i].max_g)
                        {
                            games[i].max_g = last_num;
                        }
                        if ((strcmp(istr,"blue") == 0 || strcmp(istr,"blue\n") == 0) && last_num > games[i].max_b)
                        {
                            games[i].max_b = last_num;
                        }

                        color_flag = 0;
                        last_num = 0;
                    }
                    if ( color_flag == 0 && atoi(istr) > 0 )
                    {
                        //printf ("Lastnum: %s\n",istr);
                        last_num = atoi(istr);
                        color_flag = 1;
                    }
                }

                if (id_flag == 1)
                {
                    id_flag = 2;
                    games[i].game_id = atoi(istr);
                    
                    //printf ("%d\n", games[i].game_id);
                }

                if (strcmp(istr,"Game") == 0 && id_flag == 0)
                {
                    id_flag = 1;
                    
                }

                if ( id_flag == 3)
                {
                    id_flag = 2;                    
                }
                // Выделение очередной части строки
                istr = strtok (NULL,sep);
            }
            
            //printf ("ID:%d R:%d G:%d B:%d\n", games[i].game_id, games[i].max_r, games[i].max_g, games[i].max_b);
            //getchar();
            i++;
        }
    }

    fclose(fp);
    int sum = 0;
    for (int i = 0; i < 100; ++i)
    {
        if (games[i].max_r <= 12 && games[i].max_g <=13 && games[i].max_b <= 14)
        {
            sum += games[i].game_id;
            printf ("ID:%d R:%d G:%d B:%d\n", games[i].game_id, games[i].max_r, games[i].max_g, games[i].max_b);
        }
    }
    printf("Sum of IDs: %d\n", sum);
    return 0;
}
