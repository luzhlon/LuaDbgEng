#include "str.h"
#include "LuaDbgEng.h"
#include "LuaDbgStruct.h"
#include "LuaBreakpoint.h"
#include "LuaDebugControl.h"

luaL_Reg LuaDebugControlLib[] = 
{
	{ "AddBreakpoint", LuaAddBreakpoint },
	{ "AddEngineOptions", LuaAddEngineOptions},
	{ "AddExtension", LuaAddExtension },
	{ "Assemble", LuaAssemble},
	{ "CallExtension", LuaCallExtension},
	{ "CloseLogFile", LuaCloseLogFile},
	{ "CoerceValue", LuaCoerceValue},
	//{ "CoerceValues", LuaCoerceValues},
	//{ "ControlledOutput", LuaControlledOutput},
	//{ "ControlledOutputVaList", LuaControlledOutputVaList},
	{ "Disassemble", LuaDisassemble},
	{ "Evaluate", LuaEvaluate},
	{ "Execute", LuaExecute},
	{ "ExecuteCommandFile", LuaExecuteCommandFile},
	{ "GetActualProcessorType", LuaGetActualProcessorType},
	{ "GetBreakpointById", LuaGetBreakpointById},
	{ "GetBreakpointByIndex", LuaGetBreakpointByIndex},
	{ "GetBreakpointParameters", LuaGetBreakpointParameters},
	{ "GetCodeLevel", LuaGetCodeLevel},
	{ "GetDebuggeeType", LuaGetDebuggeeType},
	{ "GetDisassembleEffectiveOffset", LuaGetDisassembleEffectiveOffset},
	{ "GetEffectiveProcessorType", LuaGetEffectiveProcessorType},
	{ "GetEngineOptions", LuaGetEngineOptions},
	{ "GetEventFilterCommand", LuaGetEventFilterCommand},
	{ "GetEventFilterText", LuaGetEventFilterText},
	{ "GetExceptionFilterParameters", LuaGetExceptionFilterParameters},
	{ "GetExceptionFilterSecondCommand", LuaGetExceptionFilterSecondCommand},
	{ "GetExecutingProcessorType", LuaGetExecutingProcessorType},
	{ "GetExecutionStatus", LuaGetExecutionStatus},
	{ "GetExtensionByPath", LuaGetExtensionByPath},
	{ "GetExtensionFunction", LuaGetExtensionFunction},
	{ "GetInterrupt", LuaGetInterrupt},
	{ "GetInterruptTimeout", LuaGetInterruptTimeout},
	{ "GetLastEventInformation", LuaGetLastEventInformation},
	{ "GetLogFile", LuaGetLogFile},
	{ "GetLogMask", LuaGetLogMask},
	{ "GetNearInstruction", LuaGetNearInstruction},
	{ "GetNotifyEventHandle", LuaGetNotifyEventHandle},
	{ "GetNumberBreakpoints", LuaGetNumberBreakpoints},
	{ "GetNumberEventFilters", LuaGetNumberEventFilters},
	{ "GetNumberPossibleExecutingProcessorTypes", LuaGetNumberPossibleExecutingProcessorTypes},
	{ "GetNumberProcessors", LuaGetNumberProcessors},
	{ "GetNumberSupportedProcessorTypes", LuaGetNumberSupportedProcessorTypes},
	{ "GetPageSize", LuaGetPageSize},
	{ "GetPossibleExecutingProcessorTypes", LuaGetPossibleExecutingProcessorTypes},
	{ "GetProcessorTypeNames", LuaGetProcessorTypeNames},
	{ "GetPromptText", LuaGetPromptText},
	{ "GetRadix", LuaGetRadix},
	{ "GetReturnOffset", LuaGetReturnOffset},
	{ "GetSpecificFilterArgument", LuaGetSpecificFilterArgument},
	{ "GetSpecificFilterParameters", LuaGetSpecificFilterParameters},
	{ "GetStackTrace", LuaGetStackTrace},
	{ "GetSupportedProcessorTypes", LuaGetSupportedProcessorTypes},
	{ "GetSystemErrorControl", LuaGetSystemErrorControl},
	{ "GetSystemVersion", LuaGetSystemVersion},
	{ "GetTextMacro", LuaGetTextMacro},
	{ "GetWindbgExtensionApis32", LuaGetWindbgExtensionApis32 },
	{ "Input", LuaInput},
	{ "IsPointer64Bit", LuaIsPointer64Bit},
	{ "OpenLogFile", LuaOpenLogFile},
	{ "Output", LuaOutput},
	{ "OutputCurrentState", LuaOutputCurrentState},
	{ "OutputDisassembly", LuaOutputDisassembly},
	{ "OutputDisassemblyLines", LuaOutputDisassemblyLines},
	//{ "OutputPrompt", LuaOutputPrompt},
	//{ "OutputPromptVaList", LuaOutputPromptVaList},
	{ "OutputStackTrace", LuaOutputStackTrace},
	//{ "OutputVaList", LuaOutputVaList},
	{ "OutputVersionInformation", LuaOutputVersionInformation},
	{ "ReadBugCheckData", LuaReadBugCheckData},
	{ "RemoveBreakpoint", LuaRemoveBreakpoint},
	{ "RemoveEngineOptions", LuaRemoveEngineOptions},
	{ "RemoveExtension", LuaRemoveExtension},
	{ "ReturnInput", LuaReturnInput},
	{ "SetCodeLevel", LuaSetCodeLevel},
	{ "SetEffectiveProcessorType", LuaSetEffectiveProcessorType},
	{ "SetEngineOptions", LuaSetEngineOptions},
	{ "SetEventFilterCommand", LuaSetEventFilterCommand},
	//{ "SetExceptionFilterParameters", LuaSetExceptionFilterParameters},
	{ "SetExceptionFilterSecondCommand", LuaSetExceptionFilterSecondCommand},
	{ "SetExecutionStatus", LuaSetExecutionStatus},
	{ "SetInterrupt", LuaSetInterrupt},
	{ "SetInterruptTimeout", LuaSetInterruptTimeout},
	{ "SetLogMask", LuaSetLogMask},
	{ "SetNotifyEventHandle", LuaSetNotifyEventHandle},
	{ "SetRadix", LuaSetRadix},
	{ "SetSpecificFilterArgument", LuaSetSpecificFilterArgument},
	{ "SetSpecificFilterParameters", LuaSetSpecificFilterParameters},
	{ "SetSystemErrorControl", LuaSetSystemErrorControl},
	{ "SetTextMacro", LuaSetTextMacro},
	{ "WaitForEvent", LuaWaitForEvent},
	{ 0, 0 }
};

