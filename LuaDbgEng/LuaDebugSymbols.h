#ifndef __LUADEBUGSYMBOLS_H_
#define __LUADEBUGSYMBOLS_H_

#include "LuaAPI.h"
#include "dbgeng.h"

#define DbgSymbol IDebugSymbols3

int LuaAddSymbolOptions(lua_State *L);
int LuaAppendImagePath(lua_State *L);
int LuaAppendSourcePath(lua_State *L);
int LuaAppendSymbolPath(lua_State *L);
int LuaCreateSymbolGroup(lua_State *L);
int LuaEndSymbolMatch(lua_State *L);
int LuaFindSourceFile(lua_State *L);
int LuaGetFieldOffset(lua_State *L);
int LuaGetImagePath(lua_State *L);
int LuaGetLineByOffset(lua_State *L);
int LuaGetModuleByIndex(lua_State *L);
int LuaGetModuleByModuleName(lua_State *L);
int LuaGetModuleByOffset(lua_State *L);
int LuaGetModuleNames(lua_State *L);
int LuaGetModuleParameters(lua_State *L);
int LuaGetNameByOffset(lua_State *L);
int LuaGetNearNameByOffset(lua_State *L);
int LuaGetNextSymbolMatch(lua_State *L);
int LuaGetNumberModules(lua_State *L);
int LuaGetOffsetByLine(lua_State *L);
int LuaGetOffsetByName(lua_State *L);
int LuaGetOffsetTypeId(lua_State *L);
int LuaGetScope(lua_State *L);
int LuaGetScopeSymbolGroup(lua_State *L);
int LuaGetSourceFileLineOffsets(lua_State *L);
int LuaGetSourcePath(lua_State *L);
int LuaGetSourcePathElement(lua_State *L);
int LuaGetSymbolModule(lua_State *L);
int LuaGetSymbolOptions(lua_State *L);
int LuaGetSymbolPath(lua_State *L);
int LuaGetSymbolTypeId(lua_State *L);
int LuaGetTypeId(lua_State *L);
int LuaGetTypeName(lua_State *L);
int LuaGetTypeSize(lua_State *L);
int LuaOutputTypedDataPhysical(lua_State *L);
int LuaOutputTypedDataVirtual(lua_State *L);
int LuaReadTypedDataPhysical(lua_State *L);
int LuaReadTypedDataVirtual(lua_State *L);
int LuaReload(lua_State *L);
int LuaRemoveSymbolOptions(lua_State *L);
int LuaResetScope(lua_State *L);
int LuaSetImagePath(lua_State *L);
int LuaSetScope(lua_State *L);
int LuaSetSourcePath(lua_State *L);
int LuaSetSymbolOptions(lua_State *L);
int LuaSetSymbolPath(lua_State *L);
int LuaStartSymbolMatch(lua_State *L);
int LuaWriteTypedDataPhysical(lua_State *L);
int LuaWriteTypedDataVirtual(lua_State *L);

luaL_Reg LuaDebugSymbolsLib[];

#endif
