
function perc_w(perc)
   return GetScreenWidth() * perc
end

function perc_h(perc)
   return GetScreenHeight() * perc
end

function perc_min(perc)
   return min(GetScreenWidth(), GetScreenHeight()) * perc
end

function perc_max(perc)
   return max(GetScreenWidth(), GetScreenHeight()) * perc
end

function draw_text_button(rect, text)
   DrawRectangleRec(rect, LIGHTGRAY);
   DrawTextEx(GetFontDefault(), text, Vector2(rect.x + rect.width / 2, rect.y + rect.height / 2), 12, 1.0, WHITE)

   local hover = CheckCollisionPointRec(GetMousePosition(), rect)

   if hover and IsMouseButtonPressed(MOUSE_LEFT_BUTTON) then
      return true
   end
   return false
end
