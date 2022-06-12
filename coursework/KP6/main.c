#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "ma_struct.h"

bool check_apartment(Apartment *ap, int rooms, char *ao) {
    return (((rooms <= 0) || (ap->rooms == rooms)) &&
            ((ao == NULL) || (strcmp(ao, ap->ao) == 0)));
}

int execute(FILE *f_bin, int rooms, char *ao) {
    long long sum_price = 0;
    int lines = 0;
    while (!feof(f_bin)) {
        Apartment ap;
        fread(&ap, sizeof(ap), 1, f_bin);
        if (check_apartment(&ap, rooms, ao)) {
            sum_price += ap.price;
            lines++;
        }
    }
    fseek(f_bin, 0, SEEK_SET);
    double mean_price = (double)sum_price/lines;
    printf("  id   |  price  | repair | dist_to_subway | subway_dist_to_center | rooms | footage | floor | ao\n");
    while (!feof(f_bin)) {
        Apartment ap;
        fread(&ap, sizeof(ap), 1, f_bin);
        if (check_apartment(&ap, rooms, ao) && ap.price < mean_price) {
            printf(" %.5d | %lld |   %d    |      %.4d      |         %.5d         |   %d   |  %.1lf   |  %.2d   | %s\n",
                   ap.id, ap.price, ap.repair, ap.dist_to_subway, ap.subway_dist_to_center, ap.rooms, ap.footage, ap.floor, ap.ao);
        }
    }
    return 0;
}

// Find all apartments with the specified rooms and AO (optional), the price of which is less than the mean price
// main bin_file [rooms] [ao]
int main(int argc, char * argv[]) {
    if (argc > 4 || argc < 2) {
        fprintf(stderr, "wrong number of arguments\n");
        return 1;
    }
    FILE * f_bin = fopen(argv[1], "r");
    if (f_bin == NULL) {
        fprintf(stderr, "error read bin_file\n");
        return 1;
    }
    int rooms = (argc >= 3)? argv[2][0]-'0' : -1;
    char *ao = (argc == 4)? argv[3] : NULL;
    return execute(f_bin, rooms, ao);
}
