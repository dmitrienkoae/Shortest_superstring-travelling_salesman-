#include "FuncSumgraph.cpp"

inline size_t cost(const VVint &og, const LPss &path) {
	size_t result = 0;
	for (auto &it : path) {
		result += og[it.first][it.second];
	}
	return result;
}


inline void findPathRecursive(SumGraph& g, const VVint& og, LPss& path, int limit, int& record, LPss& record_path) {
	int n = g.size();
	if (n == 1) {
		record_path.push_back(std::make_pair(0, 0));
		return;
	}
	if (n == 2) {

		std::pair<size_t, size_t> last_pair;
		int count = 0;
		for (size_t i = 0; i < g.size_normal(); i++) {
			if (g.rows[i]) continue;
			for (size_t j = 0; j < g.size_normal(); j++) {
				if (g.columns[j]) continue;

				if (g.at(i, j) != _inf1) {
					last_pair.first = i;
					last_pair.second = j;
					path.push_back(last_pair);
					count++;
				}
			}

		}
		int end_cost = cost(og, path);
		if (end_cost < record) {
			record = end_cost;
			record_path = path;
		}

		return;
	}

	LPss zer;
	int cur_cost = SubtractFromMatrix(g);
	limit += cur_cost;
	//std::cout << "limit:" << limit << std::endl;
	//std::cout << "record:" << record << std::endl;
	if (limit >= record)
		return;

	//std::cout << "n = " << n << std::endl << g << std::endl;
	zer = FindZeroesCoef(g);
	if (!zer.size()) return;
	std::pair<size_t, size_t> zer_front = zer.front();

	path.push_back(zer_front);

	int c_cost = cost(og, path);
	if (c_cost >= record)
		return;

	g.removeRowColumn(zer_front.first, zer_front.second);
	//std::cout << "Remove edge : (" << zer_front.first << "," << zer_front.second << ")" << std::endl;
	//std::cout << " Matrix with delete edge (" << zer_front.first << "," << zer_front.second << ")" << std::endl << g << std::endl;

	PsPss val_pos_inf = g.addInfinity();
	int val = val_pos_inf.first;
	Pss pos = val_pos_inf.second;
	//Find path with edge with max zero coef
	findPathRecursive(g, og, path, limit, record, record_path);
	//return g to step back for other recursion
	g.returnRowColumn(zer_front.first, zer_front.second);
	g.at(pos.first, pos.second) = val;
	g.at(zer_front.first, zer_front.second) = _inf1 + 1;
	//std::cout << " Matrix without delete edge (" << zer_front.first << "," << zer_front.second << ")" << std::endl << g << std::endl;
	//return path to step back
	path.pop_back();
	//Find path without edge with max zero coef
	findPathRecursive(g, og, path, limit, record, record_path);

	return;
}

inline std::pair <size_t, size_t> reduceMinOverlapEdge(const VVint& matrix_overlap, LPss& path) {
	//VVint matrix_overlap = overlaps(vs);
	std::pair <size_t, size_t> del_edge;
	int min = matrix_overlap[path.back().first][path.back().second];
	auto it_min = path.begin();
	auto prev = path.front();
	// We need the overlap between the first and last elements is min
	for (auto it = path.begin(); it != path.end(); ++it) {
		if (min >= matrix_overlap[it->first][it->second]) {
			min = matrix_overlap[it->first][it->second];
			it_min = it;
			del_edge.first = it->first;
			del_edge.second = it->second;
		}
		prev = *it;
	}

	path.remove(*it_min);
	return del_edge;

}


inline Vint shift(LPss &path, std::pair <size_t, size_t> del_edge) {
	size_t beg = del_edge.second;
	size_t end = del_edge.first;
	Vint new_path;
	size_t n = path.size();
	while (new_path.size() != n) {
		for (auto it = path.begin(); it != path.end(); it++) {
			if (it->first == beg) {
				new_path.push_back(it->first);
				beg = (it->second);
				//path.erase(it);
			}

		}

	}

	new_path.push_back(beg);
	return new_path;
}


inline Vint findMinPath(SumGraph g, const VVint& og, const VVint& matrix_overlap) {

	LPss path, record_path;
	int record = _inf1;

	findPathRecursive(g, og, path, 0, record, record_path);
	std::pair <size_t, size_t> del_edge = reduceMinOverlapEdge(matrix_overlap, record_path);
	Vint new_path = shift(record_path, del_edge);
	return new_path;
}

