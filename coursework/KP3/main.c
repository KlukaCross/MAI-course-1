#include <stdio.h>
#include <math.h>
#define NUMBER_ITERS 100
#define K_EPSILON 100.

double get_machine_epsilon();
double get_func_value(double x);
double get_teilor_value(double x, double eps, int *num_iters);
void print_start_table(double a, double b);
void print_string(int i, double x, double func_value, double teilor_value, int num_iters);

int main() {
    int number_segments;
    scanf("%d", &number_segments);
    const double eps = get_machine_epsilon() * K_EPSILON, a = -1, b = 1;
    const double step = (b-a)/(number_segments-1);
    double x = a;
    print_start_table(a, b);
    for (int i = 0; i < number_segments; i++) {
        int num_iters = 0;
        double func_value = get_func_value(x), teilor_value = get_teilor_value(x, eps, &num_iters);
        print_string(i+1, x, func_value, teilor_value, num_iters);
        x += step;
    }
    return 0;
}

double get_machine_epsilon() {
    double eps = 1.0;
    while (1.0 + eps / 2.0 > 1.0) eps = eps / 2.0;
    return eps;
}

double get_func_value(double x) {
    return log(2+x);
}

double get_teilor_value(double x, double eps, int *num_iters) {
    double sum = get_func_value(0), currentVal = 1;
    int sign = 1, i;
    for (i = 1; i < NUMBER_ITERS && fabs(currentVal) > eps; i++) {
        currentVal = sign*pow(x, i)/(i*pow(2, i));
        sum += currentVal;
        sign = -sign;
    }
    *num_iters = i;
    return sum;
}

void print_start_table(double a, double b) {
    printf("F(x) = ln(2+x)\tx on the segment [%.2lf, %.2lf]\nMachine epsilon - %.54lf\nK_EPSILON = %f\n"
           "Max number of iterations - %d\n", a, b, get_machine_epsilon(), K_EPSILON, NUMBER_ITERS);
    printf("__________________________________________________________________________________________\n");
    printf("|  i  |   x   |         F(x)         |     Taylor series    |  k  |         delta        |\n");
}

void print_string(int i, double x, double func_value, double teilor_value, int num_iters) {
    printf("| %.3d | % .2lf | %.18lf |% .18lf | %.3d |% .18lf |\n", i, x, func_value, teilor_value, num_iters, fabs(func_value-teilor_value));
}
