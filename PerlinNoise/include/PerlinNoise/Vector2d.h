#pragma once

#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2d {
public:
    Vector2d();

    Vector2d(double x, double y);

    Vector2d(const Vector2d &other) = default; // Copy constructor
    Vector2d(Vector2d &&other) noexcept; // Move constructor
    ~Vector2d() = default; // Destructor

    Vector2d &operator=(Vector2d &&other) noexcept; // Move assignment
    Vector2d &operator=(const Vector2d &other); // Copy assignment

    // Getters
    [[nodiscard]] double x() const;

    [[nodiscard]] double y() const;

    // Arithmetic operations
    double operator*(const Vector2d &other) const;

    Vector2d operator*(double c) const;

    friend Vector2d operator*(double c, const Vector2d &vec);

    Vector2d operator/(double c) const;

    Vector2d operator+(const Vector2d &other) const;

    Vector2d operator-(const Vector2d &other) const;

    // Normalization functions
    [[nodiscard]] Vector2d normalized() const;

    void normalize();

    [[nodiscard]] double norm() const;

private:
    double m_x;
    double m_y;

    [[nodiscard]] double magnitude() const;
};

#endif
