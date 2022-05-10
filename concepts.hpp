#ifndef  __RQ_SOLVER_CONCEPTS
#define  __RQ_SOLVER_CONCEPTS

#include <concepts>

template<typename F, typename T>
concept has_function = requires (const T& t) {
	F::f(t, t);
};

template<typename F, typename T>
concept has_inverse = requires (const T& t) {
	F::inverse(t);
};

template<typename F>
concept has_neutral = requires {
	F::neutral;
};

template<typename F, typename T>
concept has_range_function = requires (const T& t, size_t sz) {
	F::f_range(t, sz);
};


#endif