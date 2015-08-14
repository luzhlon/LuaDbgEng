#include "LuaDbgStruct.h"
#include "LuaAPI.h"
//#include "Windbgext.h"

void NewArrayTable(lua_State *L, LUA_STRUCT_FUNC func, void *p, int n, int cell)
{
	LuaAPI lua(L);
	lua.newtable();
	for (int i = 0; i < n; i++)
	{
		func(L, (void *)((char *)p+i*cell));
		lua.seti(-2, i);
	}
}

void BREAKPOINT_PARAMETERS2Table(lua_State *L, DEBUG_BREAKPOINT_PARAMETERS *st)
{
	LuaAPI lua(L);

	lua.newtable();
	lua.pushinteger(st->Offset);
	lua.setfield(-2, "Offset");
	lua.pushinteger(st->Id);
	lua.setfield(-2, "Id");
	lua.pushinteger(st->BreakType);
	lua.setfield(-2, "BreakType");
	lua.pushinteger(st->ProcType);
	lua.setfield(-2, "ProcType");
	lua.pushinteger(st->Flags);
	lua.setfield(-2, "Flags");
	lua.pushinteger(st->DataSize);
	lua.setfield(-2, "DataSize");
	lua.pushinteger(st->DataAccessType);
	lua.setfield(-2, "DataAccessType");
	lua.pushinteger(st->PassCount);
	lua.setfield(-2, "PassCount");
	lua.pushinteger(st->CurrentPassCount);
	lua.setfield(-2, "CurrentPassCount");
	lua.pushinteger(st->MatchThread);
	lua.setfield(-2, "MatchThread");
	lua.pushinteger(st->CommandSize);
	lua.setfield(-2, "CommandSize");
	lua.pushinteger(st->OffsetExpressionSize);
	lua.setfield(-2, "OffsetExpressionSize");
}

void Table2BREAKPOINT_PARAMETERS(lua_State *L, DEBUG_BREAKPOINT_PARAMETERS *st)
{
	LuaAPI lua(L);

	lua.Assert(lua.istable(1), "DEBUG_BREAKPOINT_PARAMETERS must be a table.");

	lua.getfield(-1, "Offset");
	st->Offset = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "Id");
	st->Id = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "BreakType");
	st->BreakType = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "ProcType");
	st->ProcType = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "Flags");
	st->Flags = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "DataSize");
	st->DataSize = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "DataAccessType");
	st->DataAccessType = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "PassCount");
	st->PassCount = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "CurrentPassCount");
	st->CurrentPassCount = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "MatchThread");
	st->MatchThread = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "CommandSize");
	st->CommandSize = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "OffsetExpressionSize");
	st->OffsetExpressionSize = lua.tointeger(-1); lua.pop(1);
}

void CREATE_PROCESS_OPTIONS2Table(lua_State *L, DEBUG_CREATE_PROCESS_OPTIONS *st)
{
	LuaAPI lua(L);

	lua.newtable();
	lua.pushinteger(st->CreateFlags);
	lua.setfield(-2, "CreateFlags");
	lua.pushinteger(st->EngCreateFlags);
	lua.setfield(-2, "EngCreateFlags");
	lua.pushinteger(st->VerifierFlags);
	lua.setfield(-2, "VerifierFlags");
	lua.pushinteger(st->Reserved);
	lua.setfield(-2, "Reserved");
}

void Table2CREATE_PROCESS_OPTIONS(lua_State *L, DEBUG_CREATE_PROCESS_OPTIONS *st)
{
	LuaAPI lua(L);

	lua.Assert(lua.istable(1), "DEBUG_CREATE_PROCESS_OPTIONS must be a table.");

	lua.getfield(-1, "CreateFlags");
	st->CreateFlags = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "EngCreateFlags");
	st->EngCreateFlags = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "VerifierFlags");
	st->VerifierFlags = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "Reserved");
	st->Reserved = lua.tointeger(-1); lua.pop(1);
}

