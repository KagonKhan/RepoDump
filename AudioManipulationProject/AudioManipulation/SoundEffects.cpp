#define _USE_MATH_DEFINES
#include "SoundEffects.h"
#include <sstream>

SoundEffects* SoundEffects::sInstance = nullptr;
double SoundEffects::H3 = 246.9;
double SoundEffects::C4 = 261.63;
double SoundEffects::Cis4 = 277.18;
double SoundEffects::D4 = 293.66;
double SoundEffects::Dis4 = 311.13;
double SoundEffects::E4 = 329.63;
double SoundEffects::F4 = 349.23;
double SoundEffects::Fis4 = 369.99;
double SoundEffects::G4 = 392.00;
double SoundEffects::Gis4 = 415.30;
double SoundEffects::A4 = 440.00;
double SoundEffects::Ais4 = 466.16;
double SoundEffects::H4 = 493.88;
double SoundEffects::C5 = 523.25;
double SoundEffects::Cis5 = 554.40;
double SoundEffects::D5 = 587.30;
double SoundEffects::Dis5 = 622.30;
double SoundEffects::E5 = 659.30;
double SoundEffects::F5 = 698.50;
double SoundEffects::Fis5 = 740.00;
double SoundEffects::G5 = 784.00;
double SoundEffects::Gis5 = 830.60;
double SoundEffects::A5 = 880.00;
double SoundEffects::Ais5 = 932.30;
double SoundEffects::H5 = 987.80;
double SoundEffects::C6 = 1046.5;


SoundEffects::SoundEffects() {
	assert(sInstance == nullptr);
	sInstance = this;

}

template <typename T> int SoundEffects::sgn(T val) {
    return (T(0) < val) - (val < T(0));
}
double SoundEffects::TriangleWave   (double note, double amplitude, int t) {
    double p = (sInstance->SAMPLING_FREQUENCY / note);
    return (2 * amplitude) / M_PI * asin(sin(2 * M_PI * t / p));
}
double SoundEffects::SineWave       (double note, double amplitude, int t) {
    double p = (sInstance->SAMPLING_FREQUENCY / note);
    return amplitude * sin((2 * M_PI / p) * t);
}
double SoundEffects::SawtoothWave   (double note, double amplitude, int t) {
    double p = (sInstance->SAMPLING_FREQUENCY / note);
    return 2 * (t / p - floor(t / p + 1 / 2)) - 1;
}
double SoundEffects::RectangleWave  (double note, double amplitude, int t) {
    double p = (sInstance->SAMPLING_FREQUENCY / note);
    return sgn(sin((2 * M_PI * t) / p));
}








/* TODO: ADD SAFEGUARDS REGARDING AUDIO FORMATS*/

/// <summary>
/// Read WAV file into internal storage with unique name
/// </summary>
/// <param name="path">to the file</param>
/// <param name="name"> of the file, extension required, has to be unique</param>
void SoundEffects::LoadAudioSource(const std::string& path, const std::string& name) {
    auto& audioMap = sInstance->m_Sources;
    auto pairFound = audioMap.find(name);

    if (pairFound != audioMap.end()) {
        std::cout << "[INFO] File name already exists! Adding skipped!\n";
        return;
    }
    else {
        std::cout << "[INFO] Adding " << name << "!\n";
        audioMap[name].load(path + name);

        /* TODO: Expand this, right now it's absolutely basic*/
        sInstance->m_BackUps = sInstance->m_Sources;
        return;
    }
}

void SoundEffects::LoadAudioSource(AudioFile<double> source, const std::string& name)
{
    auto& audioMap = sInstance->m_Sources;
    auto pairFound = audioMap.find(name);

    if (pairFound != audioMap.end()) {
        std::cout << "[INFO] File name already exists! Adding skipped!\n";
        return;
    }
    else {
        std::cout << "[INFO] Adding " << name << "!\n";
        audioMap[name] = source;

        /* TODO: Expand this, right now it's absolutely basic*/
        sInstance->m_BackUps = sInstance->m_Sources;
        return;
    }
}

/* TODO: ADD SAFEGUARDS REGARDING AUDIO FORMATS*/

void SoundEffects::SaveAudioSource  (const std::string& path, const std::string& name, const std::string& savename) {
    auto& audioMap = sInstance->m_Sources;
    auto pairFound = audioMap.find(name);

    if (pairFound == audioMap.end()) {
        std::cout << "[WARNING] Name not found!\n";
        return;
    }
    else {
        audioMap[name].save(path + savename);
    }
}


