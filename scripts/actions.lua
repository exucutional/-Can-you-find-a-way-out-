local objects = require "scripts/objects"
function nope()
end
function player_move_down(object)
    local velocity = object:getVelocity()
    object:setVelocity(velocity.x, setting.speed_rate)
    object:playAnimation(setting.animation.walk)
end
function player_move_left(object)
    local velocity = object:getVelocity()
    object:setVelocity(-setting.speed_rate, velocity.y)
    object:playAnimation(setting.animation.walk)
    object:mirrorFlip()
end
function player_move_up(object)
    local velocity = object:getVelocity()
    object:setVelocity(velocity.x, -setting.speed_rate)
    object:playAnimation(setting.animation.walk)
end
function player_move_right(object)
    local velocity = object:getVelocity()
    object:setVelocity(setting.speed_rate, velocity.y)
    object:playAnimation(setting.animation.walk)
    object:mirrorUnFlip()
end