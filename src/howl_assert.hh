#pragma once
#include <cassert>
#include <spdlog/spdlog.h>

#ifdef NDEBUG

#define H_ASSERT(B)
#define H_ASSERT_EX(X, S, Y)

#else

inline void breakOnWindows()
{
#ifdef WIN32
    __debugbreak();
#endif
}

#define H_ASSERT(B)                                                                 \
    {                                                                               \
        if (!(B))                                                                   \
        {                                                                           \
            spdlog::error("Boolean assertion failed at {}:{}", __FILE__, __LINE__); \
            breakOnWindows();                                                       \
            assert(0 && "Assertion failed");                                        \
        }                                                                           \
    }

#define H_ASSERT_EX(X, S, Y)                                                                 \
    {                                                                                        \
        if (!((X)S(Y)))                                                                      \
        {                                                                                    \
            spdlog::error("Assertion failed at {}:{} - {} {} {} failed", __FILE__, __LINE__, \
                          (X), #S, (Y));                                                     \
            breakOnWindows();                                                                \
            assert(0 && "Assertion failed");                                                 \
        }                                                                                    \
    }

#endif
