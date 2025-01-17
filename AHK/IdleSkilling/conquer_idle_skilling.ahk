#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
#SingleInstance force
#Persistent 

SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
CoordMode, Mouse, Screen ; makes mouse coordinates to be relative to screen.
CoordMode, ToolTip, Screen ; makes tooltip to appear at position, relative to screen.


; USAGE: Define as 1 to find out where the swap buttons are (coords), fill in the coords, change to 0, enjoy not having CTS
firstUse := false
normalSkillSwap   := {x: 653, y: 1180}
advancedSkillSwap := {x: 561, y: 1353} 


settimer start, 0

return


start:
	while GetKeyState("capslock","T"){
		If (firstUse = true) {
			RenderMousePosition()
			Continue
		}
		Click
		Sleep 250
		MouseGetPos xx, yy
		Click(normalSkillSwap)
		PressAllSkills()
		Sleep 150
		Click(normalSkillSwap)
		PressAllSkills()
		Sleep 150
		Click(advancedSkillSwap)
		PressAllSkills()
		MouseMove, xx, yy
	}

return

PressAllSkills(){
	Send, 1
	Sleep 5
	
	Send, 2
	Sleep 5
	
	Send, 3
	Sleep 5

	Send, 4
	Sleep 5
	
	Send, 5
}


RenderMousePosition(){
	MouseGetPos xx, yy
	ToolTip %xx%`, %yy%, %xx%, %yy%
}

Click(position, delay = 75){
	MouseClick, left, position.x, position.y
	Sleep delay
	;MsgBox % position.x ", " position.y
}
*ESC::ExitApp