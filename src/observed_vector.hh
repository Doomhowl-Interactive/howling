#pragma once
#include <functional>
#include <set>
#include <vector>

namespace howl
{
/**
 * std::vector that sends listeners an event when it is mutated.
 */
template<typename T>
class observed_vector
{
public:
    class listener
    {
    public:
        virtual ~listener() = default;
        virtual void onVectorChanged() = 0;
    };

    constexpr observed_vector(std::size_t size, T defaultValue = {})
        : mVec(size, defaultValue)
    {
    }

    constexpr observed_vector() = default;

    template <typename Func>
    constexpr void mutate(Func mutateFunc)
    {
        mutateFunc(mVec);
        for (listener* lis : listener)
        {
            lis->onVectorChanged();
        }
    }

    /// Use if you know what you're doing.
    constexpr std::vector<T>& bypass()
    {
        return mVec;
    }

    /// read only access to vector
    constexpr const std::vector<T>& operator*() const
    {
        return mVec;
    }

    /// read only access to vector
    constexpr const std::vector<T>* operator->() const
    {
        return &mVec;
    }

    constexpr void addListener(listener* list)
    {
        mListeners.emplace(list);
    }

    constexpr void removeListener(listener* list)
    {
        mListeners.erase(list);
    }

private:
    std::vector<T> mVec {};
    std::set<listener*> mListeners {};
};
}