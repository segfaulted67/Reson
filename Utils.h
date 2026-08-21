#pragma once

#include <iostream>
#include <cstdlib>

namespace Reson {
	inline constexpr auto pi = 3.14159265358979323846264338327950288419716939937510;
	inline constexpr auto tau = 6.28318530717958647692528676655900576839433879875021;
    inline constexpr auto two_pi = tau;
	inline constexpr auto half_pi = 1.57079632679489661923132169163975144;
	inline constexpr auto quarter_pi = 0.785398163397448309615660845819875721;
	inline constexpr auto inv_pi = 0.318309886183790671537767526745028724;
	inline constexpr auto two_over_pi = 0.636619772367581343075535053490057448;
	inline constexpr auto two_over_sqrt_pi = 1.12837916709551257389615890312154517;
	inline constexpr auto e = 2.718281828459045235360287471352662497757247093699959574966967627724076630353547594571382178525166427427466;
	inline constexpr auto log2e = 1.44269504088896340735992468100189214;
	inline constexpr auto log10e = 0.434294481903251827651128918916605082;
	inline constexpr auto ln2 = 0.693147180559945309417232121458176568;
	inline constexpr auto ln10 = 2.30258509299404568401799145468436421;
	inline constexpr auto sqrt2 = 1.41421356237309504880168872420969808;
	inline constexpr auto inv_sqrt2 = 0.707106781186547524400844362104849039;

	inline constexpr auto epsilon = 1e-6;

	template <typename T>
	inline constexpr bool IsPowerOfTwo(const T N)
	{
		return (N > 0) && ((N & (N - 1)) == 0);
	}

	inline constexpr size_t ZeroPadding2(const size_t N)
	{
		size_t M = 1;
		while (M < 2 * N - 1) {
			M <<= 1;
		}
		return M;
	}

	// template <typename T>
	// inline constexpr bool IsPowerOfTwo(T x)
	// {
	// 	auto temp = static_cast<int32_t>(x);
	// 	return temp != 0 && !(temp & (temp - 1));
	// }

	template <typename T>
	inline constexpr T Max(T a, T b)
	{
		return a > b ? a : b;
	}

	template <typename T>
	inline constexpr T Delta(T a, T b)
	{
		return std::abs(a - b);
	}
}