void EXCEPTION_FILTER_PARAMETERS2Table(lua_State *L, DEBUG_EXCEPTION_FILTER_PARAMETERS *st)
{
	LuaAPI lua(L);

	lua.newtable();
	lua.pushinteger(st->ExecutionOption);
	lua.setfield(-2, "ExecutionOption");
	lua.pushinteger(st->ContinueOption);
	lua.setfield(-2, "ContinueOption");
	lua.pushinteger(st->TextSize);
	lua.setfield(-2, "TextSize");
	lua.pushinteger(st->CommandSize);
	lua.setfield(-2, "CommandSize");
	lua.pushinteger(st->SecondCommandSize);
	lua.setfield(-2, "SecondCommandSize");
	lua.pushinteger(st->ExceptionCode);
	lua.setfield(-2, "ExceptionCode");
}

void Table2EXCEPTION_FILTER_PARAMETERS(lua_State *L, DEBUG_EXCEPTION_FILTER_PARAMETERS *st)
{
	LuaAPI lua(L);

	lua.Assert(lua.istable(1), "DEBUG_EXCEPTION_FILTER_PARAMETERS must be a table.");

	lua.getfield(-1, "ExecutionOption");
	st->ExecutionOption = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "ContinueOption");
	st->ContinueOption = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "TextSize");
	st->TextSize = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "CommandSize");
	st->CommandSize = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "SecondCommandSize");
	st->SecondCommandSize = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "ExceptionCode");
	st->ExceptionCode = lua.tointeger(-1); lua.pop(1);
}

void HANDLE_DATA_BASIC2Table(lua_State *L, DEBUG_HANDLE_DATA_BASIC *st)
{
	LuaAPI lua(L);

	lua.newtable();
	lua.pushinteger(st->TypeNameSize);
	lua.setfield(-2, "TypeNameSize");
	lua.pushinteger(st->ObjectNameSize);
	lua.setfield(-2, "ObjectNameSize");
	lua.pushinteger(st->Attributes);
	lua.setfield(-2, "Attributes");
	lua.pushinteger(st->GrantedAccess);
	lua.setfield(-2, "GrantedAccess");
	lua.pushinteger(st->HandleCount);
	lua.setfield(-2, "HandleCount");
	lua.pushinteger(st->PointerCount);
	lua.setfield(-2, "PointerCount");
}

void Table2HANDLE_DATA_BASIC(lua_State *L, DEBUG_HANDLE_DATA_BASIC *st)
{
	LuaAPI lua(L);

	lua.Assert(lua.istable(1), "DEBUG_HANDLE_DATA_BASIC must be a table.");

	lua.getfield(-1, "TypeNameSize");
	st->TypeNameSize = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "ObjectNameSize");
	st->ObjectNameSize = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "Attributes");
	st->Attributes = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "GrantedAccess");
	st->GrantedAccess = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "HandleCount");
	st->HandleCount = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "PointerCount");
	st->PointerCount = lua.tointeger(-1); lua.pop(1);
}

void MODULE_AND_ID2Table(lua_State *L, DEBUG_MODULE_AND_ID *st)
{
	LuaAPI lua(L);

	lua.newtable();
	lua.pushinteger(st->ModuleBase);
	lua.setfield(-2, "ModuleBase");
	lua.pushinteger(st->Id);
	lua.setfield(-2, "Id");
}

void Table2MODULE_AND_ID(lua_State *L, DEBUG_MODULE_AND_ID *st)
{
	LuaAPI lua(L);

	lua.Assert(lua.istable(1), "DEBUG_MODULE_AND_ID must be a table.");

	lua.getfield(-1, "ModuleBase");
	st->ModuleBase = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "Id");
	st->Id = lua.tointeger(-1); lua.pop(1);
}

