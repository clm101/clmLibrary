#ifndef CLM_GEN_MATH_H
#define CLM_GEN_MATH_H

#include <stdexcept>
#include <cstdlib>
#include <bit>
#include <numbers>
#include <concepts>

namespace clm::math {
	extern constexpr float abs(float val) noexcept
	{
		if (val >= 0.0f) {
			return val;
		}
		else {
			std::uint32_t valConv = std::bit_cast<std::uint32_t>(val);
			valConv &= 0x7FFFFFFF;
			return std::bit_cast<float>(valConv);
		}
	}

	extern constexpr double abs(double val) noexcept
	{
		if (val >= 0.0f) {
			return val;
		}
		else {
			std::uint64_t valConv = std::bit_cast<std::uint64_t>(val);
			valConv &= 0x7FFF'FFFF'FFFF'FFFF;
			return std::bit_cast<double>(valConv);
		}
	}

	static constexpr float DEFAULT_FLOAT_THRESHOLD = 0.0001f;
	static constexpr double DEFAULT_DOUBLE_THRESHOLD = 0.000001;

	extern constexpr float sqrt_ce(float val, float threshold = DEFAULT_FLOAT_THRESHOLD) noexcept;
	extern constexpr double sqrt_ce(double val, double threshold = DEFAULT_DOUBLE_THRESHOLD) noexcept;

	extern constexpr float sqrt(float val, float threshold = DEFAULT_FLOAT_THRESHOLD) noexcept
	{
		return std::is_constant_evaluated() ? sqrt_ce(val, threshold) : std::sqrtf(val);
	}

	extern constexpr double sqrt(double val, double threshold = DEFAULT_DOUBLE_THRESHOLD) noexcept
	{
		return std::is_constant_evaluated() ? sqrt_ce(val, threshold) : std::sqrt(val);
	}
	/*struct SqrtOutput
	{
		float result;
		size_t iterationCount;
	};*/

	extern constexpr float sqrt_ce(float val, float threshold) noexcept
	{
		if (val < 0.0f) {
			return NAN;
		}
		std::uint32_t valConv = std::bit_cast<std::uint32_t>(val);
		//constexpr std::uint32_t expMask = 0x7F800000u;
		std::uint32_t exp = valConv >> 23;
		exp >>= 1;
		exp += 63;

		constexpr std::uint32_t manMask = 0x007FFFFFu;
		std::uint32_t mantissa = valConv & manMask;
		mantissa = (1 << 22) | (mantissa >> 1);

		valConv = (exp << 23) | mantissa;
		float previous = std::bit_cast<float>(valConv);
		float current = previous;
		do {
			previous = val / current;
			current = 0.5f * (current + previous);
		} while (abs(current - previous) > threshold);

		return current;
	}

	/*extern constexpr float sqrt_no_priming(float val, float threshold = 0.0001f)
	{
		float previous = 0.0f;
		float current = val;

		do {
			previous = val / current;
			current = 0.5f * (current + previous);
		} while (abs(current - previous) > threshold);

		return current;
	}*/

	static constexpr double NaN = std::numeric_limits<double>::quiet_NaN();
	extern constexpr double sqrt_ce(double val, double threshold) noexcept
	{
		if (val < 0.0f) {
			return NaN;
		}
		std::uint64_t valConv = std::bit_cast<std::uint64_t>(val);
		//std::uint64_t expMask = 0x7FF0'0000'0000'0000u;
		std::uint64_t exp = valConv >> 52;
		exp >>= 1;
		exp += 511;

		std::uint64_t manMask = 0x000F'FFFF'FFFF'FFFFu;
		std::uint64_t mantissa = valConv & manMask;
		mantissa = (1ull << 51) | (mantissa >> 1);

		valConv = (exp << 52) | mantissa;
		double previous = std::bit_cast<double>(valConv);
		double current = previous;
		do {
			previous = val / current;
			current = 0.5 * (current + previous);
		} while (abs(current - previous) > threshold);

		return current;
	}

	template<std::floating_point T>
	extern constexpr T degrees_to_radians(T degrees) noexcept
	{
		return degrees * std::numbers::pi_v<T> / static_cast<T>(180);
	}

	template<typename T>
	extern constexpr T clamp(T x, T min, T max) noexcept
	{
		if (x < min) {
			return min;
		}
		else if (x > max) {
			return max;
		}
		else {
			return x;
		}
	}

	constexpr std::uint32_t lzcnt_ce(std::uint32_t val) noexcept;
	constexpr std::uint32_t lzcnt(std::uint32_t val) noexcept
	{
		return std::is_constant_evaluated() ? lzcnt_ce(val) : __lzcnt(val);
	}

	constexpr std::uint32_t lzcnt_ce(std::uint32_t val) noexcept
	{
		std::uint32_t count = 0u;
		while (val != 0) {
			val >>= 1;
			count++;
		}
		return 32u - count;
	}
}

#endif