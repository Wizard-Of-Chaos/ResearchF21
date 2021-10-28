#include "dftfuncs.h"

std::vector<std::complex<double>> getDFT(const std::vector<std::complex<double>> samples)
{
	std::vector<std::complex<double>> dft(samples.size());

	std::complex<double> temp(0,0);

	for (int i = 0; i < samples.size(); ++i) {
		for (int j = 0; j < samples.size(); ++j) {
			temp = std::complex<double>((double(-1 * 2 * i * j) / (double)samples.size()), 0);
			dft[i] += samples[j] * exp(IMAGINARY * PI * temp) / (double)samples.size();
		}
	}
	return dft;
}

std::vector<std::complex<double>> samplesToComplex(const std::vector<double> samples)
{
	std::vector<std::complex<double>> complex_samples;
	for (double s : samples) {
		complex_samples.push_back(std::complex<double>(s, 0));
	}
	return complex_samples;
}