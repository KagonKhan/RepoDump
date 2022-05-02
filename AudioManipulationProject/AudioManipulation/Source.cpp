#include <iostream>
#include "SoundEffects.h"




int main() {
	SoundEffects soundeffect;


	SoundEffects::LoadAudioSource("","Dorime.wav");
	SoundEffects::AddEchoEffect("Dorime.wav", 0.75, 0.5, MODE::INFINITE);
	SoundEffects::SaveAudioSource("", "Dorime.wav", "triple Echo Dorime.wav");

	SoundEffects::A4;
	return 0;
}