#include "ma_struct.h"
#include <stdio.h>

int write_to_bin(FILE *f_input, FILE *f_output) {
    while (!feof(f_input)) {
        Apartment ap;
        fscanf(f_input, "%d:%lld:%d:%d:%d:%d:%lf:%d:%s", &ap.id, &ap.price, &ap.repair, &ap.dist_to_subway, &ap.subway_dist_to_center, &ap.rooms, &ap.footage, &ap.floor, &ap.ao);
        if (1 != fwrite(&ap, sizeof(ap), 1, f_output)) {
            fprintf(stderr, "error write to f_output\n");
            return 1;
        }
    }
    return 0;
}

// to_bin file_input [file_output]
int main(int argc, char * argv[]) {
    if (argc > 3 || argc < 2) {
        fprintf(stderr, "wrong number of arguments\n");
        return 1;
    }
    FILE * f_input = fopen(argv[1], "r");
    if (f_input == NULL) {
        fprintf(stderr, "error read file_input\n");
        return 1;
    }
    char *output_name = "output.bin";
    if (argc == 3) output_name = argv[2];
    FILE * f_output = fopen(output_name, "w");
    if (f_output == NULL) {
        fscanf(stderr, "error open file_output\n");
        return 1;
    }
    return write_to_bin(f_input, f_output);
}
