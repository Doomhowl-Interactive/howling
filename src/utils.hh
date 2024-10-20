#pragma once
#include <cstddef>
#include <cstdlib>
#include <stdexcept>

#include "hash_utils.hh"
#include "howl_assert.hh"
#include "logging.hh"
#include "math_operators.hh"

#include "raylib.h"
#include "raymath.h"

// macros for unit testing
#ifdef I_WANT_TO_BREAK_FREE
#define protected public
#define private public
#endif

namespace HOWLING_NAMESPACE
{

template<typename T>
int sign(T val)
{
    return (T(0) < val) - (val < T(0));
}

template<typename T, typename C>
T* cmalloc(C count)
{
    return reinterpret_cast<T*>(std::calloc(static_cast<std::size_t>(count), sizeof(T)));
}

inline Vector3 boundingBoxCenter(const BoundingBox& bb)
{
    auto size = Vector3Subtract(bb.max, bb.min);
    return Vector3Add(bb.min, Vector3Scale(size, 0.5f));
}

inline BoundingBox boundsWithCenter(Vector3 pos, Vector3 size)
{
    Vector3 halfSize = Vector3Scale(size, 0.5f);
    return {
        Vector3Subtract(pos, halfSize),
        Vector3Add(pos, halfSize)
    };
}

inline Vector3 boundingBoxSize(BoundingBox bounds)
{
    return Vector3Subtract(bounds.max, bounds.min);
}

inline void drawSolidBoundingBox(BoundingBox bounds, Color color)
{
    DrawCubeV(boundingBoxCenter(bounds), boundingBoxSize(bounds), color);
}

inline bool colorIsEqual(Color a, Color b, bool checkAlpha = true)
{
    bool eq = a.r == b.r && a.g == b.g && a.b == b.b;
    if (eq && checkAlpha)
    {
        eq = a.a == b.a;
    }
    return eq;
}

inline Vector3 colorToVec3(Color color)
{
    return {
        static_cast<float>(color.r) / 255.f,
        static_cast<float>(color.g) / 255.f,
        static_cast<float>(color.b) / 255.f
    };
}

inline Color randomColor(int minElement, int maxElement, int opacity = 255)
{

    return Color {
        unsigned char(GetRandomValue(minElement, maxElement)),
        unsigned char(GetRandomValue(minElement, maxElement)),
        unsigned char(GetRandomValue(minElement, maxElement)),
        unsigned char(opacity)
    };
}

inline float mapValue(float value,
                      float istart,
                      float istop,
                      float ostart,
                      float ostop)
{
    return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}

struct Point3D
{
    int x;
    int y;
    int z;

    constexpr auto operator<=>(const Point3D&) const = default;

    constexpr Point3D()
        : x(0)
        , y(0)
        , z(0)
    {
    }

    constexpr Point3D(int x, int y, int z)
        : x(x)
        , y(y)
        , z(z)
    {
    }

    constexpr Point3D(const Vector3& vec)
        : x(int(vec.x))
        , y(int(vec.y))
        , z(int(vec.z))
    {
    }

    constexpr int operator[](int index) const
    {
        switch (index)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            throw std::out_of_range("invalid index");
        }
    }
};

inline bool isVector3Zero(Vector3 vec)
{
    return FloatEquals(vec.x, 0.f) && FloatEquals(vec.y, 0.f) && FloatEquals(vec.z, 0.f);
}

}
