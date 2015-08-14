#include "str.h"
#include "LuaDbgEng.h"
#include "LuaDebugSystemObjects.h"

luaL_Reg LuaDebugSystemObjectsLib[] = 
{
	{ "GetProcess", LuaGetProcess },

	{ "GetCurrentProcessDataOffset", LuaGetCurrentProcessDataOffset },
	{ "GetCurrentProcessExecutableName", LuaGetCurrentProcessExecutableName},
	{ "GetCurrentProcessHandle", LuaGetCurrentProcessHandle},
	{ "GetCurrentProcessId", LuaGetCurrentProcessId},
	{ "GetCurrentProcessPeb", LuaGetCurrentProcessPeb},
	{ "GetCurrentProcessSystemId", LuaGetCurrentProcessSystemId},
	{ "GetCurrentThreadDataOffset", LuaGetCurrentThreadDataOffset},
	{ "GetCurrentThreadHandle", LuaGetCurrentThreadHandle},
	{ "GetCurrentThreadId", LuaGetCurrentThreadId},
	{ "GetCurrentThreadSystemId", LuaGetCurrentThreadSystemId},
	{ "GetCurrentThreadTeb", LuaGetCurrentThreadTeb},
	{ "GetEventProcess", LuaGetEventProcess},
	{ "GetEventThread", LuaGetEventThread},
	{ "GetNumberProcesses", LuaGetNumberProcesses},
	{ "GetNumberThreads", LuaGetNumberThreads},
	{ "GetProcessIdByDataOffset", LuaGetProcessIdByDataOffset},
	{ "GetProcessIdByHandle", LuaGetProcessIdByHandle},
	{ "GetProcessIdByPeb", LuaGetProcessIdByPeb},
	{ "GetProcessIdBySystemId", LuaGetProcessIdBySystemId},
	{ "GetProcessIdsByIndex", LuaGetProcessIdsByIndex},
	{ "GetThreadIdByDataOffset", LuaGetThreadIdByDataOffset},
	{ "GetThreadIdByHandle", LuaGetThreadIdByHandle},
	{ "GetThreadIdByProcessor", LuaGetThreadIdByProcessor},
	{ "GetThreadIdBySystemId", LuaGetThreadIdBySystemId},
	{ "GetThreadIdByTeb", LuaGetThreadIdByTeb},
	{ "GetThreadIdsByIndex", LuaGetThreadIdsByIndex},
	{ "GetTotalNumberThreads", LuaGetTotalNumberThreads},
	{ "SetCurrentProcessId", LuaSetCurrentProcessId},
	{ "SetCurrentThreadId", LuaSetCurrentThreadId},
	{ 0, 0 }
};