int LuaAssemble(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG64 endoffset;
	ULONG64 offset = lua.checkintegerL(2);
	PCSTR instr = lua.checkstringL(3);

	if (Control->Assemble(offset, instr, &endoffset))
		lua.Push((lua_Integer)endoffset);
	else
		lua.Push(false);

	return 1;
}

int LuaAddBreakpoint(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	DbgBreakpoint *bp;
	RSLT(Control->AddBreakpoint(lua.checkintegerL(2), lua.checkintegerL(3), (IDebugBreakpoint **)&bp));
	SOK() ? NewLuaBreakpoint(L, bp) : lua.Push(false);

	return 1;
}

int LuaAddEngineOptions(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	RSLT(Control->AddEngineOptions(lua.checkintegerL(2)));
	lua.Push((bool)SOK());

	return 0;
}

int LuaAddExtension(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG64 h;
	RSLT(Control->AddExtension(lua.checkstringL(2), lua.checkintegerL(2), &h));
	lua.Push((bool)SOK());

	return 1;
}

int LuaCallExtension(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	RSLT(Control->CallExtension(lua.checkintegerL(2), lua.checkstringL(2), lua.checkstringL(4)));
	lua.Push((bool)SOK());

	return 1;
}

int LuaCloseLogFile(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	RSLT(Control->CloseLogFile());
	lua.Push((bool)SOK());

	return 1;
}

