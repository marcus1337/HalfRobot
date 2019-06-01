


function wait(self)

	local tim = getTicks(model)-self.etime

	if tim > 80 then
		local dir = getDir(entity)
		if dir == 0 then
			setDir(entity, 1)
		else
			setDir(entity,0)
		end

		return run
	end

	return nil
end



function run(self)

local dir = getDir(entity)

if updown then

	if dir == 0 and isBlocked2(entity, model) == true then
		return wait
	elseif dir == 1 and isBlocked2(entity, model) == true then
		return wait
	end

else

	if dir == 0 and isBlocked(entity, model) == true then
		return wait
	elseif dir == 1 and isBlocked(entity, model) == true then
		return wait
	end

	end

return nil
end

function enter(self)

	self.etime = getTicks(model)

	if self.action == wait then
		self.xv = 0
		self.yv = 0
	end

	if self.action == run then
		local dir = getDir(entity)
		--print("dir: " .. tostring(dir) .. "  updown: " .. tostring(updown))
		if updown == false then
			if dir == 1 then
				self.xv = 1
			else
				self.xv = -1
			end
		else
			if dir == 1 then
				self.yv = -1
			else
				self.yv = 1
			end
		end

	end

	return nil
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
