
local f = io.open('log.txt', 'w')

io.output(f)

local log =
{
    DEBUG_ASMOPT_XXX = {},
    DEBUG_ATTACH_XXX = {},
    DEBUG_DUMP_XXX = {},
    DEBUG_ENGOPT_XXX = {},
    DEBUG_EVENT_XXX = {},
    DEBUG_FILTER_XXX = {},
    DEBUG_FIND_SOURCE_XXX = {},
    DEBUG_FORMAT_XXX = {},
    DEBUG_OUTCTL_XXX = {},
    DEBUG_OUTPUT_XXX = {},
    DEBUG_PROCESS_XXX = {},
    DEBUG_STATUS_XXX = {},
    DEBUG_SYMBOL_XXX = {},
    DEBUG_TYPEOPTS_XXX = {}
}

local function cDefines(filename)
    if not filename then return error('filename is nil') end
    local f = io.open(filename)
    if not f then print 'Open file error.' return nil end
    local line = ""
    return function()
       line = f:read('*l')
       if not line then f:close() return nil end
       local d,s = line:match('%s*#define%s+([%w_]+)%s+(.*)') 
       if d then
           return d, s
       else
           return false
       end
    end
end

for d, s in cDefines('dbgeng.h') do 
    if d then
    if d ~= 'INTERFACE' then
        if     d:find '^DEBUG_ASMOPT' then log.DEBUG_ASMOPT_XXX[d] = s
        elseif d:find '^DEBUG_ATTACH' then log.DEBUG_ATTACH_XXX[d] = s
        elseif d:find '^DEBUG_DUMP'  then log.DEBUG_DUMP_XXX[d] = s
        elseif d:find '^DEBUG_ENGOPT'  then log.DEBUG_ENGOPT_XXX[d] = s
        elseif d:find '^DEBUG_EVENT'  then log.DEBUG_EVENT_XXX[d] = s
        elseif d:find '^DEBUG_FILTER'  then log.DEBUG_FILTER_XXX[d] = s
        elseif d:find '^DEBUG_FIND_SOURCE' then log.DEBUG_FIND_SOURCE_XXX[d] = s
        elseif d:find '^DEBUG_FORMAT'  then log.DEBUG_FORMAT_XXX[d] = s
        elseif d:find '^DEBUG_OUTCTL' then log.DEBUG_OUTCTL_XXX[d] = s
        elseif d:find '^DEBUG_OUTPUT' then log.DEBUG_OUTPUT_XXX[d] = s
        elseif d:find '^DEBUG_PROCESS' then log.DEBUG_PROCESS_XXX[d] = s
        elseif d:find '^DEBUG_STATUS' then log.DEBUG_STATUS_XXX[d] = s
        elseif d:find '^DEBUG_SYMBOL' then log.DEBUG_SYMBOL_XXX[d] = s
        elseif d:find '^DEBUG_TYPEOPTS' then log.DEBUG_TYPEOPTS_XXX[d] = s
        end
    end end
end

for k,v in pairs(log) do
    print(k, ':')
    io.write(k, ':', '\n')
    for d, s in pairs(v) do
        print('\t', d, s)
        io.write(string.format('\t{ "%s", %s },\n', d, d))
    end
end

f:close()

