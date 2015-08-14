#ifndef _LUAAPI_H_
#define _LUAAPI_H_

#include "lua.hpp"
#include <stdarg.h>
#include <Windows.h>

#define LUA_END_FIELD {0, 0}

class LuaCallback;

class LuaAPI
{
public:
	LuaAPI(lua_State *L);
	LuaAPI();
	~LuaAPI();

	lua_State* SetState(lua_State *L);//如果存在则返回原来的lua_State

	typedef char Int1;
	typedef unsigned short uInt1;
	typedef short Int2;
	typedef unsigned short uInt2;
	typedef int Int4;
	typedef unsigned int uInt4;
	typedef long long Int8;
	typedef unsigned long long uInt8;

	typedef struct
	{
		const char *name;
		int         value;
	}LUA_CONSTANT;

	//Push...
	inline void pushvalue(int i) { return lua_pushvalue(m_L, i); }
	inline void pushnumber(lua_Number n) { return lua_pushnumber(m_L, n); }
	inline void pushboolean(int b) { return lua_pushboolean(m_L, b); }
	inline void pushinteger(lua_Integer i) { return lua_pushinteger(m_L, i); }
	inline int  pushthread(lua_State* L) { return lua_pushthread(L); }
	inline int  pushglobaltable() { return lua_pushglobaltable(m_L); }
	inline void pushlightuserdata(void *p) { return lua_pushlightuserdata(m_L, p); }
	inline void Push(lua_Integer i) { return lua_pushinteger(m_L, i); }
	inline void Push(int i) { return lua_pushinteger(m_L, i); }
	inline void Push(long i) { return lua_pushinteger(m_L, i); }
	inline void Push(unsigned long long i) { return lua_pushinteger(m_L, i); }
	inline void Push(void *p) { return lua_pushlightuserdata(m_L, p); }
	inline void Push(lua_Number n) { return lua_pushnumber(m_L, n); }
	inline void Push(bool b) { return lua_pushboolean(m_L, b); }
	inline void Push(lua_CFunction f, int n = 0) { return lua_pushcclosure(m_L, f, n); }
	inline void Push(void) { return lua_pushnil(m_L); }
	inline const char *Push(const char *s) { return lua_pushstring(m_L, s); }
	inline const char *pushstring(const char *s) { return lua_pushstring(m_L, s); }
	inline const char *pushlstring(const char *s, size_t len){ return lua_pushlstring(m_L, s, len); }
	inline const char *pushvfstring(const char *fmt, va_list args){ return lua_pushvfstring(m_L, fmt, args); }
	const char *pushfstring(const char *fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		return lua_pushvfstring(m_L, fmt, args);
	}
	//to...
	inline int toboolean(int index){ return lua_toboolean(m_L, index); }
	inline lua_CFunction tocfunction(int index){ return lua_tocfunction(m_L, index); }
	inline lua_Integer tointeger(int index){ return lua_tointeger(m_L, index); }
	inline lua_Integer tointegerx(int index, int *isnum = NULL){ return lua_tointegerx(m_L, index, isnum); }
	inline const char *tolstring(int index, size_t *len){ return lua_tolstring(m_L, index, len); }
	inline const char *tostring(int index){ return lua_tostring(m_L, index); }
	inline lua_Number tonumber(int index){ return lua_tonumber(m_L, index); }
	inline lua_Number tonumberx(int index, int *isnum = NULL){ return lua_tonumberx(m_L, index, isnum); }
	inline void *touserdata(int index){ return lua_touserdata(m_L, index); };
	inline lua_State *tothread(int index){ return lua_tothread(m_L, index); };
	//opt..
	inline lua_Integer optinteger(int arg, lua_Integer d){ return luaL_optinteger(m_L, arg, d); }
	inline const char * optlstring(int arg, const char * d, size_t *l = NULL)
												{ return luaL_optlstring(m_L, arg, d, l); }
	inline lua_Number optnumber(int arg, lua_Number d){ return luaL_optinteger(m_L, arg, d); }
	inline const char * optstring(int arg, const char * d)
												{ return luaL_optstring(m_L, arg, d); }
	//load ...
	inline int dostringL(const char *str) { return luaL_dostring(m_L, str); }
	inline int dofileL(const char *file) { return luaL_dofile(m_L, file); }
	inline int loadfileL(const char *file){ return luaL_loadfile(m_L, file); }
	inline int loadbufferL(const char *buf, size_t len, const char *name)
	{
		return luaL_loadbuffer(m_L, buf, len, name);
	}
	inline int pcall(int nargs, int nresults, int msgh)
	{
		return lua_pcall(m_L, nargs, nresults, msgh);
	}
	//check ...
	inline int          checkstack(int n) { return lua_checkstack(m_L, n); }
	inline void         checktypeL(int arg, int t){ return luaL_checktype(m_L, arg, t); }
	inline void         checkstackL(int sz, const char *msg = NULL){ return luaL_checkstack(m_L, sz, msg); }
	inline void *       checkudataL(int ud, const char *tname){ return luaL_checkudata(m_L, ud, tname); }
	inline const char * checkstringL(int arg){ return luaL_checkstring(m_L, arg); }
	inline int          checkoption(int arg, const char *def, const char *lst[])
													{ return luaL_checkoption(m_L, arg, def, lst); }
	inline lua_Integer  checkintegerL(int arg){ return luaL_checkinteger(m_L, arg); }

