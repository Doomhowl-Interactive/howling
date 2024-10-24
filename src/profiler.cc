#include "profiler.hh"
#include "logging.hh"
#include "raymath.h"

#include <unordered_map>
#include <deque>
#include <chrono>
#include <cassert>

namespace HOWLING_NAMESPACE
{
namespace profiler
{

class ProfilerTask {
public:
    void start()
    {
        startMicros = GetCurrentMicrosecond();
    }

    void end()
    {
        constexpr size_t SAMPLE_COUNT = 128;
        while (samples.size() > SAMPLE_COUNT - 1) {
            samples.pop_back();
        }

        size_t microsPassed = GetCurrentMicrosecond() - startMicros;
        double millisPassed = static_cast<double>(microsPassed) / 1000.0;
        samples.push_front(millisPassed);
    }

    double best() const
    {
        auto best = std::min_element(samples.begin(), samples.end());
        if (best != samples.end()) {
            return *best;
        }
        return 0.0;
    }

    double worst() const
    {
        auto worst = std::max_element(samples.begin(), samples.end());
        if (worst != samples.end()) {
            return *worst;
        }
        return 0.0;
    }

    double average() const
    {
        double sum = 0.f;
        for (const double s : samples) {
            sum += s;
        }
        return sum / samples.size();
    }

private:
    std::deque<double> samples {};
    size_t startMicros = 0;

    static size_t GetCurrentMicrosecond()
    {
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
    }
};

static std::unordered_map<std::string, ProfilerTask> tasks;
static bool collapsed = false;

const std::string& profiler::beginTask(const std::string& name)
{
    ProfilerTask* task;
    try {
        task = &tasks.at(name);
    } catch (std::out_of_range) {
        task = &tasks[name];
    }
    task->start();
    return name;
}

void profiler::endTask(const std::string& name)
{
    try {
        tasks.at(name).end();
    } catch (std::out_of_range) {
        spdlog::warn("Profiler task named {} was not started!", name);
        assert(0);
    }
}

void profiler::print(std::ostream& os)
{
    auto format = [](double time) {
        if (time > 1000.0 / 60.0) {
            return fmt::format("!<{:.4f}>!", time);
        }
        return fmt::format("{:.4f}", time);
    };

    if (IsKeyPressed(KEY_P)) {
        collapsed = !collapsed;
    }

    if (collapsed) {
        os << "Profiler collapsed";
    } else {
        os << "Profiler (in millis)\n\n\n";

        for (auto& [name, task] : tasks) {
            os << name
               << " : worst " << format(task.worst())
               << " : best " << format(task.best())
               << " : avg " << format(task.average()) << "\n\n";
        }
    }
}

void profiler::draw(Font font, Vector2 pos, float textSize)
{
    std::stringstream str;
    print(str);
    const std::string text = str.str();

    Vector2 size = MeasureTextEx(font, text.c_str(), textSize, 1.f);
    DrawRectangleV({ 10.f, 40.f }, Vector2Multiply(size, { 1.1f, 1.f }), ColorAlpha(BLACK, 0.7f));
    DrawTextEx(font, text.c_str(), { 10.f, 40.f }, textSize, 1.f, YELLOW);
}


}
}
