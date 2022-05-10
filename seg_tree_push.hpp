#include <span>

#include "concepts.hpp"
#include "functor_wrapper.hpp"

template<typename T, typename F>
struct seg_tree_push : functor_wrapper<T, F>{
	std::vector<T> sums;
	std::vector<T> del;
	std::vector<bool> has_del;
	size_t size = 0;

	seg_tree_push() = default;

	void build(int x, int l, int r, std::span<const T> a) {
		has_del[x] = false;
		if (l == r) {
			sums[x] = a[l];
			return;
		}
		int y = (l + r) >> 1;
		int z = x + ((y - l + 1) << 1);
		build(x + 1, l, y, a);
		build(z, y + 1, r, a);
		sums[x] = functor_wrapper<T, F>:: template f<F, T>(sums[x + 1], sums[z]);
	}

	void push(int x, int l, int r) {
		if (!has_del[x]) return;
		int y = (l + r) >> 1;
		int z = x + ((y - l + 1) << 1);
		has_del[x + 1] = has_del[z] = true;
		del[x + 1] = del[z] = del[x];
		sums[x + 1] = functor_wrapper<T, F>:: template f_range<F, T>(del[x], y - l + 1);
		sums[z] = functor_wrapper<T, F>:: template f_range<F, T>(del[x], r - y);
		has_del[x] = false;
	}

	void modify(int x, int l, int r, int ll, int rr, const T& val) {
		if (ll <= l && r <= rr) {
			sums[x] = functor_wrapper<T, F>:: template f_range<F, T>(val, r - l + 1);
			has_del[x] = true;
			del[x] = val;
			return;
		}
		int y = (l + r) >> 1;
		int z = x + ((y - l + 1) << 1);
		push(x, l, r);
		if (ll <= y) modify(x + 1, l, y, ll, rr, val);
		if (rr > y)  modify(z, y + 1, r, ll, rr, val);
		sums[x] = functor_wrapper<T, F>:: template f<F, T>(sums[x + 1], sums[z]);
	}

	T get(int x, int l, int r, int ll, int rr) {
		if (ll <= l && r <= rr) return sums[x];
		int y = (l + r) >> 1;
		int z = x + ((y - l + 1) << 1);
		push(x, l, r);
		if (rr <= y) return get(x + 1, l, y, ll, rr);
		if (ll > y) return get(z, y + 1, r, ll, rr);
		return functor_wrapper<T, F>:: template f<F, T>(get(x + 1, l, y, ll, rr), get(z, y + 1, r, ll, rr));
	}

	void init_vec(std::span<const T> a) {
		size = a.size();
		sums.resize(size * 2 - 1);
		del.resize(size * 2 - 1);
		has_del.resize(size * 2 - 1);
		build(0, 0, size - 1, a);
	}

	template<typename ...Fargs>
	seg_tree_push(const T * a, size_t size_, Fargs&&...fargs) : functor_wrapper<T, F>(std::forward<Fargs>(fargs)...) {init_vec(std::span<const T>(a, size_));}
	template<typename ...Fargs>
	seg_tree_push(const std::span<const T> & a, Fargs&&...fargs) : functor_wrapper<T, F>(std::forward<Fargs>(fargs)...) { init_vec(a); } 

	T get_range(int begin, int end) {
		return get(0, 0, size - 1, begin, end - 1);
	}

	T get(int id) {
		return get(0, 0, size - 1, id, id);
	}

	void set(int id, const T & val) {
		modify(0, 0, size - 1, id, id, val);
	}

	void set_range(int begin, int end, const T & val) {
		modify(0, 0, size - 1, begin, end - 1, val);
	}

	std::vector<T> to_vec() {
		std::vector<T> ret(size);
		for (int i = 0; i < size; i++) ret[i] = get(i);
		return ret;
	}

	std::string get_name() const {
		return "segment tree with delayed midifications";
	}

	~seg_tree_push() {
	}
};