    #pragma once
    #include <cmath>
    #include <utility>

    #ifndef VECTOR2D_H
    #define VECTOR2D_H

    class Vector2d {
    public:
        Vector2d() : m_x(0.0), m_y(0.0) {
        }

        Vector2d(double x, double y) : m_x(x), m_y(y) {
        }

        //Copy constructor is default, but we explicitly mention it because of the rule of 5
        Vector2d(const Vector2d &other) = default;

        //Move constructor
        Vector2d(Vector2d &&other) noexcept : m_x(std::exchange(other.m_x, 0)), m_y(std::exchange(other.m_y, 0)) {
        }

        //Destructor is default, but we explicitly mention it because of the rule of 5
        ~Vector2d() = default;

        //Move assignment
        Vector2d &operator=(Vector2d &&other) noexcept {
            if (this == &other) {
                return *this;
            }

            std::swap(m_x, other.m_x);
            std::swap(m_y, other.m_y);

            return *this;
        }

        //Copy assignment
        Vector2d &operator=(const Vector2d &other) {
            if (this == &other) {
                return *this;
            }

            m_x = other.m_x;
            m_y = other.m_y;

            return *this;
        }

        // getters
        [[nodiscard]] double x() const {
            return m_x;
        }

        [[nodiscard]] double y() const {
            return m_y;
        }

        // arithmetic operations
        double operator*(const Vector2d &other) const {
            return m_x * other.x() + m_y * other.y();
        }

        Vector2d operator*(const double c) const {
            return {m_x * c, m_y * c};
        }

        friend Vector2d operator*(const double c, const Vector2d &vec) {
            return {vec.m_x * c, vec.m_y * c};
        }

        Vector2d operator/(const double c) const {
            return {m_x / c, m_y / c};
        }

        Vector2d operator+(const Vector2d &other) const {
            return {m_x + other.x(), m_y + other.y()};
        }

        Vector2d operator-(const Vector2d &other) const {
            return {m_x - other.x(), m_y - other.y()};
        }

        // normalization functions
        [[nodiscard]] Vector2d normalized() const {
            if (magnitude() == 0.0) {
                // If the magnitude is 0, return a zero vector to avoid division by zero
                return {0.0, 0.0};
            }
            return {m_x / magnitude(), m_y / magnitude()};
        }

        void normalize() {
            //If we have the same problem as above, we just set it to 0
            if (magnitude() == 0.0) {
                m_x = 0;
                m_y = 0;
            }
            m_x = m_x / magnitude();
            m_y = m_y / magnitude();
        }

        [[nodiscard]] double norm() const {
            return magnitude();
        }

    private:
        double m_x;
        double m_y;

        [[nodiscard]] double magnitude() const {
            return std::sqrt(m_x * m_x + m_y * m_y);
        }
    };

    #endif
