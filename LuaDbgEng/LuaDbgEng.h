#ifndef _LUADBGEGN_H_
#define _LUADBGEGN_H_

#include <assert.h>
#include "dbgeng.h"
#include "LuaAPI.h"

#define DbgClient IDebugClient5
#define DbgControl IDebugControl4
#define DbgDataSpc IDebugDataSpaces4
#define DbgRegist IDebugRegisters2
#define DbgSymbol IDebugSymbols3
#define DbgSysObj IDebugSystemObjects4

#define DbgBreakpoint IDebugBreakpoint
#define DbgSymbolGroup IDebugSymbolGroup

extern HRESULT    g_LastRlt;
#define RSLT(s)   g_LastRlt = s
#define SOK()     (g_LastRlt == S_OK)
int LuaGetLastError(lua_State *L);

extern DbgClient *   g_Client;
extern DbgControl *  g_Ctrl;
extern DbgDataSpc *  g_DatSpc;
extern DbgRegist *   g_Reg;
extern DbgSymbol *   g_Sym;
extern DbgSysObj *   g_SysObj;

extern HANDLE        g_waitEvent;
extern ULONG         g_waitFlags;
extern ULONG         g_waitTime;
extern int           g_refCallback;
extern LuaAPI       *g_luaCallback;

int InitLuaDbgEng(lua_State *);

int LuaGetConstantTable(lua_State *);
int LuaSetUserdataMetatable(lua_State *);

int LuaDebugCreate(lua_State *L);
int LuaNewEventCB(lua_State *L);
int LuaNewOutputCB(lua_State *L);
int LuaNewInputCB(lua_State *L);

int LuaGetInterfaces(lua_State *L);

luaL_Reg LuaDbgEngLib[];

#endif
