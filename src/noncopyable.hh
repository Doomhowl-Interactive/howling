#pragma once

namespace howl
{
/**
 * Inherit this class to prevent copying.
 */
class noncopyable
{
protected:
    noncopyable() = default;
    ~noncopyable() = default;

    noncopyable(const noncopyable&) = delete;
    noncopyable& operator=(const noncopyable&) = delete;
};
}
