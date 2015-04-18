#ifndef __LUADEBUGDATASPACES_H_
#define __LUADEBUGDATASPACES_H_

#include "LuaAPI.h"
#include "dbgeng.h"

#define DbgDataSpc IDebugDataSpaces4

int LuaCheckLowMemory(lua_State *L);
int LuaReadBusData(lua_State *L);
int LuaReadControl(lua_State *L);
int LuaReadDebuggerData(lua_State *L);
int LuaReadIo(lua_State *L);
int LuaReadMsr(lua_State *L);
int LuaReadPhysical(lua_State *L);
int LuaReadPointersVirtual(lua_State *L);
int LuaReadProcessorSystemData(lua_State *L);
int LuaReadVirtual(lua_State *L);
int LuaReadVirtualUncached(lua_State *L);
int LuaSearchVirtual(lua_State *L);
int LuaWriteBusData(lua_State *L);
int LuaWriteControl(lua_State *L);
int LuaWriteIo(lua_State *L);
int LuaWriteMsr(lua_State *L);
int LuaWritePhysical(lua_State *L);
int LuaWritePointersVirtual(lua_State *L);
int LuaWriteVirtual(lua_State *L);
int LuaWriteVirtualUncached(lua_State *L);

luaL_Reg LuaDebugDataSpacesLib[];

#endif