int LuaGetProcess(lua_State *L)
{
	LuaAPI lua(L);
	
	const char * t = lua.checkstringL(1);
	int i = 2, top = lua.gettop();
	if (!strcmp(t, "cur"))//GetCurrentProcess ...
	{
		for (i = 2; i <= top; i++)
		{
			if (lua.isnoneornil(i))
			{
				lua.Push();
				continue;
			}
			t = lua.checkstringL(i);
			if (!strcmp(t, "id"))
			{
				ULONG id;
				RSLT(g_SysObj->GetCurrentProcessId(&id));
				SOK() ? lua.pushinteger(id) : lua.Push(false);
			}
			else if (!strcmp(t, "peb"))
			{
				ULONG64 pebOffset;
				RSLT(g_SysObj->GetCurrentProcessPeb(&pebOffset));
				SOK() ?	lua.pushinteger(pebOffset) : lua.Push(false);
			}
			else if (!strcmp(t, "sysid"))
			{
				ULONG64 sysid;
				RSLT(g_SysObj->GetCurrentProcessPeb(&sysid));
				SOK() ?	lua.pushinteger(sysid) : lua.Push(false);
			}
			else if (!strcmp(t, "handle"))
			{
				ULONG64 handle;
				RSLT(g_SysObj->GetCurrentProcessPeb(&handle));
				SOK() ?	lua.pushinteger(handle) : lua.Push(false);
			}
			else if (!strcmp(t, "exename"))
			{
				char exename[320];
				ULONG exesize;
				RSLT(g_SysObj->GetCurrentProcessExecutableName(exename, 320, &exesize));
				SOK() ?	lua.pushlstring(exename, exesize) : lua.Push(false);
			}
			else if (!strcmp(t, "dataoffset"))
			{
				ULONG64 data;
				RSLT(g_SysObj->GetCurrentProcessDataOffset(&data));
				SOK() ?	lua.pushinteger(data) : lua.Push(false);
			}
			else
				lua.Push();
		}
		return top - 1;
	}
	else if (!strcmp(t, "id"))//GetProcessIdBy ...
	{
		ULONG id;
		t = lua.checkstringL(2);
		if (!strcmp(t, "handle"))
		{
			ULONG handle = lua.checkintegerL(3);
			RSLT(g_SysObj->GetProcessIdByHandle(handle, &id));
			SOK() ?	lua.pushinteger(id) : lua.Push(false);
		}
		else if (!strcmp(t, "peb"))
		{
			ULONG64 pebOffset = lua.checkintegerL(3);
			RSLT(g_SysObj->GetProcessIdByPeb(pebOffset, &id));
			SOK() ?	lua.pushinteger(id) : lua.Push(false);
		}
		else if (!strcmp(t, "sysid"))
		{
			ULONG64 sysid = lua.checkintegerL(3);
			RSLT(g_SysObj->GetProcessIdBySystemId(sysid, &id));
			SOK() ?lua.pushinteger(id) : lua.Push(false);
		}
		else if (!strcmp(t, "index"))
		{
			ULONG id[100];
			ULONG sysid[100];
			ULONG n = 0; 
			g_SysObj->GetNumberProcesses(&n);
			RSLT(g_SysObj->GetProcessIdsByIndex(0, n, id, sysid));
			if (SOK())
			{
				lua.Push(false);
				return 1;
			}
			int i = 0;
			if (lua.isnoneornil(2))
			{
				while (i++ < n)lua.pushinteger(id[i]);
				return n;
			}
			i = lua.checkintegerL(2);
			while (i++ < n)lua.pushinteger(id[i]);
			return 1;
		}
		else if (!strcmp(t, "dataoffset"))
		{
			ULONG64 data = lua.checkintegerL(2);
			RSLT(g_SysObj->GetProcessIdByDataOffset(data, &id));
			SOK() ?	lua.pushinteger(id) : lua.Push(false);
		}
		else
		{
			lua.Push();
			lua.Assert(false, "GetProcess arg #3 error!");
			return 0;//²»»á·µ»Ø
		}

		return 1;
	}
	else if (!strcmp(t, "num"))//GetNumberProcesses
	{
		ULONG n;
		RSLT(g_SysObj->GetNumberProcesses(&n));
		SOK() ?	lua.pushinteger(n) : lua.Push(false);
		return 1;
	}
	else if (!strcmp(t, "event"))//GetEventProcess
	{
		ULONG id;
		RSLT(g_SysObj->GetEventProcess(&id));
		SOK() ? lua.pushinteger(id) : lua.Push(false);
		return 1;
	
	}
	else
	{
		lua.Assert(false, "GetProcess arg #2 error!");
	}
}

int LuaGetCurrentProcessDataOffset(lua_State *L)
{
	LuaAPI lua(L);
	DbgSysObj *SysObj = (DbgSysObj *)lua.CheckUserPointer(1, str::utLuaDebugSystemObjects);

	ULONG64 offset;
	RSLT(SysObj->GetCurrentProcessDataOffset(&offset));
	SOK() ? lua.pushinteger(offset) : lua.Push(false);

	return 1;
}

int LuaGetCurrentProcessExecutableName(lua_State *L)
{
	LuaAPI lua(L);
	DbgSysObj *SysObj = (DbgSysObj *)lua.CheckUserPointer(1, str::utLuaDebugSystemObjects);

	char buf[10240];
	ULONG size;
	RSLT(SysObj->GetCurrentProcessExecutableName(buf, 10240, &size));
	SOK() ? lua.pushlstring(buf, size) : lua.Push(false);

	return 1;
}

