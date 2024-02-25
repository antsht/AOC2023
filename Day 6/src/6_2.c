// Time:        38     67     76     73
// Distance:   234   1027   1157   1236

#include <math.h>
#include <stdio.h>

long long int get_number_of_ways(long long int a, long long int b, long long int c);
long long int times[1] = {38677673};
long long int distances[1] = {234102711571236};
int main() {
    long long int r0 = get_number_of_ways(-1, times[0], -distances[0]);

    printf("Total: %lld", r0);

    return 0;
}

long long int get_number_of_ways(long long int a, long long int b, long long int c) {
    long long int discr = b * b - 4 * a * c;
    float x1, x2;
    x1 = (-b + sqrt(discr)) / (2 * a);
    x2 = (-b - sqrt(discr)) / (2 * a);
    printf("From %f To %f\n", x1, x2);
    long long int res = ((long long int)x2) - ((long long int)x1);
    printf("res: %lld\n", res);
    return res;
}