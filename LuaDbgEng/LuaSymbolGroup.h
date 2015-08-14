#ifndef _LUASYMBOLGROUP_H_
#define _LUASYMBOLGROUP_H_

#include "dbgeng.h"
#include "LuaAPI.h"
#include "LuaDbgEng.h"

class LuaSymbolGroup : public DbgSymbolGroup
{
public:
	LuaSymbolGroup(LuaAPI *, DbgSymbolGroup * sg = NULL);
	~LuaSymbolGroup();

};

void NewLuaSymbolGroup(lua_State *L, DbgSymbolGroup * sg);

int Lua_SGAddSymbol(lua_State *L);
int Lua_SGExpandSymbol(lua_State *L);
int Lua_SGGetNumberSymbols(lua_State *L);
int Lua_SGGetSymbolName(lua_State *L);
int Lua_SGGetSymbolParameters(lua_State *L);
int Lua_SGOutputAsType(lua_State *L);
int Lua_SGOutputSymbols(lua_State *L);
int Lua_SGRemoveSymbolByIndex(lua_State *L);
int Lua_SGRemoveSymbolByName(lua_State *L);
int Lua_SGWriteSymbol(lua_State *L);

luaL_Reg LuaDbgEngSGLib[];

#endif
