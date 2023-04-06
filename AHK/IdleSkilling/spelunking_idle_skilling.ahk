#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
#SingleInstance force
#Persistent 

SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
CoordMode, Mouse, Screen ; makes mouse coordinates to be relative to screen.
CoordMode, ToolTip, Screen ; makes tooltip to appear at position, relative to screen.


; USAGE: Define as 1 to find out where the swap buttons are (coords), fill in the coords, change to 0, enjoy not having CTS
; Measure first, second, eighth pot positions, recommended to choose same spot (fill bar)


firstUse 		:= False
delve  			:= {x: 2389, y: 1119}
bag 			:= {x: 777, y: 1290}


settimer start, 0

return


start:
	while GetKeyState("capslock","T"){
		If (firstUse = true) {
			RenderMousePosition()
			Continue
		}	
		else {
			Spelunk()
		}
return
}



return
	
Spelunk(){
global
	Click(delve, 1000) ; extract
	Loop 10{
		Click(bag, 10) ; loot bags
	} Sleep 2000
	Click(delve, 3000) ; delve again
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