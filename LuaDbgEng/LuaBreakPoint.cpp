#include "str.h"
#include "LuaDbgStruct.h"
#include "LuaBreakpoint.h"

luaL_Reg LuaDbgEngBPLib[] = 
{
	{ "AddFlags", Lua_BPAddFlags },
	{ "GetAdder", Lua_BPGetAdder},
	{ "GetCommand", Lua_BPGetCommand},
	{ "GetCurrentPassCount", Lua_BPGetCurrentPassCount},
	{ "GetDataParameters", Lua_BPGetDataParameters},
	{ "GetFlags", Lua_BPGetFlags},
	{ "GetId", Lua_BPGetId},
	{ "GetMatchThreadId", Lua_BPGetMatchThreadId},
	{ "GetOffset", Lua_BPGetOffset},
	{ "GetOffsetExpression", Lua_BPGetOffsetExpression},
	{ "GetParameters", Lua_BPGetParameters},
	{ "GetPassCount", Lua_BPGetPassCount},
	{ "GetType", Lua_BPGetType},
	{ "RemoveFlags", Lua_BPRemoveFlags},
	{ "SetCommand", Lua_BPSetCommand},
	{ "SetDataParameters", Lua_BPSetDataParameters},
	{ "SetFlags", Lua_BPSetFlags},
	{ "SetMatchThreadId", Lua_BPSetMatchThreadId},
	{ "SetOffset", Lua_BPSetOffset},
	{ "SetOffsetExpression", Lua_BPSetOffsetExpression},
	{ "SetPassCount", Lua_BPSetPassCount},
	{0,0}
};

void NewLuaBreakpoint(lua_State *L, DbgBreakpoint *bp)
{
	LuaAPI lua(L);
	
	lua.NewUserPointer(bp, str::utLuaBreakpoint);
	lua.newlibL(LuaDbgEngBPLib);
	lua.SetMetaField(-2, "__index");
}

LuaBreakpoint::LuaBreakpoint(LuaAPI *lua, DbgBreakpoint *bp)
{
	lua->NewUserPointer(bp ? this : bp, str::utLuaBreakpoint);
	lua->newlibL(LuaDbgEngBPLib);
	lua->SetMetaField(-2, "__index");
}

LuaBreakpoint::~LuaBreakpoint()
{
}

