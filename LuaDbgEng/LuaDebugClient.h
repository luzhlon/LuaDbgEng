#ifndef __LUADEBUGCLIENT_H_
#define __LUADEBUGCLIENT_H_

#include "LuaAPI.h"
#include "dbgeng.h"

#define DbgClient IDebugClient5

int LuaQueryControl(lua_State *L);
int LuaQuerySymbols(lua_State *L);
int LuaQueryRegisters(lua_State *L);
int LuaQueryDataSpaces(lua_State *L);
int LuaQuerySystemObjects(lua_State *L);

int LuaCreateProcess(lua_State *L);
int LuaAttachProcess(lua_State *L);
int LuaAddProcessOptions(lua_State *L);
int LuaAttachKernel(lua_State *L);
int LuaConnectProcessServer(lua_State *L);
int LuaConnectSession(lua_State *L);
//CreateClient Creates a new client object for the current thread.
int LuaCreateProcessAndAttach(lua_State *L);
int LuaDetachProcesses(lua_State *L);
int LuaDisconnectProcessServer(lua_State *L);
int LuaDispatchCallbacks(lua_State *L);
int LuaEndSession(lua_State *L);
int LuaExitDispatch(lua_State *L);
int LuaFlushCallbacks(lua_State *L);
int LuaGetEventCallbacks(lua_State *L);
int LuaGetExitCode(lua_State *L);
int LuaGetIdentity(lua_State *L);
int LuaGetInputCallbacks(lua_State *L);
int LuaGetKernelConnectionOptions(lua_State *L);
int LuaGetOtherOutputMask(lua_State *L);
int LuaGetOutputCallbacks(lua_State *L);
int LuaGetOutputLinePrefix (lua_State *L);
int LuaGetProcessOptions(lua_State *L);
int LuaGetRunningProcessDescription(lua_State *L);
int LuaGetRunningProcessSystemIdByExecutableName(lua_State *L);
int LuaGetRunningProcessSystemIds(lua_State *L);
int LuaOpenDumpFile(lua_State *L);
int LuaOutputIdentity(lua_State *L);
int LuaOutputServers(lua_State *L);
int LuaRemoveProcessOptions(lua_State *L);
int LuaSetEventCallbacks(lua_State *L);
int LuaSetInputCallbacks(lua_State *L);
int LuaSetKernelConnectionOptions(lua_State *L);
int LuaSetOtherOutputMask(lua_State *L);
int LuaSetOutputCallbacks(lua_State *L);
int LuaSetOutputLinePrefix (lua_State *L);
int LuaSetProcessOptions(lua_State *L);
int LuaStartProcessServer(lua_State *L);
int LuaStartServer(lua_State *L);
int LuaTerminateProcesses(lua_State *L);
int LuaWriteDumpFile(lua_State *L);
/*
//IDebugClient2
int LuaAbandonCurrentProcess(lua_State *L);
int LuaAddDumpInformationFile(lua_State *L);
int LuaDetachCurrentProcess(lua_State *L);
int LuaEndProcessServer(lua_State *L);
int LuaIsKernelDebuggerEnabled(lua_State *L);
int LuaTerminateCurrentProcess(lua_State *L);
int LuaWaitForProcessServerEnd(lua_State *L);
int LuaWriteDumpFile2(lua_State *L);
//IDebugClient4
int LuaGetDumpFile(lua_State *L);
//IDebugClient5
int LuaCreateProcess2(lua_State *L);
int LuaGetNumberEventCallbacks(lua_State *L);
int LuaGetNumberOutputCallbacks(lua_State *L);
int LuaGetNumberInputCallbacks(lua_State *L);
*/
luaL_Reg LuaDebugClientLib[];

#endif
