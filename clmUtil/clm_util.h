#ifndef CLM_UTIL_H
#define CLM_UTIL_H

/*

This file contains a random assortment of useful utility functions with no reason to be in their own file

*/

#include <string>
#include <exception>
#include <concepts>

#include <clm_concepts_ext.h>

namespace clm::util {
#ifdef _DEBUG
	extern constexpr bool release = false;
#else
	extern constexpr bool release = true;
#endif

	extern inline bool compare(const std::string& str1, const std::string& str2)
	{
		return str1.compare(str2) == 0;
	}

	template<util::all_same<bool>...Bs>
	inline bool disjunction(Bs...conditions)
	{
		return (conditions || ...);
	}
	template<util::all_same<bool>...Bs>
	inline bool conjunction(Bs...conditions)
	{
		return (conditions && ...);
	}
}

#endif