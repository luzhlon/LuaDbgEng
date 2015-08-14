#include "str.h"
#include "LuaDbgStruct.h"
#include "LuaSymbolGroup.h"

luaL_Reg LuaDbgEngSGLib[] =
{
	{ "AddSymbol", Lua_SGAddSymbol },
	{ "ExpandSymbol", Lua_SGExpandSymbol },
	{ "GetNumberSymbols", Lua_SGGetNumberSymbols },
	{ "GetSymbolName", Lua_SGGetSymbolName },
	{ "GetSymbolParameters", Lua_SGGetSymbolParameters },
	{ "OutputAsType", Lua_SGOutputAsType },
	{ "OutputSymbols", Lua_SGOutputSymbols },
	{ "RemoveSymbolByIndex", Lua_SGRemoveSymbolByIndex },
	{ "RemoveSymbolByName", Lua_SGRemoveSymbolByName },
	{ "WriteSymbol", Lua_SGWriteSymbol },
	{0,0}
};

void NewLuaSymbolGroup(lua_State *L, DbgSymbolGroup * sg)
{
	LuaAPI lua(L);

	lua.NewUserPointer(sg, str::utLuaSymbolGroup);
	lua.newlibL(LuaDbgEngSGLib);
	lua.SetMetaField(-2, "__index");
}

LuaSymbolGroup::LuaSymbolGroup(LuaAPI *lua, DbgSymbolGroup * sg)
{
	lua->NewUserPointer(sg ? this : sg, str::utLuaSymbolGroup);
	lua->newlibL(LuaDbgEngSGLib);
	lua->SetMetaField(-2, "__index");
}


LuaSymbolGroup::~LuaSymbolGroup()
{
}

int Lua_SGAddSymbol(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbolGroup *sg = (DbgSymbolGroup *)lua.CheckUserPointer(1, str::utLuaSymbolGroup);

	ULONG index = lua.checkintegerL(3);
	RSLT(sg->AddSymbol(lua.checkstringL(2), &index));
	SOK() ? lua.pushinteger(index) : lua.Push(false);

	return 1;
}

int Lua_SGExpandSymbol(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbolGroup *sg = (DbgSymbolGroup *)lua.CheckUserPointer(1, str::utLuaSymbolGroup);

	RSLT(sg->ExpandSymbol(lua.checkintegerL(2), lua.checkintegerL(3)));
	lua.Push((bool)SOK());

	return 1;
}

int Lua_SGGetNumberSymbols(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbolGroup *sg = (DbgSymbolGroup *)lua.CheckUserPointer(1, str::utLuaSymbolGroup);

	ULONG n;
	RSLT(sg->GetNumberSymbols(&n));
	SOK() ? lua.pushinteger(n) : lua.Push(false);

	return 1;
}

int Lua_SGGetSymbolName(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbolGroup *sg = (DbgSymbolGroup *)lua.CheckUserPointer(1, str::utLuaSymbolGroup);

	char buf[10240];
	ULONG size;
	RSLT(sg->GetSymbolName(lua.checkintegerL(2), buf, 10240, &size));
	SOK() ? lua.pushlstring(buf, size) : lua.Push(false);

	return 1;
}

int Lua_SGGetSymbolParameters(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbolGroup *sg = (DbgSymbolGroup *)lua.CheckUserPointer(1, str::utLuaSymbolGroup);

	ULONG count = lua.checkintegerL(3);
	DEBUG_SYMBOL_PARAMETERS *p = new DEBUG_SYMBOL_PARAMETERS[count];
	RSLT(sg->GetSymbolParameters(lua.checkintegerL(2), count, p));
	SOK() ?
		NewArrayTable(L, (LUA_STRUCT_FUNC)SYMBOL_PARAMETERS2Table, p, count, sizeof(DEBUG_SYMBOL_PARAMETERS))
		: lua.Push(false);

	return 1;
}

int Lua_SGOutputAsType(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbolGroup *sg = (DbgSymbolGroup *)lua.CheckUserPointer(1, str::utLuaSymbolGroup);

	RSLT(sg->OutputAsType(lua.checkintegerL(2), lua.checkstringL(3)));
	lua.Push((bool)SOK());

	return 1;
}

int Lua_SGOutputSymbols(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbolGroup *sg = (DbgSymbolGroup *)lua.CheckUserPointer(1, str::utLuaSymbolGroup);

	RSLT(sg->OutputSymbols(lua.checkintegerL(2),
		lua.checkintegerL(3), lua.checkintegerL(4), lua.checkintegerL(5)));
	lua.Push((bool)SOK());

	return 1;
}

int Lua_SGRemoveSymbolByIndex(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbolGroup *sg = (DbgSymbolGroup *)lua.CheckUserPointer(1, str::utLuaSymbolGroup);

	RSLT(sg->RemoveSymbolByIndex(lua.checkintegerL(2)));
	lua.Push((bool)SOK());

	return 1;
}

int Lua_SGRemoveSymbolByName(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbolGroup *sg = (DbgSymbolGroup *)lua.CheckUserPointer(1, str::utLuaSymbolGroup);

	RSLT(sg->RemoveSymbolByName(lua.checkstringL(2)));
	lua.Push((bool)SOK());

	return 1;
}

int Lua_SGWriteSymbol(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbolGroup *sg = (DbgSymbolGroup *)lua.CheckUserPointer(1, str::utLuaSymbolGroup);

	RSLT(sg->WriteSymbol(lua.checkintegerL(2), lua.checkstringL(3)));
	lua.Push((bool)SOK());

	return 1;
}
