#include "str.h"
#include "LuaDbgEng.h"
#include "LuaDbgStruct.h"
#include "LuaDebugRegisters.h"

luaL_Reg LuaDebugRegistersLib[] =
{
	{ "GetDescription", LuaGetDescription },
	{ "GetFrameOffset", LuaGetFrameOffset },
	{ "GetIndexByName", LuaGetIndexByName },
	{ "GetInstructionOffset", LuaGetInstructionOffset },
	{ "GetNumberRegisters", LuaGetNumberRegisters },
	{ "GetStackOffset", LuaGetStackOffset },
	{ "GetValue", LuaGetValue },
	//{ "GetValues", LuaGetValues },
	{ "OutputRegisters", LuaOutputRegisters },
	{ "SetValue", LuaSetValue },
	//{ "SetValues", LuaSetValues },
	{ 0, 0 }
};

int LuaGetDescription(lua_State *L)
{
	LuaAPI lua(L);
	DbgRegist *Reg = (DbgRegist *)lua.CheckUserPointer(1, str::utLuaDebugRegisters);

	char str[1024];
	ULONG size;
	DEBUG_REGISTER_DESCRIPTION desc;
	RSLT(Reg->GetDescription(lua.checkintegerL(2), str, 1024, &size, &desc));
	SOK() ? (lua.pushlstring(str, size),
		REGISTER_DESCRIPTION2Table(L, &desc)) : lua.Push(false);

	return SOK() ? 2 : 1;
}

int LuaGetFrameOffset(lua_State *L)
{
	LuaAPI lua(L);
	DbgRegist *Reg = (DbgRegist *)lua.CheckUserPointer(1, str::utLuaDebugRegisters);

	ULONG64 offset;
	RSLT(Reg->GetFrameOffset(&offset));
	SOK() ? lua.pushinteger(offset) : lua.Push(false);

	return 1;
}

int LuaGetIndexByName(lua_State *L)
{
	LuaAPI lua(L);
	DbgRegist *Reg = (DbgRegist *)lua.CheckUserPointer(1, str::utLuaDebugRegisters);

	ULONG i;
	RSLT(Reg->GetIndexByName(lua.checkstringL(2), &i));
	SOK() ? lua.pushinteger(i) : lua.Push(false);

	return 1;
}

int LuaGetInstructionOffset(lua_State *L)
{
	LuaAPI lua(L);
	DbgRegist *Reg = (DbgRegist *)lua.CheckUserPointer(1, str::utLuaDebugRegisters);

	ULONG64 offset;
	RSLT(Reg->GetInstructionOffset(&offset));
	SOK() ? lua.pushinteger(offset) : lua.Push(false);

	return 1;
}

int LuaGetNumberRegisters(lua_State *L)
{
	LuaAPI lua(L);
	DbgRegist *Reg = (DbgRegist *)lua.CheckUserPointer(1, str::utLuaDebugRegisters);

	ULONG n;
	RSLT(Reg->GetNumberRegisters(&n));
	SOK() ? lua.pushinteger(n) : lua.Push(false);

	return 1;
}

int LuaGetStackOffset(lua_State *L)
{
	LuaAPI lua(L);
	DbgRegist *Reg = (DbgRegist *)lua.CheckUserPointer(1, str::utLuaDebugRegisters);

	ULONG64 offset;
	RSLT(Reg->GetStackOffset(&offset));
	SOK() ? lua.pushinteger(offset) : lua.Push(false);

	return 1;
}

int LuaGetValue(lua_State *L)
{
	LuaAPI lua(L);
	DbgRegist *Reg = (DbgRegist *)lua.CheckUserPointer(1, str::utLuaDebugRegisters);

	DEBUG_VALUE dv;
	RSLT(Reg->GetValue(lua.checkintegerL(2), &dv));
	SOK() ? VALUE2Table(L, &dv) : lua.Push(false);

	return 1;
}

int LuaGetValues(lua_State *L)
{
	LuaAPI lua(L);
	DbgRegist *Reg = (DbgRegist *)lua.CheckUserPointer(1, str::utLuaDebugRegisters);

	return 0;
}

int LuaOutputRegisters(lua_State *L)
{
	LuaAPI lua(L);
	DbgRegist *Reg = (DbgRegist *)lua.CheckUserPointer(1, str::utLuaDebugRegisters);

	RSLT(Reg->OutputRegisters(lua.checkintegerL(2), lua.checkintegerL(3)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaSetValue(lua_State *L)
{
	LuaAPI lua(L);
	DbgRegist *Reg = (DbgRegist *)lua.CheckUserPointer(1, str::utLuaDebugRegisters);

	DEBUG_VALUE dv;
	lua.pushvalue(3);
	Table2VALUE(L, &dv);
	RSLT(Reg->GetValue(lua.checkintegerL(2), &dv));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaSetValues(lua_State *L)
{
	LuaAPI lua(L);
	DbgRegist *Reg = (DbgRegist *)lua.CheckUserPointer(1, str::utLuaDebugRegisters);

	return 0;
}
