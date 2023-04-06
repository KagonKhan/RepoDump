#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
#SingleInstance force
#Persistent 

SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
CoordMode, Mouse, Screen ; makes mouse coordinates to be relative to screen.
CoordMode, ToolTip, Screen ; makes tooltip to appear at position, relative to screen.



firstUse 		:= True
1stMiner		:= {x: 243, y: 387}
1stResource		:= {x: 471, y: 387}
2ndMiner		:= {x: 850, y: 393}
2ndResource		:= {x: 1050, y: 393}
4thMiner		:= {x: 243, y: 750}
4thResource		:= {x: 471, y: 750}


settimer start, 0

return


start:
	while GetKeyState("capslock","T"){
		If (firstUse = true) {
			RenderMousePosition()
			Continue
		}	
	}

return



Mining(){



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
