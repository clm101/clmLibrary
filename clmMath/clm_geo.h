#ifndef CLM_GEO_H
#define CLM_GEO_H

#include <concepts>

#include "clm_vector.h"
#include "clm_gen_math.h"

namespace clm::math {
	template<std::floating_point T>
	constexpr bool lines_intersect(const Point2<T>& a1, 
								   const Point2<T>& a2, 
								   const Point2<T>& b1, 
								   const Point2<T>& b2)
	{
		T Lax = a2[0] - a1[0];
		T Lay = a2[1] - a1[1];
		T Lbx = b2[0] - b1[0];
		T Lby = b2[1] - b1[1];

		T A = Lby - (Lay * Lbx) / Lby;
		T B = a1[1] - b1[1] + (Lay / Lby) * (b1[0] - a1[0]);

		
		// Consider using a different condition
		if (A == static_cast<T>(0))
		{
			return false;
		}

		T result = B / A;
		return (result >= static_cast<T>(0) &&
				result <= static_cast<T>(1));
	}

	template<std::floating_point T>
	constexpr T distance(T x1, T y1, T x2, T y2)
	{
		return math::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	}
}

#endif