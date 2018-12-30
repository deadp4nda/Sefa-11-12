---Arbeitsstand:
--

---TODO: programm lookup table
--

-- INCLUDES:
--local http = require("http")



---___SEND___---

---
--- PARSER ---
---

-- |send - Parser| --
-- Eingabe: String - UI-Eingabe
-- Ausgabe: Funktionsaufruf

local cert = nil



function interpret_input(ui_input)
    local name = "interpret_input: "
    local content = split_input(ui_input)
    local n = content[1]
    local commands = {
        ["send_file"]=0,
        ["send_comm"]=0,
        ["get"]=0,
        ["open"]=0,
        ["shutdown"]=0,
        ["y"]=0,
        ["n"]=0,
        ["connect"]=0,
        ["reconnect"]=0,
        ["disconnect"]=0,
        ["squit"]=0,
        ["mangomeow"]=0}
    if commands[n]~=nil then
        if n=="y" or n=="n" or cert==true or n=="disconnect" or n=="connect" or n=="squit" then
            local result = _G[content[1]](content)
        else
            t_write("ERROR: "..name.."Zertifikat ungültig!")
        end

    else
        local subject = string.format("%q",content[1])
        t_write("ERROR: ".. name .. subject .. " - unbekannter Befehl!")
    end
end


-- |Parser:- Eingabeverarbeitung| --
-- Eingabe: String - UI-Eingabe
-- Ausgabe: Table: Argumente der Eingabe

function mangomeow()
    t_write("Meow meow - Meow")
end

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

function startup()
    local ext_ip = c_getwan()
    t_write("Willkommen zu MangoThunfisch! Ihre IPs lauten:\n WAN:   "..ext_ip.."\n LOCAL: ".."PLATZHALTER")
end

function squit(args)
    c_squit()
end

function t_write(str)
    c_terminal_output(str)
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
    if get_length(args)==1 then
        local file_name = args[2]
        local file_type = 0
        c_issue_file(file_name, file_type)
        print( "debug: "..name.." successful")
        t_write("done")
    else
        t_write("ERROR: "..name.." Argumentenzahl unpassend")
    end
end

function to_string(str)
    if str ==nil then return "" else return str end
end

-- |send| --
-- Eingabe:
-- Ausgabe:
function send_comm(args)
    local name = "send_comm"
    local argument_number = get_length(args)
    if argument_number>=2 and argument_number<=4 then
        local command_name = args[2]
        local result = tonumber(args[3])
        local programm = to_string(args[5])
        local command_arguments = to_string(args[4])

        --TODO instr + prog lookup table
        c_issue_instruction(0, 0, programm.." "..command_name.." "..command_arguments, result)
        return "debug: "..name.." successful"
    else
        t_write("ERROR: "..name.." Argumentenzahl unpassend")
    end
end

function instr_lookup(key)
    local inst = {
        ["Exit"]=0,
        ["Kill"]=0,
        ["GetFileList"]=0,
        ["GetPrgmList"]=0,
        ["RetrieveFile"]=0,
        ["Execute"]=0,
        ["Chat"]=0,
        ["FileToBeSent"]=0,
        ["InvalidInstr"]=0
    }
    --whatever
end

function prog_lookup(key)
    local prog={
        ["This"]=0,
        ["InvalidProg"]=0,
        ["Bash"]=0
    }
    --whatever II
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
        local todo = "send file"
        --TODO
        c_issue_instruction(todo)
        return "debug: "..name.." successful"

    else
        t_write("ERROR: "..name.." Argumentenzahl unpassend")
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
        t_write("ERROR: "..name.." Argumentenzahl unpassend")
    end
end


-- || --
-- Eingabe:
-- Ausgabe:


function connect(args)
    local name = "connect"
    local argument_number = get_length(args)
    if argument_number==1 or argument_number==2 then
        local ip = args[2]
        if args[3]==nil then
            local port = 0
        else
            local port = tonumber(args[3])
        end
        local state = c_connect_to(ip, port)
        cert = true
	    if state == 0 then
            t_write("failed")

	    end
        
    else
        t_write("ERROR: "..name.." Argumentenzahl unpassend")
    end
end

function reconnect(args)
    local name = "reconnect"
    local argument_number = get_length(args)
    if argument_number==1 or argument_number==2 then
        local ip = args[2]
        local port = args[4]
        disconnect({"disconnect", nil})
        connect({"connect",ip,port})
    else
        t_write("ERROR: "..name.." Argumentenzahl unpassend")
    end