void MODULE_PARAMETERS2Table(lua_State *L, DEBUG_MODULE_PARAMETERS *st)
{
	LuaAPI lua(L);

	lua.newtable();
	lua.pushinteger(st->Base);
	lua.setfield(-2, "Base");
	lua.pushinteger(st->Size);
	lua.setfield(-2, "Size");
	lua.pushinteger(st->TimeDateStamp);
	lua.setfield(-2, "TimeDateStamp");
	lua.pushinteger(st->Checksum);
	lua.setfield(-2, "Checksum");
	lua.pushinteger(st->Flags);
	lua.setfield(-2, "Flags");
	lua.pushinteger(st->SymbolType);
	lua.setfield(-2, "SymbolType");
	lua.pushinteger(st->ImageNameSize);
	lua.setfield(-2, "ImageNameSize");
	lua.pushinteger(st->ModuleNameSize);
	lua.setfield(-2, "ModuleNameSize");
	lua.pushinteger(st->LoadedImageNameSize);
	lua.setfield(-2, "LoadedImageNameSize");
	lua.pushinteger(st->SymbolFileNameSize);
	lua.setfield(-2, "SymbolFileNameSize");
	lua.pushinteger(st->MappedImageNameSize);
	lua.setfield(-2, "MappedImageNameSize");
}

void Table2MODULE_PARAMETERS(lua_State *L, DEBUG_MODULE_PARAMETERS *st)
{
	LuaAPI lua(L);

	lua.Assert(lua.istable(1), "DEBUG_MODULE_PARAMETERS must be a table.");

	lua.getfield(-1, "Base");
	st->Base = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "Size");
	st->Size = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "TimeDateStamp");
	st->TimeDateStamp = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "Checksum");
	st->Checksum = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "Flags");
	st->Flags = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "SymbolType");
	st->SymbolType = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "ImageNameSize");
	st->ImageNameSize = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "ModuleNameSize");
	st->ModuleNameSize = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "LoadedImageNameSize");
	st->LoadedImageNameSize = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "SymbolFileNameSize");
	st->SymbolFileNameSize = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "MappedImageNameSize");
	st->MappedImageNameSize = lua.tointeger(-1); lua.pop(1);
}

void REGISTER_DESCRIPTION2Table(lua_State *L, DEBUG_REGISTER_DESCRIPTION *st)
{
	LuaAPI lua(L);

	lua.newtable();
	lua.pushinteger(st->Type);
	lua.setfield(-2, "Type");
	lua.pushinteger(st->Flags);
	lua.setfield(-2, "Flags");
	lua.pushinteger(st->SubregMaster);
	lua.setfield(-2, "SubregMaster");
	lua.pushinteger(st->SubregLength);
	lua.setfield(-2, "SubregLength");
	lua.pushinteger(st->SubregMask);
	lua.setfield(-2, "SubregMask");
	lua.pushinteger(st->SubregShift);
	lua.setfield(-2, "SubregShift");
	lua.pushinteger(st->Reserved0);
	lua.setfield(-2, "Reserved0");
}

void Table2REGISTER_DESCRIPTION(lua_State *L, DEBUG_REGISTER_DESCRIPTION *st)
{
	LuaAPI lua(L);

	lua.Assert(lua.istable(1), "DEBUG_REGISTER_DESCRIPTION must be a table.");

	lua.getfield(-1, "Type");
	st->Type = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "Flags");
	st->Flags = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "SubregMaster");
	st->SubregMaster = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "SubregLength");
	st->SubregLength = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "SubregMask");
	st->SubregMask = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "SubregShift");
	st->SubregShift = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "Reserved0");
	st->Reserved0 = lua.tointeger(-1); lua.pop(1);
}

void SPECIFIC_FILTER_PARAMETERS2Table(lua_State *L, DEBUG_SPECIFIC_FILTER_PARAMETERS *st)
{
	LuaAPI lua(L);

	lua.newtable();
	lua.pushinteger(st->ExecutionOption);
	lua.setfield(-2, "ExecutionOption");
	lua.pushinteger(st->ContinueOption);
	lua.setfield(-2, "ContinueOption");
	lua.pushinteger(st->TextSize);
	lua.setfield(-2, "TextSize");
	lua.pushinteger(st->CommandSize);
	lua.setfield(-2, "CommandSize");
	lua.pushinteger(st->ArgumentSize);
	lua.setfield(-2, "ArgumentSize");
}

