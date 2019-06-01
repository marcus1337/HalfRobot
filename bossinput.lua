
function wait(self)

	local tim = getTicks(model)-self.etime
	local x, y = getPosV(entity)
	local dir = getDir(entity)

	if(tim > 50) then
		return run
	end

	if inAir(entity) == 1 then
	return jump
	end

	if x < 50 and dir == 0 then
		setDir(entity, 1)
		fire(entity)
	elseif x > 330 and dir == 1 then
		setDir(entity, 0)
		fire(entity)
	end

	return nil
end

function jump(self)

	local x, y = getPosV(entity)
	local ticks = getTicks(model)

	local tim = getTicks(model)-self.etime

	if tim > 25 and self.yv < 0 then
		self.yv = 1
	end

	if inAir(entity) == 0 and self.yv > 0 then
		if self.xv == 0 then
			return wait
		else
			return run
		end
	end

	if self.yv > 0 and self.yv < 2 then
		self.yv = self.yv + 1
	end
	if self.yv < 0 and self.yv > -2 then
		self.yv = self.yv - 1
	end

	return nil
end

function run(self)

local x, y = getPosV(entity)
local dir = getDir(entity)

--print("x: " .. x .. "  dir: " .. dir)
	if x < 40 and dir == 0 then
		return wait
	end
	if x > 330 and dir == 1 then
		return wait
	end

if inAir(entity) == 1 then
	return jump
end

if dir == 0 and isBlocked(entity, model) == true then
	return jump
end

	return nil
end

function enter(self)
	self.etime = getTicks(model)
	self.yv = 0
	if self.action == wait then
		self.xv = 0
		self.yv = 0
	return nil
	elseif self.action == jump then
	if inAir(entity) == 0 then
		self.yv = -1
		else
		self.yv = 1
	 end

	return nil
	elseif self.action == run then

		local dir = getDir(entity)
		if dir == 1 then
			self.xv = 1
			else
			self.xv = -1
		end
	return nil
end
end

local MyState = {}
MyState.__index = MyState
function MyState.new()
	local self = setmetatable({}, MyState)
	self.enter = enter
	self.action = wait
	self.etime = 0
	self.xv = 0
	self.yv = 0
	return self
end

function MyState.set_state(self, newstate)
  self.action = newstate
end

local stat = MyState.new()


function doState()

	local nystat = stat:action()

	if nystat ~= nil then
		stat.action = nystat
		stat:enter()
	end

	return stat.xv, stat.yv
end