end


-- || --
-- Eingabe:
-- Ausgabe:

function disconnect(args)
    local name = "connect"
    local argument_number = 0
    if argument_number==0 or argument_number==1 then
        c_issue_instruction(0, 1, "disconnect", 0)
        c_disconnect()
        cert = nil
    else
        t_write("ERROR: "..name.." Argumentenzahl unpassend")
    end
end

-- || --
-- Eingabe:
-- Ausgabe:

function shutdown(args)
    send_comm({"send_comm", "shutdown",0,})
end

function y()
    if cert == nil then
        t_write("Verbindung wurde autorisiert!")
        c_issue_instruction(0, 1, "AUTH_SUCC", 0)
        cert=true
    end

end

function n()
    if cert == nil then
        cert=false
        t_write("Verbindung wurde verweigert!")
        c_issue_instruction(0, 1, "AUTH_FAIL", 0)
        disconnect({"disconnect",""})
    end
end

function certificate()
    --TODO
    local IP = "whatever, muss ich noch einfügen"
    local msg = "Eingehende verbindung von "..IP..". Ablehnen mit 'n', Annehmen mit 'y'."
    t_write(msg)
end

-- || --
-- Eingabe:
-- Ausgabe:
function authenticate()
    send_comm({"certificate"})
end


---___RECEIVE___---
function interpret_comm(type_id,prog_id,comm,result)
    if prog_id == 0 then
        t_write("Eingehende Anweisung: "..comm)
        local name = "interpret_comm"
        os.execute(comm)
        --os.exit()
        if result==1 then
            send_file({"send_file", "output.txt",""})
        end
    elseif prog_id == 1 then
        feedback(comm)
    end
end

function filetrans_start(f_name, f_hash, f_type, f_size)
    t_write("Dateiübertragung wurde gestartet:\n"..f_name.."-"..f_size)
    local x = io.open(temp_path.."file_save.txt","a")
    x:write(f_hash..","..f_name..","..f_type..","..f_size.."\n")
    x:close()

end

function filetrans_end()
    t_write("Dateiübertragung beendet")
end

function table_contains(tab, key)
    return tab[key]~=nil
end

function feedback(input_str)
    local arg = split_input(input_str)
    local output = {
        ["CONNECTION_INITIATED"]="Verbindung erfolgreich initialisiert",
        ["FILE_CONNECTION_INITIATED"]="Übertragung erfolgreich initialisiert",
        ["FILE_CONNECTION_CLOSED"]="Übertragung beendet!",
        ["FILE_CANCELLED"]="Dateiübertregung abgebrochen",
        ["REMOTE_CONNECTION_RECEIVED"]="Eingehende Verbindung erhalten",
        ["REMOTE_CONNECTION_CLOSED"]="Eingehende Verbindung beendet",
        ["BYTES_RECEIVED"]="Empfangene Bytes: "..tostring(arg[2]),
        ["BYTES_SENT"]="Gesendete Bytes: "..tostring(arg[2]),
        ["NO_FILES_IN_QUEUE"]="Keine Dateien in der Warteschlange",
        ["TRANSMISSION_STARTED"]="Übertragung gestartet",
        ["TRANSMISSION_ENDED"]="Übertragung beendet",
        ["AUTH_SUCC"]= "Verbindung wurde autorisiert!",
        ["AUTH_FAIL"]="Verbindung wurde verweigert!"
    }
    local request = {
        ["disconnect"]="",
        ["TEMP"]="",
        ["GET_FILES"]="",
        ["CONNECTION_CLOSED"]="Verbindung beendet",

        ["GET_REMOTE_FILES"]=""
    }

    if table_contains(output, arg[1]) then

        t_write(output[arg[1]])
    elseif table_contains(request, arg[1]) then

        _G[arg[1]](arg[2])

    else
        t_write("ERROR: feedback: unknown state")
    end

end


function CONNECTION_CLOSED()
    t_write("Verbindung wurde beendet")
    cert = nil
end

local temp_path = ""



function TEMP(comm)
    temp_path = comm
    print("debug:"..temp_path)
end

function GET_FILES()
    --file_save.txt

end

function GET_REMOTE_FILES()

end

---
--- DEBUG ---
---
--s = "send_filex 127:a:0:1:b filename mp4"
-- TODO error()
--feedback("BYTES_RECEIVED MEWO")
--startup()
startup()