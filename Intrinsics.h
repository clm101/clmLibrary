#ifndef INTRINSICS_H
#define INTRINSICS_H
#include <intrin.h>
#include <array>

namespace clm::util::math::intrin {
	template<__m128(*oper)(__m128, __m128)>
	std::array<float, 4> vec_4_float_oper(float lhs0 = 0.0f, float rhs0 = 0.0f,
										  float lhs1 = 0.0f, float rhs1 = 0.0f,
										  float lhs2 = 0.0f, float rhs2 = 0.0f,
										  float lhs3 = 0.0f, float rhs3 = 0.0f) noexcept
	{
		__m128 lhsVec = _mm_set_ps(lhs0, lhs1, lhs2, lhs3);
		__m128 rhsVec = _mm_set_ps(rhs0, rhs1, rhs2, rhs3);
		__m128 operOut = oper(lhsVec, rhsVec);
		float out[4];
		_mm_store_ps(out, operOut);
		return std::to_array(out);
	}

	template<__m128d(*oper)(__m128d, __m128d)>
	std::array<double, 2> vec_2_double_oper(double lhs0 = 0.0, double rhs0 = 0.0,
											double lhs1 = 0.0, double rhs1 = 0.0) noexcept
	{
		__m128d lhs = _mm_set_pd(lhs0, lhs1);
		__m128d rhs = _mm_set_pd(rhs0, rhs1);
		__m128d operOut = oper(lhs, rhs);
		double out[2];
		_mm_store_pd(out, operOut);
		return std::to_array(out);
	}

	template<__m256d(*oper)(__m256d, __m256d)>
	std::array<double, 4> vec_4_double_oper(double lhs0 = 0.0, double rhs0 = 0.0,
											double lhs1 = 0.0, double rhs1 = 0.0,
											double lhs2 = 0.0, double rhs2 = 0.0,
											double lhs3 = 0.0, double rhs3 = 0.0) noexcept
	{
		__m256d lhs = _mm256_set_pd(lhs0, lhs1, lhs2, lhs3);
		__m256d rhs = _mm256_set_pd(rhs0, rhs1, rhs2, rhs3);
		__m256d operOut = oper(lhs, rhs);
		double out[4];
		_mm256_store_pd(out, operOut);
		return std::to_array(out);
	}

	inline __m128 add_floats(__m128 a, __m128 b) noexcept
	{
		return _mm_add_ps(a, b);
	}

	inline __m128d add_doubles(__m128d a, __m128d b) noexcept
	{
		return _mm_add_pd(a, b);
	}

	inline __m256d add_doubles(__m256d a, __m256d b) noexcept
	{
		return _mm256_add_pd(a, b);
	}

	inline __m128 sub_floats(__m128 a, __m128 b) noexcept
	{
		return _mm_sub_ps(a, b);
	}
}
#endif