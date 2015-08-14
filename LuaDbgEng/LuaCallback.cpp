#include "LuaCallback.h"
#include "LuaBreakpoint.h"
#include "LuaAPI.h"
#include "str.h"

LuaEventCallback::LuaEventCallback(LuaAPI *lua)
{
	lua->checktypeL(1, LUA_TTABLE);
	m_lua = lua->NewCallback(1);
	lua->NewUserPointer(this, str::utLuaEventCallback);
}

LuaEventCallback::~LuaEventCallback()
{
	delete m_lua;
}

HRESULT LuaInputCallback::StartInput(IN ULONG BuffSize)
{
	if (!m_lua->InitCallback()) return 0;
	m_lua->pushvalue(1);
	m_lua->Push(true);
	m_lua->pushinteger(BuffSize);
	m_lua->BeginCallback(0, 0);
	return 0;
}

HRESULT LuaInputCallback::EndInput()
{
	if (!m_lua->InitCallback()) return 0;
	m_lua->pushvalue(1);
	m_lua->Push(false);
	m_lua->BeginCallback(0, 0);
	return 0;
}

HRESULT LuaOutputCallback::Output(IN ULONG Mask, IN PCSTR Text)
{
	const char *type;

	switch (Mask)
	{
	case DEBUG_OUTPUT_NORMAL:
		type = "NORMAL";
		break;
	case DEBUG_OUTPUT_ERROR:
		type = "ERROR";
		break;
	case DEBUG_OUTPUT_WARNING:
		type = "WARNING";
		break;
	case DEBUG_OUTPUT_VERBOSE:
		type = "VERBOSE";
		break;
	case DEBUG_OUTPUT_PROMPT:
		type = "PROMPT";
		break;
	case DEBUG_OUTPUT_PROMPT_REGISTERS:
		type = "PROMPT_REGISTERS";
		break;
	case DEBUG_OUTPUT_DEBUGGEE:
		type = "DEBUGGEE";
		break;
	case DEBUG_OUTPUT_SYMBOLS:
		type = "SYMBOLS";
		break;
	case DEBUG_OUTPUT_EXTENSION_WARNING:
		type = "EXTENSION_WARNING";
		break;
	case DEBUG_OUTPUT_DEBUGGEE_PROMPT:
		type = "DEBUGGEE_PROMPT";
		break;
	}
	if (!m_lua->InitCallback()) return 0;
	m_lua->Push(type);
	m_lua->Push(Text);
	if( !m_lua->BeginCallback(0))
		printf("[ERROR:Output] %s", m_lua->tostring(-1));
	return 0;
}

HRESULT LuaEventCallback::GetInterestMask(PULONG Mask)
{
	*Mask |= DEBUG_EVENT_BREAKPOINT;
	*Mask |= DEBUG_EVENT_EXCEPTION;
	*Mask |= DEBUG_EVENT_CREATE_THREAD;
	*Mask |= DEBUG_EVENT_EXIT_THREAD;
	*Mask |= DEBUG_EVENT_CREATE_PROCESS;
	*Mask |= DEBUG_EVENT_EXIT_PROCESS;
	*Mask |= DEBUG_EVENT_LOAD_MODULE;
	*Mask |= DEBUG_EVENT_UNLOAD_MODULE;
	*Mask |= DEBUG_EVENT_SYSTEM_ERROR;
	*Mask |= DEBUG_EVENT_SESSION_STATUS;
	*Mask |= DEBUG_EVENT_CHANGE_DEBUGGEE_STATE;
	*Mask |= DEBUG_EVENT_CHANGE_ENGINE_STATE;
	*Mask |= DEBUG_EVENT_CHANGE_SYMBOL_STATE;

	return S_OK;
}

int LuaEventCallback::InitCallback(const char *s)
{
	return m_lua->InitCallback(s);
}

HRESULT LuaEventCallback::BeginCallback()
{
	if (!m_lua->BeginCallback(1))
	{
		printf("[ERROR:]\n\t", m_lua->tostring(-1));
		return DEBUG_STATUS_NO_CHANGE;
	}
	return m_lua->tointeger(-1);
}

HRESULT LuaEventCallback::Breakpoint(IDebugBreakpoint *bp)
{
	InitCallback("Breakpoint");
	NewLuaBreakpoint(m_lua->GetState(), bp);
	return BeginCallback();
}

HRESULT LuaEventCallback::ChangeDebuggeeState(ULONG Flags, ULONG64 Argument)
{
	InitCallback("ChangeDebuggeeState");
	m_lua->pushinteger(Flags);
	m_lua->pushinteger(Argument);
	return BeginCallback();
}

HRESULT LuaEventCallback::ChangeEngineState(ULONG Flags, ULONG64 Argument)
{
	InitCallback("ChangeEngineState");
	m_lua->pushinteger(Flags);
	m_lua->Push(Argument);
	return BeginCallback();
}

