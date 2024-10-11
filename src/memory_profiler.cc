#include "memory_profiler.hh"

#ifdef LOG_ALLOCATIONS // debug mode

#include <cstdlib>
#include <iostream>
#include <cassert>

static size_t sAllocations = 0;
static size_t sDeallocations = 0;

void* operator new(size_t size)
{
    ++sAllocations;
    return malloc(size);
}

void operator delete(void* ptr) noexcept
{
    ++sDeallocations;
    free(ptr);
}

void* operator new[](size_t size)
{
    ++sAllocations;
    return malloc(size);
}

void operator delete[](void* ptr) noexcept
{
    ++sDeallocations;
    free(ptr);
}

namespace {

struct Printer {
    ~Printer()
        {
            std::cout << "Allocations: " << sAllocations << '\n';
            std::cout << "Deallocations: " << sDeallocations << '\n';
        }
};

static Printer sP = {};

}

namespace HOWLING_NAMESPACE
{
namespace memory
{

std::size_t getAllocationsSinceStart()
{
    return sAllocations;
}

std::size_t getDeallocationsSinceStart()
{
    return sDeallocations;
}

static std::size_t sAllocationsOnStart = 0;
static std::size_t sDeallocationsOnStart = 0;
static bool sMeasuringAllocations = false;

void beginAllocationCount()
{
    sAllocationsOnStart = sAllocations;
    sDeallocationsOnStart = sDeallocations;
    sMeasuringAllocations = true;
}

std::pair<std::size_t,std::size_t> endAllocationCount()
{
    assert(sMeasuringAllocations && "beginAllocationCount not called");
    sMeasuringAllocations = false;
    return std::make_pair<std::size_t,std::size_t>(
        sAllocations - sAllocationsOnStart,
        sDeallocations - sDeallocationsOnStart);
}


}
}

#else // release mode

namespace HOWLING_NAMESPACE
{
namespace memory
{

std::size_t getAllocationsSinceStart()
{
    return 0;
}

std::size_t getDeallocationsSinceStart()
{
    return 0;
}

void beginAllocationCount()
{
}

std::pair<std::size_t,std::size_t> endAllocationCount()
{
    return std::make_pair<std::size_t,std::size_t>(0,0);
}

}
}

#endif
