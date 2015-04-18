#ifndef __LUADEBUGCONTROL_H_
#define __LUADEBUGCONTROL_H_

#include "LuaAPI.h"
#include "dbgeng.h"

#define DbgControl IDebugControl4

int LuaAddBreakpoint(lua_State *L);
int LuaAddEngineOptions(lua_State *L);
int LuaAddExtension(lua_State *L);
int LuaAssemble(lua_State *L);
int LuaCallExtension(lua_State *L);
int LuaCloseLogFile(lua_State *L);
int LuaCoerceValue(lua_State *L);
int LuaCoerceValues(lua_State *L);
int LuaControlledOutput(lua_State *L);
int LuaControlledOutputVaList(lua_State *L);
int LuaDisassemble(lua_State *L);
int LuaEvaluate(lua_State *L);
int LuaExecute(lua_State *L);
int LuaExecuteCommandFile(lua_State *L);
int LuaGetActualProcessorType(lua_State *L);
int LuaGetBreakpointById(lua_State *L);
int LuaGetBreakpointByIndex(lua_State *L);
int LuaGetBreakpointParameters(lua_State *L);
int LuaGetCodeLevel(lua_State *L);
int LuaGetDebuggeeType(lua_State *L);
int LuaGetDisassembleEffectiveOffset(lua_State *L);
int LuaGetEffectiveProcessorType(lua_State *L);
int LuaGetEngineOptions(lua_State *L);
int LuaGetEventFilterCommand(lua_State *L);
int LuaGetEventFilterText(lua_State *L);
int LuaGetExceptionFilterParameters(lua_State *L);
int LuaGetExceptionFilterSecondCommand(lua_State *L);
int LuaGetExecutingProcessorType(lua_State *L);
int LuaGetExecutionStatus(lua_State *L);
int LuaGetExtensionByPath(lua_State *L);
int LuaGetExtensionFunction(lua_State *L);
int LuaGetInterrupt(lua_State *L);
int LuaGetInterruptTimeout(lua_State *L);
int LuaGetLastEventInformation(lua_State *L);
int LuaGetLogFile(lua_State *L);
int LuaGetLogMask(lua_State *L);
int LuaGetNearInstruction(lua_State *L);
int LuaGetNotifyEventHandle(lua_State *L);
int LuaGetNumberBreakpoints(lua_State *L);
int LuaGetNumberEventFilters(lua_State *L);
int LuaGetNumberPossibleExecutingProcessorTypes(lua_State *L);
int LuaGetNumberProcessors(lua_State *L);
int LuaGetNumberSupportedProcessorTypes(lua_State *L);
int LuaGetPageSize(lua_State *L);
int LuaGetPossibleExecutingProcessorTypes(lua_State *L);
int LuaGetProcessorTypeNames(lua_State *L);
int LuaGetPromptText(lua_State *L);
int LuaGetRadix(lua_State *L);
int LuaGetReturnOffset(lua_State *L);
int LuaGetSpecificFilterArgument(lua_State *L);
int LuaGetSpecificFilterParameters(lua_State *L);
int LuaGetStackTrace(lua_State *L);
int LuaGetSupportedProcessorTypes(lua_State *L);
int LuaGetSystemErrorControl(lua_State *L);
int LuaGetSystemVersion(lua_State *L);
int LuaGetTextMacro(lua_State *L);
int LuaGetWindbgExtensionApis32 (lua_State *L);
int LuaInput(lua_State *L);
int LuaIsPointer64Bit(lua_State *L);
int LuaOpenLogFile(lua_State *L);
int LuaOutput(lua_State *L);
int LuaOutputCurrentState(lua_State *L);
int LuaOutputDisassembly(lua_State *L);
int LuaOutputDisassemblyLines(lua_State *L);
int LuaOutputPrompt(lua_State *L);
int LuaOutputPromptVaList(lua_State *L);
int LuaOutputStackTrace(lua_State *L);
int LuaOutputVaList(lua_State *L);
int LuaOutputVersionInformation(lua_State *L);
int LuaReadBugCheckData(lua_State *L);
int LuaRemoveBreakpoint(lua_State *L);
int LuaRemoveEngineOptions(lua_State *L);
int LuaRemoveExtension(lua_State *L);
int LuaReturnInput(lua_State *L);
int LuaSetCodeLevel(lua_State *L);
int LuaSetEffectiveProcessorType(lua_State *L);
int LuaSetEngineOptions(lua_State *L);
int LuaSetEventFilterCommand(lua_State *L);
int LuaSetExceptionFilterParameters(lua_State *L);
int LuaSetExceptionFilterSecondCommand(lua_State *L);
int LuaSetExecutionStatus(lua_State *L);
int LuaSetInterrupt(lua_State *L);
int LuaSetInterruptTimeout(lua_State *L);
int LuaSetLogMask(lua_State *L);
int LuaSetNotifyEventHandle(lua_State *L);
int LuaSetRadix(lua_State *L);
int LuaSetSpecificFilterArgument(lua_State *L);
int LuaSetSpecificFilterParameters(lua_State *L);
int LuaSetSystemErrorControl(lua_State *L);
int LuaSetTextMacro(lua_State *L);
int LuaWaitForEvent(lua_State *L);

luaL_Reg LuaDebugControlLib[];

#endif
