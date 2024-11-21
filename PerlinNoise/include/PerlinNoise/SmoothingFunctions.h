//
// Created by Andi Felder on 19.11.2024.
//

#ifndef SMOOTHING_FUNCTIONS_H
#define SMOOTHING_FUNCTIONS_H

#include <cmath>

double cubic(double d);
double linear(double d);
double smooth_cos(double d);
double quintic(double d);
double hermite(double d);
double exponential(double d);
double gaussian(double d);
double piecewiseQuadratic(double d);

#endif // SMOOTHING_FUNCTIONS_H
