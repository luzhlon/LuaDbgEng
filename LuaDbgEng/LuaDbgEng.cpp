#include "str.h"
#include "LuaDbgEng.h"
#include "LuaConstant.h"
#include "LuaCallback.h"
#include "LuaDebugClient.h"

DbgClient *   g_Client = NULL;
DbgControl *  g_Ctrl = NULL;
DbgDataSpc *  g_DatSpc = NULL;
DbgRegist *   g_Reg = NULL;
DbgSymbol *   g_Sym = NULL;
DbgSysObj *   g_SysObj = NULL;

HRESULT g_LastRlt;

luaL_Reg LuaDbgEngLib[] = 
{
    { "NewEventCB", LuaNewEventCB },
    { "NewOutputCB", LuaNewOutputCB },
    { "NewInputCB", LuaNewInputCB },
    { "DebugCreate", LuaDebugCreate },

	{ "GetInterfaces", LuaGetInterfaces },
	{ "GetConstTable", LuaGetConstantTable },
	{ "GetLastError", LuaGetLastError },
	{0, 0}
};

int LuaGetLastError(lua_State *L)
{
	const char *err;
	switch (g_LastRlt)
	{
	case S_OK:
		err = "S_OK"; break;
	case S_FALSE:
		err = "S_FALSE"; break;
	case E_FAIL:
		err = "E_FAIL";break;
	case E_INVALIDARG:
		err = "E_INVALIDARG";break;
	case E_NOINTERFACE:
		err = "E_NOINTERFACE";break;
	case E_OUTOFMEMORY:
		err = "E_OUTOFMEMORY";break;
	case E_UNEXPECTED:
		err = "E_UNEXPECTED";break;
	case E_NOTIMPL:
		err = "E_NOTIMPL";break;
	}
	lua_pushstring(L, err);
	return 1;
}

int LuaGetInterfaces(lua_State *L)
{
	LuaAPI lua(L);

	extern luaL_Reg LuaDebugClientLib[];
	extern luaL_Reg LuaDebugControlLib[];
	extern luaL_Reg LuaDebugSymbolsLib[];
	extern luaL_Reg LuaDebugRegistersLib[];
	extern luaL_Reg LuaDebugDataSpacesLib[];
	extern luaL_Reg LuaDebugSystemObjectsLib[];

	lua.NewUserPointer(g_Client, str::utLuaDebugClient);
	lua.newlibL(LuaDebugClientLib); lua.SetMetaField(-2, "__index");

	lua.NewUserPointer(g_Ctrl, str::utLuaDebugControl);
	lua.newlibL(LuaDebugControlLib); lua.SetMetaField(-2, "__index");
	lua.NewUserPointer(g_Sym, str::utLuaDebugSymbols);
	lua.newlibL(LuaDebugSymbolsLib); lua.SetMetaField(-2, "__index");
	lua.NewUserPointer(g_Reg, str::utLuaDebugRegisters);
	lua.newlibL(LuaDebugRegistersLib); lua.SetMetaField(-2, "__index");
	lua.NewUserPointer(g_DatSpc, str::utLuaDebugDataSpaces);
	lua.newlibL(LuaDebugDataSpacesLib); lua.SetMetaField(-2, "__index");
	lua.NewUserPointer(g_SysObj, str::utLuaDebugSystemObjects);
	lua.newlibL(LuaDebugSystemObjectsLib); lua.SetMetaField(-2, "__index");

	return 6;
}

int InitLuaDbgEng(lua_State *L)
{
	/*
	RSLT(DebugCreate(__uuidof(DbgClient), (void **)&g_Client)); assert(SOK());
	RSLT(g_Client->QueryInterface(__uuidof(DbgControl), (void **)&g_Ctrl)); assert(SOK());
	RSLT(g_Client->QueryInterface(__uuidof(DbgDataSpc), (void **)&g_DatSpc)); assert(SOK());
	RSLT(g_Client->QueryInterface(__uuidof(DbgRegist), (void **)&g_Reg)); assert(SOK());
	RSLT(g_Client->QueryInterface(__uuidof(DbgSymbol), (void **)&g_Sym)); assert(SOK());
	RSLT(g_Client->QueryInterface(__uuidof(DbgSysObj), (void **)&g_SysObj)); assert(SOK());
	*/
	//Load LuaDbgEng library's C part
	LuaAPI lua(L);
	lua.NewLibrary("LuaDbgEngCore", LuaDbgEngLib);
	return 1;
}

int LuaGetConstantTable(lua_State *L)
{
	static int RefConsTable = 0;

	LuaAPI lua(L);
	if (RefConsTable)
		lua.rawgeti(LUA_REGISTRYINDEX, RefConsTable);
	else
	{
		lua.NewConstantTable(lua_constant);
		lua.pushvalue(-1);
		RefConsTable = lua.refL(LUA_REGISTRYINDEX);
	}
		
	return 1;
}

int LuaSetUserdataMetatable(lua_State *L)
{
	LuaAPI lua(L);

	if (lua.isuserdata(1)&&lua.istable(2))lua.setmetatable(1);
	else
		lua.Push(false);

	lua.Push(true);
	return 1;
}

int LuaDebugCreate(lua_State *L)
{
	LuaAPI lua(L);

	DbgClient *Client;
	RSLT(DebugCreate(__uuidof(DbgClient), (void **)&Client));
	SOK() ? (lua.NewUserPointer(Client, str::utLuaDebugClient),
			lua.newlibL(LuaDebugClientLib),
			lua.SetMetaField(-2, "__index")) : lua.Push(false);

	return 1;
}

int LuaNewEventCB(lua_State *L)
{
	new LuaEventCallback(new LuaAPI(L));
	return 1;
}

int LuaNewOutputCB(lua_State *L)
{
	new LuaOutputCallback(new LuaAPI(L));
	return 1;
}

int LuaNewInputCB(lua_State *L)
{
	new LuaInputCallback(new LuaAPI(L));
	return 1;
}

extern "C" int __declspec(dllexport) luaopen_LuaDbgEng(lua_State *L)
{
	return InitLuaDbgEng(L);
}

BOOL WINAPI DllMain(HINSTANCE  hModule, DWORD  dwReason, LPVOID  lpvReserved)
{
	return 1;
}
