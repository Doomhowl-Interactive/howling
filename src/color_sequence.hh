#pragma once
#include "raylib.h"
#include "rng_machine.hh"

#include <optional>

namespace HOWLING_NAMESPACE
{
class ColorSequence
{
public:
    virtual ~ColorSequence() = default;

    [[nodiscard]] Color nextColor();

protected:
    std::size_t mIndex {};

private:
    virtual Color getNextColor() = 0;
};

class RainbowColorSequence : public ColorSequence
{
private:
    Color getNextColor() override;
};

class RandomColorSequence : public ColorSequence
{
public:
    RandomColorSequence(unsigned char minElement = 0, unsigned char maxElement = 255, std::optional<unsigned int> seed = {});

private:
    Color getNextColor() override;

    unsigned char mMinElement;
    unsigned char mMaxElement;
    RngMachine mRng;
};

class GradientColorSequence : public ColorSequence
{
public:
    GradientColorSequence(Color startColor, Color endColor, std::size_t steps);

private:
    Color getNextColor() override;

    Color mStartColor;
    Color mEndColor;
    std::size_t mSteps;
};

}
