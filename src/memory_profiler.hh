#pragma once
#include <cstddef>
#include <utility>

namespace HOWLING_NAMESPACE
{
namespace memory
{

[[nodiscard]] std::size_t getAllocationsSinceStart();
[[nodiscard]] std::size_t getDeallocationsSinceStart();

/// Start measuring new (de)allocations. Use endAllocationCount() to stop.
void beginAllocationCount();

/// Stop counting (de)allocations and return how many happened since beginAllocationCount()
/// \returns Pair containing allocation and deallocation count.
[[nodiscard]] std::pair<std::size_t, std::size_t> endAllocationCount();

}
}
