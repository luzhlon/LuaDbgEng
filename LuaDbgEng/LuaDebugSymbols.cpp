#include "str.h"
#include "LuaDbgEng.h"
#include "LuaDbgStruct.h"
#include "LuaSymbolGroup.h"
#include "LuaDebugSymbols.h"

luaL_Reg LuaDebugSymbolsLib[] = 
{
	{ "AddSymbolOptions", LuaAddSymbolOptions },
	{ "AppendImagePath", LuaAppendImagePath },
	{ "AppendSourcePath", LuaAppendSourcePath },
	{ "AppendSymbolPath", LuaAppendSymbolPath },
	{ "CreateSymbolGroup", LuaCreateSymbolGroup },
	{ "EndSymbolMatch", LuaEndSymbolMatch },
	{ "FindSourceFile", LuaFindSourceFile },
	{ "GetFieldOffset", LuaGetFieldOffset },
	{ "GetImagePath", LuaGetImagePath },
	{ "GetLineByOffset", LuaGetLineByOffset },
	{ "GetModuleByIndex", LuaGetModuleByIndex },
	{ "GetModuleByModuleName", LuaGetModuleByModuleName },
	{ "GetModuleByOffset", LuaGetModuleByOffset },
	{ "GetModuleNames", LuaGetModuleNames },
	{ "GetModuleParameters", LuaGetModuleParameters },
	{ "GetNameByOffset", LuaGetNameByOffset },
	{ "GetNearNameByOffset", LuaGetNearNameByOffset },
	{ "GetNextSymbolMatch", LuaGetNextSymbolMatch },
	{ "GetNumberModules", LuaGetNumberModules },
	{ "GetOffsetByLine", LuaGetOffsetByLine },
	{ "GetOffsetByName", LuaGetOffsetByName },
	{ "GetOffsetTypeId", LuaGetOffsetTypeId },
	{ "GetScope", LuaGetScope },
	{ "GetScopeSymbolGroup", LuaGetScopeSymbolGroup },
	{ "GetSourceFileLineOffsets", LuaGetSourceFileLineOffsets },
	{ "GetSourcePath", LuaGetSourcePath },
	{ "GetSourcePathElement", LuaGetSourcePathElement },
	{ "GetSymbolModule", LuaGetSymbolModule },
	{ "GetSymbolOptions", LuaGetSymbolOptions },
	{ "GetSymbolPath", LuaGetSymbolPath },
	{ "GetSymbolTypeId", LuaGetSymbolTypeId },
	{ "GetTypeId", LuaGetTypeId },
	{ "GetTypeName", LuaGetTypeName },
	{ "GetTypeSize", LuaGetTypeSize },
	{ "OutputTypedDataPhysical", LuaOutputTypedDataPhysical },
	{ "OutputTypedDataVirtual", LuaOutputTypedDataVirtual },
	{ "ReadTypedDataPhysical", LuaReadTypedDataPhysical },
	{ "ReadTypedDataVirtual", LuaReadTypedDataVirtual },
	{ "Reload", LuaReload },
	{ "RemoveSymbolOptions", LuaRemoveSymbolOptions },
	{ "ResetScope", LuaResetScope },
	{ "SetImagePath", LuaSetImagePath },
	{ "SetScope", LuaSetScope },
	{ "SetSourcePath", LuaSetSourcePath },
	{ "SetSymbolOptions", LuaSetSymbolOptions },
	{ "SetSymbolPath", LuaSetSymbolPath },
	{ "StartSymbolMatch", LuaStartSymbolMatch },
	{ "WriteTypedDataPhysical", LuaWriteTypedDataPhysical },
	{ "WriteTypedDataVirtual", LuaWriteTypedDataVirtual },
	{ 0, 0 }
};

int LuaGetMatchSymbols(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	ULONG64 handle, offset;
	ULONG   matchsize;
	char    buf[1024];
	int     i = 0;
	PCSTR   symbol = lua.checkstringL(2);
	for (Sym->StartSymbolMatch(symbol, &handle), lua.newtable();
		Sym->GetNextSymbolMatch(handle, buf, 1024, &matchsize, &offset); i++)
	{
		lua.Push(offset);
		buf[matchsize] = 0;
		lua.setfield(-2, buf);
	}
	Sym->EndSymbolMatch(handle);
	if (!i) lua.Push(false);

	return 1;
}

