----------------------------------------------------------------------
----------------------Test code---------------------------------------
----------------------------------------------------------------------

local d = _D
local Ui = NonGUI

d.OnLoadUI = function()
    local text = Ui.Text{
        OnEnter = function(text)
            local ok, err = pcall(load(text:value()))
            if not ok then print('[ERROR:OnEnter]', err) end
            text:value('')
            return true
        end,
        Style = Ui.wxTE_MULTILINE,
        Width = 100, Height = 100
    } 
    Ui.AddPane(text, Ui.wxBOTTOM, 'Perform Lua scripts')
end

d.OnWaitEvent = function()
    d.Client:CreateProcess([[D:\BaiDuYun\Projects\VC6\Ñ¹Ëõ\Debug\Ñ¹Ëõ.exe]])
end

d.SetInputCallback(function(isStart, buffsize)
    print '----------------INPUT----------------'  
end)

d.SetOutputCallback(function(outp, text)
    io.write(text)
end)

d.SetEventCallback {
    Breakpoint = function(bp)
        print ('Breakpoint', bp)
    end,
    CreateThread = function(...)
        print('CreateThread', ...)
    end
}

return d

----------------------------------------------------------------------
----------------------------------------------------------------------
----------------------------------------------------------------------
--[[
dbg:SetEventCallback("LoadModule", function(t)
    --print('LoadModule:'..t["ImageName"], string.format("%x", t.BaseOffset))
    --[[
    local cmd = string.format("u %x", t.BaseOffset+250)
    dbg:Execute(cmd)
    --]]
    --[[
    local s, n = nil, t.BaseOffset + 512
    for i=1,10 do
        s, n = dbg:Disassemble(n)
        print(s)
        print(s:match("%w+%s+%w+%s+(%w+)%s+(%w+)%s+(%w+).*"))
    end
    --]]
    --
    --[[
    local r = dbg:GetOffset("CreateFile")
    if not r then return end
    if type(r)=="number" then print(string.format("%x", r)) return end
    for k,v in pairs(r) do print(k,v) end
    --return con.DEBUG_STATUS_GO_HANDLED
end)
--]]--
