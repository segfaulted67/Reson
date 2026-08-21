#pragma once

#include <cmath>
#include <complex>
#include <vector>
#include <cassert>

#include "Utils.h"

#define foreach(index_name, starting_index, ending_index)		\
	for (size_t index_name = starting_index; index_name < ending_index; index_name++)

namespace Reson::DSP {
	enum WindowFunctions {
		Rectangular,
		Hanning,
		Hamming,
		Lanczos,
		Gaussian
	};

	template <typename T>
	inline std::vector<T> ComplexToReal(const std::vector<std::complex<T>> &input)
	{
		std::vector<T> output(input.size());
		for (size_t i = 0; i < input.size(); i++) {
			output[i] = input[i].real();
		}
		return output;
	}

	template <typename T>
	inline std::vector<std::complex<T>> RealToComplex(const std::vector<T> &input)
	{
		std::vector<std::complex<T>> output(input.size());
		for (size_t i = 0; i < input.size(); i++) {
			output[i] = input[i];
		}
		return output;
	}

	template <typename T>
	inline std::vector<T> Magnitude(const std::vector<std::complex<T>>& fft)
	{
		std::vector<T> mag(fft.size());

		for (std::size_t i = 0; i < fft.size(); ++i)
			mag[i] = std::abs(fft[i]);

		return mag;
	}

	inline void Normalize(std::vector<float>& v)
	{
		if (v.empty()) return;

		float max = std::abs(v[0]);

		for (float x : v)
			max = std::max(max, std::abs(x));

		if (max <= 0.0) return;

		for (float &x : v)
			x /= max;
	}

	template <typename T>
	inline void RectangularWindow(std::vector<std::complex<T>>& samples)
	{
		for (size_t i = 0; i < samples.size(); i++) {
			samples[i] *= (T)1;
		}
	}

	template <typename T>
	inline void HanningWindow(std::vector<std::complex<T>>& samples)
	{
		if (samples.size() <= 1) return;

		for (size_t i = 0; i < samples.size(); i++) {
			T t = (T)i / (samples.size() - 1);
			T function = 0.5 * (1 - std::cos(two_pi * t));
			samples[i] *= function;
		}
	}

	template <typename T>
	inline void HammingWindow(std::vector<std::complex<T>>& samples)
	{
		if (samples.size() <= 1) return;

		for (size_t i = 0; i < samples.size(); i++) {
			T t = (T)i / (samples.size() - 1);
			T function = 0.54 - 0.46 * std::cos(two_pi * t);
			samples[i] *= function;
		}
	}

	template <typename T>
	inline void LanczosWindow(std::vector<std::complex<T>>& samples)
	{
		if (samples.size() <= 1) return;

		for (size_t i = 0; i < samples.size(); i++) {
			T t = pi * ((2 * T(i) / (samples.size() - 1)) - 1);
			T function = (t == T(0)) ? T(1) : std::sin(t) / t;
			samples[i] *= function;
		}
	}

	template <typename T>
	inline void GaussianWindow(std::vector<std::complex<T>>& samples, T sigma = (T)0.4)
	{
		if (samples.size() <= 1) return;

		const T center = (samples.size() - 1) * T(0.5);
		const T scale = sigma * center;

		for (size_t i = 0; i < samples.size(); i++) {
			T t = (i - center) / scale;
			T function = std::exp(-0.5 * t * t);
			samples[i] *= function;
		}
	}

	template <typename T>
	inline void WindowFunction(std::vector<std::complex<T>>& samples, WindowFunctions window)
	{
		switch(window) {
		case Rectangular:
			RectangularWindow(samples);
			break;
		case Hanning:
			HanningWindow(samples);
			break;
		case Hamming:
			HammingWindow(samples);
			break;
		case Lanczos:
			LanczosWindow(samples);
			break;
		case Gaussian:
			GaussianWindow(samples);
		}

	}

	template <typename T>
	inline std::vector<T> ToDb(const std::vector<T>& mag, T amp_rel = T(1))
	{
		std::vector<T> db(mag.size());

		for (size_t i = 0; i < mag.size(); i++) {
			if (mag[i] == 0.0) db[i] = T(0);
			else db[i] = T(20) * std::log10(mag[i] / amp_rel);
		}
		return db;
	}

	inline size_t BinFromIndex(size_t i, size_t size, float gamma = 0.5)
	{
		float t = (float)i / size;
		return (size_t)(std::pow(t, gamma) * (size * 0.5));
	}

	template <typename T>
	std::vector<std::complex<T>> DFT(const std::vector<std::complex<T>>& input);
	/* Iterative Cooley–Tukey FFT with Bit-Reversal: https://cp-algorithms.com/algebra/fft.html*/
	template <typename T>
	std::vector<std::complex<T>> Radix2(const std::vector<std::complex<T>>& input);
	template <typename T>
	std::vector<std::complex<T>> InvRadix2(const std::vector<std::complex<T>>& input);
	template <typename T>
	inline std::vector<std::complex<T>> FFT_Radix2(const std::vector<std::complex<T>>& input)
	{
		return Radix2(input);
	}
	template <typename T>
	inline std::vector<std::complex<T>> IFFT_Radix2(const std::vector<std::complex<T>>& input)
	{
		return InvRadix2(input);
	}
	template <typename T>
	inline std::vector<std::complex<T>> FFT_Radix2(const std::vector<std::complex<T>>& input, bool inverse)
	{
		if (inverse)	return IFFT_Radix2(input);
		else 			return FFT_Radix2(input);
	}
	/* Bluestein FFT algorithm */
	/* https://rocm.docs.amd.com/projects/rocFFT/en/docs-5.7.1/design/bluestein.html */
	/* https://dsp-book.narod.ru/FFTBB/0270_PDF_C13.pdf */
	template <typename T>
	std::vector<std::complex<T>> FFT(const std::vector<std::complex<T>>& input);
	template <typename T>
	void FFT(const std::vector<std::complex<T>>& input, std::vector<std::complex<T>>& output);
	template <typename T>
	std::vector<std::complex<T>> FFT(const std::vector<T>& input);
	template <typename T>
	std::vector<std::complex<T>> IFFT(const std::vector<std::complex<T>>& input);
	template <typename T>
	void IFFT(const std::vector<std::complex<T>>& input, std::vector<std::complex<T>>& output);
	template <typename T>
	inline std::vector<std::complex<T>> FFT(const std::vector<std::complex<T>>& input, bool inverse)
	{
		if (inverse)	return IFFT(input);
		else 	return FFT(input);
	}
}

#include "fft.inl"
