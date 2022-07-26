#ifndef CLM_ARRAY_H
#define CLM_ARRAY_H

#include <cassert>

template<typename T, size_t Size>
class array_t {
public:
	constexpr array_t() = default;
	constexpr array_t(const T(&lhs)[Size]) noexcept
	{
		for (size_t i = 0; i < Size; i += 1)
		{
			m_data[i] = lhs[i];
		}
	}
	constexpr array_t(const array_t&) = default;
	constexpr ~array_t() = default;

	template<typename Self>
	constexpr auto& operator[](this Self&& self, size_t index)
	{
		if (!std::is_constant_evaluated())
		{
			assert(index < Size);
		}
		return self.m_data[index];
	}

	constexpr const T& front() const noexcept
	{
		return m_data[0];
	}

	constexpr const T& back() const noexcept
	{
		return m_data[Size - 1];
	}

	constexpr const T* data() const noexcept
	{
		return m_data;
	}

	constexpr bool empty() const noexcept
	{
		return Size == 0;
	}

	constexpr size_t size() const noexcept
	{
		return Size;
	}
private:
	T m_data[Size]{};
};

#endif