int LuaCoerceValue(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	DEBUG_VALUE in, out; lua.pushvalue(2);
	Table2VALUE(L, &in); lua.pop(1);

	RSLT(Control->CoerceValue(&in, lua.checkintegerL(3), &out));
	SOK() ? VALUE2Table(L, &out) : lua.Push(false);

	return 1;
}

int LuaCoerceValues(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	//RSLT(Control->CoerceValues(&in, lua.checkintegerL(3), &out));
	//SOK() ? VALUE2Table(L, &out) : lua.Push(false);

	return 1;
}

int LuaControlledOutput(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	//RSLT(Control->ControlledOutput(&in, , &out));
	//lua.Push((bool)SOK());

	return 1;
}

int LuaDisassemble(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	char buf[256];
	ULONG64 endoffset;
	ULONG disasmSize;
	PSTR  Buf = buf;
	ULONG64 offset = lua.checkintegerL(2);

	RSLT(Control->Disassemble(offset, NULL, Buf, 256, &disasmSize, &endoffset));
	if (SOK())
	{
		lua.pushlstring(Buf, disasmSize);
		lua.pushinteger(endoffset);
		return 2;
	}
	lua.Push(false);

	return 1;
}

int LuaEvaluate(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	DEBUG_VALUE d;
	ULONG ri;
	RSLT(Control->Evaluate(lua.checkstringL(2), lua.checkintegerL(3), &d, &ri));
	SOK() ? (VALUE2Table(L, &d), lua.pushinteger(ri)) : lua.Push(false);

	return SOK() ? 2 : 1;
}

int LuaExecute(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	PCSTR cmd = lua.checkstringL(2);
	ULONG outctrl = lua.isnoneornil(3) ? DEBUG_OUTCTL_THIS_CLIENT : lua.checkintegerL(3);
	ULONG flags = lua.isnoneornil(4) ?  DEBUG_EXECUTE_ECHO  : lua.checkintegerL(4);
	RSLT(Control->Execute(outctrl, cmd, flags));
	int s = lua_status(L);
	lua.Push((bool)SOK());

	return 1;
}

int LuaExecuteCommandFile(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	RSLT(Control->ExecuteCommandFile(lua.checkintegerL(2), lua.checkstringL(3), lua.checkintegerL(4)));
	lua.Push((bool)SOK());

	return 1;
}

int LuaGetActualProcessorType(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG type;
	RSLT(Control->GetActualProcessorType(&type));
	lua.Push((bool)SOK());

	return 1;
}

int LuaGetBreakpointById(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	DbgBreakpoint *bp;
	RSLT(Control->GetBreakpointById(lua.checkintegerL(2), (IDebugBreakpoint **)&bp));
	SOK() ? lua.NewUserPointer(bp, str::utLuaBreakpoint) : lua.Push(false);

	return 1;
}

int LuaGetBreakpointByIndex(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	DbgBreakpoint *bp;
	RSLT(Control->GetBreakpointByIndex(lua.checkintegerL(2), (IDebugBreakpoint **)&bp));
	SOK() ? lua.NewUserPointer(bp, str::utLuaBreakpoint) : lua.Push(false);

	return 1;
}

int LuaGetBreakpointParameters(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	DEBUG_BREAKPOINT_PARAMETERS dbp;
	//RSLT(Control->GetBreakpointParameters(lua.checkintegerL(2), (IDebugBreakpoint **)&bp));
	//SOK() ? lua.NewUserPointer(dbp, str::utLuaBreakpoint) : lua.Push(false);

	return 1;
}

int LuaGetCodeLevel(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG lev;
	RSLT(Control->GetCodeLevel(&lev));
	SOK() ? lua.pushinteger(lev) : lua.Push(false);

	return 1;
}

