#pragma once

#include <cmath>
#include <complex>
#include <vector>
#include <cassert>

#include "Utils.h"

namespace Reson {
	namespace fft {
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
			float max = v[0];

			for (float x : v)
				max = std::max(max, x);

			if (max <= 0.0) return;

			for (float &x : v)
				x /= max;
		}

		template <typename T>
		inline void HannWindow(std::vector<std::complex<T>>& samples)
		{
			for (size_t i = 0; i < samples.size(); i++) {
				double t = (double)i / (samples.size() - 1);
				double hann = 0.5 * (1 - cos(TwoPi * t));
				samples[i] *= hann;
			}
		}

		template <typename T>
		inline std::vector<T> ToDb(const std::vector<T>& mag, size_t amp_rel = 32767)
		{
			std::vector<T> db(mag.size());

			for (size_t i = 0; i < mag.size(); i++) {
				db[i] = 20 * std::log10(mag[i] / amp_rel);
			}
			return db;
		}

		inline size_t BinFromIndex(size_t i, size_t size, float gamma = 0.5)
		{
			float t = (float)i / size;
			return (size_t)(std::pow(t, gamma) * (size * 0.5));
		}

		/* Iterative Cooley–Tukey FFT with Bit-Reversal: https://cp-algorithms.com/algebra/fft.html*/
		template <typename T>
		std::vector<std::complex<T>> FFT(const std::vector<std::complex<T>>& input);
		template <typename T>
		std::vector<std::complex<T>> FFT(const std::vector<T>& input);
		template <typename T>
		std::vector<std::complex<T>> IFFT(const std::vector<std::complex<T>>& input);
	}
}

#include "fft.inl"
