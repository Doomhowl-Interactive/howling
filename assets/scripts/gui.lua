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

--- Draws a text button and checks for mouse clicks.
--- @param rect Rectangle The rectangle (x, y, width, height) defining the button's position and size.
--- @param text string The text displayed on the button.
--- @return boolean Returns true if the button is clicked, false otherwise.
function draw_text_button(rect, text)
   DrawRectangleRec(rect, LIGHTGRAY);
   DrawTextEx(GetFontDefault(), text, Vector2(rect.x + rect.width / 2, rect.y + rect.height / 2), 12, 1.0, WHITE)

   local hover = CheckCollisionPointRec(GetMousePosition(), rect)

   if hover and IsMouseButtonPressed(MOUSE_LEFT_BUTTON) then
      return true
   end
   return false
end
