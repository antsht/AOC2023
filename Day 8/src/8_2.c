#include <stdio.h>

// Функция для нахождения наибольшего общего делителя (НОД)
long long findGCD(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Функция для нахождения НОК двух чисел
long long findLCM(long long a, long long b) { return (a * b) / findGCD(a, b); }

// Функция для нахождения НОК шести чисел
long long findLCMofSix(long long num1, long long num2, long long num3, long long num4, long long num5,
                       long long num6) {
    long long lcm1 = findLCM(num1, num2);
    long long lcm2 = findLCM(lcm1, num3);
    long long lcm3 = findLCM(lcm2, num4);
    long long lcm4 = findLCM(lcm3, num5);
    long long lcm5 = findLCM(lcm4, num6);
    return lcm5;
}

long long main() {
    // Замените эти значения на свои шесть натуральных чисел
    long long num1 = 15517;
    long long num2 = 13939;
    long long num3 = 17621;
    long long num4 = 19199;
    long long num5 = 12361;
    long long num6 = 20777;

    long long result = findLCMofSix(num1, num2, num3, num4, num5, num6);

    printf("Наименьшее общее кратное для %ld, %ld, %ld, %ld, %ld и %ld: %lld\n", num1, num2, num3, num4, num5,
           num6, result);

    return 0;
}