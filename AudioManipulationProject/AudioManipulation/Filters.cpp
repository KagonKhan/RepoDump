#include <iostream>
#include <vector>
#include <fstream>
#include "AudioFile.h"

/* Number of filter constants (odd)*/
const int M = 21;

/* Steep filter, high cut-off */
double filterConstantsV2[]{
 -0.000155, -0.000388, -0.000547, -0.000398, 0.000221, 0.001218, 0.002161, 0.002380, 0.001288,
 -0.001191, -0.004323, -0.006627, -0.006413, -0.002662, 0.004129, 0.011617, 0.016157, 0.014216,
 0.004218, -0.011981, -0.028759, -0.038005, -0.031772, -0.005464, 0.039701, 0.096042, 0.151104,
 0.191245,

 0.205941,

 0.191245,
 0.151104, 0.096042, 0.039701, -0.005464, -0.031772, -0.038005, -0.028759, -0.011981, 0.004218,
 0.014216, 0.016157, 0.011617, 0.004129, -0.002662, -0.006413, -0.006627, -0.004323, -0.001191,
 0.001288, 0.002380, 0.002161, 0.001218, 0.000221, -0.000398, -0.000547, -0.000388, -0.000155
};

/* Steep filter, low cut-off */
double filterConstants[]{
	-0.000013, -0.000058, -0.000144, -0.000256, -0.000345, -0.000327, -0.000099, 0.000422, 0.001249, 0.002272,
	0.003227, 0.003711, 0.003257, 0.001462, -0.001845, -0.006435, -0.011579, -0.016047, -0.018243, -0.016481, -0.009349, 0.003909,

	0.023080, 0.046841, 0.072840, 0.098003, 0.119038, 0.133015,
	0.137914,
	0.133015, 0.119038, 0.098003, 0.072840, 0.046841, 0.023080,

	0.003909, -0.009349, -0.016481, -0.018243, -0.016047, -0.011579, -0.006435, -0.001845, 0.001462, 0.003257, 0.003711, 0.003227,
	0.002272, 0.001249, 0.000422, -0.000099, -0.000327, -0.000345, -0.000256, -0.000144, -0.000058,	-0.000013
};

/* Gentle filter, high cut-off*/
double smallFilter[]{
	0.000003, -0.000107, -0.000990, -0.003402, -0.005863, -0.001761, 0.019603, 0.065069, 0.127383, 0.183312,
	
	0.205941,
	
	0.183312, 0.127383, 0.065069, 0.019603, -0.001761, -0.005863, -0.003402, -0.000990, -0.000107, 0.000003
};

/* Hold last sample */
double delayLine[M]{ 0 };

enum class FilterType : int {LPF, HPF, BPF};

void ApplyLPF(AudioFile<double>::AudioBuffer& input, AudioFile<double>::AudioBuffer& output, int numOfSamples ) {

	for (int i = 0; i < numOfSamples; ++i) {
		double currentSample = input[0][i];

		for (int j = M - 2; j >= 0; j--)
			delayLine[j + 1] = delayLine[j];
		delayLine[0] = currentSample;


		double result = 0;
		for (int j = 0; j < M; j++)
			result = result + delayLine[j] * smallFilter[j];

		output[0][i] = result;
	}
}

void ApplyHPF(AudioFile<double>::AudioBuffer& input, AudioFile<double>::AudioBuffer& output, int numOfSamples ) {

	for (int i = 0; i < numOfSamples; ++i) {
		double currentSample = input[0][i];

		for (int j = M - 2; j >= 0; j--)
			delayLine[j + 1] = delayLine[j];
		delayLine[0] = currentSample;

		double result = 0;
		for (int j = 0; j < M; j++)	{
			if (j == M / 2) {
				result = result + delayLine[j] * (-1) * (smallFilter[j] - 1);
				continue;
			}
			result = result + delayLine[j] * (-1) * smallFilter[j];
		}

		output[0][i] = result;
	}
}

void ProcessData(AudioFile<double>& input, AudioFile<double>& output, FilterType filterType) 
{

	output.setSampleRate(input.getSampleRate());

	int numSamples = input.getNumSamplesPerChannel();
	int numChannel = input.getNumChannels();

	AudioFile<double>::AudioBuffer Output;
		Output.resize(1);
		Output[0].resize(numSamples);

	/* Merge Channels */
	for (int i = 0; i < numSamples; ++i) {
		double currentSample = 0;

		for (int j = 0; j < numChannel; ++j)
			currentSample += input.samples[j][i]; // [channel][sample]	

		if (numChannel > 1)
			currentSample /= 2;

		input.samples[0][i] = currentSample;
	}

	switch (filterType) {
		case FilterType::LPF:

			ApplyLPF(input.samples, Output, numSamples);
			if(output.setAudioBuffer(Output))
					output.save("output_LPF.wav"); 

			break;


		case FilterType::HPF:

			ApplyHPF(input.samples, Output, numSamples);
			if (output.setAudioBuffer(Output))
				output.save("output_HPF.wav"); 

			break;


		case FilterType::BPF:
			ApplyLPF(input.samples, Output, numSamples);
			ApplyHPF(Output, Output, numSamples);

			if (output.setAudioBuffer(Output))
				output.save("output_BPF.wav");

			break;

		default: break;
	}

}

int main() {
	AudioFile<double> audioFile, output;
	audioFile.load("input.wav");
	audioFile.printSummary();

	//ProcessData(audioFile, output, FilterType::LPF);
	//ProcessData(audioFile, output, FilterType::HPF);
	ProcessData(audioFile, output, FilterType::BPF);
	
	return 0;
}