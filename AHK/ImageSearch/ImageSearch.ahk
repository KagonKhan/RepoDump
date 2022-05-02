#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.

#SingleInstance Force

CoordMode, Pixel, screen  ; Interprets the coordinates below as relative to the screen rather than the active window.

; Wrapper for ImageSearch
ImageSearch(file, left, top, width, height){
		
	ImageSearch, FoundX, FoundY, left, top, width, height, %file%
		
	if (ErrorLevel = 2){
		TrayTip,, Could not search.		
	}
	else if (ErrorLevel = 1){
		TrayTip,, Image could not be found on the screen.
	}	
	else {
		Arr:=[FoundX,FoundY]
		return Arr
	}

}