#include "audiofuncs.h"
#include <iostream>

using namespace std;

//DFT functions -- these will take in a vector of samples from an audio file and apply a DFT / IDFT to them.
vector<complex<double>> getDFT(vector<double> samples)
{
	fftw_complex* in, * out;
	fftw_plan p;
	in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * samples.size());
	out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * samples.size());
	p = fftw_plan_dft_1d(samples.size(), in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	for (int i = 0; i < samples.size(); ++i) {
		in[i][0] = samples[i];
		in[i][1] = 0;
	} //loads array with samples
	fftw_execute(p);

	fftw_destroy_plan(p);
	fftw_free(in);
	vector<complex<double>> retval;
	for (int i = 0; i < samples.size(); ++i) {
		complex<double> temp(out[i][0], out[i][1]);
		retval.push_back(temp);
	}
	fftw_free(out);
	return retval;
}

vector<double> getIDFT(vector<complex<double>> samples)
{
	fftw_complex* in, * out;
	fftw_plan p;
	in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * samples.size());
	out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * samples.size());
	p = fftw_plan_dft_1d(samples.size(), in, out, FFTW_BACKWARD, FFTW_ESTIMATE);
	for (int i = 0; i < samples.size(); ++i) {
		in[i][0] = samples[i].real();
		in[i][1] = samples[i].imag();
	}

	fftw_execute(p);
	fftw_destroy_plan(p);
	fftw_free(in);
	vector<double> retval;
	for (int i = 0; i < samples.size(); ++i) {
		retval.push_back(out[i][0]);
	}
	return retval;
}
//The IDFT just uses FFTW_BACKWARD as the identifier.

//Some functions to generate / mess with test audio
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

void dftAudio(AudioFile<double>& file)
{
	std::cout << "Running DFT - this may take awhile" << std::endl;
	std::vector<std::complex<double>> dftsamples = getDFT(file.samples[0]);
	std::cout << "Acquired DFT from audio file. Probably. Putting them back now--" << std::endl;
	file.samples[0] = getIDFT(dftsamples);
	std::cout << "Replaced." << std::endl;
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

//Random functions for normal distribution and other distributions

vector<pair<int, double>> randomSamples(AudioFile<double> file)
{
	int numsamples = file.getNumSamplesPerChannel();
	vector<pair<int, double>> ret;
	default_random_engine gen;
	binomial_distribution<int> distribution(numsamples/2, .5);
	for (int i = 0; i < numsamples / 5; ++i) {
		pair<int, double> temp;
		int rando = distribution(gen);
		temp.first = rando;
		temp.second = file.samples[0][rando];
		ret.push_back(temp);
		cout << "Grabbing sample at " << rando << ", value " << file.samples[0][rando] << endl;
	}
	return ret;
}