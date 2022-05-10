#include <span>

#include "concepts.hpp"
#include "functor_wrapper.hpp"

template<typename T, typename F>
struct prefix_sum : functor_wrapper<T, F>{
	T * sums;
	size_t size = 0;

	prefix_sum() = default;

	void init_vec(std::span<const T> a) {
		size = a.size();
		sums = new T[size + 1];
		sums[0] = functor_wrapper<T, F>:: template get_neutral<F>();
		for (int i = 0; i < size; i++) sums[i + 1] = functor_wrapper<T, F>:: template f<F, T>(sums[i], a[i]);
	}

	template<typename ...Fargs>
	prefix_sum(const T * a, size_t size_, Fargs&&...fargs) : functor_wrapper<T, F>(std::forward<Fargs>(fargs)...) {init_vec(std::span<const T>(a, size_));}
	template<typename ...Fargs>
	prefix_sum(const std::span<const T> & a, Fargs&&...fargs) : functor_wrapper<T, F>(std::forward<Fargs>(fargs)...) { init_vec(a); } 


	T get_range(size_t begin, size_t end) const {
		return functor_wrapper<T, F>::substr(sums[end], sums[begin]);
	}

	T get(size_t id) const {
		return functor_wrapper<T, F>::substr(sums[id + 1], sums[id]);
	}

	std::vector<T> to_vec() {
		std::vector<T> ret(size);
		for (int i = 0; i < size; i++) ret[i] = get(i);
		return ret;
	}

	std::string get_name() const {
		return "prefix_solver";
	}

	~prefix_sum() {
		if (sums != nullptr) delete [] sums;
	}
};