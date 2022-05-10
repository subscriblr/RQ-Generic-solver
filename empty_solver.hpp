template<typename T>
struct empty_solver{
	T * arr;
	size_t size = 0;
	empty_solver() = default;

	void init(std::span<const T> a) {
		size = a.size();
		arr = new T[size];
		for (int i = 0; i < size; i++) arr[i] = a[i];
	}

	empty_solver(std::span<const T> a) { init(a);}
	empty_solver(const T * a, size_t size_) {init(std::span<const T> (a, size_));}

	void set(int id, const T & val) {
		arr[id] = val;
	}
	T get(int id) {
		return arr[id];
	}
	std::vector<T> to_vec() {
		std::vector<T> ret(size);
		for (int i = 0; i < size; i++) ret[i] = arr[i];
		return ret;
	}

	std::string get_name() const {
		return "empty_solver";
	}

	~empty_solver() {
		if (arr != nullptr) delete [] arr;
	}
};