int Lua_BPAddFlags(lua_State *L)
{
	LuaAPI lua(L);
	DbgBreakpoint *bp = (DbgBreakpoint *)lua.checkintegerL(1);

	RSLT(bp->AddFlags(lua.checkintegerL(2)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int Lua_BPGetAdder(lua_State *L)
{
	LuaAPI lua(L);
	DbgBreakpoint *bp = (DbgBreakpoint *)lua.checkintegerL(1);

	
	return 1;
}

int Lua_BPGetCommand(lua_State *L)
{
	LuaAPI lua(L);
	DbgBreakpoint *bp = (DbgBreakpoint *)lua.checkintegerL(1);

	char s[10240];
	ULONG len;
	RSLT(bp->GetCommand(s, 10240, &len));
	SOK() ? lua.pushlstring(s, len) : lua.Push(false);

	return 1;
}

int Lua_BPGetCurrentPassCount(lua_State *L)
{
	LuaAPI lua(L);
	DbgBreakpoint *bp = (DbgBreakpoint *)lua.checkintegerL(1);

	ULONG n;
	RSLT(bp->GetCurrentPassCount(&n));
	SOK() ? lua.pushinteger(n) : lua.Push(false);

	return 1;
}

int Lua_BPGetDataParameters(lua_State *L)
{
	LuaAPI lua(L);
	DbgBreakpoint *bp = (DbgBreakpoint *)lua.checkintegerL(1);

	ULONG size, type;
	RSLT(bp->GetDataParameters(&size, &type));
	if (SOK())
	{
		lua.pushinteger(size);
		lua.pushinteger(type);
		return 2;
	}
	lua.Push(false);

	return 1;
}

int Lua_BPGetFlags(lua_State *L)
{
	LuaAPI lua(L);
	DbgBreakpoint *bp = (DbgBreakpoint *)lua.checkintegerL(1);

	ULONG flags;
	RSLT(bp->GetFlags(&flags));
	SOK() ? lua.pushinteger(flags) : lua.Push(false);
	
	return 1;
}

int Lua_BPGetId(lua_State *L)
{
	LuaAPI lua(L);
	DbgBreakpoint *bp = (DbgBreakpoint *)lua.checkintegerL(1);

	ULONG id;
	RSLT(bp->GetFlags(&id));
	SOK() ? lua.pushinteger(id) : lua.Push(false);
	
	return 1;
}

int Lua_BPGetMatchThreadId(lua_State *L)
{
	LuaAPI lua(L);
	DbgBreakpoint *bp = (DbgBreakpoint *)lua.checkintegerL(1);

	ULONG tid;
	RSLT(bp->GetMatchThreadId(&tid));
	SOK() ? lua.pushinteger(tid) : lua.Push(false);

	return 1;
}

int Lua_BPGetOffset(lua_State *L)
{
	LuaAPI lua(L);
	DbgBreakpoint *bp = (DbgBreakpoint *)lua.checkintegerL(1);

	ULONG64 offset;
	RSLT(bp->GetOffset(&offset));
	SOK() ? lua.pushinteger(offset) : lua.Push(false);

	return 1;
}

int Lua_BPGetOffsetExpression(lua_State *L)
{
	LuaAPI lua(L);
	DbgBreakpoint *bp = (DbgBreakpoint *)lua.checkintegerL(1);

	char s[10240]; ULONG len;
	RSLT(bp->GetOffsetExpression(s, 10240, &len));
	SOK() ? lua.pushlstring(s, len) : lua.Push(false);

	return 1;
}

int Lua_BPGetParameters(lua_State *L)
{
	LuaAPI lua(L);
	DbgBreakpoint *bp = (DbgBreakpoint *)lua.checkintegerL(1);

	DEBUG_BREAKPOINT_PARAMETERS dbp;
	RSLT(bp->GetParameters(&dbp));
	SOK() ? BREAKPOINT_PARAMETERS2Table(L, &dbp) : lua.Push(false);
	
	return 1;
}

int Lua_BPGetPassCount(lua_State *L)
{
	LuaAPI lua(L);
	DbgBreakpoint *bp = (DbgBreakpoint *)lua.checkintegerL(1);

	ULONG count;
	RSLT(bp->GetPassCount(&count));
	SOK() ? lua.pushinteger(count) : lua.Push(false);
	
	return 1;
}

int Lua_BPGetType(lua_State *L)
{
	LuaAPI lua(L);
	DbgBreakpoint *bp = (DbgBreakpoint *)lua.checkintegerL(1);

	ULONG bt, pt;
	RSLT(bp->GetType(&bt, &pt));
	SOK() ? (lua.pushinteger(bt),
		lua.pushinteger(pt)) : lua.Push(false);

	return 1;
}

int Lua_BPRemoveFlags(lua_State *L)
{
	LuaAPI lua(L);
	DbgBreakpoint *bp = (DbgBreakpoint *)lua.checkintegerL(1);

	RSLT(bp->RemoveFlags(lua.checkintegerL(2)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int Lua_BPSetCommand(lua_State *L)
{
	LuaAPI lua(L);
	DbgBreakpoint *bp = (DbgBreakpoint *)lua.checkintegerL(1);

	RSLT(bp->SetCommand(lua.checkstringL(2)));
	lua.Push((bool)SOK());

	return 1;
}

int Lua_BPSetDataParameters(lua_State *L)
{
	LuaAPI lua(L);
	DbgBreakpoint *bp = (DbgBreakpoint *)lua.checkintegerL(1);

	RSLT(bp->SetDataParameters(lua.checkintegerL(2), lua.checkintegerL(3)));
	lua.Push((bool)SOK());

	return 1;
}

int Lua_BPSetFlags(lua_State *L)
{
	LuaAPI lua(L);
	DbgBreakpoint *bp = (DbgBreakpoint *)lua.checkintegerL(1);

	RSLT(bp->SetFlags(lua.checkintegerL(2)));
	lua.Push((bool)SOK());
	
	return 1;
}

int Lua_BPSetMatchThreadId(lua_State *L)
{
	LuaAPI lua(L);
	DbgBreakpoint *bp = (DbgBreakpoint *)lua.checkintegerL(1);

	RSLT(bp->SetMatchThreadId(lua.checkintegerL(2)));
	lua.Push((bool)SOK());
	
	return 1;
}

int Lua_BPSetOffset(lua_State *L)
{
	LuaAPI lua(L);
	DbgBreakpoint *bp = (DbgBreakpoint *)lua.checkintegerL(1);

	RSLT(bp->SetOffset(lua.checkintegerL(2)));
	lua.Push((bool)SOK());
	
	return 1;
}

int Lua_BPSetOffsetExpression(lua_State *L)
{
	LuaAPI lua(L);
	DbgBreakpoint *bp = (DbgBreakpoint *)lua.checkintegerL(1);

	RSLT(bp->SetOffsetExpression(lua.checkstringL(2)));
	lua.Push((bool)SOK());
	
	return 1;
}

int Lua_BPSetPassCount(lua_State *L)
{
	LuaAPI lua(L);
	DbgBreakpoint *bp = (DbgBreakpoint *)lua.checkintegerL(1);

	RSLT(bp->SetPassCount(lua.checkintegerL(2)));
	lua.Push((bool)SOK());

	return 1;
}

