#include "str.h"
#include "LuaDbgEng.h"
#include "LuaDebugDataSpaces.h"

luaL_Reg LuaDebugDataSpacesLib[] =
{
	{ "CheckLowMemory", LuaCheckLowMemory },
	{ "ReadBusData", LuaReadBusData },
	{ "ReadControl", LuaReadControl },
	{ "ReadDebuggerData", LuaReadDebuggerData },
	{ "ReadIo", LuaReadIo },
	{ "ReadMsr", LuaReadMsr },
	{ "ReadPhysical", LuaReadPhysical },
	{ "ReadPointersVirtual", LuaReadPointersVirtual },
	{ "ReadProcessorSystemData", LuaReadProcessorSystemData },
	{ "ReadVirtual", LuaReadVirtual },
	{ "ReadVirtualUncached", LuaReadVirtualUncached },
	{ "SearchVirtual", LuaSearchVirtual },
	{ "WriteBusData", LuaWriteBusData },
	{ "WriteControl", LuaWriteControl },
	{ "WriteIo", LuaWriteIo },
	{ "WriteMsr", LuaWriteMsr },
	{ "WritePhysical", LuaWritePhysical },
	{ "WritePointersVirtual", LuaWritePointersVirtual },
	{ "WriteVirtual", LuaWriteVirtual },
	{ "WriteVirtualUncached", LuaWriteVirtualUncached },
	{ 0, 0 }
};


int LuaCheckLowMemory(lua_State *L)
{
	LuaAPI lua(L);
	DbgDataSpc *DatSpc = (DbgDataSpc *)lua.CheckUserPointer(1, str::utLuaDebugDataSpaces);

	RSLT(DatSpc->CheckLowMemory(););
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaReadBusData(lua_State *L)
{
	LuaAPI lua(L);
	DbgDataSpc *DatSpc = (DbgDataSpc *)lua.CheckUserPointer(1, str::utLuaDebugDataSpaces);

	RSLT(DatSpc->CheckLowMemory(););
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaReadControl(lua_State *L)
{
	LuaAPI lua(L);
	DbgDataSpc *DatSpc = (DbgDataSpc *)lua.CheckUserPointer(1, str::utLuaDebugDataSpaces);

	RSLT(DatSpc->CheckLowMemory(););
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaReadDebuggerData(lua_State *L)
{
	LuaAPI lua(L);
	DbgDataSpc *DatSpc = (DbgDataSpc *)lua.CheckUserPointer(1, str::utLuaDebugDataSpaces);

	RSLT(DatSpc->CheckLowMemory(););
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaReadIo(lua_State *L)
{
	LuaAPI lua(L);
	DbgDataSpc *DatSpc = (DbgDataSpc *)lua.CheckUserPointer(1, str::utLuaDebugDataSpaces);

	RSLT(DatSpc->CheckLowMemory(););
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaReadMsr(lua_State *L)
{
	LuaAPI lua(L);
	DbgDataSpc *DatSpc = (DbgDataSpc *)lua.CheckUserPointer(1, str::utLuaDebugDataSpaces);

	RSLT(DatSpc->CheckLowMemory(););
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaReadPhysical(lua_State *L)
{
	LuaAPI lua(L);
	DbgDataSpc *DatSpc = (DbgDataSpc *)lua.CheckUserPointer(1, str::utLuaDebugDataSpaces);

	RSLT(DatSpc->CheckLowMemory(););
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaReadPointersVirtual(lua_State *L)
{
	LuaAPI lua(L);
	DbgDataSpc *DatSpc = (DbgDataSpc *)lua.CheckUserPointer(1, str::utLuaDebugDataSpaces);

	RSLT(DatSpc->CheckLowMemory(););
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaReadProcessorSystemData(lua_State *L)
{
	LuaAPI lua(L);
	DbgDataSpc *DatSpc = (DbgDataSpc *)lua.CheckUserPointer(1, str::utLuaDebugDataSpaces);

	RSLT(DatSpc->CheckLowMemory(););
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaReadVirtual(lua_State *L)
{
	LuaAPI lua(L);

	ULONG   bytesread = 0;
	ULONG64 offset = lua.checkintegerL(1);
	PVOID   buf = (PVOID)lua.checkintegerL(2);
	ULONG   size = lua.checkintegerL(3);

	RSLT(g_DatSpc->ReadVirtual(offset, buf, size, &bytesread));
	SOK() ? lua.pushinteger(bytesread) : lua.Push(false);
	
	return 1;
}

int LuaReadVirtualUncached(lua_State *L)
{
	LuaAPI lua(L);
	DbgDataSpc *DatSpc = (DbgDataSpc *)lua.CheckUserPointer(1, str::utLuaDebugDataSpaces);

	RSLT(DatSpc->CheckLowMemory(););
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaSearchVirtual(lua_State *L)
{
	LuaAPI lua(L);
	DbgDataSpc *DatSpc = (DbgDataSpc *)lua.CheckUserPointer(1, str::utLuaDebugDataSpaces);

	RSLT(DatSpc->CheckLowMemory(););
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaWriteBusData(lua_State *L)
{
	LuaAPI lua(L);
	DbgDataSpc *DatSpc = (DbgDataSpc *)lua.CheckUserPointer(1, str::utLuaDebugDataSpaces);

	RSLT(DatSpc->CheckLowMemory(););
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaWriteControl(lua_State *L)
{
	LuaAPI lua(L);
	DbgDataSpc *DatSpc = (DbgDataSpc *)lua.CheckUserPointer(1, str::utLuaDebugDataSpaces);

	RSLT(DatSpc->CheckLowMemory(););
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaWriteIo(lua_State *L)
{
	LuaAPI lua(L);
	DbgDataSpc *DatSpc = (DbgDataSpc *)lua.CheckUserPointer(1, str::utLuaDebugDataSpaces);

	RSLT(DatSpc->CheckLowMemory(););
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaWriteMsr(lua_State *L)
{
	LuaAPI lua(L);
	DbgDataSpc *DatSpc = (DbgDataSpc *)lua.CheckUserPointer(1, str::utLuaDebugDataSpaces);

	RSLT(DatSpc->CheckLowMemory(););
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaWritePhysical(lua_State *L)
{
	LuaAPI lua(L);
	DbgDataSpc *DatSpc = (DbgDataSpc *)lua.CheckUserPointer(1, str::utLuaDebugDataSpaces);

	RSLT(DatSpc->CheckLowMemory(););
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaWritePointersVirtual(lua_State *L)
{
	LuaAPI lua(L);
	DbgDataSpc *DatSpc = (DbgDataSpc *)lua.CheckUserPointer(1, str::utLuaDebugDataSpaces);

	RSLT(DatSpc->CheckLowMemory(););
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaWriteVirtual(lua_State *L)
{
	LuaAPI lua(L);

	ULONG   byteswrite = 0;
	ULONG64 offset = lua.checkintegerL(1);
	PVOID   buf = (PVOID)lua.checkintegerL(2);
	ULONG   size = lua.checkintegerL(3);

	RSLT(g_DatSpc->WriteVirtual(offset, buf, size, &byteswrite));
	SOK() ? lua.pushinteger(byteswrite) : lua.Push(false);

	return 1;
}

int LuaWriteVirtualUncached(lua_State *L)
{
	LuaAPI lua(L);
	DbgDataSpc *DatSpc = (DbgDataSpc *)lua.CheckUserPointer(1, str::utLuaDebugDataSpaces);

	RSLT(DatSpc->CheckLowMemory(););
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