int LuaGetDebuggeeType(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG c, q;
	RSLT(Control->GetDebuggeeType(&c, &q));
	SOK() ? (lua.pushinteger(c), lua.pushinteger(q)) : lua.Push(false);

	return 1;
}

int LuaGetDisassembleEffectiveOffset(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG64 offset;
	RSLT(Control->GetDisassembleEffectiveOffset(&offset));
	SOK() ? lua.pushinteger(offset) : lua.Push(false);

	return 1;
}

int LuaGetEffectiveProcessorType(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG type;
	RSLT(Control->GetEffectiveProcessorType(&type));
	SOK() ? lua.pushinteger(type) : lua.Push(false);

	return 1;
}

int LuaGetEngineOptions(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG opt;
	RSLT(Control->GetEngineOptions(&opt));
	SOK() ? lua.pushinteger(opt) : lua.Push(false);

	return 1;
}

int LuaGetEventFilterCommand(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	char str[10240];
	ULONG len;
	RSLT(Control->GetEventFilterCommand(lua.checkintegerL(2),
		                               str, 10240, &len));
	SOK() ? lua.pushlstring(str, len) : lua.Push(false);

	return 1;
}

int LuaGetEventFilterText(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	char str[10240];
	ULONG len;
	RSLT(Control->GetEventFilterText(lua.checkintegerL(2),
		                               str, 10240, &len));
	SOK() ? lua.pushlstring(str, len) : lua.Push(false);

	return 1;
}

int LuaGetExceptionFilterParameters(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	//RSLT(Control->GetExceptionFilterParameters(lua.checkintegerL(), lua.checkintegerL(), lua.checkintegerL()));
	//SOK() ? lua.pushlstring(str, len) : lua.Push(false);

	return 1;
}

int LuaGetExceptionFilterSecondCommand(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	char cmd[10240]; ULONG size;
	RSLT(Control->GetExceptionFilterSecondCommand(lua.checkintegerL(2), cmd, 10240, &size));
	SOK() ? lua.pushlstring(cmd, size) : lua.Push(false);

	return 1;
}

int LuaGetExecutingProcessorType(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG type;
	RSLT(Control->GetExecutingProcessorType(&type));
	SOK() ? lua.pushinteger(type) : lua.Push(false);

	return 1;
}

int LuaGetExecutionStatus(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG status;
	RSLT(Control->GetExecutionStatus(&status));
	SOK() ? lua.pushinteger(status) : lua.Push(false);

	return 1;
}

int LuaGetExtensionByPath(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	PCSTR path = lua.checkstringL(2);
	ULONG64 handle;
	RSLT(Control->GetExtensionByPath(path, &handle));
	SOK() ? lua.pushinteger(handle) : lua.Push(false);

	return 1;
}

int LuaGetExtensionFunction(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	FARPROC func;
	RSLT(Control->GetExtensionFunction(lua.checkintegerL(2),
				lua.checkstringL(3), &func));
	SOK() ? lua.pushinteger((lua_Integer)func) : lua.Push(false);

	return 1;
}

int LuaGetInterrupt(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	RSLT(Control->GetInterrupt());
	lua.Push((bool)SOK());

	return 1;
}

int LuaGetInterruptTimeout(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG t;
	RSLT(Control->GetInterruptTimeout(&t));
	SOK() ? lua.pushinteger(t) : lua.Push(false);

	return 1;
}

int LuaGetLastEventInformation(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG type, pid, tid, exSize, descSize;
	char ex[10240], desc[10240];
	//RSLT(Control->GetLastEventInformation(&type, &pid, &tid, 0, &exSize, 0, , 10240, &descSize));
	//SOK() ? lua.pushinteger(t) : lua.Push(false);

	return 1;
}

