#include <stdio.h>
#include <string.h>

int main()
{
    long int total = 0;
    char buffer[256];

    FILE * fp = fopen("1.txt", "r");
    if(fp==NULL)
        {
            perror("Error occured while opening 1.txt");
            return 1;
        }
    while(!feof (fp)) {
    if (fgets(buffer, 256, fp))
        {
            int digit_s = -1, digit_e = -1, i = 0;
            int res = 0;

            while(buffer[i] != '\0')
            {
                if (buffer[i] >= 48 && buffer[i] <= 57){
                    if (digit_s == -1)
                    {
                        digit_s = buffer[i];
                    }
                digit_e = buffer[i];}
                i++;
            }

            res = (digit_s - 48 ) * 10 + (digit_e - 48);
        total += res;
        //printf("%c - %c - %d\n", digit_s, digit_e, res);
        }
    }

    fclose(fp);
    printf("%ld", total);
    return 0;
}