void Table2SPECIFIC_FILTER_PARAMETERS(lua_State *L, DEBUG_SPECIFIC_FILTER_PARAMETERS *st)
{
	LuaAPI lua(L);

	lua.Assert(lua.istable(1), "DEBUG_SPECIFIC_FILTER_PARAMETERS must be a table.");

	lua.getfield(-1, "ExecutionOption");
	st->ExecutionOption = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "ContinueOption");
	st->ContinueOption = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "TextSize");
	st->TextSize = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "CommandSize");
	st->CommandSize = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "ArgumentSize");
	st->ArgumentSize = lua.tointeger(-1); lua.pop(1);
}

void STACK_FRAME2Table(lua_State *L, DEBUG_STACK_FRAME *st)
{
	LuaAPI lua(L);

	lua.newtable();
	lua.pushinteger(st->InstructionOffset);
	lua.setfield(-2, "InstructionOffset");
	lua.pushinteger(st->ReturnOffset);
	lua.setfield(-2, "ReturnOffset");
	lua.pushinteger(st->FrameOffset);
	lua.setfield(-2, "FrameOffset");
	lua.pushinteger(st->StackOffset);
	lua.setfield(-2, "StackOffset");
	lua.pushinteger(st->FuncTableEntry);
	lua.setfield(-2, "FuncTableEntry");
		lua.newtable();
		for (int i = 0; i < 4; i++)
		{
			lua.pushinteger(st->Params[i]);
			lua.seti(-2, i);
		}
		lua.setfield(-2, "Params");
		lua.newtable();
		for (int i = 0; i < 6; i++)
		{
			lua.pushinteger(st->Reserved[i]);
			lua.seti(-2, i);
		}
		lua.setfield(-2, "Reserved");
	lua.pushinteger(st->Virtual);
	lua.setfield(-2, "Virtual");
	lua.pushinteger(st->FrameNumber);
	lua.setfield(-2, "FrameNumber");
}

void Table2STACK_FRAME(lua_State *L, DEBUG_STACK_FRAME *st)
{
	LuaAPI lua(L);

	lua.Assert(lua.istable(1), "DEBUG_STACK_FRAME must be a table.");

	lua.getfield(-1, "InstructionOffset");
	st->InstructionOffset = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "ReturnOffset");
	st->ReturnOffset = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "FrameOffset");
	st->FrameOffset = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "StackOffset");
	st->StackOffset = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "FuncTableEntry");
	st->FuncTableEntry = lua.tointeger(-1); lua.pop(1);
		lua.getfield(-1, "Params");
		if (lua.istable(-1)) for (int i = 0; i < 4; i++)
		{
			lua.geti(-1, i);
			st->Params[i] = lua.tointeger(-1);
			lua.pop(1);
		} else lua.pop(1);
		lua.getfield(-1, "Reserved");
		if (lua.istable(-1)) for (int i = 0; i < 6; i++)
		{
			lua.geti(-1, i);
			st->Reserved[i] = lua.tointeger(-1);
			lua.pop(1);
		} else lua.pop(1);
	lua.getfield(-1, "Virtual");
	st->Virtual = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "FrameNumber");
	st->FrameNumber = lua.tointeger(-1); lua.pop(1);
}

void SYMBOL_ENTRY2Table(lua_State *L, DEBUG_SYMBOL_ENTRY *st)
{
	LuaAPI lua(L);

	lua.newtable();
	lua.pushinteger(st->ModuleBase);
	lua.setfield(-2, "ModuleBase");
	lua.pushinteger(st->Offset);
	lua.setfield(-2, "Offset");
	lua.pushinteger(st->Id);
	lua.setfield(-2, "Id");
	lua.pushinteger(st->Arg64);
	lua.setfield(-2, "Arg64");
	lua.pushinteger(st->Size);
	lua.setfield(-2, "Size");
	lua.pushinteger(st->Flags);
	lua.setfield(-2, "Flags");
	lua.pushinteger(st->TypeId);
	lua.setfield(-2, "TypeId");
	lua.pushinteger(st->NameSize);
	lua.setfield(-2, "NameSize");
	lua.pushinteger(st->Token);
	lua.setfield(-2, "Token");
	lua.pushinteger(st->Tag);
	lua.setfield(-2, "Tag");
	lua.pushinteger(st->Arg32);
	lua.setfield(-2, "Arg32");
	lua.pushinteger(st->Reserved);
	lua.setfield(-2, "Reserved");
}