int LuaAddSymbolOptions(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	RSLT(Sym->AddSymbolOptions(lua.checkintegerL(2)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaAppendImagePath(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	RSLT(Sym->AppendImagePath(lua.checkstringL(2)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaAppendSourcePath(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	RSLT(Sym->AppendSourcePath(lua.checkstringL(2)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaAppendSymbolPath(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	RSLT(Sym->AppendSymbolPath(lua.checkstringL(2)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaCreateSymbolGroup(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	DbgSymbolGroup *group;
	RSLT(Sym->CreateSymbolGroup((PDEBUG_SYMBOL_GROUP *)&group));
	SOK() ? NewLuaSymbolGroup(L, group) : lua.Push(false);

	return 1;
}

int LuaEndSymbolMatch(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	RSLT(Sym->EndSymbolMatch(lua.checkintegerL(2)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaFindSourceFile(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	char str[10240];
	ULONG u, size;
	RSLT(Sym->FindSourceFile(lua.checkintegerL(2),
							lua.checkstringL(3),
							lua.checkintegerL(4),
							&u, str, 10240, &size));
	SOK() ? (lua.pushinteger(u),lua.pushlstring(str, size))
			: lua.Push(false);

	return SOK() ? 2 : 1;
}

int LuaGetFieldOffset(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	ULONG offset;
	RSLT(Sym->GetFieldOffset(lua.checkintegerL(2), lua.checkintegerL(3), lua.checkstringL(4), &offset));
	SOK() ? lua.pushinteger(offset) : lua.Push(false);

	return 1;
}

int LuaGetImagePath(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	char str[1024];
	ULONG size;
	RSLT(Sym->GetImagePath(str, 1024, &size));
	SOK() ? lua.pushlstring(str, size) : lua.Push(false);

	return 1;
}

int LuaGetLineByOffset(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	char str[1024];
	ULONG line, size;
	ULONG64 disp;
	RSLT(Sym->GetLineByOffset(lua.checkintegerL(2), &line, str, 1024, &size, &disp));
	SOK() ? (lua.pushinteger(line), lua.pushlstring(str, size), lua.pushinteger(disp)) :
		lua.Push(false);

	return SOK() ? 3 : 1;
}

int LuaGetModuleByIndex(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	ULONG64 moud;
	RSLT(Sym->GetModuleByIndex(lua.checkintegerL(2), &moud));
	SOK() ? lua.pushinteger(moud) : lua.Push(false);

	return 1;
}

int LuaGetModuleByModuleName(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	ULONG i;
	ULONG64 moud;
	RSLT(Sym->GetModuleByModuleName(lua.checkstringL(2), lua.checkintegerL(3), &i, &moud));
	SOK() ? (lua.pushinteger(i), lua.pushinteger(moud)) : lua.Push(false);

	return SOK() ? 2 : 1;
}

int LuaGetModuleByOffset(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	ULONG i;
	ULONG64 moud;
	RSLT(Sym->GetModuleByOffset(lua.checkintegerL(2), lua.checkintegerL(3), &i, &moud));
	SOK() ? (lua.pushinteger(i), lua.pushinteger(moud)) : lua.Push(false);

	return SOK() ? 2 : 1;
}

int LuaGetModuleNames(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	char istr[1024], mstr[1024], lstr[1024];
	ULONG ilen, mlen, llen;
	RSLT(Sym->GetModuleNames(lua.checkintegerL(2), lua.checkintegerL(3),
		istr, 1024, &ilen, mstr, 1024, &mlen, lstr, 1024, &llen));
	SOK() ? (lua.pushlstring(istr, ilen),
			lua.pushlstring(mstr, mlen),
			lua.pushlstring(lstr, llen)) : lua.Push(false);

	return SOK() ? 3 : 1;
}

int LuaGetModuleParameters(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);


	return 1;
}

int LuaGetNameByOffset(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	char buf[10240];
	ULONG size;
	ULONG64 disp;
	RSLT(Sym->GetNameByOffset(lua.checkintegerL(2), buf, 10240, &size, &disp));
	SOK() ? (lua.pushlstring(buf, size),
		     lua.pushinteger(disp)) : lua.Push(false);

	return 2;
}

int LuaGetNearNameByOffset(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	char buf[10240];
	ULONG size;
	ULONG64 disp;
	RSLT(Sym->GetNearNameByOffset(lua.checkintegerL(2), lua.toboolean(3), buf, 10240, &size, &disp));
	SOK() ? (lua.pushlstring(buf, size),
		     lua.pushinteger(disp)) : lua.Push(false);

	return 2;
}

int LuaGetNextSymbolMatch(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	char buf[10240];
	ULONG matchSize;
	ULONG64 offset;
	RSLT(Sym->GetNextSymbolMatch(lua.checkintegerL(2), buf, 10240, &matchSize, &offset));
	SOK() ? (lua.pushlstring(buf, matchSize),
		     lua.pushinteger(offset)) : lua.Push(false);

	return 2;
}

int LuaGetNumberModules(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	ULONG loaded, unloaded;
	RSLT(Sym->GetNumberModules(&loaded, &unloaded));
	SOK() ? (lua.pushinteger(loaded),
		lua.pushinteger(unloaded)) : lua.Push(false);

	return 2;
}

int LuaGetOffsetByLine(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	ULONG64 offset;
	RSLT(Sym->GetOffsetByLine(lua.checkintegerL(2), lua.checkstringL(3), &offset));
	SOK() ? lua.pushinteger(offset) : lua.Push(false);

	return 1;
}

int LuaGetOffsetByName(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	ULONG64 offset;
	PCSTR   symbol = lua.checkstringL(2);
	RSLT(Sym->GetOffsetByName(symbol, &offset));
	SOK() ? lua.pushinteger(offset) : lua.Push(false);

	return 1;
}

int LuaGetOffsetTypeId(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	ULONG id;
	ULONG64 module;
	RSLT(Sym->GetOffsetTypeId(lua.checkintegerL(2), &id, &module));
	SOK() ? (lua.pushinteger(id),
		lua.pushinteger(module)) : lua.Push(false);

	return 2;
}

int LuaGetScope(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	ULONG64 InstrOffset;
	DEBUG_STACK_FRAME dsf;
	ULONG   nConts = lua.checkintegerL(2);
	RSLT(Sym->GetScope(&InstrOffset, &dsf, NULL, nConts));
	SOK() ? (lua.pushinteger(InstrOffset),
		STACK_FRAME2Table(L, &dsf)) : lua.Push(false);

	return 2;
}

int LuaGetScopeSymbolGroup(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	DbgSymbolGroup *dsg;
	RSLT(Sym->GetScopeSymbolGroup(lua.checkintegerL(2), (IDebugSymbolGroup *)
		(lua.isnoneornil(3) ? NULL : lua.CheckUserPointer(3, str::utLuaSymbolGroup)),
		(PDEBUG_SYMBOL_GROUP *)&dsg));
	SOK() ? NewLuaSymbolGroup(L, dsg) : lua.Push(false);

	return 1;
}

int LuaGetSourceFileLineOffsets(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	ULONG64 Buf;
	ULONG   lines;
	RSLT(Sym->GetSourceFileLineOffsets(lua.checkstringL(2), &Buf, lua.checkintegerL(3), &lines));
	SOK() ? (lua.pushinteger(Buf),
		lua.pushinteger(lines)) : lua.Push(false);

	return 2;
}

int LuaGetSourcePath(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	char buf[10240];
	ULONG size;
	RSLT(Sym->GetSourcePath(buf, 10240, &size));
	SOK() ? lua.pushlstring(buf, size) : lua.Push(false);

	return 1;
}

int LuaGetSourcePathElement(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	char buf[10240];
	ULONG size;
	RSLT(Sym->GetSourcePathElement(lua.checkintegerL(2), buf, 10240, &size));
	SOK() ? lua.pushlstring(buf, size) : lua.Push(false);

	return 1;
}

int LuaGetSymbolModule(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	ULONG64 module;
	RSLT(Sym->GetSymbolModule(lua.checkstringL(2), &module));
	SOK() ? lua.pushinteger(module) : lua.Push(false);

	return 1;
}

int LuaGetSymbolOptions(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	ULONG opt;
	RSLT(Sym->GetSymbolOptions(&opt));
	SOK() ? lua.pushinteger(opt) : lua.Push(false);

	return 1;
}

int LuaGetSymbolPath(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	char buf[10240];
	ULONG size;
	RSLT(Sym->GetSymbolPath(buf, 10240, &size));
	SOK() ? lua.pushlstring(buf, size) : lua.Push(false);

	return 1;
}

int LuaGetSymbolTypeId(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	ULONG typeId;
	ULONG64 module;
	RSLT(Sym->GetSymbolTypeId(lua.checkstringL(2), &typeId, &module));
	SOK() ? (lua.pushinteger(typeId),
		lua.pushinteger(module)) : lua.Push(false);

	return 2;
}

int LuaGetTypeId(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	ULONG typeId;
	RSLT(Sym->GetTypeId(lua.checkintegerL(2), lua.checkstringL(3), &typeId));
	SOK() ? lua.pushinteger(typeId) : lua.Push(false);

	return 1;
}

int LuaGetTypeName(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	char buf[10240];
	ULONG size;
	RSLT(Sym->GetTypeName(lua.checkintegerL(2), lua.checkintegerL(3), buf, 10240, &size));
	SOK() ? lua.pushlstring(buf, size) : lua.Push(false);

	return 1;
}

int LuaGetTypeSize(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	ULONG size;
	RSLT(Sym->GetTypeSize(lua.checkintegerL(2), lua.checkintegerL(3), &size));
	SOK() ? lua.pushinteger(size) : lua.Push(false);

	return 1;
}

int LuaOutputTypedDataPhysical(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	RSLT(Sym->OutputTypedDataPhysical(lua.checkintegerL(2),
										lua.checkintegerL(3),
										lua.checkintegerL(4),
										lua.checkintegerL(5),
										lua.checkintegerL(6)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaOutputTypedDataVirtual(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	RSLT(Sym->OutputTypedDataVirtual(lua.checkintegerL(2),
										lua.checkintegerL(3),
										lua.checkintegerL(4),
										lua.checkintegerL(5),
										lua.checkintegerL(6)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaReadTypedDataPhysical(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	char buf[10240];
	ULONG size;
	RSLT(Sym->ReadTypedDataPhysical(lua.checkintegerL(2),
										lua.checkintegerL(3),
										lua.checkintegerL(4),
										buf, 10240, &size));
	SOK() ? lua.pushlstring(buf, size) : lua.Push(false);

	return 1;
}

int LuaReadTypedDataVirtual(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	char buf[10240];
	ULONG size;
	RSLT(Sym->ReadTypedDataVirtual(lua.checkintegerL(2),
										lua.checkintegerL(3),
										lua.checkintegerL(4),
										buf, 10240, &size));
	SOK() ? lua.pushlstring(buf, size) : lua.Push(false);

	return 1;
}

int LuaReload(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	RSLT(Sym->Reload(lua.checkstringL(2)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaRemoveSymbolOptions(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	RSLT(Sym->RemoveSymbolOptions(lua.checkintegerL(2)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaResetScope(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	RSLT(Sym->ResetScope());
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaSetImagePath(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	RSLT(Sym->SetImagePath(lua.checkstringL(2)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaSetScope(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	return 1;
}

int LuaSetSourcePath(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	RSLT(Sym->SetSourcePath(lua.checkstringL(2)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaSetSymbolOptions(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	RSLT(Sym->SetSymbolOptions(lua.checkintegerL(2)));
	SOK() ? lua.Push(true) : lua.Push(false);

	return 1;
}

int LuaSetSymbolPath(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	RSLT(Sym->SetSymbolPath(lua.checkstringL(2)));
	SOK() ? lua.Push(true) : lua.Push(false);
	
	return 1;
}

int LuaStartSymbolMatch(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	ULONG64 handle;
	RSLT(Sym->StartSymbolMatch(lua.checkstringL(2), &handle));
	SOK() ? lua.pushinteger(handle) : lua.Push(false);

	return 1;
}

int LuaWriteTypedDataPhysical(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	ULONG size;
	RSLT(Sym->WriteTypedDataPhysical(lua.checkintegerL(2),
										lua.checkintegerL(3),
										lua.checkintegerL(4),
										lua.ToBuffer(5),
										10240, &size));
	SOK() ? lua.pushinteger(size) : lua.Push(false);

	return 1;
}

int LuaWriteTypedDataVirtual(lua_State *L)
{
	LuaAPI lua(L);
	DbgSymbol *Sym = (DbgSymbol *)lua.CheckUserPointer(1, str::utLuaDebugSymbols);

	ULONG size;
	RSLT(Sym->WriteTypedDataVirtual(lua.checkintegerL(2),
										lua.checkintegerL(3),
										lua.checkintegerL(4),
										lua.ToBuffer(5),
										10240, &size));
	SOK() ? lua.pushinteger(size) : lua.Push(false);

	return 1;
}
