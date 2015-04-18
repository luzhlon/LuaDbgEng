--自动生成 table和各种Struct转换函数的脚本 
--将C函数输出到log.txt文件中
--
local f = io.open('struct.txt', 'r')
local con = f:read('*a') f:close()
local log = io.open('log.txt', 'w')
io.output(log)


local function writeToLog(tN, fields)
    --Struct 2 Table
    io.write('void ', tN:sub(7, -1), '2Table(lua_State *L, ', tN, ' *st)\n{\n')
    io.write('\t', 'LuaAPI lua(L);\n\n')
    io.write('\t', 'lua.newtable();\n')
    iterator = fields:gmatch'[%w_]+%s+([%w_]+);'
    for field in iterator do
        io.write('\t', 'lua.pushinteger(st->', field, ');\n')
        io.write('\t', 'lua.setfield(-2, "', field, '");\n')
    end
    io.write('}\n\n')
    --Table 2 Struct 
    io.write('void Table2', tN:sub(7, -1), '(lua_State *L, ', tN, ' *st)\n{\n')
    io.write('\t', 'LuaAPI lua(L);\n\n')
    iterator = fields:gmatch'[%w_]+%s+([%w_]+);'
    for field in iterator do
        io.write('\t', 'lua.getfield(-1, "', field, '");\n')
        io.write('\t', 'st->', field, ' = lua.tointeger(-1); lua.pop(1);\n')
    end
    io.write('}\n\n')
end

local function writeDecl(tN, fields)
    io.write('void ', tN:sub(7, -1), '2Table(lua_State *L, ', tN, ' *st);\n')
    io.write('void Table2', tN:sub(7, -1), '(lua_State *L, ', tN, ' *st);\n')
end

local i = 0
for stName, fields, typeName in con:gmatch('typedef[%s%c]+(struct[%s%c]+[%w_]+)[%s%c]+(%b{})[%s%c]+(.-);')
do
    --writeToLog(typeName:match'([%w_]+),', fields)
    writeDecl(typeName:match'([%w_]+),', fields)
    print(typeName) io.read()
    i = i + 1
end
log:close()
