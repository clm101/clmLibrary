#ifndef CLM_VECTOR_H
#define CLM_VECTOR_H

#include <array>
#include <concepts>
#include <algorithm>
#include <utility>
#include <cmath>
#include "clm_gen_math.h"

template<typename T, typename...Ts>
struct base_type
{
	static T value;
};

template<typename T>
concept valid_vec_type = std::floating_point<T> || std::integral<T>;

namespace clm::math {
	template<valid_vec_type T, size_t dim>
	class Vector
	{
	public:
		constexpr Vector() noexcept
			:
			elems({})
		{}
		template<valid_vec_type...Ts>
		constexpr Vector(Ts...vals)
			:
			elems({static_cast<T>(vals)...})
		{}

		constexpr ~Vector() noexcept = default;

		constexpr Vector(const Vector<T, dim>& rhs)
			:
			Vector()
		{
			std::copy(rhs.elems.begin(), rhs.elems.end(), elems.begin());
		}

		constexpr Vector(Vector&& rhs) noexcept
		{
			elems = std::move(rhs.elems);
		}

		constexpr const Vector& operator=(const Vector& rhs) noexcept
		{
			std::copy(rhs.elems.begin(), rhs.elems.end(), elems.begin());
			return *this;
		}

		constexpr const Vector& operator=(Vector&& rhs) noexcept
		{
			elems = std::move(rhs.elems);
			return *this;
		}

		template<valid_vec_type U> requires std::convertible_to<T, U>
		constexpr explicit operator Vector<U, dim>() const noexcept
		{
			Vector<U, dim> ret{};
			for (size_t i = 0; i < dim; i++)
			{
				ret[i] = static_cast<U>((*this)[i]);
			}
			return ret;
		}

		template<typename U> requires(U::U(T{}))
			constexpr explicit operator U() const noexcept
		{
			return {*this};
		}

		constexpr const T& operator[](size_t pos) const
		{
			return elems[pos];
		}
		constexpr T& operator[](size_t pos)
		{
			return elems[pos];
		}

		constexpr Vector<T, dim> operator+(const Vector<T, dim>& rhs) const noexcept
		{
			Vector<T, dim> sum{};
			auto& lhs = *this;
			for (size_t i = 0; i < dim; i++)
			{
				sum[i] = lhs[i] + rhs[i];
			}
			return sum;
		}

		constexpr Vector operator-(const Vector& rhs) const noexcept
		{
			Vector diff{};
			auto& lhs = *this;
			for (size_t i = 0; i < dim; i++)
			{
				diff[i] = lhs[i] - rhs[i];
			}
			return diff;
		}

		template<valid_vec_type U>
		constexpr Vector operator*(U rhs) const noexcept
		{
			T rhsT = static_cast<T>(rhs);
			Vector product{};
			auto& lhs = *this;
			for (size_t i = 0; i < dim; i++)
			{
				product[i] = lhs[i] * rhsT;
			}
			return product;
		}

		template<valid_vec_type U>
		constexpr Vector operator/(U rhs) const noexcept
		{
			T rhsT = static_cast<T>(rhs);
			Vector product{};
			auto& lhs = *this;
			for (size_t i = 0; i < dim; i++)
			{
				product[i] = lhs[i] / rhsT;
			}
			return product;
		}

		constexpr bool operator==(const Vector& rhs) const noexcept
		{
			const Vector& lhs = *this;
			for (size_t i = 0; i < dim; i++)
			{
				if constexpr (std::is_floating_point_v<T>)
				{
					constexpr T threshold = static_cast<T>(0.0001);
					if (math::abs(lhs[i] - rhs[i]) < threshold)
					{
						return false;
					}
				}
				else
				{
					if (lhs[i] != rhs[i])
					{
						return false;
					}
				}
			}
			return true;
		}

		constexpr bool operator !=(const Vector& rhs) const noexcept
		{
			return !operator==(rhs);
		}

		template<valid_vec_type U> requires std::convertible_to<U, T>
		friend constexpr Vector operator*(U lhs, const Vector& rhs) noexcept
		{
			return rhs * static_cast<T>(lhs);
		}

		constexpr Vector operator-() const noexcept
		{
			const Vector& rhs = *this;
			return {-1 * rhs};
		}

