#ifndef  __RQ_TEMPLATES
#define  __RQ_TEMPLATES

#include "empty_solver.hpp"
#include "prefix_sum.hpp"
#include "fenwik.hpp"
#include "seg_tree_push.hpp"

#include "methods.hpp"

constexpr int best_solver(int mask, int i) {
	if (i == SOLVER_N) return i;
	if ((mask & eq_solver_mods[i]) == mask) return i;
	return best_solver(mask, i + 1);
}

template <int...>
struct Prop_finder{};

template <int F, int...REST>
struct Prop_finder<F, REST...>{
	static constexpr int mask_update(int ret) {
		if constexpr (F < METHOD_N) {
			ret |= method_mods[F];
			ret ^= ret & method_mods_clear[F];
		}
		if constexpr (F >= METHOD_N) {
			ret ^= ret & property_mods_clear[F - METHOD_N];
		}
		return ret;
	}

	template<int Curid>
	static constexpr int func_update() {
		if constexpr (F < METHOD_N) {
			static_assert(Curid == 0 || method_fun_id[F] == 0 || Curid == method_fun_id[F]);
			return Curid | method_fun_id[F];
		} else {
			return Curid;
		}
	}

	static const int mask = mask_update(Prop_finder<REST...>::mask);
	static const int solver_id = best_solver(mask, 0);
	static const int func_id = func_update<Prop_finder<REST...>::func_id>();
};

template <>
struct Prop_finder<> {
	static const int func_id = 0;
	static const int mask = default_mods;
	static const int solver_id = best_solver(mask, 0);
};

         //T, solver_id, functor_id
template <typename, int, int>
struct id_to_solver{};

template <typename T, int Fid>
struct id_to_solver<T, EMPTY, Fid>{
	using type = empty_solver<T>;
};

template <typename T, int Fid>
struct id_to_solver<T, PREFIX_SOLVER, Fid>{
	using type = prefix_sum<T, typename id_to_fun<Fid, T>::type >;
};

template <typename T, int Fid>
struct id_to_solver<T, FENWIK, Fid>{
	using type = fenwik<T, typename id_to_fun<Fid, T>::type >;
};

template <typename T, int Fid>
struct id_to_solver<T, SEGMENT_TREE_PUSH, Fid>{
	using type = seg_tree_push<T, typename id_to_fun<Fid, T>::type >;
};


template <typename T, int...MODS>
struct RQ_solver : id_to_solver<T, Prop_finder<MODS...>::solver_id, Prop_finder<MODS...>::func_id>::type{
	using base = typename id_to_solver<T, Prop_finder<MODS...>::solver_id, Prop_finder<MODS...>::func_id>::type;
	using base::base;
	using base::get_name;

	T get_sum(size_t begin, size_t end) {return base::get_range(begin, end);}
	T get_xor(size_t begin, size_t end) {return base::get_range(begin, end);}
	T get_min(size_t begin, size_t end) {return base::get_range(begin, end);}
	T get_max(size_t begin, size_t end) {return base::get_range(begin, end);}
};

#endif


                
