#include <span>

#include "concepts.hpp"
#include "functor_wrapper.hpp"

template<typename T, typename F>
struct fenwik : functor_wrapper<T, F>{
	T * sums;
	size_t size = 0;

	fenwik() = default;

	void init_vec(std::span<const T> a) {
		size = a.size();
		sums = new T[size];
		for (int i = 0; i < size; i++) sums[i] = a[i];
		for (int i = 0; i < size; i++) {
			int next = i | (i + 1);
			sums[next] = functor_wrapper<T, F>:: template f<F, T>(sums[i], sums[next]);
		}
	}

	template<typename ...Fargs>
	fenwik(const T * a, size_t size_, Fargs&&...fargs) : functor_wrapper<T, F>(std::forward<Fargs>(fargs)...) {init_vec(std::span<const T>(a, size_));}
	template<typename ...Fargs>
	fenwik(const std::span<const T> & a, Fargs&&...fargs) : functor_wrapper<T, F>(std::forward<Fargs>(fargs)...) { init_vec(a); } 

	T get_prefix(int id) const {
		T res = functor_wrapper<T, F>:: template get_neutral<F>();
		while (id >= 0) {
			res = functor_wrapper<T, F>:: template f<F, T>(res, sums[id]);
			id = (id & (id + 1)) - 1;
		}
		return res;
	}

	T get_range(int begin, int end) const {
		return functor_wrapper<T, F>::substr(get_prefix(end - 1), get_prefix(begin - 1));
	}

	T get(int id) const {
		return functor_wrapper<T, F>::substr(get_prefix(id), get_prefix(id - 1));
	}

	void add(int id, const T & val) {
		while (id < size) {
			sums[id] = functor_wrapper<T, F>:: template f<F, T>(sums[id], val);
			id |= id + 1;
		}
	}

	void set(int id, const T & val) {
		auto change = functor_wrapper<T, F>::substr(val, get(id));
		add(id, change);
	}

	std::vector<T> to_vec() {
		std::vector<T> ret(size);
		for (int i = 0; i < size; i++) ret[i] = get(i);
		return ret;
	}

	std::string get_name() const {
		return "fenwik_solver";
	}

	~fenwik() {
		if (sums != nullptr) delete [] sums;
	}
};