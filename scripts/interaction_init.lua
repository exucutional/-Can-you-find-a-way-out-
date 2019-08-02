local objects = require "scripts/objects"
intManager:addScript("player_ball", setting.type.player, setting.type.ball)
intManager:addScript("player_wall", setting.type.player, setting.type.wall)
intManager:addScript("ball_player", setting.type.ball, setting.type.player)
intManager:addScript("ball_ball", setting.type.ball, setting.type.ball)
intManager:addScript("ball_bullet", setting.type.ball, setting.type.bullet)
intManager:addScript("ball_wall", setting.type.ball, setting.type.wall)
intManager:addScript("bullet_ball", setting.type.bullet, setting.type.ball)
intManager:addScript("bullet_wall", setting.type.bullet, setting.type.wall)