int LuaGetLogFile(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	char buf[512];
	ULONG fSize;
	BOOL bAppend;
	RSLT(Control->GetLogFile(buf, 512, &fSize, &bAppend));
	if (SOK())
	{
		lua.Push(buf);
		lua.pushinteger(fSize);
		lua.Push((bool)bAppend);
		return 3;
	}
	else
	{
		lua.Push(false);
		return 1;
	}
}

int LuaGetLogMask(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG mask;
	RSLT(Control->GetLogMask(&mask));
	SOK() ? lua.pushinteger(mask) : lua.Push(false);

	return 1;
}

int LuaGetNearInstruction(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG64 offset;
	LONG delta = lua.isnoneornil(3) ? 1 : (LONG)lua.checkintegerL(3);
	RSLT(Control->GetNearInstruction(lua.checkintegerL(2), delta, &offset));
	SOK() ? lua.pushinteger(offset) : lua.Push(false);

	return 1;
}

int LuaGetNotifyEventHandle(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG64 handle;
	RSLT(Control->GetNotifyEventHandle(&handle));
	SOK() ? lua.pushinteger(handle) : lua.Push(false);

	return 1;
}

int LuaGetNumberBreakpoints(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG n;
	RSLT(Control->GetNumberBreakpoints(&n));
	SOK() ? lua.pushinteger(n) : lua.Push(false);

	return 1;
}

int LuaGetNumberEventFilters(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG a,b,c;
	RSLT(Control->GetNumberEventFilters(&a, &b, &c));
	if (SOK())
	{
		lua.pushinteger(a);
		lua.pushinteger(b);
		lua.pushinteger(c);
		return 3;
	}
	else
	{
		lua.Push(false);
		return 1;
	}
}

int LuaGetNumberPossibleExecutingProcessorTypes(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG n;
	RSLT(Control->GetNumberPossibleExecutingProcessorTypes(&n));
	SOK() ? lua.pushinteger(n) : lua.Push(false);

	return 1;
}

int LuaGetNumberProcessors(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG n;
	RSLT(Control->GetNumberProcessors(&n));
	SOK() ? lua.pushinteger(n) : lua.Push(false);

	return 1;
}

int LuaGetNumberSupportedProcessorTypes(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG n;
	RSLT(Control->GetNumberSupportedProcessorTypes(&n));
	SOK() ? lua.pushinteger(n) : lua.Push(false);

	return 1;
}

int LuaGetPageSize(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG size;
	RSLT(Control->GetPageSize(&size));
	SOK() ? lua.pushinteger(size) : lua.Push(false);

	return 1;
}

int LuaGetPossibleExecutingProcessorTypes(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG start = lua.isnoneornil(2) ? 0 : lua.checkintegerL(2),
		count = lua.checkintegerL(3), types[1024];
	RSLT(Control->GetPossibleExecutingProcessorTypes(start, count, types));
	lua.newtable();
	for (int i = 0; i < count; i++)
	{
		lua.pushinteger(types[i]);
		lua.seti(-2, i+1);
	}
	SOK() ? NULL : lua.Push(false);

	return 1;
}

int LuaGetProcessorTypeNames(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	char name[1024], abbr[1024];
	ULONG fullSize, abbrSize;
	RSLT(Control->GetProcessorTypeNames(lua.checkintegerL(2), name, 1024, &fullSize, abbr, 1024, &abbrSize));
	if (SOK())
	{
		lua.Push(name);
		lua.Push(abbr);
		lua.pushinteger(fullSize);
		lua.pushinteger(abbrSize);
		return 4;
	}
	else
	{
		lua.Push(false);
		return 1;
	}
}

int LuaGetPromptText(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	char str[10240]; ULONG size;
	RSLT(Control->GetPromptText(str, 10240, &size));
	SOK() ? lua.pushlstring(str, size) : lua.Push(false);

	return 1;
}

int LuaGetRadix(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG radix;
	RSLT(Control->GetRadix(&radix));
	SOK() ? lua.pushinteger(radix) : lua.Push(false);

	return 1;
}

