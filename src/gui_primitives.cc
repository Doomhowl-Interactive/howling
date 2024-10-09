#include "gui_primitives.hh"
#include "raylib.h"

namespace HOWLING_NAMESPACE
{

using LuaRectangle = sol::table;

Rectangle luaRect(const sol::table& table)
{
    return {
        .x = table.get_or("x", 0.f),
        .y = table.get_or("y", 0.f),
        .width = table.get_or("w", 0.f),
        .height = table.get_or("h", 0.f)
    };
}

LUAFUNC static sol::table get_screen_size(sol::state& state)
{
    auto tbl = state.create_table();
    tbl["w"] = GetScreenWidth();
    tbl["h"] = GetScreenHeight();
    tbl["x"] = GetScreenWidth();
    tbl["y"] = GetScreenHeight();
    return tbl;
}

LUAFUNC static bool draw_text_button(LuaRectangle ldest, std::string text)
{
    Rectangle dest = luaRect(ldest);
    DrawRectangleRec(dest, LIGHTGRAY);
    // Vector2 size = MeasureTextEx(
    DrawText(text.c_str(), dest.x + dest.width * 0.5f, dest.y + dest.height * 0.5f, 12, WHITE);

    bool hover = CheckCollisionPointRec(GetMousePosition(), dest);

    if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        return true;
    }
    return false;
}

void GuiPrimitives::registerLuaPlugin(LuaMachine& machine)
{
    machine.registerLuaFunction("draw_text_button", draw_text_button);
    machine.registerLuaFunction("get_screen_size", [&machine](){ return get_screen_size(machine.state); });
}

}
