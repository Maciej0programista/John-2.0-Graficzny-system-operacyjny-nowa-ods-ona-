#ifndef COMMAND_LUA_H
#define COMMAND_LUA_H

#include <Lua.h>
#include <lauxlib.h>

void registerLuaCommands(lua_State *L);

#endif
