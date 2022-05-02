#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.

CoordMode, Mouse, Screen ; makes mouse coordinates to be relative to screen.
CoordMode, ToolTip, Screen ; makes tooltip to appear at position, relative to screen.

#SingleInstance force
#Persistent 

; Prints mouse coordinates next to the pointer if capslock is on
settimer start, 0

return

start:
	if !GetKeyState("capslock","T"){
		ToolTip ; reset
	}
	else {
		MouseGetPos xx, yy
		ToolTip %xx%`, %yy%, %xx%, %yy%
	}
return



*ESC::ExitApp