int LuaGetReturnOffset(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG64 offset;
	RSLT(Control->GetReturnOffset(&offset));
	SOK() ? lua.pushinteger(offset) : lua.Push(false);

	return 1;
}

int LuaGetSpecificFilterArgument(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	char str[10240]; ULONG size;
	RSLT(Control->GetSpecificFilterArgument(lua.checkintegerL(2), str, 10240, &size));
	SOK() ? lua.pushlstring(str, size) : lua.Push(false);

	return 1;
}

int LuaGetSpecificFilterParameters(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);


	return 1;
}

int LuaGetStackTrace(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG nFilled, nFrames = lua.checkintegerL(5);
	DEBUG_STACK_FRAME *pdsf = new DEBUG_STACK_FRAME[nFrames];
	RSLT(Control->GetStackTrace(lua.checkintegerL(2),
		lua.checkintegerL(3), lua.checkintegerL(4), pdsf, nFrames, &nFilled));
	SOK() ?
		(NewArrayTable(L, (LUA_STRUCT_FUNC)STACK_FRAME2Table, pdsf, nFilled, sizeof(DEBUG_STACK_FRAME)),
		lua.pushinteger(nFilled)) : lua.Push(false);

	delete[] pdsf;
	return 2;
}

int LuaGetSupportedProcessorTypes(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG start = lua.checkintegerL(2),
		count = lua.checkintegerL(3); 
	ULONG *p = new ULONG[count];
	RSLT(Control->GetSupportedProcessorTypes(start, count, p));
	if (SOK())
	{
		lua.newtable();
		for (int i = 0; i < count; i++)
		{
			lua.pushinteger(p[i]);
			lua.seti(-2, i);
		}
	}
	else
		lua.Push(false);

	delete[] p;
	return 1;
}

int LuaGetSystemErrorControl(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG OutLev, BpLev;
	RSLT(Control->GetSystemErrorControl(&OutLev, &BpLev));
	SOK() ? (lua.pushinteger(OutLev), lua.pushinteger(BpLev)) : lua.Push(false);

	return SOK()? 2 : 1;
}

int LuaGetSystemVersion(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG plId, Major, Minor, SerPakSize, BuildSize, nSerPak;
	char  SerPakStr[1024]; char  BuildStr[1024];
	RSLT(Control->GetSystemVersion(&plId, &Major, &Minor, SerPakStr, 1024, &SerPakSize, &nSerPak, BuildStr, 1024, &BuildSize));
	SOK() ? (lua.pushinteger(plId),
		lua.pushinteger(Major),
		lua.pushinteger(Minor),
		lua.pushlstring(SerPakStr, SerPakSize),
		lua.pushinteger(nSerPak),
		lua.pushlstring(BuildStr, BuildSize)) : lua.Push(false);

	return SOK() ? 6 : 1;
}

int LuaGetTextMacro(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	char str[1024]; ULONG size;
	RSLT(Control->GetTextMacro(lua.checkintegerL(2), str, 1024, &size));
	SOK() ? lua.pushlstring(str, size) : lua.Push(false);

	return 1;
}

int LuaGetWindbgExtensionApis32 (lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);


	return 1;
}

int LuaInput(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG size , len = lua.isnoneornil(2) ? 10240 : lua.checkintegerL(2);
	char *buf = (char *)malloc(len);
	RSLT(Control->Input(buf, len, &size));
	SOK() ? lua.pushlstring(buf, size) : lua.Push(false);
	free(buf);

	return 1;
}

int LuaIsPointer64Bit(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	RSLT(Control->IsPointer64Bit());
	lua.Push((bool)SOK());

	return 1;
}

int LuaOpenLogFile(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	PCSTR szFile = lua.checkstringL(2);
	bool  bAppend = lua.isnoneornil(3) ? false : lua.toboolean(3);
	RSLT(Control->OpenLogFile(szFile, bAppend));
	lua.Push((bool)SOK());

	return 0;
}

