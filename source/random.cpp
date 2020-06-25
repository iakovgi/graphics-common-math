#include "random.h"

#include <random>
#include <chrono>

Random::Random(std::uint32_t seed):
    m_engine{},
    m_distribution{}
{
    if(seed == 0) {
        const auto now = std::chrono::system_clock::now();
        const auto sinceEpoch = now.time_since_epoch();
        const auto sinceEpochDuration = std::chrono::duration_cast<std::chrono::milliseconds>(sinceEpoch);
        seed = (std::uint32_t)sinceEpochDuration.count();
    }
    m_engine.seed(seed);
}

double Random::getUniform() noexcept
{
    return m_distribution(m_engine);
}
