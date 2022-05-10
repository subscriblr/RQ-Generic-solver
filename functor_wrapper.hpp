#ifndef  __RQ_FUNCTOR_WRAPPER
#define  __RQ_FUNCTOR_WRAPPER

#include <functional>

template <typename T, typename F>
struct functor_wrapper {	
	std::function<T(T, T)> fun;
	std::function<T(T, size_t)> fun_range;
	std::function<T(T)> inv;
	T neutral;

	functor_wrapper() = default;

	template<typename Ftype>
	functor_wrapper(Ftype f) : fun(f) {
		fun_range = [fun=fun](const T & v, size_t sz) {
			if (sz == 1) return v;
			T t = fun(v, v);
			return (sz & 1) ? fun(fun(t, t), v) : fun(t, t);
		};
	}

	template<typename Ftype>
	functor_wrapper(Ftype f, std::function<T(T)> i) : fun(f), inv(i) {}

	template<typename Ftype>
	functor_wrapper(Ftype f, std::function<T(T, size_t)> fr) : fun(f), fun_range(fr) {}


	template<typename Ftype, typename Itype>
	functor_wrapper(Ftype f, Itype i, T neu) : fun(f), inv(i), neutral(neu) {}

	template <has_neutral Fi> 
	T get_neutral()  const {
		return Fi::neutral;
	}

	template <typename Fi>
	requires (!has_neutral<Fi>)
	T get_neutral()  const {
		return neutral;
	}

	template <typename Fi, typename Ti>
	requires (has_function<Fi, Ti>)
	Ti f(const Ti& a, const Ti& b)  const {
		return Fi::f(a, b);
	}

	template <typename Fi, typename Ti>
	requires (!has_function<Fi, Ti>)
	Ti f(const Ti& a, const Ti &b)  const {
		assert(fun != nullptr);
		return fun(a, b);
	}

	template <typename Fi, typename Ti>
	requires (has_inverse<Fi, Ti>)
	Ti f_inv(const Ti & a) const {
		return Fi::inverse(a);
	}

	template <typename Fi, typename Ti>
	requires (!has_inverse<Fi, Ti>)
	Ti f_inv(const Ti & a) const {
		assert(inv != nullptr);
		return inv(a);
	}

	T substr(const T& a, const T& b) const {
		return f<F, T>(a, f_inv<F, T>(b));
	}

	template <typename Fi, typename Ti>
	requires (has_range_function<Fi, Ti>)
	Ti f_range(const Ti& a, size_t sz)  const {
		return Fi::f_range(a, sz);
	}

	template <typename Fi, typename Ti>
	requires (!has_range_function<Fi, Ti>)
	Ti f_range(const Ti& a, size_t sz) const {
		assert(fun_range != nullptr);
		return fun_range(a, sz);
	}

	template<typename Fi>
	void set_f(const Fi & f) {
		fun = f;		
	}

	template<typename Fi>
	void set_inv(const Fi & f) {
		inv = f;		
	}

	void set_neutral(const T &z) {
		neutral = z;		
	}
};

#endif