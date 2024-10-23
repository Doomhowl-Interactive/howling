#include "color_sequence.hh"

namespace HOWLING_NAMESPACE
{
Color ColorSequence::nextColor()
{
    Color color = getNextColor();
    mIndex++;
    return color;
}

Color RainbowColorSequence::getNextColor()
{
    constexpr Color colors[] = {
        RED,
        ORANGE,
        YELLOW,
        GREEN,
        BLUE,
        VIOLET,
    };

    return colors[mIndex % std::size(colors)];
}

RandomColorSequence::RandomColorSequence(unsigned char minElement, unsigned char maxElement, std::optional<unsigned int> seed)
    : mMinElement(minElement)
    , mMaxElement(maxElement)
    , mRng(seed)
{
}

Color RandomColorSequence::getNextColor()
{
    return Color {
        static_cast<unsigned char>(mRng.randomValue(mMinElement, mMaxElement)),
        static_cast<unsigned char>(mRng.randomValue(mMinElement, mMaxElement)),
        static_cast<unsigned char>(mRng.randomValue(mMinElement, mMaxElement)),
        255,
    };
}

GradientColorSequence::GradientColorSequence(Color startColor, Color endColor, std::size_t steps)
    : mStartColor(startColor)
    , mEndColor(endColor)
    , mSteps(steps)
{
}

Color GradientColorSequence::getNextColor()
{
    float ratio = static_cast<float>(mIndex) / static_cast<float>(mSteps);
    return Color {
        static_cast<unsigned char>(mStartColor.r + (mEndColor.r - mStartColor.r) * ratio),
        static_cast<unsigned char>(mStartColor.g + (mEndColor.g - mStartColor.g) * ratio),
        static_cast<unsigned char>(mStartColor.b + (mEndColor.b - mStartColor.b) * ratio),
        255,
    };
}

}
