#pragma once
#include <string>
#include <ostream>

#include "raylib.h"

namespace HOWLING_NAMESPACE
{
namespace profiler
{

const std::string& beginTask(const std::string& name);
void endTask(const std::string& name);
void print(std::ostream& os);
void draw(Font font, Vector2 pos, float textSize);

}
}
