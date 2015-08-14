#include <stdio.h>
#include <stdarg.h>
#include "LuaAPI.h"
#include "LuaDbgEng.h"

int main()
{
	LuaAPI lua(LuaAPI::newstateL());
	lua.openlibsL();
	char buf[1024];

	InitLuaDbgEng(lua.GetState());

	while (fgets(buf, 1024, stdin))
		if (lua.loadbufferL(buf, strlen(buf), "line")
			|| lua.pcall(0, 0, 0)) fputs(lua.tostring(1), stderr);

	lua.close();
	return 0;
}