int LuaOutput(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);


	return 1;
}

int LuaOutputCurrentState(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG ctl = lua.isnoneornil(2) ? DEBUG_OUTCTL_THIS_CLIENT : lua.checkintegerL(2);
	ULONG flags = lua.isnoneornil(3) ? DEBUG_CURRENT_SYMBOL
		| DEBUG_CURRENT_DISASM | DEBUG_CURRENT_REGISTERS
		: lua.checkintegerL(3);
	bool  bAppend = lua.isnoneornil(3) ? false : lua.toboolean(3);
	RSLT(Control->OutputCurrentState(ctl, flags));
	lua.Push((bool)SOK());

	return 1;
}

int LuaOutputDisassembly(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG64 EndOffset;
	RSLT(Control->OutputDisassembly(lua.checkintegerL(2), lua.checkintegerL(3), lua.checkintegerL(4), &EndOffset));
	SOK() ? lua.pushinteger(EndOffset) : lua.Push(false);

	return 1;
}

int LuaOutputDisassemblyLines(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG   OffsetLine;
	ULONG64 StartOffset;
	ULONG64 EndOffset;
	ULONG64 LineOffsets;
	RSLT(Control->OutputDisassemblyLines
		(lua.checkintegerL(2), lua.checkintegerL(3), lua.checkintegerL(4),
		lua.checkintegerL(5),lua.checkintegerL(6),
		&OffsetLine, &StartOffset, &EndOffset, &LineOffsets));
	if (SOK())
	{
		lua.pushinteger(OffsetLine);
		lua.pushinteger(StartOffset);
		lua.pushinteger(EndOffset);
		lua.pushinteger(LineOffsets);
		return 4;
	}
	else
	{
		lua.Push(false);
		return 1;
	}
}

int LuaOutputPrompt(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);


	return 1;
}

int LuaOutputPromptVaList(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);


	return 1;
}

int LuaOutputStackTrace(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG OutCtrl = lua.checkintegerL(2),
		nFrames = lua.checkintegerL(4),
		Flags = lua.checkintegerL(5);
	DEBUG_STACK_FRAME *pdsf = new DEBUG_STACK_FRAME[nFrames];
	for (int i = 0; i < nFrames; i++)
	{
		lua.geti(3, i);
		Table2STACK_FRAME(L, &pdsf[i]);
		lua.pop(1);
	}
	RSLT(Control->OutputStackTrace(OutCtrl, pdsf, nFrames, Flags));
	lua.Push((bool)SOK());

	delete[] pdsf;
	return 1;
}

int LuaOutputVaList(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);


	return 1;
}

int LuaOutputVersionInformation(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG ctl = lua.isnoneornil(2) ? DEBUG_OUTCTL_THIS_CLIENT : lua.checkintegerL(2);
	RSLT(Control->OutputVersionInformation(ctl));
	SOK() ? lua.pushinteger(true) : lua.Push(false);

	return 1;
}

int LuaReadBugCheckData(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG Code;
	ULONG64 Arg1, Arg2, Arg3, Arg4;
	RSLT(Control->ReadBugCheckData(&Code, &Arg1, &Arg2, &Arg3, &Arg4));
	if (SOK())
	{
		lua.pushinteger(Code);
		lua.pushinteger(Arg1);
		lua.pushinteger(Arg2);
		lua.pushinteger(Arg3);
		lua.pushinteger(Arg4);
		return 5;
	}
	else
	{
		lua.Push(false);
		return 1;
	}
}

int LuaRemoveBreakpoint(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	RSLT(Control->RemoveBreakpoint((IDebugBreakpoint *)lua.CheckUserPointer(2, str::utLuaBreakpoint)));
	SOK() ? lua.pushinteger(true) : lua.Push(false);

	return 1;
}

int LuaRemoveEngineOptions(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	RSLT(Control->RemoveEngineOptions(lua.checkintegerL(2)));
	SOK() ? lua.pushinteger(true) : lua.Push(false);

	return 1;
}

