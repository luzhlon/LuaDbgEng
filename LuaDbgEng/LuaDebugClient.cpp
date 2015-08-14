#include "str.h"
#include "LuaDbgEng.h"
#include "LuaDebugClient.h"
#include "LuaDebugControl.h"
#include "LuaDebugSymbols.h"
#include "LuaDebugRegisters.h"
#include "LuaDebugDataSpaces.h"
#include "LuaDebugSystemObjects.h"

luaL_Reg LuaDebugClientLib[] =
{
	//Client
	{ "QueryControl", LuaQueryControl },
	{ "QuerySymbols", LuaQuerySymbols },
	{ "QueryRegisters", LuaQueryRegisters },
	{ "QueryDataSpaces", LuaQueryDataSpaces },
	{ "QuerySystemObjects", LuaQuerySystemObjects },

    { "CreateProcess", LuaCreateProcess},
    { "AttachProcess", LuaAttachProcess},
    { "AddProcessOptions", LuaAddProcessOptions},
    { "AttachKernel", LuaAttachKernel},
    { "ConnectProcessServer", LuaConnectProcessServer },
    { "ConnectSession", LuaConnectSession},
    { "CreateProcessAndAttach", LuaCreateProcessAndAttach },
    { "DetachProcesses", LuaDetachProcesses },
    { "DisconnectProcessServer", LuaDisconnectProcessServer },
    { "DispatchCallbacks", LuaDispatchCallbacks },
    { "EndSession", LuaEndSession },
    { "ExitDispatch", LuaExitDispatch },
    { "FlushCallbacks", LuaFlushCallbacks },
    { "GetEventCallbacks", LuaGetEventCallbacks },
    { "GetExitCode", LuaGetExitCode },
    { "GetIdentity", LuaGetIdentity },
    { "GetInputCallbacks", LuaGetInputCallbacks },
    { "GetKernelConnectionOptions", LuaGetKernelConnectionOptions },
    { "GetOtherOutputMask", LuaGetOtherOutputMask },
    { "GetOutputCallbacks", LuaGetOutputCallbacks },
    { "GetOutputLinePrefix", LuaGetOutputLinePrefix  },
    { "GetProcessOptions", LuaGetProcessOptions },
    { "GetRunningProcessDescription", LuaGetRunningProcessDescription },
    { "GetRunningProcessSystemIdByExecutableName", LuaGetRunningProcessSystemIdByExecutableName },
    { "GetRunningProcessSystemIds", LuaGetRunningProcessSystemIds },
    { "OpenDumpFile", LuaOpenDumpFile },
    { "OutputIdentity", LuaOutputIdentity },
    { "OutputServers", LuaOutputServers },
    { "RemoveProcessOptions", LuaRemoveProcessOptions },
    { "SetEventCallbacks", LuaSetEventCallbacks },
    { "SetInputCallbacks", LuaSetInputCallbacks },
    { "SetKernelConnectionOptions", LuaSetKernelConnectionOptions },
    { "SetOtherOutputMask", LuaSetOtherOutputMask },
    { "SetOutputCallbacks", LuaSetOutputCallbacks },
    { "SetOutputLinePrefix", LuaSetOutputLinePrefix  },
    { "SetProcessOptions", LuaSetProcessOptions },
    { "StartProcessServer", LuaStartProcessServer },
    { "StartServer", LuaStartServer },
    { "TerminateProcesses", LuaTerminateProcesses },
    { "WriteDumpFile", LuaWriteDumpFile },
	{ 0, 0 }
};

int LuaQueryControl(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	DbgControl *Ctrl;
	RSLT(Client->QueryInterface(__uuidof(DbgControl), (void **)&Ctrl));
	lua.NewUserPointer(Ctrl, str::utLuaDebugControl);
	lua.newlibL(LuaDebugControlLib);
	lua.SetMetaField(-2, "__index");
	if (!SOK())lua.Push(false);
	
	return 1;
}
int LuaQuerySymbols(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	DbgSymbol *Sym;
	RSLT(Client->QueryInterface(__uuidof(DbgSymbol), (void **)&Sym));
	lua.NewUserPointer(Sym, str::utLuaDebugSymbols);
	lua.newlibL(LuaDebugSymbolsLib);
	lua.SetMetaField(-2, "__index");
	if (!SOK())lua.Push(false);
	
	return 1;
}

int LuaQueryRegisters(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	DbgRegist *Reg;
	RSLT(Client->QueryInterface(__uuidof(DbgRegist), (void **)&Reg));
	lua.NewUserPointer(Reg, str::utLuaDebugRegisters);
	lua.newlibL(LuaDebugRegistersLib);
	lua.SetMetaField(-2, "__index");
	if (!SOK())lua.Push(false);
	
	return 1;
}

