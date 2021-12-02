#pragma once //Visual studio added this, and I have no idea what it means, but I fear it.

#define _USE_MATH_DEFINES
#include <utility>
#include <math.h>
#include <complex>
#include <vector>
#include <fftw3.h>
#include <random>
#include "AudioFile.h"


#ifndef AUDIOFUNCS_H
#define AUDIOFUNCS_H

using namespace std;

const complex<double> PI(M_PI, 0);//PI
const complex<double> IMAGINARY(0, 1); //i

vector<complex<double>> getDFT(const std::vector<double> samples);
vector<double> getIDFT(const std::vector<std::complex<double>> samples);

AudioFile<double> createFreakWave();
void scuff(AudioFile<double>& file);
void dftAudio(AudioFile<double>& file);
AudioFile<double> createRandWave();

vector<pair<int, double>> randomSamples(AudioFile<double> file);
#endif