int LuaGetCurrentProcessHandle(lua_State *L)
{
	LuaAPI lua(L);
	DbgSysObj *SysObj = (DbgSysObj *)lua.CheckUserPointer(1, str::utLuaDebugSystemObjects);

	ULONG64 handle;
	RSLT(SysObj->GetCurrentProcessHandle(&handle));
	SOK() ? lua.pushinteger(handle) : lua.Push(false);

	return 1;
}

int LuaGetCurrentProcessId(lua_State *L)
{
	LuaAPI lua(L);
	DbgSysObj *SysObj = (DbgSysObj *)lua.CheckUserPointer(1, str::utLuaDebugSystemObjects);

	ULONG id;
	RSLT(SysObj->GetCurrentProcessId(&id));
	SOK() ? lua.pushinteger(id) : lua.Push(false);

	return 1;
}

int LuaGetCurrentProcessPeb(lua_State *L)
{
	LuaAPI lua(L);
	DbgSysObj *SysObj = (DbgSysObj *)lua.CheckUserPointer(1, str::utLuaDebugSystemObjects);

	ULONG64 offset;
	RSLT(SysObj->GetCurrentProcessPeb(&offset));
	SOK() ? lua.pushinteger(offset) : lua.Push(false);

	return 1;
}

int LuaGetCurrentProcessSystemId(lua_State *L)
{
	LuaAPI lua(L);
	DbgSysObj *SysObj = (DbgSysObj *)lua.CheckUserPointer(1, str::utLuaDebugSystemObjects);

	ULONG id;
	RSLT(SysObj->GetCurrentProcessSystemId(&id));
	SOK() ? lua.pushinteger(id) : lua.Push(false);

	return 1;
}

int LuaGetCurrentThreadDataOffset(lua_State *L)
{
	LuaAPI lua(L);
	DbgSysObj *SysObj = (DbgSysObj *)lua.CheckUserPointer(1, str::utLuaDebugSystemObjects);

	ULONG64 offset;
	RSLT(SysObj->GetCurrentThreadDataOffset(&offset));
	SOK() ? lua.pushinteger(offset) : lua.Push(false);

	return 1;
}

int LuaGetCurrentThreadHandle(lua_State *L)
{
	LuaAPI lua(L);
	DbgSysObj *SysObj = (DbgSysObj *)lua.CheckUserPointer(1, str::utLuaDebugSystemObjects);

	ULONG64 handle;
	RSLT(SysObj->GetCurrentThreadHandle(&handle));
	SOK() ? lua.pushinteger(handle) : lua.Push(false);

	return 1;
}

int LuaGetCurrentThreadId(lua_State *L)
{
	LuaAPI lua(L);
	DbgSysObj *SysObj = (DbgSysObj *)lua.CheckUserPointer(1, str::utLuaDebugSystemObjects);

	ULONG id;
	RSLT(SysObj->GetCurrentThreadId(&id));
	SOK() ? lua.pushinteger(id) : lua.Push(false);

	return 1;
}

int LuaGetCurrentThreadSystemId(lua_State *L)
{
	LuaAPI lua(L);
	DbgSysObj *SysObj = (DbgSysObj *)lua.CheckUserPointer(1, str::utLuaDebugSystemObjects);

	ULONG id;
	RSLT(SysObj->GetCurrentThreadSystemId(&id));
	SOK() ? lua.pushinteger(id) : lua.Push(false);

	return 1;
}

int LuaGetCurrentThreadTeb(lua_State *L)
{
	LuaAPI lua(L);
	DbgSysObj *SysObj = (DbgSysObj *)lua.CheckUserPointer(1, str::utLuaDebugSystemObjects);

	ULONG64 offset;
	RSLT(SysObj->GetCurrentThreadTeb(&offset));
	SOK() ? lua.pushinteger(offset) : lua.Push(false);

	return 1;
}

int LuaGetEventProcess(lua_State *L)
{
	LuaAPI lua(L);
	DbgSysObj *SysObj = (DbgSysObj *)lua.CheckUserPointer(1, str::utLuaDebugSystemObjects);

	ULONG id;
	RSLT(SysObj->GetEventProcess(&id));
	SOK() ? lua.pushinteger(id) : lua.Push(false);

	return 1;
}

