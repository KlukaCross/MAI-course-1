#include <stdio.h>
#include <math.h>
#include <stdbool.h>

typedef double (*func)(double);

typedef struct result {
    double root;
    int iters;
    bool success;
} result;

double func1(double x) {
    return 3*x - 14 + exp(x) - exp(-x);
}

double func2(double x) {
    return sqrt(1-x) - tan(x);
}

result dihotomia_method(func f, double a, double b);
result iterations_method(func iter_f, double a, double b);
result newton_method(func f, double a, double b);
double iter_f1(double x);
double iter_f2(double x);
double df(func f, double x);
double ddf(func f, double x);
void print_research(func f, func iter_f, double a, double b);

int main() {
    print_research(func1, iter_f1, 1, 3);
    printf("--------------------------------------\n");
    print_research(func2, iter_f2, 0, 1);
    return 0;
}

result dihotomia_method(func f, double a, double b) {
    result res = {0, 0, 0};
    res.success = f(a)*f(b)<0;
    if (!res.success) return res;
    double delta = pow(2, -26);
    while ((b-a) > delta) {
        double c = (a+b)/2;
        if (f(a)*f(c) < 0) {
            b = c;
        }
        else {
            a = c;
        }
        res.iters++;
    }
    res.root = (a+b)/2;
    return res;
}

double iter_f1(double x) {
    func f = func1;
    return x - f(x)/14;
}

double iter_f2(double x) {
    func f = func2;
    return x + f(x)/10;
}

result iterations_method(func iter_f, double a, double b) {
    double prev_x, x = (a + b) / 2;
    double delta = pow(2, -26);
    result res = {0, 0 , 0};
    do {
        res.success = fabs((iter_f(x + delta) - iter_f(x - delta)) / (2 * delta)) < 1;
        if (!res.success) return res;
        prev_x = x;
        x = iter_f(prev_x);
        res.iters++;
    }
    while (fabs(x - prev_x) > delta);
    res.root = x;
    return res;
}

result newton_method(func f, double a, double b) {
    double prev_x, x = (a + b) / 2;
    double delta = pow(2, -26);
    result res = {0, 0 , 0};
    do {
        res.success = fabs(f(x)*ddf(f, x)) < pow(df(f, x), 2);
        if (!res.success) return res;
        prev_x = x;
        x = prev_x - f(prev_x) / df(f, prev_x);
        res.iters++;
    }
    while (fabs(x - prev_x) > delta);
    res.root = x;
    return res;
}

double df(func f, double x) {
    double dx = pow(2, -26);
    return (f(x+dx) - f(x-dx)) / (2*dx);
}

double ddf(func f, double x) {
    double dx = pow(2, -26);
    return (f(x+dx) - 2*f(x) + f(x-dx)) / (dx*dx);
}

void print_research(func f, func iter_f, double a, double b) {
    char names[3][11] = {"dihotomia", "iterations", "newton"};
    result res[] = {dihotomia_method(f, a, b), iterations_method(iter_f, a, b), newton_method(f, a, b)};
    for (int i = 0; i < 3; i++) {
        printf("%s method:\n\troot: %.16lf\n\titerations: %d\n\tsuccess: %d\n", names[i], res[i].root, res[i].iters, res[i].success);
    }
}
