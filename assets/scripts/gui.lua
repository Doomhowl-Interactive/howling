
function rect(x,y,w,h)
   return {x=x,y=y,w=w,h=h}
end

function perc_w(perc)
   return get_screen_size().w * perc
end

function perc_h(perc)
   return get_screen_size().h * perc
end

function perc_min(perc)
   local size = get_screen_size()
   return min(size.x, size.y)
end

function perc_max(perc)
   local size = get_screen_size()
   return max(size.x, size.y)
end
