#ifndef  __RQ_FUNCTORS
#define  __RQ_FUNCTORS

template <typename T>
struct F_undef{
};

template <typename T>
struct F_sum{
	static T f (const T & a, const T & b) {
		return a + b;
	}
	static T inverse (const T & a) {
		return -a;
	}
	static T f_range (const T & a, size_t sz) {
		return a * sz;
	}
	static const T neutral = T(0);
};

template <typename T>
struct F_xor{
	static T f (const T & a, const T & b) {
		return a ^ b;
	}
	static T inverse (const T & a) {
		return a;
	}
	static T f_range (const T & a, size_t sz) {
		return (sz & 1) ? a : neutral;
	}
	static const T neutral = T(0);
};

template <typename T>
struct F_min{
	static T f (const T & a, const T & b) {
		return (a < b) ? a : b;
	}
	static T f_range (const T & a, size_t sz) {
		return a;
	}
};

template <typename T>
struct F_max{
	static T f (const T & a, const T & b) {
		return (a > b) ? a : b;
	}
	static T f_range (const T & a, size_t sz) {
		return a;
	}
};

enum functor_id {
	UNDEF_ID,
	SUM_ID,
	XOR_ID,
	MIN_ID,
	MAX_ID
};

template<int, typename>
struct id_to_fun{};

template<typename T>
struct id_to_fun<UNDEF_ID, T>{
	using type =  F_undef<T>;
};

template<typename T>
struct id_to_fun<SUM_ID, T>{
	using type =  F_sum<T>;
};

template<typename T>
struct id_to_fun<XOR_ID, T>{
	using type =  F_xor<T>;
};

template<typename T>
struct id_to_fun<MIN_ID, T>{
	using type =  F_min<T>;
};

template<typename T>
struct id_to_fun<MAX_ID, T>{
	using type =  F_max<T>;
};



#endif
