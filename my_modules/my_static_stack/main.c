#include <stdio.h>
#include <complex.h>

int main() {
    double complex a = 2 + 3.1i;
    printf("Число: %Lg+%Lgi\n", creall(a), cimagl(a));

    printf("Модуль: %Lg\n", cabsl(a));

    printf("Аргумент: %Lg", cargl(a));;
    return 0;
}
