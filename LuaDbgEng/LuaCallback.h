#ifndef __LUACALLBACK_H_
#define __LUACALLBACK_H_

#include "dbgeng.h"
class LuaAPI;
class LuaCallback;

class LuaEventCallback : public IDebugEventCallbacks
{
public:
	LuaEventCallback(LuaAPI *lua);
	~LuaEventCallback();
	virtual ULONG _stdcall AddRef() { return 0; }
	virtual ULONG _stdcall Release() { return 1; }
	virtual HRESULT _stdcall QueryInterface(REFIID id, void **ppvObj)
	{
		*ppvObj = this;
		return NOERROR;
	}

	virtual HRESULT _stdcall GetInterestMask(PULONG Mask);
	
	virtual HRESULT _stdcall Breakpoint(IDebugBreakpoint *bp);
	
	virtual HRESULT _stdcall ChangeDebuggeeState(ULONG Flags, ULONG64 Argument);
	
	virtual HRESULT _stdcall ChangeEngineState(ULONG Flags, ULONG64 Argument);
	
	virtual HRESULT _stdcall Exception(PEXCEPTION_RECORD64 Exception, ULONG FirstChance);
	
	virtual HRESULT _stdcall UnloadModule(PCSTR ImageBaseName, ULONG64 BaseOffset);
	
	virtual HRESULT _stdcall ExitProcess(ULONG ExitCode);
	
	virtual HRESULT _stdcall SessionStatus(ULONG Status);
	
	virtual HRESULT _stdcall ChangeSymbolState(ULONG Flags, ULONG64 Argument);
	
	virtual HRESULT _stdcall SystemError(ULONG Error, ULONG Level);
	
	virtual HRESULT _stdcall CreateThread(ULONG64 Handle, ULONG64 DataOffset, ULONG64 StartOffset);
	
	virtual HRESULT _stdcall ExitThread(ULONG ExitCode);
	
	virtual HRESULT _stdcall LoadModule(
		IN ULONG64  ImageFileHandle,
		IN ULONG64  BaseOffset,
		IN ULONG  ModuleSize,
		IN PCSTR  ModuleName,
		IN PCSTR  ImageName,
		IN ULONG  CheckSum,
		IN ULONG  TimeDateStamp);

	virtual HRESULT _stdcall CreateProcess(
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
		IN ULONG64  StartOffset );

private:
	LuaCallback *m_lua;

	int     InitCallback(const char *);
	HRESULT BeginCallback();
};

class LuaInputCallback : public IDebugInputCallbacks
{
public:
	LuaInputCallback(LuaAPI *lua);
	~LuaInputCallback();

	virtual ULONG _stdcall AddRef() { return 0; }
	virtual ULONG _stdcall Release() { return 1; }
	virtual HRESULT _stdcall QueryInterface(REFIID id, void **ppvObj)
	{
		*ppvObj = this;
		return NOERROR;
	}

	virtual HRESULT _stdcall StartInput(IN ULONG BuffSize);
	virtual HRESULT _stdcall EndInput();

private:
	LuaCallback *m_lua;
};

class LuaOutputCallback : public IDebugOutputCallbacks
{
public:
	LuaOutputCallback(LuaAPI *lua);
	~LuaOutputCallback();

	virtual ULONG _stdcall AddRef() { return 0; }
	virtual ULONG _stdcall Release() { return 1; }
	virtual HRESULT _stdcall QueryInterface(REFIID id, void **ppvObj)
	{
		*ppvObj = NULL;

		if (IsEqualIID(id, __uuidof(IUnknown)) ||
			IsEqualIID(id, __uuidof(IDebugOutputCallbacks)))
		{
			*ppvObj = (IDebugOutputCallbacks *)this;
			AddRef();
			return S_OK;
		}
		else
		{
			return E_NOINTERFACE;
		}
	}

	virtual HRESULT _stdcall Output(IN ULONG Mask, IN PCSTR Text);
	
private:
	LuaCallback *m_lua;
};

#endif
