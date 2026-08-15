namespace Reson {
	namespace fft {
		template <typename T>
		std::vector<std::complex<T>> FFT(const std::vector<std::complex<T>>& input)
		{
			std::vector<std::complex<T>> output(input);
			size_t size = input.size();
			assert((size & (size-1)) == 0 && "This fft(Cooley-Tukey FFT) only works for power of two");

			for (size_t i = 1, j = 0; i < size; i++) {
				size_t bit = size >> 1;
				for (; j & bit; bit >>= 1)
					j ^= bit;
				j ^= bit;
				if (i < j) {
					std::complex<T> temp = output[i];
					output[i] = output[j];
					output[j] = temp;
				}
			}

			for (size_t len = 2; len <= size; len <<= 1) {
				double angle = -TwoPi / len;
				std::complex<T> wlen(cos(angle), sin(angle));
				for (size_t i = 0; i < size; i += len) {
					std::complex<T> w(1.0, 0.0);
					for (size_t j = 0; j < len / 2; j++) {
						std::complex<T> u = output[i + j], v = output[i + j + len / 2] * w;
						output[i + j] = u + v;
						output[i + j + len/2] = u - v;
						w = w * wlen;
					}
				}
			}
			return output;
		}

		template <typename T>
		std::vector<std::complex<T>> FFT(const std::vector<T>& input)
		{
			auto complex_input = RealToComplex(input);
			return FFT(complex_input);
		}

		template <typename T>
		std::vector<std::complex<T>> IFFT(const std::vector<std::complex<T>>& input)
		{
			std::vector<std::complex<T>> output(input);
			size_t size = input.size();
			assert((size & (size-1)) == 0 && "This inverse fft(Cooley-Tukey FFT inverse) only works for power of two");

			for (size_t i = 1, j = 0; i < size; i++) {
				size_t bit = size >> 1;
				for (; j & bit; bit >>= 1)
					j ^= bit;
				j ^= bit;
				if (i < j) {
					std::complex<T> temp = output[i];
					output[i] = output[j];
					output[j] = temp;
				}
			}

			for (size_t len = 2; len <= size; len <<= 1) {
				double angle = TwoPi / len;
				std::complex<T> wlen(cos(angle), sin(angle));
				for (size_t i = 0; i < size; i += len) {
					std::complex<T> w(1.0, 0.0);
					for (size_t j = 0; j < len / 2; j++) {
						std::complex<T> u = output[i + j], v = output[i + j + len / 2] * w;
						output[i + j] = u + v;
						output[i + j + len/2] = u - v;
						w = w * wlen;
					}
				}
			}
			for (size_t i = 0; i < size; i++) {
				output[i] /= size;
			}

			return output;
		}
	}
}