HRESULT LuaEventCallback::Exception(PEXCEPTION_RECORD64 Exception, ULONG FirstChance)
{
	if(!InitCallback("Exception")) return DEBUG_STATUS_NO_CHANGE;

	m_lua->newtable();
	m_lua->pushinteger(Exception->ExceptionCode);
	m_lua->setfield(-2, "ExceptionCode");
	m_lua->pushinteger(Exception->ExceptionFlags);
	m_lua->setfield(-2, "ExceptionFlags");
	m_lua->pushinteger(Exception->ExceptionRecord);
	m_lua->setfield(-2, "ExceptionRecord");
	m_lua->pushinteger(Exception->ExceptionAddress);
	m_lua->setfield(-2, "ExceptionAddress");
	m_lua->pushinteger(Exception->NumberParameters);
	m_lua->setfield(-2, "NumberParameters");
	m_lua->newtable();
	for (int i = 0; i < EXCEPTION_MAXIMUM_PARAMETERS; i++)
	{
		m_lua->pushinteger(Exception->ExceptionInformation[i]);
		m_lua->seti(-2, i);
	}
	m_lua->setfield(-2, "ExceptionInformation");

	m_lua->pushboolean(FirstChance);

	return BeginCallback();
}

HRESULT LuaEventCallback::UnloadModule(PCSTR ImageBaseName, ULONG64 BaseOffset)
{
	InitCallback("UnloadModule");
	m_lua->Push(ImageBaseName);
	m_lua->Push((lua_Integer)BaseOffset);
	return BeginCallback();
}

HRESULT LuaEventCallback::ExitProcess(ULONG ExitCode)
{
	InitCallback("ExitProcess");
	m_lua->Push((lua_Integer)ExitCode);
	return BeginCallback();
}

HRESULT LuaEventCallback::SessionStatus(ULONG Status)
{
	InitCallback("SessionStatus");
	m_lua->Push((lua_Integer)Status);
	return BeginCallback();
}

HRESULT LuaEventCallback::ChangeSymbolState(ULONG Flags, ULONG64 Argument)
{
	InitCallback("ChangeSymbolState");
	m_lua->pushinteger(Flags);
	m_lua->pushinteger(Argument);
	return BeginCallback();
}

HRESULT LuaEventCallback::SystemError(ULONG Error, ULONG Level)
{
	InitCallback("SystemError");
	m_lua->pushinteger(Error);
	m_lua->pushinteger(Level);
	return BeginCallback();
}

HRESULT LuaEventCallback::CreateThread(ULONG64 Handle, ULONG64 DataOffset, ULONG64 StartOffset)
{
	InitCallback("CreateThread");
	m_lua->Push((lua_Integer)Handle);
	m_lua->Push((lua_Integer)DataOffset);
	m_lua->Push((lua_Integer)StartOffset);
	return BeginCallback();
}

HRESULT LuaEventCallback::ExitThread(ULONG ExitCode)
{
	InitCallback("ExitThread");
	m_lua->Push((lua_Integer)ExitCode);
	return BeginCallback();
}

HRESULT LuaEventCallback::LoadModule(
	IN ULONG64  ImageFileHandle,
	IN ULONG64  BaseOffset,
	IN ULONG  ModuleSize,
	IN PCSTR  ModuleName,
	IN PCSTR  ImageName,
	IN ULONG  CheckSum,
	IN ULONG  TimeDateStamp)
{
	if(!InitCallback("LoadModule")) return DEBUG_STATUS_NO_CHANGE;

	m_lua->Push((lua_Integer)ImageFileHandle);
	m_lua->Push((lua_Integer)BaseOffset);
	m_lua->Push((lua_Integer)ModuleSize);
	m_lua->Push((lua_Integer)CheckSum);
	m_lua->Push((lua_Integer)TimeDateStamp);
	m_lua->Push(ModuleName);
	m_lua->Push(ImageName);

	return BeginCallback();
}

HRESULT LuaEventCallback::CreateProcess(
		IN ULONG64  ImageFileHandle,
		IN ULONG64  Handle,
		IN ULONG64  BaseOffset,
		IN ULONG  ModuleSize,
		IN PCSTR  ModuleName,
		IN PCSTR  ImageName,
		IN ULONG  CheckSum,
		IN ULONG  TimeDataStamp,
		IN ULONG64  InitialThreadHandle,
		IN ULONG64  ThreadDataOffset,
		IN ULONG64  StartOffset )
{
	if(!InitCallback("CreateProcess")) return DEBUG_STATUS_NO_CHANGE;

	m_lua->Push((lua_Integer)ImageFileHandle);
	m_lua->Push((lua_Integer)Handle);
	m_lua->Push((lua_Integer)BaseOffset);
	m_lua->Push((lua_Integer)ModuleSize);
	m_lua->Push(ModuleName);
	m_lua->Push(ImageName);
	m_lua->Push((lua_Integer)CheckSum);
	m_lua->Push((lua_Integer)TimeDataStamp);
	m_lua->Push((lua_Integer)InitialThreadHandle);
	m_lua->Push((lua_Integer)ThreadDataOffset);
	m_lua->Push((lua_Integer)StartOffset);

	return BeginCallback();
}

LuaOutputCallback::LuaOutputCallback(LuaAPI *lua)
{
	lua->checktypeL(1, LUA_TFUNCTION);
	m_lua = lua->NewCallback(1);
	lua->NewUserPointer(this, str::utLuaOutputCallback);
}

LuaOutputCallback::~LuaOutputCallback()
{
	delete m_lua;
}

LuaInputCallback::LuaInputCallback(LuaAPI *lua)
{
	lua->checktypeL(1, LUA_TFUNCTION);
	m_lua = lua->NewCallback(1);
	lua->NewUserPointer(this, str::utLuaInputCallback);
}

LuaInputCallback::~LuaInputCallback()
{
	delete m_lua;
}