int LuaQueryDataSpaces(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	DbgDataSpc *Data;
	RSLT(Client->QueryInterface(__uuidof(DbgDataSpc), (void **)&Data));
	lua.NewUserPointer(Data, str::utLuaDebugDataSpaces);
	lua.newlibL(LuaDebugDataSpacesLib);
	lua.SetMetaField(-2, "__index");
	if (!SOK())lua.Push(false);
	
	return 1;
}

int LuaQuerySystemObjects(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	DbgSysObj *SysObj;
	RSLT(Client->QueryInterface(__uuidof(DbgSysObj), (void **)&SysObj));
	lua.NewUserPointer(SysObj, str::utLuaDebugSystemObjects);
	lua.newlibL(LuaDebugSystemObjectsLib);
	lua.SetMetaField(-2, "__index");
	if (!SOK())lua.Push(false);
	
	return 1;
}

int LuaCreateProcess(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	const char *cmd = lua.checkstringL(2);
	ULONG flags = lua.isnoneornil(3)?
		DEBUG_CREATE_PROCESS_NO_DEBUG_HEAP | DEBUG_PROCESS : lua.checkintegerL(3);
	ULONG srv = lua.isnoneornil(4)? NULL : lua.checkintegerL(4);

	RSLT(Client->CreateProcess(srv, (PSTR)cmd, flags));
	lua.Push(SOK());

	return 1;
}

int LuaAttachProcess(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	ULONG pid = lua.checkintegerL(2);
	ULONG flags = lua.isnoneornil(3)?
		DEBUG_CREATE_PROCESS_NO_DEBUG_HEAP | DEBUG_PROCESS : lua.checkintegerL(3);
	ULONG srv = lua.isnoneornil(4)? NULL : lua.checkintegerL(4);

	RSLT(Client->AttachProcess(srv, pid, flags));
	lua.Push(SOK());
	return 1;
}

