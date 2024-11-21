#include <iostream>

#include "PerlinNoiseGenerator.h"

double PerlinNoiseGenerator::eval(const Vector2d& p) {
    //Step 1: calculate corner points for a given vector
    int x0 = floor(p.x());
    int y0 = floor(p.y());
    int x1 = x0 + 1;
    int y1 = y0 + 1;

    //Step 2: compute distance vectors
    Vector2d d0(p.x() - x0, p.y() - y0);
    Vector2d d1(p.x() - x1, p.y() - y0);
    Vector2d d2(p.x() - x0, p.y() - y1);
    Vector2d d3(p.x() - x1, p.y() - y1);

    //Step 3: calculate gradients for the four corners
    Vector2d g0 = getGradient(x0, y0);
    Vector2d g1 = getGradient(x1, y0);
    Vector2d g2 = getGradient(x0, y1);
    Vector2d g3 = getGradient(x1, y1);

    //Step 4: Compute dot products
    double n0 = d0 * g0;
    double n1 = d1 * g1;
    double n2 = d2 * g2;
    double n3 = d3 * g3;

    //Step 5: Compute horizontal and vertical distances to the grid lines
    double wx = p.x() - x0;
    double wy = p.y() - y0;

    //Step 6: Smooth the weights
    double sx = smooth(wx);
    double sy = smooth(wy);

    //Step 7: Interpolate scalar products horizontally
    double perlinx1 = n0 + sx * (n1 - n0);
    double perlinx2 = n2 + sx * (n3 - n2);

    //Last Step: Interpolate vertically
    double perlinxy = perlinx1 + sy * (perlinx2 - perlinx1);

    return perlinxy;
}

//Gradient helper function. We normalize the coordinates and compute the '1-D' index
Vector2d PerlinNoiseGenerator::getGradient(int x, int y) const {
    x = x % m_gridWidth;
    y = y % m_gridHeight;
    return m_gradients[y * m_gridWidth + x];
}

//Smooth function
double PerlinNoiseGenerator::smooth(double d) const {
    return m_smoothFn(d);
}
