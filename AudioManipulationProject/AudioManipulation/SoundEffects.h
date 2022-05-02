#pragma once

#include <cmath>
#include "AudioFile.h"
#include <string>
#include <map>
enum class MODE { DELAY = 0, TRIPLE, INFINITE };

class SoundEffects
{
	std::map<std::string, AudioFile<double>> m_Sources;
	std::map<std::string, AudioFile<double>> m_BackUps;
	static SoundEffects* sInstance;
	enum class WaveType : int { sine, triangle, rectangle, sawtooth };

	template <typename T> int sgn(T val);
	double TriangleWave(double note, double amplitude, int t);
	double SineWave(double note, double amplitude, int t);
	double SawtoothWave(double note, double amplitude, int t);
	double RectangleWave(double note, double amplitude, int t);

	double SAMPLING_FREQUENCY = 96000;


public:

	static double H3;
	static double C4		;
	static double Cis4	;
	static double D4		;
	static double Dis4	;
	static double E4		;
	static double F4		;
	static double Fis4	;
	static double G4		;
	static double Gis4	;
	static double A4		;
	static double Ais4	;
	static double H4		;
	static double C5		;
	static double Cis5	;
	static double D5		;
	static double Dis5	;
	static double E5		;
	static double F5		;
	static double Fis5	;
	static double G5		;
	static double Gis5	;
	static double A5		;
	static double Ais5	;
	static double H5		;
	static double C6		;


	SoundEffects();
	static void LoadAudioSource(const std::string& path, const std::string& name);
	static void LoadAudioSource(AudioFile<double> source, const std::string& name);
	static void SaveAudioSource(const std::string& path, const std::string& name, const std::string& savename);

	static AudioFile<double>& GetAudioFromName(const std::string& name);
	static void AddEchoEffect(const std::string& name, double delay, double attenuation, MODE mode);
	
	AudioFile<double> GenerateWave(WaveType type, double note, double length, double amplitude);
	static void ApplyEnvelope(double length, double offset, AudioFile<double>& source);
};

