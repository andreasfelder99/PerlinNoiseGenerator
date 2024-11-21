#include <cassert>
#include <memory>
#include <numbers>
#include <random>
#include <vector>

#include "Random.h"
#include "Vector2d.h"

#ifndef PERLIN_NOISE_GENERATOR_H
#define PERLIN_NOISE_GENERATOR_H

class PerlinNoiseGenerator {
  public:
    PerlinNoiseGenerator() = delete;
    PerlinNoiseGenerator(size_t gridSize) : PerlinNoiseGenerator(gridSize, gridSize, 0) {}
    PerlinNoiseGenerator(size_t gridWidth, size_t gridHeight)
        : PerlinNoiseGenerator(gridWidth, gridHeight, 0) {}
    PerlinNoiseGenerator(size_t gridWidth, size_t gridHeight, int seed)
        : m_rand(seed),
          m_gridWidth(gridWidth),
          m_gridHeight(gridHeight),
          m_gradients(std::make_unique<Vector2d[]>(gridWidth * gridHeight)) {
        for (size_t y = 0; y < gridHeight; ++y) {
            for (size_t x = 0; x < gridWidth; ++x) {
                // Generate a random angle in the range [0, 2pi)
                double angle = m_rand.next() * 2 * std::numbers::pi;

                // Compute the gradient vector using the angle
                Vector2d gradient(std::cos(angle), std::sin(angle));

                // Store the gradient vector
                m_gradients[y * gridWidth + x] = gradient;
            }
        }
    }

    PerlinNoiseGenerator(size_t gridWidth, size_t gridHeight, int seed,
                         std::function<double(double)> smoothFn)
        : m_rand(seed), m_gridWidth(gridWidth), m_gridHeight(gridHeight),
          m_smoothFn(std::move(smoothFn)),
          m_gradients(std::make_unique<Vector2d[]>(gridWidth * gridHeight)) {
        for (size_t y = 0; y < gridHeight; ++y) {
            for (size_t x = 0; x < gridWidth; ++x) {
                double angle = m_rand.next() * 2 * std::numbers::pi;
                m_gradients[y * gridWidth + x] = Vector2d(std::cos(angle), std::sin(angle));
            }
        }
    }

    int seed() const { return m_rand.seed(); }
    double eval(const Vector2d& p);
    Vector2d getGradient(int x, int y) const;
    double smooth(double d) const;

  private:

  private:
    Random m_rand;
    size_t m_gridWidth;
    size_t m_gridHeight;
    std::unique_ptr<Vector2d[]> m_gradients;
    std::function<double(double)> m_smoothFn;
};

#endif // PERLIN_NOISE_GENERATOR_H