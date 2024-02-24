#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char buffer[256];

unsigned long int seeds[20];

typedef enum { seed, soil, fertilizer, water, humidity, light, temperature, location } category;
const char *categoryNames[] = {"seed",     "soil",  "fertilizer",  "water",
                               "humidity", "light", "temperature", "location"};

typedef struct {
    unsigned long int dst;
    unsigned long int src;
    unsigned long int range;
} range_t;

typedef struct {
    category src_t;
    category dst_t;
    range_t converter_rows[50];
    int converters_cnt;
} converter_t;

converter_t c_seed_to_soil;
converter_t c_soil_to_fertilizer;
converter_t c_fertilizer_to_water;
converter_t c_water_to_light;
converter_t c_light_to_temperature;
converter_t c_temperature_to_humidity;
converter_t c_humidity_to_location;

converter_t converter_init(category src_t, category dst_t);
int read_seeds_from_file(char *filename);
converter_t read_converter_from_file(char *filename, category src_t, category dst_t);
unsigned long int convert_value(unsigned long int src_val, converter_t converter);
unsigned long int convert_seed_to_location(unsigned long int seed);

int main() {
    read_seeds_from_file("5seeds.txt");

    c_seed_to_soil = read_converter_from_file("5seed-to-soil.txt", seed, soil);
    c_soil_to_fertilizer = read_converter_from_file("5soil-to-fertilizer.txt", soil, fertilizer);
    c_fertilizer_to_water = read_converter_from_file("5fertilizer-to-water.txt", fertilizer, water);
    c_water_to_light = read_converter_from_file("5water-to-light.txt", water, light);
    c_light_to_temperature = read_converter_from_file("5light-to-temperature.txt", light, temperature);
    c_temperature_to_humidity =
        read_converter_from_file("5temperature-to-humidity.txt", temperature, humidity);
    c_humidity_to_location = read_converter_from_file("5humidity-to-location.txt", humidity, location);

    unsigned long int min_location = convert_seed_to_location(seeds[0]);
    for (int i = 1; i < 20; ++i) {
        unsigned long int current_location = convert_seed_to_location(seeds[i]);
        if (current_location < min_location) min_location = current_location;
    }

    printf("\n\n %lu \n\n", min_location);

    return 0;
}

int read_seeds_from_file(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error occured while opening 5seeds.txt");
        return 1;
    }
    while (!feof(fp)) {
        if (fgets(buffer, 256, fp)) {
            char sep[10] = " ";
            char *istr;
            istr = strtok(buffer, sep);
            int i = 0;
            while (istr != NULL) {
                seeds[i++] = atol(istr);
                printf("Seed %d: %lu \n", i, seeds[i - 1]);
                istr = strtok(NULL, sep);
            }

            // getchar();
        }
    }

    fclose(fp);
    return 0;
}

converter_t read_converter_from_file(char *filename, category src_t, category dst_t) {
    converter_t converter = converter_init(src_t, dst_t);
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error occured while opening 5seeds.txt");
        return *(converter_t *)NULL;
    }

    int i = 0;
    while (!feof(fp)) {
        if (fgets(buffer, 256, fp)) {
            char sep[10] = " ";
            char *istr;
            istr = strtok(buffer, sep);
            converter.converter_rows[i].dst = atol(istr);
            istr = strtok(NULL, sep);
            converter.converter_rows[i].src = atol(istr);
            istr = strtok(NULL, sep);
            converter.converter_rows[i].range = atol(istr);
            istr = strtok(NULL, sep);
            converter.converters_cnt++;

            printf("%s to %s N: %d Dst: %lu Src: %lu Range: %lu\n", categoryNames[converter.src_t],
                   categoryNames[converter.dst_t], converter.converters_cnt, converter.converter_rows[i].dst,
                   converter.converter_rows[i].src, converter.converter_rows[i].range);
            i++;
            // getchar();
        }
    }

    fclose(fp);
    return converter;
}

converter_t converter_init(category src_t, category dst_t) {
    converter_t new_converter;
    new_converter.src_t = src_t;
    new_converter.dst_t = dst_t;
    new_converter.converters_cnt = 0;
    return new_converter;
}

unsigned long int convert_value(unsigned long int src_val, converter_t converter) {
    unsigned long int dst_val = src_val;
    long int diff;
    for (int i = 0; i < converter.converters_cnt; ++i) {
        if (src_val >= converter.converter_rows[i].src &&
            src_val < converter.converter_rows[i].src + converter.converter_rows[i].range) {
            diff = converter.converter_rows[i].dst - converter.converter_rows[i].src;
            dst_val = src_val + diff;
            // printf("Match on row: %d", i);
        }
    }
    return dst_val;
}

unsigned long int convert_seed_to_location(unsigned long int seed) {
    unsigned long int result = convert_value(seed, c_seed_to_soil);
    result = convert_value(result, c_soil_to_fertilizer);
    result = convert_value(result, c_fertilizer_to_water);
    result = convert_value(result, c_water_to_light);
    result = convert_value(result, c_light_to_temperature);
    result = convert_value(result, c_temperature_to_humidity);
    result = convert_value(result, c_humidity_to_location);
    return result;
}