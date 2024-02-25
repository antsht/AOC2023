#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_5.h"

int main() {
    char buffer[256];
    unsigned long int seeds[20];
    const char *categoryNames[] = {"seed",     "soil",  "fertilizer",  "water",
                                   "humidity", "light", "temperature", "location"};
    read_seeds_from_file("../data/5seeds.txt", buffer, seeds);

    converter_t c_seed_to_soil =
        read_converter_from_file("../data/5seed-to-soil.txt", seed, soil, buffer, categoryNames);
    converter_t c_soil_to_fertilizer =
        read_converter_from_file("../data/5soil-to-fertilizer.txt", soil, fertilizer, buffer, categoryNames);
    converter_t c_fertilizer_to_water = read_converter_from_file("../data/5fertilizer-to-water.txt",
                                                                 fertilizer, water, buffer, categoryNames);
    converter_t c_water_to_light =
        read_converter_from_file("../data/5water-to-light.txt", water, light, buffer, categoryNames);
    converter_t c_light_to_temperature = read_converter_from_file("../data/5light-to-temperature.txt", light,
                                                                  temperature, buffer, categoryNames);
    converter_t c_temperature_to_humidity = read_converter_from_file(
        "../data/5temperature-to-humidity.txt", temperature, humidity, buffer, categoryNames);
    converter_t c_humidity_to_location = read_converter_from_file("../data/5humidity-to-location.txt",
                                                                  humidity, location, buffer, categoryNames);

    unsigned long int min_location = convert_seed_to_location(
        seeds[0], c_seed_to_soil, c_soil_to_fertilizer, c_fertilizer_to_water, c_water_to_light,
        c_light_to_temperature, c_temperature_to_humidity, c_humidity_to_location);
    for (int i = 1; i < 20; ++i) {
        unsigned long int current_location = convert_seed_to_location(
            seeds[i], c_seed_to_soil, c_soil_to_fertilizer, c_fertilizer_to_water, c_water_to_light,
            c_light_to_temperature, c_temperature_to_humidity, c_humidity_to_location);
        if (current_location < min_location) min_location = current_location;
    }

    printf("\n\n %lu \n\n", min_location);

    return 0;
}
