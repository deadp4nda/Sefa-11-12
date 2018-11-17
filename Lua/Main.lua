---Arbeitsstand:
--
---TODO: preplace debug.getinfo
---TODO: programm lookup table
--


---___SEND___---

---
--- PARSER ---
---

-- |send - Parser| --
-- Eingabe: String - UI-Eingabe
-- Ausgabe: Funktionsaufruf

function interpret_input(ui_input)
    local content = split_input(ui_input)
    print("debug: interpret - split complete\n")
    local commands = {
        ["send_file"]=0,
        ["send_comm"]=0,
        ["get"]=0,
        ["open"]=0,
        ["shutdown"]=0}
    if commands[content[1]]~=NIL then
        local result = _G[content[1]](content)
        print("debug: interpret - result complete\n")
        print(result)
    else
        local name = debug.getinfo(1, "n").name
        print("ERROR: "..name..string.format("%q",content[1]).." unbekannter Befehl!")
    end


end


-- |Parser:- Eingabeverarbeitung| --
-- Eingabe: String - UI-Eingabe
-- Ausgabe: Table: Argumente der Eingabe

function split_input(input)
    local content = {}
    local i = 0
    for word in string.gmatch(input, "[%a%d%p]*") do
        if word~="" then
            i = i + 1
            content[i] = word
        end

    end
    return content
end

---
--- COMMANDS ---
---

function get_length(table)
    local i = -1
    for _ in pairs(table) do
        i = i+1 end
    return i
end

-- |send| --
-- Eingabe:
-- Ausgabe:
function send_file(args)
    if get_length(args)==3 then
        local ip = args[2]
        local file_name = args[3]
        local file_type = args[4]
        if authenticate(ip) then
            local blank = "c_call_sendfile(filename, filetype, ip))"
            return "debug: "..debug.getinfo(1, "n").name.." successful"
        else
            print("ERROR: "..debug.getinfo(1, "n").name.." Übertragung wurde abgelehnt")
        end
    else
        print("ERROR: "..debug.getinfo(1, "n").name.." Argumentenzahl unpassend")
    end
end


-- |send| --
-- Eingabe:
-- Ausgabe:
function send_comm(args)
    local argument_number = get_length(args)
    if argument_number==3 or argument_number==2 then
        local ip = args[2]
        local command_name = args[3]
        local command_arguments = args[4]
        if authenticate(ip) then
            local blank = "c_call_sendcomm(ip, commname, [commargs]))"
            return "debug: "..debug.getinfo(1, "n").name.." successful"
        else
            print("ERROR: "..debug.getinfo(1, "n").name.." Übertragung wurde abgelehnt")
        end
    else
        print("ERROR: "..debug.getinfo(1, "n").name.." Argumentenzahl unpassend")
    end
end


-- || --
-- Eingabe:
-- Ausgabe:
function get(args)
    local argument_number = get_length(args)
    if argument_number==3 then
        local ip = args[2]
        local file_name = args[3]
        local file_type = args[4]
        if authenticate(ip) then
            local blank = "c_call_getfile(ip, filename, filetype))"
            return "debug: "..debug.getinfo(1, "n").name.." successful"
        else
            print("ERROR: "..debug.getinfo(1, "n").name.." Übertragung wurde abgelehnt")
        end
    else
        print("ERROR: "..debug.getinfo(1, "n").name.." Argumentenzahl unpassend")
    end
end


-- || --
-- Eingabe:
-- Ausgabe:
function open(args)
    local argument_number = get_length(args)
    if argument_number==3 or argument_number==4 then
        local ip = args[2]
        local file_name = args[3]
        local file_type = args[4]
        local programm = args[5]
        if authenticate(ip) then
            -- programm loockup table
            local blank = "c_call_openfile(ip, filename, filetype, [programm_id]))"
            return "debug: "..debug.getinfo(1, "n").name.." successful"
        else
            print("ERROR: "..debug.getinfo(1, "n").name.." Übertragung wurde abgelehnt")
        end
    else
        print("ERROR: "..debug.getinfo(1, "n").name.." Argumentenzahl unpassend")
    end
end


-- || --
-- Eingabe:
-- Ausgabe:
function shutdown(args)
    print("debug: call: shutdown")
    return "debug: shutdown()"
end


-- || --
-- Eingabe:
-- Ausgabe:
function authenticate(ip)
    print("debug: call: authenticate")
    local blank=true
    --blank = c_call_auth(ip)
    return blank
end


---___RECEIVE___---
function interpret_output(args)
    return "empty"
end



---
--- DEBUG ---
---
s = "send_file 127:a:0:1:b filename mp4"
interpret_input(s)
