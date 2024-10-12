#pragma once

/*
  Adapted from https://github.com/RobLoach/raylib-cpp with license:

  Copyright (c) 2019-2021 Rob Loach (@RobLoach)

  This software is provided "as-is", without any express or implied warranty. In no event
  will the authors be held liable for any damages arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose, including commercial
  applications, and to alter it and redistribute it freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not claim that you
  wrote the original software. If you use this software in a product, an acknowledgment
  in the product documentation would be appreciated but is not required.

  2. Altered source versions must be plainly marked as such, and must not be misrepresented
  as being the original software.

  3. This notice may not be removed or altered from any source distribution.
*/

#include "raylib.h"
#include "raymath.h"

#include <string>

namespace HOWLING_NAMESPACE
{

/**
 * Determine whether or not the vectors are equal.
 */
inline bool operator==(const Vector2& subj, const Vector2& other)
{
    return subj.x == other.x && subj.y == other.y;
}

/**
 * Add two vectors (v1 + v2)
 */
inline Vector2 operator+(const Vector2& subj, const Vector2& vector2)
{
    return Vector2Add(subj, vector2);
}

inline Vector2& operator+=(Vector2& subj, const Vector2& vector2)
{
    subj = Vector2Add(subj, vector2);
    return subj;
}

/**
 * Subtract two vectors (v1 - v2)
 */
inline Vector2& operator-(Vector2& subj, const Vector2& vector2)
{
    subj = Vector2Subtract(subj, vector2);
    return subj;
}

inline Vector2& operator-=(Vector2& subj, const Vector2& vector2)
{
    subj = Vector2Subtract(subj, vector2);
    return subj;
}

/**
 * Negate vector
 */
inline Vector2 operator-(const Vector2& subj)
{
    return Vector2Negate(subj);
}

/**
 * Multiply vector by vector
 */
inline Vector2 operator*(const Vector2& subj, const Vector2& vector2)
{
    return Vector2Multiply(subj, vector2);
}

/**
 * Scale vector (multiply by value)
 */
inline Vector2 operator*(const Vector2& subj, const float scale)
{
    return Vector2Scale(subj, scale);
}

inline Vector2& operator*=(Vector2& subj, const float scale)
{
    subj = Vector2Scale(subj, scale);
    return subj;
}

inline Vector2& operator*=(Vector2& subj, const Vector2& vector2)
{
    subj = Vector2Multiply(subj, vector2);
    return subj;
}

/**
 * Divide vector by vector
 */
inline Vector2 operator/(const Vector2& subj, const Vector2& vector2)
{
    return Vector2Divide(subj, vector2);
}

/**
 * Divide vector by value
 */
inline Vector2 operator/(const Vector2& subj, const float div)
{
    return Vector2Scale(subj, 1.f / div);
}

inline Vector2& operator/=(Vector2& subj, const Vector2& vector2)
{
    subj = Vector2Divide(subj, vector2);
    return subj;
}

inline Vector2& operator/=(Vector2& subj, const float div)
{
    subj = Vector2Scale(subj, 1.f / div);
    return subj;
}

inline bool operator==(const Vector3& subj, const Vector3& other)
{
    return subj.x == other.x && subj.y == other.y && subj.z == other.z;
}

/**
 * Add two vectors
 */
inline Vector3 operator+(const Vector3& subj, const Vector3& vector3)
{
    return Vector3Add(subj, vector3);
}

inline Vector3& operator+=(Vector3& subj, const Vector3& vector3)
{
    subj = Vector3Add(subj, vector3);
    return subj;
}

/**
 * Subtract two vectors.
 */
inline Vector3 operator-(const Vector3& subj, const Vector3& vector3)
{
    return Vector3Subtract(subj, vector3);
}

/**
 * Negate provided vector (invert direction)
 */
inline Vector3 operator-(const Vector3& subj)
{
    return Vector3Negate(subj);
}

inline Vector3& operator-=(Vector3& subj, const Vector3& vector3)
{
    subj = Vector3Subtract(subj, vector3);
    return subj;
}

/**
 * Multiply vector by vector
 */
inline Vector3 operator*(const Vector3& subj, const Vector3& vector3)
{
    return Vector3Multiply(subj, vector3);
}

/**
 * Multiply vector by scalar
 */
inline Vector3 operator*(const Vector3& subj, const float scaler)
{
    return Vector3Scale(subj, scaler);
}

inline Vector3& operator*=(Vector3& subj, const float scale)
{
    subj = Vector3Scale(subj, scale);
    return subj;
}

inline Vector3& operator*=(Vector3& subj, const Vector3 vector3)
{
    subj = Vector3Multiply(subj, vector3);
    return subj;
}

/**
 * Divide vector by vector
 */
inline Vector3 operator/(const Vector3& subj, const Vector3& vector3)
{
    return Vector3Divide(subj, vector3);
}

/**
 * Divide a vector by a value.
 */
inline Vector3 operator/(const Vector3& subj, const float div)
{
    return Vector3Scale(subj, 1.f / div);
}

inline bool operator==(const Vector4& subj, const Vector4& other)
{
    return subj.x == other.x && subj.y == other.y && subj.z == other.z && subj.w == other.w;
}

}
