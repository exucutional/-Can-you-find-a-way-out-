local objects = require "scripts/objects"
function nope()
end
function player_ball(player, mtv)
    player:move(mtv)
end
function ball_player(ball, mtv)
    ball:move(mtv)
end
function ball_ball(ball, mtv)
    ball:move(mtv)
end
function ball_bullet(ball, mtv)
    ball:setVelocity(mtv * setting.repulsion_rate)
end
function bullet_ball(bullet)
    bullet:deactivate()
end