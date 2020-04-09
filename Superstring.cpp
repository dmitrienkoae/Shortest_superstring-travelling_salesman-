#include "FindPath.cpp"

inline int SuperstringLength(const Vstr&  vs, const VVint& og, const Vint& path) {
	if (vs.size() == 1) return vs[0].length();
	int sup_str_len = og[path[0]][path[1]];
	for (size_t i = 1; i < path.size() - 1; i++)
		sup_str_len += og[path[i]][path[i + 1]] - vs[path[i]].length();
	return sup_str_len;
}

//Answer
inline std::string superString(Vstr& vs) {
	VVint matrix_overlap = overlaps(vs);
	SumGraph g(vs);
	VVint og = g.m;
	Vint path = findMinPath(g, og, matrix_overlap);
	std::string super_str = vs[path[0]];
	for (size_t i = 1; i < path.size(); i++) {
		//finds prefix and cuts it
		int delta = matrix_overlap[path[i - 1]][path[i]];
		super_str += vs[path[i]].substr(delta);
	}
	int sum_cost = SuperstringLength(vs, og, path);
	std::cout << "Sum Cost: " << sum_cost << "\n";
	return super_str;

}

//For tests
inline int superStringCost(Vstr& vs) {
	VVint matrix_overlap = overlaps(vs);
	SumGraph g(vs);
	VVint og = g.m;
	Vint path = findMinPath(g, og, matrix_overlap);
	std::string super_str = vs[path[0]];
	for (size_t i = 1; i < path.size(); i++) {
		//finds prefix and cuts it
		int delta = matrix_overlap[path[i - 1]][path[i]];
		super_str += vs[path[i]].substr(delta);
	}
	int sum_cost = SuperstringLength(vs, og, path);
	std::cout << "Sum Cost: " << sum_cost << "\n";
	return sum_cost;

}