void Table2SYMBOL_ENTRY(lua_State *L, DEBUG_SYMBOL_ENTRY *st)
{
	LuaAPI lua(L);

	lua.Assert(lua.istable(1), "DEBUG_SYMBOL_ENTRY must be a table.");

	lua.getfield(-1, "ModuleBase");
	st->ModuleBase = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "Offset");
	st->Offset = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "Id");
	st->Id = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "Arg64");
	st->Arg64 = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "Size");
	st->Size = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "Flags");
	st->Flags = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "TypeId");
	st->TypeId = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "NameSize");
	st->NameSize = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "Token");
	st->Token = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "Tag");
	st->Tag = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "Arg32");
	st->Arg32 = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "Reserved");
	st->Reserved = lua.tointeger(-1); lua.pop(1);
}

void SYMBOL_PARAMETERS2Table(lua_State *L, DEBUG_SYMBOL_PARAMETERS *st)
{
	LuaAPI lua(L);

	lua.newtable();
	lua.pushinteger(st->Module);
	lua.setfield(-2, "Module");
	lua.pushinteger(st->TypeId);
	lua.setfield(-2, "TypeId");
	lua.pushinteger(st->ParentSymbol);
	lua.setfield(-2, "ParentSymbol");
	lua.pushinteger(st->SubElements);
	lua.setfield(-2, "SubElements");
	lua.pushinteger(st->Flags);
	lua.setfield(-2, "Flags");
	lua.pushinteger(st->Reserved);
	lua.setfield(-2, "Reserved");
}

void Table2SYMBOL_PARAMETERS(lua_State *L, DEBUG_SYMBOL_PARAMETERS *st)
{
	LuaAPI lua(L);

	lua.Assert(lua.istable(1), "DEBUG_SYMBOL_PARAMETERS must be a table.");

	lua.getfield(-1, "Module");
	st->Module = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "TypeId");
	st->TypeId = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "ParentSymbol");
	st->ParentSymbol = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "SubElements");
	st->SubElements = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "Flags");
	st->Flags = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "Reserved");
	st->Reserved = lua.tointeger(-1); lua.pop(1);
}

void SYMBOL_SOURCE_ENTRY2Table(lua_State *L, DEBUG_SYMBOL_SOURCE_ENTRY *st)
{
	LuaAPI lua(L);

	lua.newtable();
	lua.pushinteger(st->ModuleBase);
	lua.setfield(-2, "ModuleBase");
	lua.pushinteger(st->Offset);
	lua.setfield(-2, "Offset");
	lua.pushinteger(st->FileNameId);
	lua.setfield(-2, "FileNameId");
	lua.pushinteger(st->EngineInternal);
	lua.setfield(-2, "EngineInternal");
	lua.pushinteger(st->Size);
	lua.setfield(-2, "Size");
	lua.pushinteger(st->Flags);
	lua.setfield(-2, "Flags");
	lua.pushinteger(st->FileNameSize);
	lua.setfield(-2, "FileNameSize");
	lua.pushinteger(st->StartLine);
	lua.setfield(-2, "StartLine");
	lua.pushinteger(st->EndLine);
	lua.setfield(-2, "EndLine");
	lua.pushinteger(st->StartColumn);
	lua.setfield(-2, "StartColumn");
	lua.pushinteger(st->EndColumn);
	lua.setfield(-2, "EndColumn");
	lua.pushinteger(st->Reserved);
	lua.setfield(-2, "Reserved");
}

