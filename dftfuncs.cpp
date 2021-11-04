#include "dftfuncs.h"
#include <iostream>

using namespace std;

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