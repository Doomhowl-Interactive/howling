#include "rng_machine.hh"

namespace HOWLING_NAMESPACE
{

RngMachine::RngMachine(const std::optional<unsigned int>& seedParam)
    : seed(seedParam.value_or(std::random_device()()))
    , gen(seed)
{
}

RngMachine::RngMachine(unsigned int)
    : seed(seed)
    , gen(seed)
{
}

double RngMachine::randomValue(double min, double max)
{
    std::uniform_real_distribution<double> dis(min, max);
    return dis(gen);
}

float RngMachine::randomValue(float min, float max)
{
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}

int RngMachine::randomValue(int min, int max)
{
    std::uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}

long RngMachine::getSeed() const
{
    return seed;
}

RngMachine& RngMachine::global()
{
    return *sGlobal;
}

}