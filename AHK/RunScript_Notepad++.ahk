; Run Script or Selection in Notepad++
; by boiler
;
; Thanks to lexikos for "How to: Run Dynamic Script... Through a Pipe!"
; and to HotKeyIt for his RunTempScript function using the above, both found here:
; https://autohotkey.com/board/topic/23575-how-to-run-dynamic-script-through-a-pipe/?st=0
;
; Usage:
;	When run from a shortcut key or toolbar button in Notepad++, it follows these rules:
;	- If some text is selected, it will run the selection as a script through a pipe (doesn't create a file)
;	- If no text is selected and the file has been saved as a .ahk file, it will run the script after first
;	  saving the script if some changes were made since the last save
;	- If no text is selected and the file has never been saved, it will run the entire text through a pipe
;	  (and returns caret to the position it was before it selected all the text)

SetTitleMatchMode, 1
StatusBarGetText, StatusBarText, 3, ahk_exe notepad++.exe
ClipSave := ClipboardAll
RegExMatch(StatusBarText, "(?<=Sel : )\d+", SelectionLen)
if SelectionLen ; run the selected text only in a named pipe
{
	Clipboard := ""
	Send, ^c
	ClipWait, 1, 1
	if !ErrorLevel
		RunTempScript(Clipboard, "Selected Text - " A_TickCount)
	Clipboard := ClipSave
}
else ; run the whole script
{
	WinGetTitle, Title, ahk_exe notepad++.exe
	StringReplace, Title, Title, % " - Notepad++"
	if (SubStr(Title, -3) = ".ahk") ; has been saved as an ahk file
	{
		if (SubStr(Title, 1, 1) = "*") ; changes since last save, so save it
		{
			WinMenuSelectItem, ahk_exe notepad++.exe,, File, Save
			Title := SubStr(Title, 2) ; remove "*"
			WinWait, %Title% ; wait for title without "*"
		}
		SplitPath, Title,, WorkingDir
		Run, %Title%, %WorkingDir%
	}
	else ; file has not been saved so grab all the text and run it in a named pipe
	{
		ControlGetFocus, ControlName, ahk_exe notepad++.exe
		if (InStr(ControlName, "Scintilla"))
		{
			ControlGetText, ScriptText, %ControlName%, ahk_exe notepad++.exe
			RunTempScript(ScriptText, "Unsaved Script - " A_TickCount)
		}
	}
}
return

RunTempScript(TempScript, name="")
{
	If name =
	pipe_name := A_TickCount
	Else
	pipe_name := name
	pipe_ga := CreateNamedPipe(pipe_name, 2)
	pipe    := CreateNamedPipe(pipe_name, 2)
	if (pipe=-1 or pipe_ga=-1)
	{
		MsgBox CreateNamedPipe failed.
		ExitApp
	}
	Run, %A_AhkPath% "\\.\pipe\%pipe_name%",,,PID
	DllCall("ConnectNamedPipe","uint",pipe_ga,"uint",0)
	DllCall("CloseHandle","uint",pipe_ga)
	DllCall("ConnectNamedPipe","uint",pipe,"uint",0)
	Script := chr(0xfeff) TempScript
	if !DllCall("WriteFile","uint",pipe,"str",Script,"uint",(StrLen(Script)+1)*2,"uint*",0,"uint",0)
		MsgBox WriteFile failed: %ErrorLevel%/%A_LastError%
	DllCall("CloseHandle","uint",pipe)
	Return PID
}

CreateNamedPipe(Name, OpenMode=3, PipeMode=0, MaxInstances=255)
{
    return DllCall("CreateNamedPipe","str","\\.\pipe\" Name,"uint",OpenMode
        ,"uint",PipeMode,"uint",MaxInstances,"uint",0,"uint",0,"uint",0,"uint",0)
}