---Arbeitsstand:
--

---TODO: programm lookup table
--


---___SEND___---

---
--- PARSER ---
---

-- |send - Parser| --
-- Eingabe: String - UI-Eingabe
-- Ausgabe: Funktionsaufruf

local cert = NIL

function interpret_input(ui_input)
    local name = "interpret_input: "
    local content = split_input(ui_input)
    local commands = {
        ["send_file"]=0,
        ["send_comm"]=0,
        ["get"]=0,
        ["open"]=0,
        ["shutdown"]=0,
        ["y"]=0,
        ["n"]=0}
    if commands[content[1]]~=NIL then
        if content[1]=="y" or content[1]=="n" or cert==true then
            local result = _G[content[1]](content)
        else
            print("ERROR: "..name.."Zertifikat ungültig!")
        end

    else
        local subject = string.format("%q",content[1])
        print("ERROR: ".. name .. subject .. " - unbekannter Befehl!")
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



function t_write(str)
    local blank = "c_call_terminalw(str)"
end

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
    local name = "send_file"
    if get_length(args)==2 then
        local file_name = args[2]
        local file_type = args[3]
        local blank = "c_call_sendfile(filename, filetype))"
        return "debug: "..name.." successful"
    else
        print("ERROR: "..name.." Argumentenzahl unpassend")
    end
end


-- |send| --
-- Eingabe:
-- Ausgabe:
function send_comm(args)
    local name = "send_comm"
    local argument_number = get_length(args)
    if argument_number>=2 and argument_number<=4 then
        local command_name = args[2]
        local result = args[3]
        local programm = args[4]
        local command_arguments = args[5]


        local blank = "c_call_sendcomm(commname, [programm], [arguments]))"
        return "debug: "..name.." successful"
    else
        print("ERROR: "..name.." Argumentenzahl unpassend")
    end
end


-- || --
-- Eingabe:
-- Ausgabe:
function get_file(args)
    local name = "get_file"
    local argument_number = get_length(args)
    if argument_number==2 then
        local file_path = args[2]
        local file_type = args[3]
        local blank = "c_call_getfile(filepath, filetype))"
        return "debug: "..name.." successful"

    else
        print("ERROR: "..name.." Argumentenzahl unpassend")
    end
end


-- || --
-- Eingabe:
-- Ausgabe:
function open(args)
    local name = "open"
    local argument_number = get_length(args)
    if argument_number==2 or argument_number==3 then
        local file_path = args[2]
        local file_type = args[3]
        local programm = args[4]
            -- programm loockup table
        send_file({"send_file", file_path, file_type})
        send_comm({"send_comm", "exec", "0" ,programm, {file_path, file_type}})
        return "debug: "..name.." successful"

    else
        print("ERROR: "..name.." Argumentenzahl unpassend")
    end
end


-- || --
-- Eingabe:
-- Ausgabe:

function reconnect(args)
    local name = "reconnect"
    local argument_number = get_length(args)
    if argument_number==2 or argument_number==3 then
        local ip = args[2]
        local pol = args[3]
        local port = args[4]
        disconnect({"disconnect", pol})
        local blank = "c_call_connect(ip, [port])"
    else
        print("ERROR: "..name.." Argumentenzahl unpassend")
    end
end


-- || --
-- Eingabe:
-- Ausgabe:

function disconnect(args)
    local name = "connect"
    local argument_number = get_length(args)
    if argument_number==0 or argument_number==1 then
        local pol = args[2]
        local blank = "c_call_disconnect(ip, [pol])"
    else
        print("ERROR: "..name.." Argumentenzahl unpassend")
    end
end

-- || --
-- Eingabe:
-- Ausgabe:

function shutdown(args)
    send_comm({"send_comm", "shutdown",0,})
end

function y()
    if cert == NIL then

        cert=true
    end

end

function n()
    if cert == NIL then
        cert=false


        disconnect({"disconnect",""})
    end
end

function certificate()
    local IP = "whatever, muss ich noch einfügen"
    local msg = "Eingehende verbindung von "..IP..". Ablehnen mit 'n', Annehmen mit 'y'."
    print(msg)
end

-- || --
-- Eingabe:
-- Ausgabe:
function authenticate()
    send_comm({"certificate"})
end


---___RECEIVE___---
function interpret_comm(args)
    local name = "interpret_comm"
    if get_length(args)>=2 and get_length(args)<=4 then
        local command = args[1]
        local result = args[2]
        local programm = args[3]
        local arguments = args[4]
        os.execute(programm.." "..command.." "..arguments..">output.txt")
        os.exit()
        if result=="1" then
            send_file({"send_file", "output.txt",""})
        end
    elseif get_length(args)==0 then
        if args[1] == "certificate" then
            certificate()
        else
            print("ERROR: "..name.." Unbekannter Befehl")
        end
    else
        print("ERROR: "..name.." Argumentenzahl unpassend")
    end
end

function filetrans_start(f_name, f_hash, f_type, f_size)
    local x = io.open("file_save.txt","a")
    x:write(f_hash..","..f_name..","..f_type..","..f_size.."\n")
    x:close()

end

function filetrans_end()
    print("Send_file: Completed! bal bla filemüll")
end

function table_contains(tab, key)
    return set[key]~=NIL
end

function feedback(input_str, arg)
    local output = {
        ["CONNECTION_INITIATED"]="",
        ["CONNECTION_CLOSED"]="",
        ["FILE_CANCELLED"]="",
        ["REMOTE_CONNECTION_RECEIVED"]="",
        ["REMOTE_CONNECTION_CLOSED"]="",
        ["BYTES_RECEIVED"]="",
        ["BYTES_SENT"]="",
        ["NO_FILES_IN_QUEUE"]="",
        ["TRANSMISSION_STARTED"]="",
        ["TRANSMISSION_ENDED"]="",
        ["CONNECTION_INITIATED"]=""
    }
    local request = {
        ["GET_FILES"]="",
        ["GET_REMOTE_FILES"]=""
    }
    if table_contains(output,input_str) then
        print(output[input_str])
    else
        _G[request[input_str]]()
    end
end

function GET_FILES()
    --file_save.txt

end

function GET_REMOTE_FILES()

end

---
--- DEBUG ---
---
s = "send_filex 127:a:0:1:b filename mp4"

