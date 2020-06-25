#ifndef GRAPHICS_COMMON_MATH_RANDOM_HPP__
#define GRAPHICS_COMMON_MATH_RANDOM_HPP__

#include <random>

class Random
{
public:
    Random(std::uint32_t seed = 0);
    ~Random() = default;

    Random(const Random& that) = delete;
    Random(Random&& that) = delete;
    Random& operator=(const Random& that) = delete;
    Random& operator=(Random&& that) = delete;

    double getUniform() noexcept;

private:
    std::default_random_engine m_engine;
    std::uniform_real_distribution<double> m_distribution;
};

#endif // GRAPHICS_COMMON_MATH_RANDOM_HPP__
