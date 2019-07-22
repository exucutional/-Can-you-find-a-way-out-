--gamestate_init_lua
local objects = require "scripts/objects"
local assets = require "scripts/assets"
for key1, val1 in pairs(textures) do
	local texture = asManager:createTexture(textures[key1].name)
	assert(texture:loadFromFile(textures[key1].path, IntRect.new()), "_____ERROR: Texture is no loaded")
end
for key1, val in pairs(animations) do
	local animation = asManager:createAnimation(animations[key1].name)
	local texture = asManager:getTexture(animations[key1].texture)
	animation:setSpriteSheet(texture);
	for key2, val2 in pairs(animations[key1].frames) do
		animation:addFrame(IntRect.new(val2[1], val2[2], val2[3], val2[4]))
	end
end
for key1, val1 in pairs(objlist) do
	;
end
local animation_player_down = asManager:getAnimation("animation_player_down")
local animation_player_left = asManager:getAnimation("animation_player_left")
local animation_player_right = asManager:getAnimation("animation_player_right")
local animation_player_up = asManager:getAnimation("animation_player_up")
local animation_ball = asManager:getAnimation("animation_ball")
local mainObj = oManager:createDynamicGameObject()
player:setObject(mainObj)
mainObj:addAnimation(animation_player_down, aDown)
mainObj:addAnimation(animation_player_left, aLeft)
mainObj:addAnimation(animation_player_up, aUp)
mainObj:addAnimation(animation_player_right, aRight)
mainObj:setPosition(0, 0)
mainObj:setAnimation(aDown)
mainObj:setType(setting.type.player)
local ball = oManager:createDynamicGameObject()
ball:addAnimation(animation_ball, aDown)
ball:setPosition(300, 300)
ball:setAnimation(aDown)
ball:setType(setting.type.ball)