	inline void         argcheckL(int cond, int iarg, const char *msg){ return luaL_argcheck(m_L, cond, iarg, msg); }
	inline int          argerrorL(int iarg, const char *msg){ return luaL_argerror(m_L, iarg, msg); }

	//create ...
	inline void         createtable(int narr, int nrec){ return lua_createtable(m_L, narr, nrec); }

	//is ...
	inline int          isnil(int index){ return lua_isnil(m_L, index); }
	inline int          isnone(int index){ return lua_isnone(m_L, index); }
	inline int          isnoneornil(int index){ return lua_isnoneornil(m_L, index); }
	inline int          isfunction(int index){ return lua_isfunction(m_L, index); }
	inline int          iscfunction(int index){ return lua_iscfunction(m_L, index); }
	inline int          isnumber(int index){ return lua_isnumber(m_L, index); }
	inline int          isinteger(int index){ return lua_isinteger(m_L, index); }
	inline int          isuserdata(int index){ return lua_isuserdata(m_L, index); }
	inline int          islightuserdata(int index){ return lua_islightuserdata(m_L, index); }
	inline int          isstring(int index){ return lua_isstring(m_L, index); }
	inline int          istable(int index){ return lua_istable(m_L, index); }
	inline int          isthread(int index){ return lua_isthread(m_L, index); }
	inline int          isboolean(int index){ return lua_isboolean(m_L, index); }

	//new ...
	inline void *       newuserdata(size_t size){ return lua_newuserdata(m_L, size); }
	inline void         newtable(){ return lua_newtable(m_L); }
	inline int          newmetatableL(const char *tname){ return luaL_newmetatable(m_L, tname); }
	inline void         newlibL(const luaL_Reg l[]){ return luaL_newlib(m_L, l); }
	inline void         newlibtableL(const luaL_Reg l[]){ return luaL_newlibtable(m_L, l); }
	inline lua_State *  newthread(){ return lua_newthread(m_L); }

	//set get ...
	inline void         setfield(int index, const char *k){ return lua_setfield(m_L, index, k); }
	inline int          getfield(int index, const char *k){ return lua_getfield(m_L, index, k); }
	inline void         seti(int index, lua_Integer i){ return lua_seti(m_L, index, i); }
	inline int          geti(int index, lua_Integer i){ return lua_geti(m_L, index, i); }
	inline void         settable(int index){ return lua_settable(m_L, index); }
	inline int          gettable(int index){ return lua_gettable(m_L, index); }
	inline int          setmetatable(int index = -2){ return lua_setmetatable(m_L, index); }
	inline int          getmetatable(int index = -1){ return lua_getmetatable(m_L, index); }
	inline void         setglobal(const char *name){ return lua_setglobal(m_L, name); }
	inline int          getglobal(const char *name){ return lua_getglobal(m_L, name); }
	inline void         setuservalue(int index = -2){ return lua_setuservalue(m_L, index); }
	inline int          getuservalue(int index = -1){ return lua_getuservalue(m_L, index); }
	inline void         setfuncsL(const luaL_Reg *l, int nup = 0){ return luaL_setfuncs(m_L, l, nup); }
	inline int          gettop(){ return lua_gettop(m_L); }
	inline void         settop(int index){ return lua_settop(m_L, index); }
	inline int          getsubtableL(int idx, const char *fname){ return luaL_getsubtable(m_L, idx, fname); }

	//inline lua_State *  newthread(){ return lua_newthread(m_L); }
	inline int          resume(lua_State *from, int nargs){ return lua_resume(m_L, from, nargs); }
	inline int          yield(lua_State *L, int nargs){ return lua_yield(L, nargs); }

