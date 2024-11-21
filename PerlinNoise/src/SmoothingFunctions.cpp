//
// Created by Andi Felder on 19.11.2024.
//
#include "SmoothingFunctions.h"

double cubic(double d) {
    return 3 * d * d - 2 * d * d * d;
}

double linear(double d) {
    return d;
}

double smooth_cos(double d) {
    return (1 - std::cos(M_PI * d)) / 2;
}

double quintic(double d) {
    return 6 * pow(d, 5) - 15 * pow(d, 4) + 10 * pow(d, 3);
}

double hermite(double d) {
    return d * d * (3 - 2 * d);
}

double exponential(double d) {
    return 1 - exp(-d);
}

double gaussian(double d) {
    double sigma = 0.25;
    return exp(-((d - 0.5) * (d - 0.5)) / (2 * sigma * sigma));
}

double piecewiseQuadratic(double d) {
    if (d < 0.5) {
        return 2 * d * d;
    } else {
        return 1 - 2 * (1 - d) * (1 - d);
    }
}
