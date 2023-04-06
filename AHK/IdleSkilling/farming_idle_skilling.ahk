#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
#SingleInstance force
#Persistent 

SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
CoordMode, Mouse, Screen ; makes mouse coordinates to be relative to screen.
CoordMode, ToolTip, Screen ; makes tooltip to appear at position, relative to screen.


; USAGE: Define as 1 to find out where the swap buttons are (coords), fill in the coords, change to 0, enjoy not having CTS
; Measure first, second, eighth pot positions, recommended to choose same spot (fill bar)
firstUse 		:= False
goNextPlant 	:= False
goPreviousPlant := False


firstPot  				:= {x: 233, y: 532}
secondPot 				:= {x: 500, y: 532}
eighthPot 				:= {x: 233, y: 890}

harvestAllButton  		:= {x: 310, y: 1080}

emptySpace		  		:= {x: 1816, y: 102}

soilMinusButton	  		:= {x: 893, y: 1138}
soilPlusButton	  		:= {x: 1075, y: 1138}
seedMinusButton	  		:= {x: 1172, y: 1138}
seedPlusButton	  		:= {x: 1353, y: 1138}

onePercentButton	  	:= {x: 1188, y: 1273}
fivePercentButton	  	:= {x: 1277, y: 1273}
twofivePercentButton  	:= {x: 1370, y: 1273}

leftArrow	  			:= {x: 1565, y: 1120}
rightArrow	  			:= {x: 1789, y: 1120}



settimer start, 0

return


start:
	while GetKeyState("capslock","T"){
		If (firstUse = true) {
			RenderMousePosition()
			Continue
		}	
	}
	
	if GetKeyState("1"){
		goNextPlant:= False
		CycleAllPlants()
	}
	if GetKeyState("2"){
		goNextPlant:= True
		CycleAllPlants()
	}
	if GetKeyState("3"){
		goNextPlant		:= False
		goPreviousPlant := True
		CycleAllPlants()
	}
	if GetKeyState("4"){
		ResetFlowers()
	}
	if GetKeyState("5"){
		PipelineFlowers()
	}
return



; Goes through all of the plants and either `1` replants them, `2` proceeds by one, `3` receeds by one
CycleAllPlants(){
	global 
	
	Click(emptySpace)
	Click(harvestAllButton)
	Sleep 11000 ; wait for harvest all to finish
	
	potDeltaX := secondPot.x - firstPot.x
	currentPotPosition := {x: firstPot.x, y: firstPot.y}
	Loop 2 { ;rows
		Loop 7 { ;columns
			Click(currentPotPosition)
			ProcessPot()
			currentPotPosition.x += potDeltaX
		}
		currentPotPosition := {x: eighthPot.x, y: eighthPot.y}
	}

	click(emptySpace)
	click(harvestAllButton)
}

ProcessPot(){
	global
		
	If (goNextPlant) {
		Click(rightArrow)
		Click(rightArrow)
	}	
	If (goPreviousPlant) {
		Click(leftArrow)
	}
	
	Click(twofivePercentButton)
	Loop 4{
		Click(soilMinusButton)
		Click(seedMinusButton)
	}
	Click(onePercentButton)
	Click(seedPlusButton)
	Click(soilPlusButton)
}



; KEY: 4, Goes through all pots and sets them to first flower
ResetFlowers(){
	global
	
	potDeltaX := secondPot.x - firstPot.x
	currentPotPosition := {x: firstPot.x, y: firstPot.y}
	
	Loop 2 { ;rows
		Loop 7 { ;columns
			Click(currentPotPosition)
			
			Loop 30 {
				Click(leftArrow, 10)
			}
			currentPotPosition.x += potDeltaX
		}
		currentPotPosition := {x: eighthPot.x, y: eighthPot.y}
	}
}



; KEY: 5, Sets up a pipeline (1st pot 1st flower, 2nd pot 2nd flower, etc). Assumes pots are empty
PipelineFlowers(){
	global

	potDeltaX := secondPot.x - firstPot.x
	currentPotPosition := {x: firstPot.x, y: firstPot.y}
	
	Loop 2 { ;rows
		row := A_Index
		
		Loop 7 { ;columns
			Click(currentPotPosition)
			flowerIndex:= (row-1)*7 + A_Index - 1
			
			Loop %flowerIndex% {
				Click(rightArrow)
			}
			currentPotPosition.x += potDeltaX
		}
		currentPotPosition := {x: eighthPot.x, y: eighthPot.y}
	}
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