	inline void         pop(int n = 1) { return lua_pop(m_L, n); }
	inline void         close() { return lua_close(m_L); }
	inline int          type(int index){ return lua_type(m_L, index); }
	inline const char * type_name(int tp){ return lua_typename(m_L, tp); }
	inline int          refL(int t){ return luaL_ref(m_L, t); }
	inline void         unrefL(int t, int ref){ return luaL_unref(m_L, t, ref); }
	inline void         rawseti(int t, int n){ return lua_rawseti(m_L, t, n); }
	inline int          rawgeti(int t, int n){ return lua_rawgeti(m_L, t, n); }
	inline void         rawset(int t){ return lua_rawset(m_L, t); }
	inline int          rawget(int t){ return lua_rawget(m_L, t); }
	inline int          rawlen(int t){ return lua_rawlen(m_L, t); }
	inline int          error(){ return lua_error(m_L); }
	inline void         openlibsL(){ return luaL_openlibs(m_L); }

	inline int          callmeta(int obj, const char *e){ return luaL_callmeta(m_L, obj, e); }
	inline void *       testudata(int arg, const char *tname){ return luaL_testudata(m_L, arg, tname); }
	
	inline lua_State *  GetState(){ return m_L; }


	void * ToBuffer(int);
	int    SetMetaField(int, const char *);//-1, 0
	inline void   SetMetaTable(const char *);//-1, 0
	inline void   SetMetaTable(int);//-1, 0
	void   Assert(bool b, const char *err);
	void   CreateLibrary(const char *libname, luaL_Reg l[]);//0,0
	void * CheckUserdata(int index);
	void   NewLibrary(const char *libname, luaL_Reg l[]);//0,+1
	void   NewConstantTable(LUA_CONSTANT c[]);//0,+1
	void   NewMetaTable(const char *utname = NULL);//0,+1
	void * NewUserdata(size_t, const char *name);//0,+1 新建一个类型为name的userdata
	void **NewUserPointer(void *p, const char *);//0,+1 
	void * CheckUserPointer(int index, const char *);//0,0
	void   CheckFieldType(const char *field, int typ, int t = -1);
	bool   IsFieldType(const char *field, int typ, int t = -1);
	LuaCallback *NewCallback(int );//0,+1
	
	//OptField         0,0
	lua_Integer OptIntField(int obj, const char *field, lua_Integer b);
	lua_Number  OptNumField(int obj, const char *field, lua_Number b);
	const char *OptStrField(int obj, const char *field, const char *b);
	
	//C Registry table
	inline void   RegSetfield(const char *gname) { setfield(LUA_REGISTRYINDEX, gname); }
	inline int    RegGetRef() { return refL(LUA_REGISTRYINDEX); }
	inline int    RegGet(int ref) { return rawgeti(LUA_REGISTRYINDEX, ref); }
	inline int    RegGet(const char *field) { return getfield(LUA_REGISTRYINDEX, field); }
	inline void   RegFreeRef(int ref) { return unrefL(LUA_REGISTRYINDEX, ref); }

	//inline void   Lock(){ m_locked = true; }
	//inline void   Unlock(){ m_locked = false; }
	//inline bool   IsLocked(){ return m_locked; }

protected:
    lua_State *m_L;

	//Static function
public:
	static lua_State *  newstateL(){ return luaL_newstate(); }
	static LuaAPI    *  NewStateL(){ return new LuaAPI(luaL_newstate()); };
	static lua_State *  newstate(lua_Alloc f, void *ud){ return lua_newstate(f, ud); }
	static LuaAPI    *  NewState(lua_Alloc f, void *ud){ return new LuaAPI(lua_newstate(f, ud)); }
	static LuaAPI    *  NewStdState()
	{
		LuaAPI * lua = new LuaAPI(LuaAPI::newstateL());
		lua->openlibsL();
		return lua;
	}
	static void         xmove(lua_State *from, lua_State *to, int n = 1)
	{
		return lua_xmove(from, to, n);
	}
	static void         xmove(LuaAPI *from, LuaAPI *to, int n = 1)
	{
		return lua_xmove(from->GetState(), to->GetState(), n);
	}
};

class LuaCallback : public LuaAPI
{
public:
	LuaCallback(lua_State *L);
	~LuaCallback();

	int InitCallback(const char *nf = NULL);
	int InitCallback(int i);
	int BeginCallback(int nr, int msgh = 0);

private:
	int m_ref;
	int m_top;
};

#endif
