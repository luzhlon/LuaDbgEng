#ifndef _LUABREAKPOINT_H_
#define _LUABREAKPOINT_H_

#include "dbgeng.h"
#include "LuaAPI.h"
#include "LuaDbgEng.h"

class LuaBreakpoint : public DbgBreakpoint
{
public:
	LuaBreakpoint(LuaAPI *, DbgBreakpoint * bp = NULL);
	~LuaBreakpoint();

};

void NewLuaBreakpoint(lua_State *L, DbgBreakpoint *bp);

int Lua_BPAddFlags(lua_State *L);
int Lua_BPGetAdder(lua_State *L);
int Lua_BPGetCommand(lua_State *L);
int Lua_BPGetCurrentPassCount(lua_State *L);
int Lua_BPGetDataParameters(lua_State *L);
int Lua_BPGetFlags(lua_State *L);
int Lua_BPGetId(lua_State *L);
int Lua_BPGetMatchThreadId(lua_State *L);
int Lua_BPGetOffset(lua_State *L);
int Lua_BPGetOffsetExpression(lua_State *L);
int Lua_BPGetParameters(lua_State *L);
int Lua_BPGetPassCount(lua_State *L);
int Lua_BPGetType(lua_State *L);
int Lua_BPRemoveFlags(lua_State *L);
int Lua_BPSetCommand(lua_State *L);
int Lua_BPSetDataParameters(lua_State *L);
int Lua_BPSetFlags(lua_State *L);
int Lua_BPSetMatchThreadId(lua_State *L);
int Lua_BPSetOffset(lua_State *L);
int Lua_BPSetOffsetExpression(lua_State *L);
int Lua_BPSetPassCount(lua_State *L);

luaL_Reg LuaDbgEngBPLib[];

#endif
