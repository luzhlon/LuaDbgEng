#ifndef __LUADEBUGSYSTEMOBJECTS_H_
#define __LUADEBUGSYSTEMOBJECTS_H_

#include "LuaAPI.h"
#include "dbgeng.h"

int LuaGetProcess(lua_State *L);

int LuaGetCurrentProcessDataOffset(lua_State *L);
int LuaGetCurrentProcessExecutableName(lua_State *L);
int LuaGetCurrentProcessHandle(lua_State *L);
int LuaGetCurrentProcessId(lua_State *L);
int LuaGetCurrentProcessPeb(lua_State *L);
int LuaGetCurrentProcessSystemId(lua_State *L);
int LuaGetCurrentThreadDataOffset(lua_State *L);
int LuaGetCurrentThreadHandle(lua_State *L);
int LuaGetCurrentThreadId(lua_State *L);
int LuaGetCurrentThreadSystemId(lua_State *L);
int LuaGetCurrentThreadTeb(lua_State *L);
int LuaGetEventProcess(lua_State *L);
int LuaGetEventThread(lua_State *L);
int LuaGetNumberProcesses(lua_State *L);
int LuaGetNumberThreads(lua_State *L);
int LuaGetProcessIdByDataOffset(lua_State *L);
int LuaGetProcessIdByHandle(lua_State *L);
int LuaGetProcessIdByPeb(lua_State *L);
int LuaGetProcessIdBySystemId(lua_State *L);
int LuaGetProcessIdsByIndex(lua_State *L);
int LuaGetThreadIdByDataOffset(lua_State *L);
int LuaGetThreadIdByHandle(lua_State *L);
int LuaGetThreadIdByProcessor(lua_State *L);
int LuaGetThreadIdBySystemId(lua_State *L);
int LuaGetThreadIdByTeb(lua_State *L);
int LuaGetThreadIdsByIndex(lua_State *L);
int LuaGetTotalNumberThreads(lua_State *L);
int LuaSetCurrentProcessId(lua_State *L);
int LuaSetCurrentThreadId(lua_State *L);

luaL_Reg LuaDebugSystemObjectsLib[];

#endif
