#pragma once //Visual studio added this, and I have no idea what it means, but I fear it.

#define _USE_MATH_DEFINES
#include <math.h>
#include <complex>
#include <vector>

#ifndef DFTFUNCS_H
#define DFTFUNCS_H



const std::complex<double> PI(M_PI, 0);//PI
const std::complex<double> IMAGINARY(0, 1); //i

std::vector<std::complex<double>> getDFT(const std::vector<std::complex<double>> samples);
std::vector<std::complex<double>> samplesToComplex(const std::vector<double> samples);
#endif