		constexpr const Vector& operator+=(const Vector& rhs) noexcept
		{
			Vector& lhs = *this;
			for (size_t i = 0; i < dim; i++)
			{
				lhs[i] += rhs[i];
			}
			return lhs;
		}

		constexpr const Vector& operator-=(const Vector& rhs) noexcept
		{
			Vector& lhs = *this;
			for (size_t i = 0; i < dim; i++)
			{
				lhs[i] -= rhs[i];
			}
			return lhs;
		}

		template<valid_vec_type U>
		constexpr const Vector& operator*=(const U rhs) noexcept
		{
			Vector& lhs = *this;
			for (size_t i = 0; i < dim; i++)
			{
				lhs[i] *= static_cast<T>(rhs);
			}
			return lhs;
		}

		template<valid_vec_type U>
		constexpr const Vector& operator/=(const U rhs) noexcept
		{
			Vector& lhs = *this;
			for (size_t i = 0; i < dim; i++)
			{
				lhs[i] /= static_cast<T>(rhs);
			}
			return lhs;
		}

		constexpr T length_squared() const noexcept
		{
			T quadraticSum{};
			for (size_t i = 0; i < dim; i++)
			{
				quadraticSum += (elems[i] * elems[i]);
			}
			return quadraticSum;
		}

		constexpr float length() const noexcept requires std::integral<T>
		{
			return clm::math::sqrt(static_cast<float>(length_squared()));
		}

		constexpr T length() const noexcept requires std::floating_point<T>
		{
			return clm::math::sqrt(length_squared());
		}
	protected:
		std::array<T, dim> elems;
	};

	template<valid_vec_type...Ts>
	Vector(Ts...)->Vector<decltype(base_type<Ts...>::value), sizeof...(Ts)>;

	template<valid_vec_type T>
	using Vec2 = Vector<T, 2>;
	using Vec2f = Vector<float, 2>;
	using Vec2d = Vector<double, 2>;
	template<valid_vec_type T>
	using Vec3 = Vector<T, 3>;
	using Vec3f = Vector<float, 3>;
	using Vec3d = Vector<double, 3>;

	template<valid_vec_type T, size_t dim>
	using Point = Vector<T, dim>;
	template<valid_vec_type T>
	using Point2 = Vector<T, 2>;
	using Point2f = Vector<float, 2>;
	using Point2d = Vector<double, 2>;
	template<valid_vec_type T>
	using Point3 = Vector<T, 3>;
	using Point3f = Vector<float, 3>;
	using Point3d = Vector<double, 3>;

	template<valid_vec_type T, size_t dim>
	extern inline Point<T, dim> midpoint(const Point<T, dim>& p1, const Point<T, dim>& p2)
	{
		return {(p1[0] + p2[0]) / 2, (p1[1] + p2[1]) / 2};
	}

	template<valid_vec_type T, size_t dim>
	constexpr T dot(const Vector<T, dim>& lhs, const Vector<T, dim>& rhs) noexcept
	{
		T dotProduct{};
		for (size_t i = 0; i < dim; i++)
		{
			dotProduct += (lhs[i] * rhs[i]);
		}
		return dotProduct;
	}

	//template<valid_vec_type T, size_t dim>
	//constexpr Vector<T, dim> cross(const Vector<T, dim>& lhs, const Vector<T, dim>& rhs)
	//{
	//	static_assert(false, "Requires specialization.");
	//	//return Vector<T, dim>{};
	//}

	template<valid_vec_type T>
	constexpr Vector<T, 3> cross(const Vector<T, 3>& lhs, const Vector<T, 3>& rhs) noexcept
	{
		return Vector<T, 3>{lhs[1] * rhs[2] - lhs[2] * rhs[1],
			lhs[0] * rhs[2] - lhs[2] * rhs[0],
			lhs[0] * rhs[1] - lhs[1] * rhs[0]};
	}

	template<std::integral T, size_t dim>
	constexpr Vector<float, dim> unit_vector(const Vector<T, dim>& vec) noexcept
	{
		return static_cast<Vector<float, dim>>(vec) / vec.length();
	}

	template<std::floating_point T, size_t dim>
	constexpr Vector<T, dim> unit_vector(const Vector<T, dim>& vec) noexcept
	{
		return vec / vec.length();
	}
}

#endif