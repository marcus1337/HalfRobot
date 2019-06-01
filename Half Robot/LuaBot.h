#pragma once
#include "lua.hpp"

#include "Entity.h"
#include "Model.h"
#include <chrono>
#include <string>

class LuaBot {
public:
	~LuaBot() {
		lua_close(L);
	}

	LuaBot(int botId) {
		mainpath = getmainpath();

		if (botId == 0)
			_luaFile = mainpath + "bossinput.lua";
		if (botId == 1 || botId == 2)
			_luaFile = mainpath + "easybotInput.lua";

		if (botId == 5)
			_luaFile = mainpath + "bossinput2.lua";
		if (botId == 6)
			_luaFile = mainpath + "bossinput3.lua";
		if (botId == 7)
			_luaFile = mainpath + "bossinput4.lua";

		L = luaL_newstate();
		luaL_openlibs(L);

		lua_register(L, "fire", fireWep);
		lua_register(L, "getTime", getTime);
		lua_register(L, "getPosV", getXYV);
		lua_register(L, "getDir", getDir);
		lua_register(L, "setDir", setDir);
		lua_register(L, "inAir", getInAir);
		lua_register(L, "isBlocked", isBlocked);
		lua_register(L, "isBlocked2", isBlocked2);

		lua_register(L, "getDistPlayer", getPlayerDistance);

		lua_register(L, "getTicks", getModelTicks);


		if (luaL_loadfile(L, _luaFile.c_str())) {
			exit(1);
		}

		if (botId == 2) {
			lua_pushboolean(L, true);
			lua_setglobal(L, "updown");
		}
		else if (botId == 1) {
			lua_pushboolean(L, false);
			lua_setglobal(L, "updown");
		}

		if (lua_pcall(L, 0, 0, 0))
			exit(1);
	
	}

	void handleInput(Entity& entity, Model& model, int& xv, int& yv) {
		lua_pushlightuserdata(L, &entity);
		lua_setglobal(L, "entity");
		lua_pushlightuserdata(L, &model);
		lua_setglobal(L, "model");
		lua_getglobal(L, "doState");
		lua_pcall(L, 0, 2, 0);
		xv = (int)lua_tointeger(L, -2);
		yv = (int)lua_tointeger(L, -1);
		lua_pop(L, 2);
	}

	void reload() {
		if (luaL_loadfile(L, _luaFile.c_str()) || lua_pcall(L, 0, 0, 0))
			exit(1);
	}

private:
	lua_State *L;
	std::string _luaFile;


	static int getTime(lua_State *L) {
		using namespace std::chrono;
		milliseconds ms = duration_cast<milliseconds>(
			system_clock::now().time_since_epoch());
		lua_pushinteger(L, ms.count() - 1499688322000);
		return 1;
	}

	static int getInAir(lua_State *L) {
		Entity* e = (Entity*)lua_touserdata(L, 1);
		lua_pushinteger(L, e->getPhysics()->isInAir());
		return 1;
	}

	static int getXYV(lua_State *L) {
		Entity* e = (Entity*)lua_touserdata(L, 1);
		int _tmpx = e->getX()-((e->getX() /400)*400);
		int _tmpy = e->getY()-((e->getY() /300)*300);
		lua_pushinteger(L, _tmpx);
		lua_pushinteger(L, _tmpy);
		return 2;
	}

	static int getPlayerDistance(lua_State *L) {
		Entity* e = (Entity*)lua_touserdata(L, 1);
		Model* m = (Model*)lua_touserdata(L, 2);
		int _tmpx = e->getX() - m->getPlayerEntity().getX();
		int _tmpy = e->getY() - m->getPlayerEntity().getY();
		lua_pushinteger(L, _tmpx);
		lua_pushinteger(L, _tmpy);
		return 2;
	}

	static int getDir(lua_State *L) {
		Entity* e = (Entity*)lua_touserdata(L, 1);
		lua_pushinteger(L, e->getDirection());
		return 1;
	}

