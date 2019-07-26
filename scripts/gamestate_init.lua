--gamestate_init_lua
local objects = require "scripts/objects"
local assets = require "scripts/assets"
--TEXTURE INITIALIZATION
for key1, val1 in pairs(textures) do
	local texture = asManager:createTexture(textures[key1].name)
	assert(texture:loadFromFile(textures[key1].path, IntRect.new()), "_____ERROR: Texture is no loaded")
end
--ANIMATION INITIALIZATION
for key1, val in pairs(animations) do
	local animation = asManager:createAnimation(animations[key1].name)
	local texture = asManager:getTexture(animations[key1].texture)
	animation:setSpriteSheet(texture);
	for _, frame in pairs(animations[key1].frames) do
		animation:addFrame(IntRect.new(frame[1], frame[2], frame[3], frame[4]))
	end
end
--DYNAMIC OBJECTS INITIALIZATION
for key1, val1 in pairs(dynobjlist) do
	local obj = oManager:newDynamicObjectType(dynobjlist[key1].type)
	obj:setPosition(dynobjlist[key1].position[1], dynobjlist[key1].position[2])
	oManager:addDynamicObject(obj)
	for key2, val2 in pairs(dynobjlist[key1].animation) do
		obj:addAnimation(asManager:getAnimation(val2), setting.animation[key2])
		obj:setAnimation(setting.animation[key2])
	end
end
local mainObj = oManager:findDynamicObject(setting.type.player)
player:setObject(mainObj)
local ball2 = oManager:newDynamicObject(setting.type.ball)
ball2:setPosition(550, 100)
--ball2:setOrigin(150, 150)
ball2:setRotation(45)
--ball2:setOrigin(0, 0)