AudioFile<double>& SoundEffects::GetAudioFromName(const std::string& name) {
    auto& audioMap = sInstance->m_Sources;
    auto pairFound = audioMap.find(name);

    if (pairFound == audioMap.end()) {
        std::cout << "[WARNING] Name not found!\n";
        /* TODO: expand this*/
        throw std::runtime_error("NAME NOT FOUND");
    }
    else {
        return audioMap[name];
    }
}

void SoundEffects::AddEchoEffect(const std::string& name, double delay, double attenuation, MODE mode) {
    /* WORKAROUND */
    if (mode == MODE::TRIPLE) {
        SoundEffects::AddEchoEffect(name, delay, attenuation, MODE::DELAY);
        SoundEffects::AddEchoEffect(name, delay, attenuation * 0.6, MODE::DELAY);
        SoundEffects::AddEchoEffect(name, delay, attenuation * 0.6 * 0.3333333333, MODE::DELAY);
        return;
    }
    
    auto& audioMap = sInstance->m_Sources;
    auto pairFound = audioMap.find(name);

    if (pairFound == audioMap.end()) {
        std::cout << "[WARNING] Name not found!\n";
        return;
    }
    AudioFile<double>& source = audioMap[name];
    int numOfSamples = source.getNumSamplesPerChannel();
    int numOfChannels = source.getNumChannels();
    int frequency = source.getSampleRate();

    AudioFile<double>::AudioBuffer resultsBuffer;
    resultsBuffer.resize(1); resultsBuffer[0].resize(numOfSamples);

    int echoBufferSize = frequency * delay;
    std::vector<double> echoBuffer(echoBufferSize, 0);

    double currentSample = 0;

    for (int i = 0; i < numOfSamples; ++i) {
        currentSample = 0;
        for (int j = 0; j < numOfChannels; ++j) {
            currentSample += source.samples[j][i]; // [channel][sample]	
        }
        currentSample /= 2;

        //Add echo
        if (mode == MODE::DELAY) {
            double temp = currentSample;
            currentSample += echoBuffer[i % echoBufferSize];
            echoBuffer[i % echoBufferSize] = temp;
        }
        else if (mode == MODE::INFINITE) {
            currentSample += echoBuffer[i % echoBufferSize];
            echoBuffer[i % echoBufferSize] = currentSample * attenuation;
        }
        resultsBuffer[0][i] = currentSample;
    }
    if(source.setAudioBuffer(resultsBuffer))
        std::cout << "Action complete!\n";
}

AudioFile<double> SoundEffects::GenerateWave(WaveType type, double note, double length, double amplitude)
{
    AudioFile<double> output;
    output.samples.resize(1);
    output.setSampleRate(sInstance->SAMPLING_FREQUENCY);
    int numberOfSamples = length * sInstance->SAMPLING_FREQUENCY;
    output.samples[0].resize(numberOfSamples);

    for (int i = 0; i < numberOfSamples; ++i) {
        double result = 0;

        switch (type) {
        case WaveType::sine:		result = RectangleWave(note, amplitude, i);		break;
        case WaveType::triangle:	result = TriangleWave(note, amplitude, i);		break;
        case WaveType::rectangle:	result = RectangleWave(note, amplitude, i);		break;
        case WaveType::sawtooth:	result = SawtoothWave(note, amplitude, i);		break;
        }
        output.samples[0][i] = result;
    }
    return output;
}

void SoundEffects::ApplyEnvelope(double length, double offset, AudioFile<double>& source)
{
    double envelope[]{ 1,0, 1,0, 1,0, 1,0, 1,0 };

    int len = length * sInstance->SAMPLING_FREQUENCY;
    int offset_i = offset * sInstance->SAMPLING_FREQUENCY;

    /* Envelope length has to be <= length of track*/
    assert((len + offset_i) <= source.getNumSamplesPerChannel());

    int env_index = 0;
    for (int i = 0; i < len; ++i) {

        /* If in the first half */
        if (i < (len / 2)) {
            source.samples[0][i + offset_i] *= envelope[env_index];
            if (i > (env_index + 1) * len / 20)
                ++env_index;
        }
        /* If in the second half */
        else {
            source.samples[0][i + offset_i] *= (len - i) / (len / 2.0);
        }
    }
}











