#ifndef COMMON_5_H
#define COMMON_5_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { seed, soil, fertilizer, water, humidity, light, temperature, location } category;

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

converter_t converter_init(category src_t, category dst_t);
int read_seeds_from_file(char *filename, char *buffer, unsigned long int *seeds);
converter_t read_converter_from_file(char *filename, category src_t, category dst_t, char *buffer,
                                     const char **categoryNames);
unsigned long int convert_value(unsigned long int src_val, converter_t converter);
unsigned long int convert_seed_to_location(unsigned long int seed, converter_t c_seed_to_soil,
                                           converter_t c_soil_to_fertilizer,
                                           converter_t c_fertilizer_to_water, converter_t c_water_to_light,
                                           converter_t c_light_to_temperature,
                                           converter_t c_temperature_to_humidity,
                                           converter_t c_humidity_to_location);

#endif