void Table2SYMBOL_SOURCE_ENTRY(lua_State *L, DEBUG_SYMBOL_SOURCE_ENTRY *st)
{
	LuaAPI lua(L);

	lua.Assert(lua.istable(1), "DEBUG_SYMBOL_SOURCE_ENTRY must be a table.");

	lua.getfield(-1, "ModuleBase");
	st->ModuleBase = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "Offset");
	st->Offset = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "FileNameId");
	st->FileNameId = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "EngineInternal");
	st->EngineInternal = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "Size");
	st->Size = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "Flags");
	st->Flags = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "FileNameSize");
	st->FileNameSize = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "StartLine");
	st->StartLine = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "EndLine");
	st->EndLine = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "StartColumn");
	st->StartColumn = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "EndColumn");
	st->EndColumn = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "Reserved");
	st->Reserved = lua.tointeger(-1); lua.pop(1);
}

void THREAD_BASIC_INFORMATION2Table(lua_State *L, DEBUG_THREAD_BASIC_INFORMATION *st)
{
	LuaAPI lua(L);

	lua.newtable();
	lua.pushinteger(st->Valid);
	lua.setfield(-2, "Valid");
	lua.pushinteger(st->ExitStatus);
	lua.setfield(-2, "ExitStatus");
	lua.pushinteger(st->PriorityClass);
	lua.setfield(-2, "PriorityClass");
	lua.pushinteger(st->Priority);
	lua.setfield(-2, "Priority");
	lua.pushinteger(st->CreateTime);
	lua.setfield(-2, "CreateTime");
	lua.pushinteger(st->ExitTime);
	lua.setfield(-2, "ExitTime");
	lua.pushinteger(st->KernelTime);
	lua.setfield(-2, "KernelTime");
	lua.pushinteger(st->UserTime);
	lua.setfield(-2, "UserTime");
	lua.pushinteger(st->StartOffset);
	lua.setfield(-2, "StartOffset");
	lua.pushinteger(st->Affinity);
	lua.setfield(-2, "Affinity");
}

void Table2THREAD_BASIC_INFORMATION(lua_State *L, DEBUG_THREAD_BASIC_INFORMATION *st)
{
	LuaAPI lua(L);

	lua.Assert(lua.istable(1), "DEBUG_THREAD_BASIC_INFORMATION must be a table.");

	lua.getfield(-1, "Valid");
	st->Valid = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "ExitStatus");
	st->ExitStatus = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "PriorityClass");
	st->PriorityClass = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "Priority");
	st->Priority = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "CreateTime");
	st->CreateTime = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "ExitTime");
	st->ExitTime = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "KernelTime");
	st->KernelTime = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "UserTime");
	st->UserTime = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "StartOffset");
	st->StartOffset = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "Affinity");
	st->Affinity = lua.tointeger(-1); lua.pop(1);
}

/*
void TYPED_DATA2Table(lua_State *L, DEBUG_TYPED_DATA *st)
{
	LuaAPI lua(L);

	lua.newtable();
	lua.pushinteger(st->ModBase);
	lua.setfield(-2, "ModBase");
	lua.pushinteger(st->Offset);
	lua.setfield(-2, "Offset");
	lua.pushinteger(st->EngineHandle);
	lua.setfield(-2, "EngineHandle");
	lua.pushinteger(st->Data);
	lua.setfield(-2, "Data");
	lua.pushinteger(st->Size);
	lua.setfield(-2, "Size");
	lua.pushinteger(st->Flags);
	lua.setfield(-2, "Flags");
	lua.pushinteger(st->TypeId);
	lua.setfield(-2, "TypeId");
	lua.pushinteger(st->BaseTypeId);
	lua.setfield(-2, "BaseTypeId");
	lua.pushinteger(st->Tag);
	lua.setfield(-2, "Tag");
	lua.pushinteger(st->Register);
	lua.setfield(-2, "Register");
}

void Table2TYPED_DATA(lua_State *L, DEBUG_TYPED_DATA *st)
{
	LuaAPI lua(L);

	lua.getfield(-1, "ModBase");
	st->ModBase = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "Offset");
	st->Offset = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "EngineHandle");
	st->EngineHandle = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "Data");
	st->Data = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "Size");
	st->Size = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "Flags");
	st->Flags = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "TypeId");
	st->TypeId = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "BaseTypeId");
	st->BaseTypeId = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "Tag");
	st->Tag = lua.tointeger(-1); lua.pop(1);
	lua.getfield(-1, "Register");
	st->Register = lua.tointeger(-1); lua.pop(1);
}
//*/