int LuaSetEventCallbacks(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	RSLT(Client->SetEventCallbacks((IDebugEventCallbacks *)
		lua.CheckUserPointer(2, str::utLuaEventCallback)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaSetOutputCallbacks(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	RSLT(Client->SetOutputCallbacks((IDebugOutputCallbacks *)
		lua.CheckUserPointer(2, str::utLuaOutputCallback)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaSetInputCallbacks(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	RSLT(Client->SetInputCallbacks((IDebugInputCallbacks *)
		lua.CheckUserPointer(2, str::utLuaInputCallback)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaAddProcessOptions(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	RSLT(Client->AddProcessOptions(lua.checkintegerL(2)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaAttachKernel(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	RSLT(Client->AttachKernel((ULONG)lua.checkintegerL(2), lua.checkstringL(3)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaConnectProcessServer(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	ULONG64 srv;
	RSLT(Client->ConnectProcessServer(lua.checkstringL(2), &srv));
	SOK() ? lua.Push(srv) : lua.Push(false);

	return 1;
}

int LuaConnectSession(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	RSLT(Client->ConnectSession(lua.checkintegerL(2), lua.checkintegerL(3)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaCreateProcessAndAttach(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	RSLT(Client->CreateProcessAndAttach(lua.checkintegerL(2),
		                                  (PSTR)lua.checkstringL(3),
										  lua.checkintegerL(4),
										  lua.checkintegerL(5),
										  lua.checkintegerL(6)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaDetachProcesses(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	RSLT(Client->DetachProcesses());
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaDisconnectProcessServer(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	RSLT(Client->DisconnectProcessServer(lua.checkintegerL(2)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaDispatchCallbacks(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	RSLT(Client->DispatchCallbacks(lua.checkintegerL(2)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaEndSession(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	RSLT(Client->EndSession(lua.checkintegerL(2)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaExitDispatch(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	RSLT(Client->ExitDispatch((IDebugClient *)Client));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaFlushCallbacks(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	RSLT(Client->FlushCallbacks());
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaGetEventCallbacks(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	PDEBUG_EVENT_CALLBACKS pDEC;
	RSLT(Client->GetEventCallbacks(&pDEC));
	SOK() ? lua.NewUserPointer(pDEC, str::utLuaEventCallback) : lua.Push(false);

	return 1;
}

int LuaGetExitCode(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	ULONG ec;
	RSLT(Client->GetExitCode(&ec));
	SOK() ? lua.pushinteger(ec) : lua.Push(false);

	return 1;
}

int LuaGetIdentity(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	char str[10240];
	ULONG len;
	RSLT(Client->GetIdentity(str, 10240, &len));
	SOK() ? lua.pushlstring(str, len) : lua.Push(false);

	return 1;
}

int LuaGetInputCallbacks(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	PDEBUG_INPUT_CALLBACKS pDIC;
	RSLT(Client->GetInputCallbacks(&pDIC));
	SOK() ? lua.NewUserPointer(pDIC, str::utLuaEventCallback) : lua.Push(false);

	return 1;
}

int LuaGetKernelConnectionOptions(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	char str[10240];
	ULONG len;
	RSLT(Client->GetKernelConnectionOptions(str, 10240, &len));
	SOK() ? lua.pushlstring(str, len) : lua.Push(false);
	
	return 1;
}

int LuaGetOtherOutputMask(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	ULONG mask;
	RSLT(Client->GetOtherOutputMask((IDebugClient *)Client, &mask));
	SOK() ? lua.pushinteger(mask) : lua.Push(false);

	return 1;
}

int LuaGetOutputCallbacks(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	PDEBUG_EVENT_CALLBACKS pDEC;
	RSLT(Client->GetEventCallbacks(&pDEC));
	SOK() ? lua.NewUserPointer(pDEC, str::utLuaEventCallback) : lua.Push(false);

	return 1;
}

int LuaGetOutputLinePrefix(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	char str[10240];
	ULONG len;
	RSLT(Client->GetOutputLinePrefix(str, 10240, &len));
	SOK() ? lua.pushlstring(str, len) : lua.Push(false);

	return 1;
}

int LuaGetProcessOptions(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	ULONG options;
	RSLT(Client->GetProcessOptions(&options));
	SOK() ? lua.pushinteger(options) : lua.Push(false);

	return 1;
}

int LuaGetRunningProcessDescription(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	char exe[5120];
	char dsp[5120];
	ULONG len1,len2;
	RSLT(Client->GetRunningProcessDescription(lua.checkintegerL(2),
	                                            lua.checkintegerL(3),
	                                            lua.checkintegerL(4),
												exe, 5120,&len1,
												dsp, 5120,&len2));
	SOK() ? (lua.pushlstring(exe, len1), lua.pushlstring(dsp, len2))
		: lua.Push(false);

	return 2;
}

int LuaGetRunningProcessSystemIdByExecutableName(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);
	
	ULONG id;
	RSLT(Client->GetRunningProcessSystemIdByExecutableName(lua.checkintegerL(2),
		                                                     lua.checkstringL(3),
		                                                     lua.checkintegerL(4),
															 &id));
	SOK() ? lua.pushinteger(id) : lua.Push(false);

	return 1;
}

int LuaGetRunningProcessSystemIds(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	ULONG ids[10240], n, i = 0;
	RSLT(Client->GetRunningProcessSystemIds(lua.checkintegerL(2),
		                                      ids, 10240, &n));
	if (!SOK())
	{
		lua.Push(false);
		return 2;
	}
	lua.newtable();
	while (i++ < n)
	{
		lua.pushinteger(ids[i]);
		lua.seti(-3, i+2);
	}

	return 1;
}

int LuaOpenDumpFile(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	RSLT(Client->OpenDumpFile((PSTR)lua.checkintegerL(2)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaOutputIdentity(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	RSLT(Client->OutputIdentity(lua.checkintegerL(2),
		                          lua.checkintegerL(3),
		                          lua.checkstringL(4)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaOutputServers(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	RSLT(Client->OutputServers(lua.checkintegerL(2),
		                          lua.checkstringL(4),
		                          lua.checkintegerL(3)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaRemoveProcessOptions(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	RSLT(Client->RemoveProcessOptions(lua.checkintegerL(2)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaSetKernelConnectionOptions(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	RSLT(Client->SetKernelConnectionOptions(lua.checkstringL(2)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaSetOtherOutputMask(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	RSLT(Client->SetOtherOutputMask((IDebugClient *)Client, lua.checkintegerL(2)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaSetOutputLinePrefix(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	RSLT(Client->SetOutputLinePrefix(lua.checkstringL(2)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaSetProcessOptions(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	RSLT(Client->SetProcessOptions(lua.checkintegerL(2)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaStartProcessServer(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	RSLT(Client->StartProcessServer(lua.checkintegerL(2), lua.checkstringL(3), 0));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaStartServer(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	RSLT(Client->StartServer(lua.checkstringL(3)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaTerminateCurrentProcess(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	RSLT(Client->TerminateCurrentProcess());
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaTerminateProcesses(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	RSLT(Client->TerminateProcesses());
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaWriteDumpFile(lua_State *L)
{
	LuaAPI lua(L);
	DbgClient *Client = (DbgClient *)lua.CheckUserPointer(1, str::utLuaDebugClient);

	RSLT(Client->WriteDumpFile(lua.checkstringL(2), lua.checkintegerL(3)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