int LuaGetEventThread(lua_State *L)
{
	LuaAPI lua(L);
	DbgSysObj *SysObj = (DbgSysObj *)lua.CheckUserPointer(1, str::utLuaDebugSystemObjects);

	ULONG id;
	RSLT(SysObj->GetEventThread(&id));
	SOK() ? lua.pushinteger(id) : lua.Push(false);

	return 1;
}

int LuaGetNumberProcesses(lua_State *L)
{
	LuaAPI lua(L);
	DbgSysObj *SysObj = (DbgSysObj *)lua.CheckUserPointer(1, str::utLuaDebugSystemObjects);

	ULONG n;
	RSLT(SysObj->GetNumberProcesses(&n));
	SOK() ? lua.pushinteger(n) : lua.Push(false);

	return 1;
}

int LuaGetNumberThreads(lua_State *L)
{
	LuaAPI lua(L);
	DbgSysObj *SysObj = (DbgSysObj *)lua.CheckUserPointer(1, str::utLuaDebugSystemObjects);

	ULONG n;
	RSLT(SysObj->GetNumberThreads(&n));
	SOK() ? lua.pushinteger(n) : lua.Push(false);

	return 1;
}

int LuaGetProcessIdByDataOffset(lua_State *L)
{
	LuaAPI lua(L);
	DbgSysObj *SysObj = (DbgSysObj *)lua.CheckUserPointer(1, str::utLuaDebugSystemObjects);

	ULONG id;
	RSLT(SysObj->GetProcessIdByDataOffset(lua.checkintegerL(2), &id));
	SOK() ? lua.pushinteger(id) : lua.Push(false);

	return 1;
}

int LuaGetProcessIdByHandle(lua_State *L)
{
	LuaAPI lua(L);
	DbgSysObj *SysObj = (DbgSysObj *)lua.CheckUserPointer(1, str::utLuaDebugSystemObjects);

	ULONG id;
	RSLT(SysObj->GetProcessIdByHandle(lua.checkintegerL(2), &id));
	SOK() ? lua.pushinteger(id) : lua.Push(false);

	return 1;
}

int LuaGetProcessIdByPeb(lua_State *L)
{
	LuaAPI lua(L);
	DbgSysObj *SysObj = (DbgSysObj *)lua.CheckUserPointer(1, str::utLuaDebugSystemObjects);

	ULONG id;
	RSLT(SysObj->GetProcessIdByPeb(lua.checkintegerL(2), &id));
	SOK() ? lua.pushinteger(id) : lua.Push(false);

	return 1;
}

int LuaGetProcessIdBySystemId(lua_State *L)
{
	LuaAPI lua(L);
	DbgSysObj *SysObj = (DbgSysObj *)lua.CheckUserPointer(1, str::utLuaDebugSystemObjects);
;
	ULONG id;
	RSLT(SysObj->GetProcessIdBySystemId(lua.checkintegerL(2), &id));
	SOK() ? lua.pushinteger(id) : lua.Push(false);

	return 1;
}

int LuaGetProcessIdsByIndex(lua_State *L)
{
	LuaAPI lua(L);
	DbgSysObj *SysObj = (DbgSysObj *)lua.CheckUserPointer(1, str::utLuaDebugSystemObjects);

	ULONG start = lua.isnoneornil(2) ? 0 : lua.checkintegerL(2);
	ULONG count = lua.isnoneornil(3) ? 5 : lua.checkintegerL(3);
	ULONG *id = new ULONG[count],
		*sysid = new ULONG[count];
	RSLT(SysObj->GetProcessIdsByIndex(start, count, id, sysid));
	int i = 0;
	if (SOK()){
	for (lua.newtable(), i = 0; i < count; i++)
	{
		lua.pushinteger(id[i]);
		lua.seti(-2, i);
	}
	for (lua.newtable(), i = 0; i < count; i++)
	{
		lua.pushinteger(sysid[i]);
		lua.seti(-2, i);
	}}
	else lua.Push(false);

	delete[] id;
	delete[] sysid;
	return 2;
}

int LuaGetThreadIdByDataOffset(lua_State *L)
{
	LuaAPI lua(L);
	DbgSysObj *SysObj = (DbgSysObj *)lua.CheckUserPointer(1, str::utLuaDebugSystemObjects);

	ULONG id;
	RSLT(SysObj->GetThreadIdByDataOffset(lua.checkintegerL(2), &id));
	SOK() ? lua.pushinteger(id) : lua.Push(false);

	return 1;
}