void VALUE2Table(lua_State *L, DEBUG_VALUE *st)
{
	LuaAPI lua(L);

	lua.newtable();
	switch (st->Type)
	{
	case DEBUG_VALUE_INT8:
		lua.pushinteger(st->I8);
		lua.setfield(-2, "I8");
		break;
	case DEBUG_VALUE_INT16:
		lua.pushinteger(st->I16);
		lua.setfield(-2, "I16");
		break;
	case DEBUG_VALUE_INT32:
		lua.pushinteger(st->I32);
		lua.setfield(-2, "I32");
		break;
	case DEBUG_VALUE_INT64:
		lua.pushinteger(st->I64);
		lua.setfield(-2, "I64");
		break;
	case DEBUG_VALUE_FLOAT32:
		lua.pushnumber(st->F32);
		lua.setfield(-2, "F32");
		break;
	case DEBUG_VALUE_FLOAT64:
		lua.pushnumber(st->F64);
		lua.setfield(-2, "F64");
		break;
	case DEBUG_VALUE_FLOAT80:
		lua.newtable();
		for (int i = 0; i < 80; i++)
		{
			lua.pushnumber(st->F80Bytes[i]);
			lua.seti(-2, i);
		}
		lua.setfield(-2, "F80Bytes");
		break;
	case DEBUG_VALUE_FLOAT128:
		lua.newtable();
		for (int i = 0; i < 128; i++)
		{
			lua.pushnumber(st->F128Bytes[i]);
			lua.seti(-2, i);
		}
		lua.setfield(-2, "F128Bytes");
		break;
	case DEBUG_VALUE_VECTOR64:
		break;
	case DEBUG_VALUE_VECTOR128:
		break;

	}
}

void Table2VALUE(lua_State *L, DEBUG_VALUE *st)
{
	LuaAPI lua(L);

	lua.Assert(lua.istable(-1), "DEBUG_VALUE must be a table.");

	switch (st->Type)
	{
	case DEBUG_VALUE_INT8:
		lua.getfield(-1, "I8");
		st->I8 = lua.tointeger(-1);
		lua.pop(1);
		break;
	case DEBUG_VALUE_INT16:
		lua.getfield(-1, "I16");
		st->I16 = lua.tointeger(-1);
		lua.pop(1);
		break;
	case DEBUG_VALUE_INT32:
		lua.getfield(-1, "I32");
		st->I32 = lua.tointeger(-1);
		lua.pop(1);
		break;
	case DEBUG_VALUE_INT64:
		lua.getfield(-1, "I64");
		st->I64 = lua.tointeger(-1);
		lua.pop(1);
		break;
	case DEBUG_VALUE_FLOAT32:
		lua.getfield(-1, "F32");
		st->F32 = lua.tonumber(-1);
		lua.pop(1);
		break;
	case DEBUG_VALUE_FLOAT64:
		lua.getfield(-1, "F64");
		st->F64 = lua.tonumber(-1);
		lua.pop(1);
		break;
	case DEBUG_VALUE_FLOAT80:
		lua.getfield(-1, "F80Bytes");
		lua.Assert(lua.istable(-1), "Invalid field 'F80Bytes': Not a table.");
		for (int i = 0; i < 80; i++)
		{
			lua.geti(-1, i);
			st->F80Bytes[i] = lua.tointeger(-1);
			lua.pop(1);
		}
		break;
	case DEBUG_VALUE_FLOAT128:
		lua.getfield(-1, "F128Bytes");
		lua.Assert(lua.istable(-1), "Invalid field 'F128Bytes': Not a table.");
		for (int i = 0; i < 128; i++)
		{
			lua.geti(-1, i);
			st->F128Bytes[i] = lua.tointeger(-1);
			lua.pop(1);
		}
		break;
	case DEBUG_VALUE_VECTOR64:
		break;
	case DEBUG_VALUE_VECTOR128:
		break;

	}
}

