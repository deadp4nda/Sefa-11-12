-- globale flags

local cert = nil
local temp_path = ""
local recent_file = nil
local se_flag = false



---___SENDE - FUNKTIONEN___---



-- Parser: Input der Eingaben > Auslösen der Funktionalität
function interpret_input(ui_input)
    local name = "interpret_input: "
    local content = split_input(ui_input)
    local n = content[1]
    local commands = {
        ["send_file"]=0,
        ["send_comm"]=0,
        ["get_file"]=0,
        ["open"]=0,
        ["shutdown"]=0,
        ["y"]=0,
        ["chat"]=0,
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


--DEBUG
function mangomeow()
    t_write("Meow meow - Meow")
end

--Enthalten eines Elements in Table
function table_contains(tab, key)
    return tab[key]~=nil
end

--Eingabeverarbeitung: String > Liste, wörter geteilt an Leerzeichen
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

--Zusammenfügen von Strings in einem Table zu einem String (Umkehren von split_input)
function set_msg(args, ind)
    local msg = ""
    for i=ind, get_length(args)+1 do
        msg = msg..to_string(args[i]).." "
    end
    return msg
end

--- Interne Funktionen
--Start-funktion
function startup()
    local ext_ip, loc_ip = c_getwan()
    t_write("Willkommen zu MangoThunfisch! Ihre IPs lauten:\nWAN:      "..ext_ip.."\nLOCAL:  "..loc_ip)
end

--Terminal Ausgabe
function t_write(str)
    c_terminal_output(str)
end

--Länge eines Tables
function get_length(table)
    local i = -1
    for _ in pairs(table) do
        i = i+1 end
    return i
end

--konvertierung von allgemeinen typen zu string, zusätzliche unterstützung von nil
function to_string(str)
    if str ==nil then return "" else return tostring(str) end
end


--Authentifizierung
function authenticate()
    send_comm({"certificate"})
end


--- Externe Befehle
-- Annehmen eiener Verbindung
function y()
    if cert == nil then
        t_write("Verbindung wurde autorisiert!")
        c_issue_instruction(0, 1, "AUTH_SUCC", 0)
        cert=true
    end

end

--Ablehnen einer Verbindung
function n()
    if cert == nil then
        cert=false
        t_write("Verbindung wurde verweigert!")
        c_issue_instruction(0, 1, "AUTH_FAIL", 0)
        disconnect({"disconnect",""})
    end
end

--Beenden des Programmes
function squit(args)
    disconnect({"disconnect", nil})
    c_squit()
end

--Versenden von chat Nachrichten
function chat(args)
    local msg = ""
    for i=2, get_length(args)+1 do
        msg = msg..args[i].." "
    end
    print("send "..msg)
    --msg = "hällow"
    c_issue_instruction(0,1,"CHAT "..msg,0)
end

--Versenden von Dateien
function send_file(args)
    local name = "send_file"
    if get_length(args)==1 then
        local file_name = args[2]
        local file_type = 0
        c_issue_file(file_name, file_type)
        print( "debug: "..name.." successful")
    else
        t_write("ERROR: "..name.." Argumentenzahl unpassend")
    end
end


--Versenden von Befehlen
function send_comm(args)
    local name = "send_comm"
    local argument_number = get_length(args)
    if argument_number>=2 then
        local result = tonumber(args[2])
        local command_name = set_msg(args,3)
        se_flag = result
        c_issue_instruction(0, 0, command_name, result)
        return "debug: "..name.." successful"
    else
        t_write("ERROR: "..name.." Argumentenzahl unpassend")
    end
end

--[[function instr_lookup(key)
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
end]]


--Datein Downloaden
function get_file(args)
    local name = "get_file"
    local argument_number = get_length(args)
    if argument_number==1 then
        local file = args[2]
        c_issue_instruction(0,1,"SEND_FILE "..file,0)

    else
        t_write("ERROR: "..name.." Argumentenzahl unpassend")
    end
end


--Datein Versenden und öffnen
function open(args)
    local name = "open"
    local argument_number = get_length(args)
    if argument_number==2 or argument_number==1 then
        local file_path = args[2]
        local programm = args[3]
            -- programm loockup table
        send_file({"send_file", file_path})
        c_issue_instruction(0,1,"OPEN "..file_name)

    else
        t_write("ERROR: "..name.." Argumentenzahl unpassend")
    end
end

-- Aufbauen eiener Verbindung
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
            t_write("DEBUG: c_connect_failed")

	    end
        
    else
        t_write("ERROR: "..name.." Argumentenzahl unpassend")
    end
end

--Verbindung trennen und neue Aufbauen
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

--Verbindung trennen
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

--Herunterfahren
function shutdown(args)
    send_comm({"send_comm", "shutdown",0,})
end



---___Empfangs-Funktionen___---

--Eingehenden Befehl interpretieren: Ausführung in os-terminal oder intern
function interpret_comm(type_id,prog_id,comm,result)
    if prog_id == 0 then
        t_write("Eingehende Anweisung: "..comm)
        local name = "interpret_comm"

        os.execute(comm.." > output.txt")
        print("exe succ")
        local out_file = io.open("output.txt", "rb")
        print("file succ")
        local cont = out_file:read("*a")
        print "cont succ"
        out_file:close()
        t_write(cont)

        if result==1 then
            send_file({"send_file", "output.txt"})
        end
    elseif prog_id == 1 then
        feedback(comm)
    end
end


--Dateiübertragung starten, speichern im downloadverzeichnis
function filetrans_start(f_name, f_hash, f_type, f_size)
    t_write("Dateiübertragung wurde gestartet:\n"..f_name.."-"..f_size)
    local x = io.open(temp_path.."file_save.txt","a")
    x:write(f_hash..","..f_name..","..to_string(f_type)..","..to_string(f_size).."\n")
    x:close()
    recent_file = temp_path..f_hash.." "..temp_path..f_name

end

--Dateiübertragung beenden: Umbenennung, terminal ausgabe des return werts
function filetrans_end()
    t_write("Dateiübertragung beendet")
    t_write(recent_file)
    local x = os.execute("ren "..recent_file)
    if x == 1 then

        os.execute("mv "..temp_path..recent_file)
    end
    if se_flag == 1 then
        local x = io.open(temp_path..split_input(recent_file)[2],"rb")
        local content = x:read("*a")
        x:close()
        t_write(content)
        se_flag = 0
    end
end

--Interpreter von Internen Flags und funktionsaufrufen
--sorgt für Ausgaben und löst interne prozesse aus
function feedback(input_str)
    local arg = split_input(input_str)
    local output = {
        ["CHAT"]=set_msg(arg,2),
        ["CONNECTION_INITIATED"]="Verbindung erfolgreich initialisiert",
        ["FILE_CONNECTION_INITIATED"]="Übertragung erfolgreich initialisiert",
        ["FILE_CONNECTION_CLOSED"]="Übertragung beendet!",
        ["FILE_CANCELLED"]="Dateiübertregung abgebrochen",
        ["REMOTE_CONNECTION_RECEIVED"]="Eingehende Verbindung erhalten",
        ["REMOTE_CONNECTION_CLOSED"]="Eingehende Verbindung beendet",
        ["BYTES_RECEIVED"]="Empfangene Bytes: "..tostring(arg[2]).."\r",
        ["BYTES_SENT"]="Gesendete Bytes: "..tostring(arg[2]).."\r",
        ["NO_FILES_IN_QUEUE"]="Keine Dateien in der Warteschlange",
        ["TRANSMISSION_STARTED"]="Übertragung gestartet",
        ["TRANSMISSION_ENDED"]="Übertragung beendet",
        ["AUTH_SUCC"]= "Verbindung wurde autorisiert!",
        ["AUTH_FAIL"]="Verbindung wurde verweigert!"
    }
    local request = {
        ["disconnect"]="",
        ["TEMP"]="",

        ["CONNECTION_CLOSED"]="Verbindung beendet",
        ["OPEN"]="",
        ["SEND_FILE"]=""

    }

    if table_contains(output, arg[1]) then

        t_write(output[arg[1]])
    elseif table_contains(request, arg[1]) then

        _G[arg[1]](set_msg(arg,2))

    else
        t_write("ERROR: feedback: unknown state")
    end

end

--Versenden einer Datei
function SEND_FILE(file)
    c_issue_file(file, 0)
end

--öffnen einer Datei
function OPEN(file)
    local x = os.execute(file)
    if x == 1 then
        os.execute("xdg-open "..file)
    end
end

--Beendete Verbindung
function CONNECTION_CLOSED()
    t_write("Verbindung wurde beendet")
    cert = nil
end


--Zertifizierung einer Verbindung
function certificate()
    --TODO
    local IP = "whatever, muss ich noch einfügen"
    local msg = "Eingehende Verbindung. Ablehnen mit 'n', Annehmen mit 'y'."
    t_write(msg)
end

--setzen der temporären path varibale
function TEMP(comm)
    temp_path = comm
    print("debug:"..temp_path)
end


---
--- DEBUG ---
---
--s = "send_filex 127:a:0:1:b filename mp4"
-- TODO error()
--feedback("BYTES_RECEIVED MEWO")
--startup()
startup()