int LuaGetThreadIdByHandle(lua_State *L)
{
	LuaAPI lua(L);
	DbgSysObj *SysObj = (DbgSysObj *)lua.CheckUserPointer(1, str::utLuaDebugSystemObjects);

	ULONG id;
	RSLT(SysObj->GetThreadIdByHandle(lua.checkintegerL(2), &id));
	SOK() ? lua.pushinteger(id) : lua.Push(false);

	return 1;
}

int LuaGetThreadIdByProcessor(lua_State *L)
{
	LuaAPI lua(L);
	DbgSysObj *SysObj = (DbgSysObj *)lua.CheckUserPointer(1, str::utLuaDebugSystemObjects);

	ULONG id;
	RSLT(SysObj->GetThreadIdByProcessor(lua.checkintegerL(2), &id));
	SOK() ? lua.pushinteger(id) : lua.Push(false);

	return 1;
}

int LuaGetThreadIdBySystemId(lua_State *L)
{
	LuaAPI lua(L);
	DbgSysObj *SysObj = (DbgSysObj *)lua.CheckUserPointer(1, str::utLuaDebugSystemObjects);

	ULONG id;
	RSLT(SysObj->GetThreadIdBySystemId(lua.checkintegerL(2), &id));
	SOK() ? lua.pushinteger(id) : lua.Push(false);

	return 1;
}

int LuaGetThreadIdByTeb(lua_State *L)
{
	LuaAPI lua(L);
	DbgSysObj *SysObj = (DbgSysObj *)lua.CheckUserPointer(1, str::utLuaDebugSystemObjects);

	ULONG id;
	RSLT(SysObj->GetThreadIdByTeb(lua.checkintegerL(2), &id));
	SOK() ? lua.pushinteger(id) : lua.Push(false);

	return 1;
}

int LuaGetThreadIdsByIndex(lua_State *L)
{
	LuaAPI lua(L);
	DbgSysObj *SysObj = (DbgSysObj *)lua.CheckUserPointer(1, str::utLuaDebugSystemObjects);

	ULONG start = lua.isnoneornil(2) ? 0 : lua.checkintegerL(2);
	ULONG count = lua.isnoneornil(3) ? 5 : lua.checkintegerL(3);
	ULONG *id = new ULONG[count],
		*sysid = new ULONG[count];
	RSLT(SysObj->GetThreadIdsByIndex(start, count, id, sysid));
	int i = 0;
	if (SOK()){
	for (lua.newtable(), i = 0; i < count; i++)
	{
		lua.pushinteger(id[i]);
		lua.seti(-2, i);
	}
	for (lua.newtable(), i = 0; i < count; i++)
	{
		lua.pushinteger(sysid[i]);
		lua.seti(-2, i);
	}}
	else lua.Push(false);

	delete[] id;
	delete[] sysid;
	return 1;
}

int LuaGetTotalNumberThreads(lua_State *L)
{
	LuaAPI lua(L);
	DbgSysObj *SysObj = (DbgSysObj *)lua.CheckUserPointer(1, str::utLuaDebugSystemObjects);

	ULONG total, large;
	RSLT(SysObj->GetTotalNumberThreads(&total, &large));
	SOK() ? (lua.pushinteger(total),
		lua.pushinteger(large)) : lua.Push(false);

	return 2;
}

int LuaSetCurrentProcessId(lua_State *L)
{
	LuaAPI lua(L);
	DbgSysObj *SysObj = (DbgSysObj *)lua.CheckUserPointer(1, str::utLuaDebugSystemObjects);

	RSLT(SysObj->SetCurrentProcessId(lua.checkintegerL(2)));
	lua.Push((bool)(SOK()));

	return 1;
}

int LuaSetCurrentThreadId(lua_State *L)
{
	LuaAPI lua(L);
	DbgSysObj *SysObj = (DbgSysObj *)lua.CheckUserPointer(1, str::utLuaDebugSystemObjects);

	RSLT(SysObj->SetCurrentThreadId(lua.checkintegerL(2)));
	lua.Push((bool)(SOK()));

	return 1;
}
