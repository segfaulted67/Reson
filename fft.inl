namespace Reson::DSP {
	template <typename T>
	std::vector<std::complex<T>> DFT(const std::vector<std::complex<T>>& input)
	{
		auto output = input;
		foreach (i, 0, input.size()) {
			std::complex<T> sum = 0.0;
    		foreach (n, 0, input.size()) {
      			T angle = -two_pi * i * n / input.size();
      			sum += input[n] * std::complex<T>(std::cos(angle), std::sin(angle));
    		}
    		output[i] = sum;
  		}
		return output;
	}

	template <typename T>
	std::vector<std::complex<T>> Radix2(const std::vector<std::complex<T>>& input)
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
			T angle = -two_pi / len;
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
	void FFT(const std::vector<std::complex<T>>& input, std::vector<std::complex<T>>& output)
	{
		if (input.size() != output.size())
			output.resize(input.size());
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
			T angle = -two_pi / len;
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
	}

	template <typename T>
	std::vector<std::complex<T>> FFT(const std::vector<T>& input)
	{
		auto complex_input = RealToComplex(input);
		return FFT(complex_input);
	}

	template <typename T>
	std::vector<std::complex<T>> InvRadix2(const std::vector<std::complex<T>>& input)
	{
		std::vector<std::complex<T>> output(input);
		size_t size = input.size();
		assert((size & (size-1)) == 0 && "This inverse Radix2(Cooley-Tukey FFT inverse) only works for power of two");

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
			T angle = two_pi / len;
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

	template <typename T>
	void IFFT(const std::vector<std::complex<T>>& input, std::vector<std::complex<T>>& output)
	{
		if (input.size() != output.size())
			output.resize(input.size());
		size_t size = input.size();
		assert((size & (size-1)) == 0 && "This inverse Radix2 Inverse(Cooley-Tukey FFT inverse) only works for power of two");

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
			T angle = two_pi / len;
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
	}

    /* https://rocm.docs.amd.com/projects/rocFFT/en/docs-5.7.1/design/bluestein.html */
	/* https://dsp-book.narod.ru/FFTBB/0270_PDF_C13.pdf */
    template <typename T>
    std::vector<std::complex<T>> FFT(const std::vector<std::complex<T>>& input)
    {
		if (IsPowerOfTwo(input.size())) {
			return Radix2(input);
		}

        const size_t size = input.size();
        if (size == 0) return { };

        auto padded_size = ZeroPadding2(size);
        std::vector<std::complex<T>> a(padded_size);
        std::vector<std::complex<T>> b(padded_size);

        foreach (i, 0, size) {
            T angle = -pi * static_cast<T>(i) * static_cast<T>(i) / static_cast<T>(size);
            a[i] = input[i] * std::complex<T>(std::cos(angle), std::sin(angle));
        }
        foreach (i, 0, size) {
            T angle = pi * static_cast<T>(i) * static_cast<T>(i) / static_cast<T>(size);
            auto value = std::complex<T>(std::cos(angle), std::sin(angle));
            b[i] = value;

            if (i != 0) {
                b[padded_size - i] = value;
            }
        }

        auto A = Radix2(a);
        auto B = Radix2(b);
        foreach (i, 0, padded_size) {
            A[i] *= B[i];
        }
        auto c = InvRadix2(A);

        std::vector<std::complex<T>> output(size);

        foreach (i, 0, size) {
            T angle = -pi * static_cast<T>(i) * static_cast<T>(i) / static_cast<T>(size);
            auto chirp = std::complex<T>(std::cos(angle), std::sin(angle));
            output[i] = c[i] * chirp;
        }
        return output;
    }

}
