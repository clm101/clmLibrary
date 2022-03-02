#ifndef CLM_COLOR_H
#define CLM_COLOR_H

#include <math/clm_vector.h>

namespace clm::color {
	template<typename T, size_t dim>
	concept valid_color_type = valid_vec_type<T> && (dim == 3 || dim == 4);

	template<valid_vec_type T>
	struct Color3 : public math::Vector<T, 3>
	{
		Color3()
			:
			math::Vector<T, 3>(), r(this->elems[0]), g(this->elems[1]), b(this->elems[2])
		{}
		Color3(T r, T g, T b)
			:
			math::Vector<T, 3>(r, g, b), r(this->elems[0]), g(this->elems[1]), b(this->elems[2])
		{}
		Color3(const math::Vector<T, 3>& vec)
			:
			math::Vector<T, 3>(vec), r(this->elems[0]), g(this->elems[1]), b(this->elems[2])
		{}

		T& r;
		T& g;
		T& b;
	};
	using Color3f = Color3<float>;
	using Color3d = Color3<double>;

	template<valid_vec_type T>
	struct Color4 : public math::Vector<T, 4>
	{
		Color4()
			:
			math::Vector<T, 4>(), r(this->elems[0]), g(this->elems[1]), b(this->elems[2]), a(this->elems[3])
		{}
		Color4(T r, T g, T b, T a)
			:
			math::Vector<T, 4>(r, g, b, a), r(this->elems[0]), g(this->elems[1]), b(this->elems[2]), a(this->elems[3])
		{}
		Color4(const math::Vector<T, 4>& vec)
			:
			math::Vector<T, 4>(vec), r(this->elems[0]), g(this->elems[1]), b(this->elems[2]), a(this->elems[3])
		{}

		T& r;
		T& g;
		T& b;
		T& a;
	};
	using Color4f = Color4<float>;
	using Color4d = Color4<double>;
}

#endif