#ifndef __LUADEBUGREGISTERS_H_
#define __LUADEBUGREGISTERS_H_

#include "LuaAPI.h"
#include "dbgeng.h"

#define DbgRegist IDebugRegisters2

int LuaGetDescription(lua_State *L);
int LuaGetFrameOffset(lua_State *L);
int LuaGetIndexByName(lua_State *L);
int LuaGetInstructionOffset(lua_State *L);
int LuaGetNumberRegisters(lua_State *L);
int LuaGetStackOffset(lua_State *L);
int LuaGetValue(lua_State *L);
int LuaGetValues(lua_State *L);
int LuaOutputRegisters(lua_State *L);
int LuaSetValue(lua_State *L);
int LuaSetValues(lua_State *L);

luaL_Reg LuaDebugRegistersLib[];

#endif
