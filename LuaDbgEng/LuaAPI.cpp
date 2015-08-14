#include "LuaAPI.h"

LuaAPI::LuaAPI(lua_State *L)
{
	m_L = L;
}

LuaAPI::LuaAPI()
{
	m_L = NULL;
}

lua_State* LuaAPI::SetState(lua_State *L)
{
	if (m_L)return m_L;
	m_L = L;
}

LuaAPI::~LuaAPI()
{
	//lua_close(m_L);
}

void LuaAPI::Assert(bool b, const char *err)
{
   if (b)return;
   Push(err);
   error();
}

void LuaAPI::CreateLibrary(const char *libname, luaL_Reg l[])//0,0
{
	newlibL(l);
	setglobal(libname);
}

void LuaAPI::NewConstantTable(LUA_CONSTANT c[])//0,+1
{
	newtable();

	int i = 0;
	while (c[i].name)
	{
		Push((lua_Integer)c[i].value);
		setfield(-2, c[i].name);
		i++;
	}
}

void * LuaAPI::CheckUserdata(int index)
{
	argcheckL(isuserdata(index), index, 0);
	return touserdata(index);
}

void * LuaAPI::NewUserdata(size_t size, const char *name)
{
	void *u = newuserdata(size);
	newmetatableL(name);
	setmetatable();
	return u;
}

void **LuaAPI::NewUserPointer(void *p, const char *tname)
{
	void **pp = (void **)NewUserdata(sizeof(void *), tname);
	if (pp) *pp = p;
	return pp;
}

void LuaAPI::NewMetaTable(const char *utname)
{
	if (utname)
		luaL_newmetatable(m_L, utname);
	else
		lua_newtable(m_L);
}

void * LuaAPI::CheckUserPointer(int index, const char *tname)
{
	void **pp = (void **)checkudataL(index, tname);
	return pp ? *pp : (void *)pp;
}

void LuaAPI::SetMetaTable(const char *utname)
{
	luaL_setmetatable(m_L, utname);
}

void LuaAPI::SetMetaTable(int nst)
{
	lua_setmetatable(m_L, nst);
}

int LuaAPI::SetMetaField(int nst, const char *field)
{
	if (!getmetatable(nst))
	{
		pop();//pop the nil
		NewMetaTable();
		SetMetaTable(nst);
		if (!getmetatable(nst)) { pop(); return 0; }
	}
	pushvalue(-2);//copy the value to set
	setfield(-2, field);
	pop(2);//pop the metatable and value to set
	return 1;
}

void * LuaAPI::ToBuffer(int index)
{
	if (isinteger(index))
		return (void*)tointeger(index);
	else if (isstring(index))
		return (void*)tostring(index);
	else if (isuserdata(index))
		return touserdata(index);
	else
		Assert(false, "Can not convert to a buffer");
}

void LuaAPI::NewLibrary(const char *libname, luaL_Reg l[])
{
	newlibL(l);
	pushvalue(-1);
	setglobal(libname);
}

lua_Integer LuaAPI::OptIntField(int obj, const char *field, lua_Integer b)
{
	getfield(obj, field);
	lua_Integer ret = optinteger(-1, b); pop();
	return ret;
}
lua_Number  LuaAPI::OptNumField(int obj, const char *field, lua_Number b)
{
	getfield(obj, field);
	lua_Number ret = optnumber(-1, b); pop();
	return ret;
}
const char *LuaAPI::OptStrField(int obj, const char *field, const char *b)
{
	getfield(obj, field);
	const char * ret = optstring(-1, b); pop();
	return ret;
}

void LuaAPI::CheckFieldType(const char *field, int typ, int t)
{
	getfield(t, field);
	checktypeL(-1, typ);
	pop(1);
}

bool LuaAPI::IsFieldType(const char *field, int typ, int t)
{
	getfield(t, field);
	bool ret = (typ == type(-1));
	pop(1);
	return ret;
}

LuaCallback *LuaAPI::NewCallback(int idcall)//0,+1
{
	int typ = type(idcall);
	if (!(typ == LUA_TFUNCTION || typ == LUA_TTABLE))
		return NULL;
	LuaCallback *l = new LuaCallback(newthread());
	pushvalue(idcall);
	xmove(this, l, 1);//回调函数或表
	return l;
}

LuaCallback::LuaCallback(lua_State *L) : LuaAPI(L)
{
	pushthread(L);
	m_ref = RegGetRef();//记录到C注册表防止被回收
}

LuaCallback::~LuaCallback()
{
	RegFreeRef(m_ref);
}

int LuaCallback::InitCallback(const char *nf)
{
	settop(1);
	if (nf)
	{
		if (!istable(1)) return 0;
		getfield(1, nf);
		if (isnoneornil(-1)) return 0;
	}
	else
	{
		if (!isfunction(1)) return 0;
		pushvalue(1);
	}
	m_top = gettop();
	return 1;
}

int LuaCallback::InitCallback(int i)
{
	settop(1);
	if (!istable(1)) return 0;
	geti(1, i);
	m_top = gettop();
	return 1;
}

int LuaCallback::BeginCallback(int nr, int msgh)
{
	return pcall(gettop() - m_top, nr, msgh);
}