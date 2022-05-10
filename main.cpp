#include <iostream>
#include <vector>
#include <span>
#include <cassert>

#include "template_rq.hpp" 

using namespace std;
 
int main(){
	std::vector<int> data = {0, 1, 2, 3, 4, 5};
	int data_arr[6] = {0, 1, 2, 3, 4, 5};

	auto s = RQ_solver<int, method::set>(data_arr, 6);
	cout << s.get_name() << endl; //empty_solver
	s.set(3, 100);

	auto s2 = RQ_solver<int, method::get_range, property::inversible>
		(data, [](int a, int b) {return a + b;}, [](int a) {return -a;});
	cout << s2.get_name() << endl;      //prefix_solver 
	cout << s2.get_range(2, 4) << endl; //5

	auto s3 = RQ_solver<int, method::get_sum, method::set, method::add>(data);
	cout << s3.get_name() << endl;    //fenwick_solver
	cout << s3.get_sum(0, 6) << endl; //15
	s3.set(0, 1);                     
	cout << s3.get_range(0, 6) << endl; //16, target function is derived as Sum, so get_range is the same method as get_sum
	s3.add(0, -1);
	cout << s3.get_range(0, 6) << endl; //15

	auto s4 = RQ_solver<int, method::get_range, property::inversible, method::set>
		(data, [](int a, int b) {return a + b;}, [](int a) {return -a;});
	cout << s4.get_name() << endl;    //fenwik_solver, passing inverse function as lambda function
	s4.set(4, 100);
	cout << s4.get_range(3, 5) << endl; //103

	auto s5 = RQ_solver<int, method::get_sum, method::set_range>(data);
	cout << s5.get_name() << endl;  //segment tree with delayed midifications
	cout << s5.get_sum(1, 5) << endl; //10
	s5.set_range(3, 6, 0);
	cout << s5.get_sum(1, 5) << endl; //3

	auto s6 = RQ_solver<int, method::get_range, method::set_range>
		(data, [](int a, int b) {return a + b;});
	cout << s6.get_name() << endl;   //segment tree with delayed midifications, log^2 for each query since we don't know how to apply function for equal elements efficiently 
	cout << s6.get_range(1, 5) << endl;//10
	s6.set_range(3, 6, 0);
	cout << s6.get_range(1, 5) << endl;//3

	auto s7 = RQ_solver<int, method::get_range, method::set_range>
		(data, [](int a, int b) {return a + b;}, [](int a, int len){ return a * len;});
	cout << s7.get_name() << endl;   //segment tree with delayed midifications, log for each query since now we know how to apply function for equal elements in constant time
	cout << s7.get_range(1, 5) << endl;//10
	s7.set_range(3, 6, 0);
	cout << s7.get_range(1, 5) << endl;//3

	
	return 0;
}
 