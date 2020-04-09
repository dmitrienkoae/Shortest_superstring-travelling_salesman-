
#pragma once

#include <vector>
#include <string>
#include <list>

typedef std::vector<int> Vint;
typedef std::vector<Vint> VVint;
typedef std::vector<std::string> Vstr;

//Find how much s2 overlap s1
inline int overlap(const std::string& s1, const std::string& s2) {
	if (&s1 == &s2)
		return 0;
	int s1_last = s1.size() - 1;
	int s2_size = s2.size();
	int	res = 0;
	for (int i = s1_last, j = 1; i >= 0 && j <= s2_size; i--, j++) {
		bool is_overlap = true;
		for (int k = 0; k < j; ++k) {
			if (s1[i + k] != s2[k]) {
				is_overlap = false;
				break;
			}
		}
		if (is_overlap)
			res = j;
	}
	return res;
}

//Matrix of Overlap
inline VVint overlaps(Vstr& vs) {
	for (size_t i = 0; i < vs.size(); i++) {
		for (size_t j = 0; j < vs.size(); j++) {
			if (i == j) continue;
			if (vs[i].find(vs[j]) != std::string::npos) {
				vs.erase(vs.begin() + j);

			}
		}
	}
	size_t n = vs.size();
	VVint m(n, Vint(n));
	for (size_t i = 0; i < n; ++i)
		for (size_t j = 0; j < n; ++j) {
			m[i][j] = overlap(vs[i], vs[j]);
			if (i == j)
				m[i][j] = 0;
		}
	return m;
}
