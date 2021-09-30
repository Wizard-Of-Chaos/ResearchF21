#define _USE_MATH_DEFINES //I didn't know this existed. Neat.

#include <iostream>
#include <cmath>
#include <string>
#include "AudioFile.h" //Uses the header file from github.com/adamstark/AudioFile


AudioFile<double> createFreakWave()
{
    AudioFile<double> sineFile; //Can either be a double or a float
    sineFile.setNumChannels(2);
    sineFile.setNumSamplesPerChannel((44100) * 10); //10 seconds of sine wave

    const double sampleRate = 44100.0;
    const double frequencyHz = 440.0;

    for (int i = 0; i < sineFile.getNumSamplesPerChannel(); ++i) {
        for (int j = 0; j < sineFile.getNumChannels(); ++j) {

            sineFile.samples[j][i] = sin(tan((i / sampleRate) * frequencyHz * (double)2.0 * M_PI)); //Writes the sine wave across the channels
        }
    }

    return sineFile;
}

void scuff(AudioFile<double>& file) //Guaranteed to make any file sound like hot trash
{
    file.setNumSamplesPerChannel(file.getNumSamplesPerChannel() / 2);
    file.setNumChannels(1);
    file.setSampleRate(22050);
}

AudioFile<double> createRandWave()
{
    AudioFile<double> randFile;
    randFile.setNumChannels(2);
    randFile.setNumSamplesPerChannel((44100) * 10);
    const double sampleRate = 44100.0;
    const double frequencyHz = 440.0;
    for (int i = 0; i < randFile.getNumSamplesPerChannel(); ++i) {
        for (int j = 0; j < randFile.getNumChannels(); ++j) {
            randFile.samples[j][i] = rand() % (int)frequencyHz;
        }
    }
    return randFile; //I just wanted to see how this would sound
}
int main()
{
    std::cout << "Generating a freaky-sounding wave in a .wav file..." << std::endl;
    std::string path = "freak.wav";
    AudioFile<double> sine = createFreakWave();

    sine.save(path, AudioFileFormat::Wave);

    std::cout << "Generated. Loading some test audio..." << std::endl;
    AudioFile<double> loadedAudio;
    loadedAudio.load("testaudio.wav");

    std::cout << "Printing summary of info" << std::endl;
    loadedAudio.printSummary();

    scuff(loadedAudio);

    loadedAudio.printSummary();

    loadedAudio.save("scuffed.wav"); //Implicitly says it's a wav file

    AudioFile<double> randAudio = createRandWave();
    randAudio.save("rand.wav");

    return 0;
}

