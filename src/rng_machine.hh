#pragma once
#include <memory>
#include <optional>
#include <random>
#include <type_traits>

namespace HOWLING_NAMESPACE
{

class RngMachine
{
public:
    RngMachine() = default;
    RngMachine(const std::optional<unsigned int>& seedParam);
    RngMachine(unsigned int seed);

    [[nodiscard]] double randomValue(double min, double max);
    [[nodiscard]] float randomValue(float min, float max);
    [[nodiscard]] int randomValue(int min, int max);

    [[nodiscard]] long getSeed() const;

    [[nodiscard]] static RngMachine& global();

private:
    unsigned int seed {};
    std::mt19937 gen {};

    static inline std::unique_ptr<RngMachine> sGlobal = std::make_unique<RngMachine>();
};

}
