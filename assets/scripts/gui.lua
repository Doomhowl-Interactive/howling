--- Returns a percentage of the screen width.
--- @param perc number The percentage (from 0 to 1) of the screen width.
--- @return number The calculated width value.
function perc_w(perc)
   return GetScreenWidth() * perc
end

--- Returns a percentage of the screen height.
--- @param perc number The percentage (from 0 to 1) of the screen height.
--- @return number The calculated height value.
function perc_h(perc)
   return GetScreenHeight() * perc
end

--- Returns a percentage of the smaller dimension (width or height).
--- @param perc number The percentage (from 0 to 1) of the smaller dimension.
--- @return number The calculated size value of the smaller dimension.
function perc_min(perc)
   return math.min(GetScreenWidth(), GetScreenHeight()) * perc
end

--- Returns a percentage of the larger dimension (width or height).
--- @param perc number The percentage (from 0 to 1) of the larger dimension.
--- @return number The calculated size value of the larger dimension.
function perc_max(perc)
   return math.max(GetScreenWidth(), GetScreenHeight()) * perc
end

--- Create rectangle around a center point
--- @param pos Vector2 center point
--- @param width number Width amount
--- @param height number Height amount
--- @return Rectangle
function rect_with_center(pos, width, height)
    return Rectangle(
        pos.x - width * 0.5,
        pos.y - height * 0.5,
        width,
        height
    )
end

--- Create rect from absolute points
--- @param x number
--- @param y number
--- @param x2 number
--- @param y2 number
--- @return Rectangle
function abs_rect(x, y, x2, y2)
   return Rectangle(
      x, y,
      x2 - x, y2 - y
   )
end

--- Copy a color, so it can be mutated without messing things up. GC go vroom.
--- @param color Color input color
--- @return Color copied color
function color_copy(color)
    return Color(color.r, color.g, color.b, color.a)
end

--- Copy a rectangle, so it can be mutated without messing things up. GC go vroom.
--- @param rect Rectangle input rect
--- @return Rectangle copied rect
function rect_copy(rect)
    return Rectangle(rect.x, rect.y, rect.width, rect.height)
end

--- Scale color components
--- @param color Color
--- @param scale number Scale between 0 and 1
--- @return color Color **New** scaled color. Can't mutate the existing one.
function color_brightness(color, scale)
    color.r = math.floor( (color.r / 255.0) * scale * 255.0 )
    color.g = math.floor( (color.g / 255.0) * scale * 255.0 )
    color.b = math.floor( (color.b / 255.0) * scale * 255.0 )
    return color
end

--- Draws a text button and checks for mouse clicks.
--- @param rect Rectangle The rectangle (x, y, width, height) defining the button's position and size.
--- @param color Color Background color of the button.
--- @param text string The text displayed on the button.
--- @param roundness number Roundness, zero for none.
--- @param segments number Segments for the roundness, zero for none.
--- @return boolean Returns true if the button is clicked, false otherwise.
function draw_text_button_ex(rect, text, color, roundness, segments)
   local hover = CheckCollisionPointRec(GetMousePosition(), rect)

   if hover then
       color = color_brightness(color_copy(color), 0.9)
   end

   if segments == 0 or roundness == 0 then
       DrawRectangleRec(rect, color) 
   else
       DrawRectangleRounded(rect, roundness, segments, color)
   end

   DrawTextEx(GetFontDefault(), text, Vector2(rect.x + rect.width / 2, rect.y + rect.height / 2),
              perc_min(0.1), 1.0, WHITE)


   if hover and IsMouseButtonPressed(MOUSE_LEFT_BUTTON) then
      return true
   end
   return false
end

--- Draws a text button and checks for mouse clicks.
--- @param rect Rectangle The rectangle (x, y, width, height) defining the button's position and size.
--- @param color Color Background color of the button.
--- @return boolean Returns true if the button is clicked, false otherwise.
function draw_text_button(rect, text, color)
    return draw_text_button_ex(rect, text, color, 0, 0)
end

--- TODO
function draw_icon_button(texture, pos, size)
   local src = Rectangle(0.0, 0.0, texture.width, texture.height)
   local dest = Rectangle(
      pos.x - size / 2,
      pos.y - size / 2,
      size,
      size
   )
   DrawTexturePro(texture, src, dest, Vector2(0.0, 0.0), 0.0, WHITE)
end

--- @param rect Rectangle
--- @param amount number
--- @return Rectangle
function pad_rect(rect, amount)
   return Rectangle(
      rect.x + amount * 0.5,
      rect.y + amount * 0.5,
      rect.width - amount,
      rect.height - amount
   )
end

--- @param rect Rectangle
function BeginScissorModeEx(rect)
   BeginScissorMode(math.floor(rect.x),
      math.floor(rect.y),
      math.floor(rect.width),
      math.floor(rect.height));
end
