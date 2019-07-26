local objects = require "scripts/objects"
intManager:addScript("player_ball", setting.type.player, setting.type.ball)
intManager:addScript("ball_player", setting.type.ball, setting.type.player)
intManager:addScript("ball_ball", setting.type.ball, setting.type.ball)
intManager:addScript("ball_bullet", setting.type.ball, setting.type.bullet)
intManager:addScript("bullet_ball", setting.type.bullet, setting.type.ball)