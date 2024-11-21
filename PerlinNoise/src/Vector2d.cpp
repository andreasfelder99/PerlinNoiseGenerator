#include "Vector2d.h"
#include <utility>

// Constructors
Vector2d::Vector2d() : m_x(0.0), m_y(0.0) {
}

Vector2d::Vector2d(double x, double y) : m_x(x), m_y(y) {
}

Vector2d::Vector2d(Vector2d &&other) noexcept
    : m_x(std::exchange(other.m_x, 0)), m_y(std::exchange(other.m_y, 0)) {
}

// Move assignment operator
Vector2d &Vector2d::operator=(Vector2d &&other) noexcept {
    if (this == &other) {
        return *this;
    }
    std::swap(m_x, other.m_x);
    std::swap(m_y, other.m_y);
    return *this;
}

// Copy assignment operator
Vector2d &Vector2d::operator=(const Vector2d &other) {
    if (this == &other) {
        return *this;
    }
    m_x = other.m_x;
    m_y = other.m_y;
    return *this;
}

// Getters
double Vector2d::x() const {
    return m_x;
}

double Vector2d::y() const {
    return m_y;
}

// Arithmetic operations
double Vector2d::operator*(const Vector2d &other) const {
    return m_x * other.x() + m_y * other.y();
}

Vector2d Vector2d::operator*(const double c) const {
    return {m_x * c, m_y * c};
}

Vector2d operator*(const double c, const Vector2d &vec) {
    return {vec.m_x * c, vec.m_y * c};
}

Vector2d Vector2d::operator/(const double c) const {
    return {m_x / c, m_y / c};
}

Vector2d Vector2d::operator+(const Vector2d &other) const {
    return {m_x + other.x(), m_y + other.y()};
}

Vector2d Vector2d::operator-(const Vector2d &other) const {
    return {m_x - other.x(), m_y - other.y()};
}

// Normalization functions
Vector2d Vector2d::normalized() const {
    if (magnitude() == 0.0) {
        return {0.0, 0.0};
    }
    return {m_x / magnitude(), m_y / magnitude()};
}

void Vector2d::normalize() {
    if (magnitude() == 0.0) {
        m_x = 0;
        m_y = 0;
    } else {
        m_x = m_x / magnitude();
        m_y = m_y / magnitude();
    }
}

double Vector2d::norm() const {
    return magnitude();
}

double Vector2d::magnitude() const {
    return std::sqrt(m_x * m_x + m_y * m_y);
}
