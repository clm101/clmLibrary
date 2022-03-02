#ifndef CLM_MATRIX_H
#define CLM_MATRIX_H

#include <array>
#include <initializer_list>

namespace clm::math {
	template<size_t dim, typename T> using Elements_t = std::array<std::array<T, dim>, dim>;
	template<size_t dim, typename T = float> class Matrix
	{
	public:
		constexpr Matrix() = default;
		constexpr Matrix(Elements_t<dim, T> elements) : m_elements(elements) {}
		constexpr Matrix(T(&elements)[dim][dim])
			:
			m_elements({})
		{
			for (size_t i = 0; i < dim; i++)
			{
				for (size_t j = 0; j < dim; j++)
				{
					m_elements[i][j] = elements[i][j];
				}
			}
		}

		constexpr Matrix(std::initializer_list<std::array<T, dim>> elements)
			:
			m_elements({})
		{
			std::copy(elements.begin(), elements.end(), m_elements.begin());
		}

		constexpr ~Matrix() = default;
		constexpr Matrix(const Matrix&) = default;
		constexpr Matrix(Matrix&&) = default;
		constexpr std::array<T, dim>& operator[](size_t row) noexcept
		{
			return m_elements[row];
		}
		constexpr const std::array<T, dim>& operator[](size_t row) const noexcept
		{
			return m_elements[row];
		}
		constexpr const Matrix& operator=(const Matrix& rhs)
		{
			for (size_t i = 0; i < dim; i++)
			{
				for (size_t j = 0; j < dim; j++)
				{
					m_elements[i][j] = rhs[i][j];
				}
			}
			return *this;
		}
		constexpr const Matrix& operator=(Matrix&& rhs)
		{
			m_elements = std::move(rhs.m_elements);
		}
		constexpr Matrix<dim - 1, T> get_reduced_mat(size_t removeRow, size_t removeCol) const noexcept
		{
			static_assert(dim != 0, L"Can't have matrix of dimension 0.");
			Matrix<dim - 1, T> reducedMatrix{};
			size_t iRM{};
			for (size_t i = 0; i < dim; i += 1)
			{
				if (i != removeRow)
				{
					size_t jRM{};
					for (size_t j = 0; j < dim; j += 1)
					{
						if (j != removeCol)
						{
							reducedMatrix[iRM][jRM] = m_elements[i][j];
							jRM += 1;
						}
					}
					iRM += 1;
				}
			}
			return reducedMatrix;
		}

		struct Iterator
		{
			T* ptr;
			Iterator(T* ptr) : ptr(ptr) {}
			bool operator!=(T* rhs) const noexcept { return ptr != rhs.ptr; }
			T& operator*() noexcept { return *ptr; }
			void operator++() noexcept { ptr++; }
		};
		struct ConstIterator
		{
			const T* ptr;
			ConstIterator(const T* ptr) : ptr(ptr) {}
			bool operator!=(const T* rhs) const noexcept { return ptr != rhs.ptr; }
			const T& operator*() noexcept { return *ptr; }
			void operator++() noexcept { ptr++; }
		};
		Iterator begin() { return Iterator{&m_elements[0][0]}; }
		ConstIterator begin() const { return ConstIterator{&m_elements[0][0]}; }
		Iterator end() { return Iterator{(&m_elements[dim - 1][dim - 1]) + 1}; }
		ConstIterator end() const { return ConstIterator{(&m_elements[dim - 1][dim - 1]) + 1}; }

		constexpr const Matrix& operator+(const Matrix& rhs) const noexcept
		{
			Matrix<dim, T> sumMatrix{};
			for (size_t i = 0; i < dim; i++)
			{
				for (size_t j = 0; j < dim; j++)
				{
					sumMatrix[i][j] = this->m_elements[i][j] + rhs[i][j];
				}
			}
			return sumMatrix;
		}
		constexpr Matrix operator-(const Matrix& rhs) const noexcept
		{
			Matrix<dim, T> sumMatrix{};
			for (size_t i = 0; i < dim; i++)
			{
				for (size_t j = 0; j < dim; j++)
				{
					sumMatrix[i][j] = this->m_elements[i][j] + rhs[i][j];
				}
			}
			return sumMatrix;
		}
		constexpr Matrix operator*(const Matrix& rhs) const noexcept
		{
			Matrix<dim, T> sumMatrix{};
			for (size_t i = 0; i < dim; i++)
			{
				for (size_t j = 0; j < dim; j++)
				{
					for (size_t k = 0; k < dim; k++)
					{
						sumMatrix[i][j] += (this->m_elements[i][k] * rhs[k][j]);
					}
				}
			}
			return sumMatrix;
		}
		template<typename G>
		constexpr Matrix operator*(G num) const noexcept
		{
			Matrix<T, dim> scaledMatrix{};
			for (size_t i = 0; i < dim; i++)
			{
				for (size_t j = 0; j < dim; j++)
				{
					scaledMatrix[i][j] = num * this->m_elements[i][j];
				}
			}
			return scaledMatrix;
		}
		template<typename G>
		friend constexpr Matrix operator*(G num, Matrix& rhs)
		{
			return rhs * num;
		}

		constexpr Matrix transpose() const noexcept
		{
			Matrix<dim, T> matrixTranspose{};
			for (size_t i = 0; i < dim; i++)
			{
				for (size_t j = 0; j < dim; j++)
				{
					matrixTranspose.m_elements[i][j] = m_elements[j][i];
				}
			}
			return matrixTranspose;
		}
		constexpr T determinant() const noexcept
		{
			if constexpr (dim == 2)
			{
				return (m_elements[0][0] * m_elements[1][1]) - (m_elements[0][1] * m_elements[1][0]);
			}
			else
			{
				T calculation = 0;
				for (size_t i = 0; i < dim; i++)
				{
					Matrix<dim - 1, T> reducedMatrix = get_reduced_mat(i, 0);
					calculation += (((i & 1) == 0 ? static_cast<T>(1) : static_cast<T>(-1)) * m_elements[i][0] * reducedMatrix.determinant());
				}
				return calculation;
			}
		}
	private:
		Elements_t<dim, T> m_elements;
	};
}

#endif