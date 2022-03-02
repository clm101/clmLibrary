#ifndef CLM_RECT_H
#define CLM_RECT_H

#include <cstdint>
#include <clmUtil/clm_system.h>
#include <utility>

namespace clm::math {
	struct Rect
	{
		std::int32_t left;
		std::int32_t top;
		std::int32_t right;
		std::int32_t bottom;

		constexpr Rect() noexcept : left(0), top(0), right(0), bottom(0) {}
		constexpr Rect(std::int32_t left,
					   std::int32_t top,
					   std::int32_t right,
					   std::int32_t bottom) noexcept
			:
			left(left), top(top), right(right), bottom(bottom)
		{}
#ifdef _WIN32
		constexpr Rect(RECT rect) noexcept
			:
			left(rect.left), top(rect.top), right(rect.right), bottom(rect.bottom)
		{}
#endif
		constexpr ~Rect() noexcept = default;
		constexpr Rect(const Rect& rhs) noexcept = default;
		constexpr Rect(Rect&& rhs) noexcept = default;
		constexpr const Rect& operator=(const Rect& rhs) noexcept
		{
			left = rhs.left; top = rhs.top;
			right = rhs.right; bottom = rhs.bottom;
			return *this;
		}
		constexpr const Rect& operator=(Rect&& rhs) noexcept
		{
			left = std::move(rhs.left);
			top = std::move(rhs.top);
			right = std::move(rhs.right);
			bottom = std::move(rhs.bottom);
			return *this;
		}
	};
	typedef Rect Rect_t;
}

#endif