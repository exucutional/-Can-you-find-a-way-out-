local objects = require "scripts/objects"
intManager:addScript("player_ball", objects.type.player, objects.type.ball)
intManager:addScript("ball_player", objects.type.ball, objects.type.player)