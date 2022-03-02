#ifndef CLM_CONCEPTS_EXT_H
#define CLM_CONCEPTS_EXT_H

#include <concepts>

namespace clm::util {
	template<typename S, typename T> concept not_same_as = !std::same_as<S, T>;
	template<typename T, typename...Ts>
	concept all_same = std::conjunction_v<std::is_same<T, Ts>...>;
}

#endif