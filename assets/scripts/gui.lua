
function rect(x,y,w,h)
   return {x=x,y=y,w=w,h=h}
end

function perc_w(perc)
   return get_screen_size().w * perc
end

function perc_h(perc)
   return get_screen_size().h * perc
end
