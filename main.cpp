#define _USE_MATH_DEFINES //I didn't know this existed. Neat.

#include <iostream>
#include <cmath>
#include <string>
#include "AudioFile.h" //Uses the header file from github.com/adamstark/AudioFile
#include "audiofuncs.h"

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

    std::cout << "Running a DFT / IDFT on an audio file..." << std::endl;
    AudioFile<double> blaster;
    blaster.load("blast.wav");
    blaster.printSummary();
    cin.get();
    randomSamples(blaster);
    dftAudio(blaster);
    blaster.save("newblast.wav");


    return 0;
}

