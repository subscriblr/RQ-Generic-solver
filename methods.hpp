#ifndef  __RQ_SOLVER_METHODS
#define  __RQ_SOLVER_METHODS

#include "functors.hpp"

static const int PROP_N = 5;

enum rq_mods{
	MODIFY,
	RANGE_MOD,
	PARTIAL_QUERY,
	NOT_INVERSIBLE, 
	NOT_IDEMPOTENT
};

static const int SOLVER_N = 6;

enum rq_solver{
	EMPTY,
	PREFIX_SOLVER,
	SPARSE_TABLE,
	FENWIK,
	SEGMENT_TREE_NO_PUSH,
	SEGMENT_TREE_PUSH
};

static constexpr int eq_solver_mods[SOLVER_N] =  {
(1 << MODIFY) | (1 << NOT_IDEMPOTENT) | (1 << NOT_INVERSIBLE),	//EMPTY
(1 << PARTIAL_QUERY) | (1 << NOT_IDEMPOTENT),	//PREFIX_SOLVER
0, //unimplemented ######## (1 << PARTIAL_QUERY) | (1 << NOT_INVERSIBLE), //SPARSE_TABLE
(1 << MODIFY) | (1 << PARTIAL_QUERY) | (1 << NOT_IDEMPOTENT), //FENWIK
0, //unimplemented ######## (1 << MODIFY) | (1 << PARTIAL_QUERY) | (1 << NOT_INVERSIBLE) | (1 << NOT_IDEMPOTENT), //SEGMENT_TREE_NO_PUSH
(1 << MODIFY) | (1 << PARTIAL_QUERY) | (1 << NOT_INVERSIBLE) | (1 << NOT_IDEMPOTENT) | (1 << RANGE_MOD)  //SEGMENT_TREE_PUSH
};


static const int METHOD_N = 9;

namespace method {
	enum method_name {
		get,
		get_range,
		set,
		set_range,
		get_sum,
		get_xor, 
		get_min,
		get_max,
		add
	};
};

static const int PROPERTY_N = 2;

namespace property {
	enum property_name {
		inversible = METHOD_N,
		idempotent = METHOD_N + 1
	};
};

/*enum rq_mods{
	MODIFY,
	RANGE_MOD,
	PARTIAL_QUERY,
	NOT_INVERSIBLE, 
	NOT_IDEMPOTENT
};*/

static constexpr int method_mods[METHOD_N] =  {
0,	//get
(1 << PARTIAL_QUERY),	//get_range
(1 << MODIFY),	//set
(1 << MODIFY) | (1 << RANGE_MOD), //set_range
(1 << PARTIAL_QUERY), //get_sum
(1 << PARTIAL_QUERY), //get_xor
(1 << PARTIAL_QUERY), //get_min
(1 << PARTIAL_QUERY), //get_max
(1 << MODIFY)	//add
};

static constexpr int method_mods_clear[METHOD_N] =  {
0, //get
0, //get_range
0, //set
0, //set_range
(1 << NOT_INVERSIBLE), //get_sum
(1 << NOT_INVERSIBLE), //get_xor
(1 << NOT_IDEMPOTENT), //get_min
(1 << NOT_IDEMPOTENT), //get_max
0 //add
};

static constexpr int method_fun_id[METHOD_N] =  {
0,	//get
0,	//get_range
0,	//set
0, //set_range
SUM_ID, //get_sum
XOR_ID, //get_xor
MIN_ID, //get_min
MAX_ID, //get_max
SUM_ID, //add
};


static constexpr int default_mods = (1 << NOT_INVERSIBLE) | (1 << NOT_IDEMPOTENT);

static constexpr int property_mods_clear[PROPERTY_N] =  {
(1 << NOT_INVERSIBLE), //inversible
(1 << NOT_IDEMPOTENT) //idempotent
};


#endif