	static int getModelTicks(lua_State *L) {
		Model* m = (Model*)lua_touserdata(L, 1);
		lua_pushinteger(L, m->getTicks());
		return 1;
	}

	static int setDir(lua_State *L) {
		Entity* e = (Entity*)lua_touserdata(L, 1);
		int d = (int)lua_tointeger(L, 2);
		e->setDirection(d);
		return 0;
	}

	static int isBlocked(lua_State *L) {
		Entity* e = (Entity*)lua_touserdata(L, 1);
		Model* m = (Model*)lua_touserdata(L, 2);
		if (e->getPhysics()->isXPathBlocked())
			lua_pushboolean(L, 1);
		else
			lua_pushboolean(L, 0);

		return 1;
	}

	static int isBlocked2(lua_State *L) {
		Entity* e = (Entity*)lua_touserdata(L, 1);
		Model* m = (Model*)lua_touserdata(L, 2);
		if (e->getPhysics()->isYPathBlocked())
			lua_pushboolean(L, 1);
		else
			lua_pushboolean(L, 0);

		return 1;
	}

	static int fireWep(lua_State *L) {
		using namespace std;
		Entity* e = (Entity*)lua_touserdata(L, 1);
		e->setWantFire(true);
		return 0;
	}




	void call_va(lua_State *L, const char *func, const char *sig, ...) {
		va_list v1;
		int narg = 0, nres = 0;

		va_start(v1, sig);

		lua_getglobal(L, func);

		////////
		bool stopper = false;
		for (narg = 0; *sig; narg++) {
			luaL_checkstack(L, 1, "too many arguments");

			switch (*sig++) {
			case 'd':
				lua_pushnumber(L, va_arg(v1, double));
				break;
			case 'i':
				lua_pushinteger(L, va_arg(v1, int));
				break;
			case 's':
				lua_pushstring(L, va_arg(v1, char*));
				break;
			case 'b':
				lua_pushboolean(L, va_arg(v1, bool));
				break;
			case '>':
				stopper = true;
				break;
			default:
				std::cerr << "ERROR " << std::endl;
			}
			if (stopper)
				break;
		}
		using namespace std;

		nres = strlen(sig);
		if (lua_pcall(L, narg, nres, 0) != 0)
			std::cout << "error calling: " << func << lua_tostring(L, -1) << std::endl;

		nres = -nres;
		while (*sig) {
			switch (*sig++) {
			case 'd':
			{
				int isnum;
				double n = lua_tonumberx(L, -1, &isnum);
				if (!isnum)
					std::cerr << "ERROR" << std::endl;
				*va_arg(v1, double*) = n;
				break;
			}
			case 'i':
			{
				int isnum;
				int n = (int)lua_tointegerx(L, -1, &isnum);
				if (!isnum)
					std::cerr << "ERROR" << std::endl;
				*va_arg(v1, int*) = n;
				lua_pop(L, 1);
				break;
			}
			case 's':
			{
				size_t somesize = 0;
				const char* s = lua_tolstring(L, -1, &somesize);
				if (s == NULL)
					exit(EXIT_FAILURE);
				char* tmp = new char[somesize];
				strcpy_s(tmp, somesize + 1, s);
				*va_arg(v1, const char**) = tmp;
				lua_pop(L, 1);
				break;
			}
			case 'b': {
				bool b = (bool)lua_toboolean(L, -1);
				*va_arg(v1, bool*) = b;
				lua_pop(L, 1);
				break;
			}
			default:
				std::cerr << "ERROR " << std::endl;
			}
		}
		va_end(v1);
	}

	private:

		std::string mainpath;

		std::string getmainpath() {
			using namespace std;
			char buffer[MAX_PATH];
			GetModuleFileName(NULL, buffer, MAX_PATH);
			string::size_type pos = string(buffer).find_last_of("\\/");
			string test = string(buffer).substr(0, pos);
			test += "\\";
			return test;
		}

};