int LuaRemoveExtension(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	RSLT(Control->RemoveExtension(lua.checkintegerL(2)));
	SOK() ? lua.pushinteger(true) : lua.Push(false);

	return 1;
}

int LuaReturnInput(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	RSLT(Control->ReturnInput(lua.checkstringL(2)));
	SOK() ? lua.pushinteger(true) : lua.Push(false);

	return 1;
}

int LuaSetCodeLevel(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	RSLT(Control->SetCodeLevel(lua.checkintegerL(2)));
	SOK() ? lua.pushinteger(true) : lua.Push(false);

	return 1;
}

int LuaSetEffectiveProcessorType(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	RSLT(Control->SetEffectiveProcessorType(lua.checkintegerL(2)));
	SOK() ? lua.pushinteger(true) : lua.Push(false);

	return 1;
}

int LuaSetEngineOptions(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	RSLT(Control->SetEngineOptions(lua.checkintegerL(2)));
	SOK() ? lua.pushinteger(true) : lua.Push(false);
	ULONG Options = lua.tointeger(2);
	RSLT(Control->SetEngineOptions(Options));
	lua.Push((bool)SOK());

	return 1;
}

int LuaSetEventFilterCommand(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	RSLT(Control->SetEventFilterCommand(lua.checkintegerL(2), lua.checkstringL(3)));
	SOK() ? lua.pushinteger(true) : lua.Push(false);

	return 1;
}

int LuaSetExceptionFilterParameters(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);


	return 1;
}

int LuaSetExceptionFilterSecondCommand(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);


	return 1;
}

int LuaSetExecutionStatus(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG status = lua.checkintegerL(2);
	RSLT(Control->SetExecutionStatus(status));
	lua.Push((bool)SOK());

	return 1;
}

int LuaSetInterrupt(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	RSLT(Control->SetInterrupt(DEBUG_INTERRUPT_ACTIVE));
	lua.Push((bool)SOK());

	return 1;
}

int LuaSetInterruptTimeout(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG t = lua.checkintegerL(2);
	RSLT(Control->SetInterruptTimeout(t));
	lua.Push((bool)SOK());

	return 1;
}

int LuaSetLogMask(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	RSLT(Control->SetLogMask(lua.checkintegerL(2)));
	lua.Push((bool)SOK());

	return 1;
}

int LuaSetNotifyEventHandle(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	RSLT(Control->SetNotifyEventHandle(lua.checkintegerL(2)));
	lua.Push((bool)SOK());

	return 1;
}

int LuaSetRadix(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	RSLT(Control->SetRadix(lua.checkintegerL(2)));
	lua.Push((bool)SOK());

	return 1;
}

int LuaSetSpecificFilterArgument(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	RSLT(Control->SetSpecificFilterArgument(lua.checkintegerL(2), lua.checkstringL(3)));
	lua.Push((bool)SOK());

	return 1;
}

int LuaSetSpecificFilterParameters(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);


	return 1;
}

int LuaSetSystemErrorControl(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	RSLT(Control->SetSystemErrorControl(lua.checkintegerL(2), lua.checkintegerL(3)));
	lua.Push((bool)SOK());

	return 1;
}

int LuaSetTextMacro(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	RSLT(Control->SetTextMacro(lua.checkintegerL(2), lua.checkstringL(3)));
	lua.Push((bool)SOK());

	return 1;
}

int LuaWaitForEvent(lua_State *L)
{
	LuaAPI lua(L);
	DbgControl *Control = (DbgControl *)lua.CheckUserPointer(1, str::utLuaDebugControl);

	ULONG Flags = lua.isnoneornil(2) ? 0 : lua.checkintegerL(2),
		Timeout = lua.isnoneornil(3) ? INFINITE : lua.checkintegerL(3);
	RSLT(Control->WaitForEvent(Flags, Timeout));
	lua.Push((bool)SOK());

	return 1;
}
