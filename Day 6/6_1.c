//Time:        38     67     76     73
//Distance:   234   1027   1157   1236

#include <stdio.h>
#include <math.h>

int get_number_of_ways(int a, int b, int c);
int times[4] = {38, 67, 76, 73};
int distances[4] = {234, 1027, 1157, 1236};
int main(){

    int r0 = get_number_of_ways(-1, times[0], -distances[0]);
    int r1 = get_number_of_ways(-1, times[1], -distances[1]);
    int r2 = get_number_of_ways(-1, times[2], -distances[2]);
    int r3 = get_number_of_ways(-1, times[3], -distances[3]);

    printf("Total: %d", r0*r1*r2*r3);


    return 0;
}

int get_number_of_ways(int a, int b, int c)
{
    int discr = b*b - 4 * a * c;
    float x1, x2;
    x1 = (-b + sqrt(discr)) / (2 * a);
    x2 = (-b - sqrt(discr)) / (2 * a);
    printf("From %f To %f\n", x1, x2);
    int res = ((int) x2) - ((int) x1);
    printf("res: %d\n", res);
    return res;
}