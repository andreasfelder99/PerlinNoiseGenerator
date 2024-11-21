//
// Created by Andi Felder on 19.11.2024.
//
#include "SmoothingFunctions.h"

double smoothCubic(double d) {
    return 3 * d * d - 2 * d * d * d;
}

double constantD(double d) {
    return d;
}

double smoothSin(double d) {
    return (1 - std::cos(M_PI * d)) / 2;
}

double smootherCubic(double d) {
    return 6 * pow(d, 5) - 15 * pow(d, 4) + 10 * pow(d, 3);
}
