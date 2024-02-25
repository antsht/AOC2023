#include "common_5.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_seeds_from_file(char *filename, char *buffer, unsigned long int *seeds) {
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

converter_t read_converter_from_file(char *filename, category src_t, category dst_t, char *buffer,
                                     const char **categoryNames) {
    converter_t converter = converter_init(src_t, dst_t);
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error occured while opening .txt");
        return converter;
        
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
    register unsigned long int dst_val = src_val;
    register long int diff;
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

unsigned long int convert_seed_to_location(unsigned long int seed, converter_t c_seed_to_soil,
                                           converter_t c_soil_to_fertilizer,
                                           converter_t c_fertilizer_to_water, converter_t c_water_to_light,
                                           converter_t c_light_to_temperature,
                                           converter_t c_temperature_to_humidity,
                                           converter_t c_humidity_to_location) {
    unsigned long int result = convert_value(seed, c_seed_to_soil);
    result = convert_value(result, c_soil_to_fertilizer);
    result = convert_value(result, c_fertilizer_to_water);
    result = convert_value(result, c_water_to_light);
    result = convert_value(result, c_light_to_temperature);
    result = convert_value(result, c_temperature_to_humidity);
    result = convert_value(result, c_humidity_to_location);
    return result;
}