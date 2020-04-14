#include "SumGraph.h"
#include "FSM.cpp"

#include <algorithm>
#include <ostream>
#include <iostream>

#define _inf1  10000

inline SumGraph::SumGraph() {
}

inline SumGraph::SumGraph(size_t n) {

	this->m = VVint(n, Vint(n));
	for (size_t i = 0; i < n; i++) {
		this->columns.push_back(0);
		this->rows.push_back(0);
	}
}

inline SumGraph::SumGraph(Vstr& vs) {
	overlaps(vs);
	size_t n = vs.size();
	for (size_t i = 0; i < n; i++) {
		this->columns.push_back(0);
		this->rows.push_back(0);
	}
}

inline SumGraph::SumGraph(VVint& vi) {
	this->m = vi;
	size_t n = vi.size();
	for (size_t i = 0; i < n; i++) {
		this->columns.push_back(0);
		this->rows.push_back(0);
	}
}

inline SumGraph::~SumGraph() {
}

///
inline void SumGraph::overlaps(Vstr& vs) {

	int olap;
	int olap2;
	for (size_t i = 0; i < vs.size(); i++) {
		for (size_t j = 0; j < vs.size(); j++) {
			if (i == j) continue;
			if (vs[i].find(vs[j]) != std::string::npos) {
				vs.erase(vs.begin() + j);

			}
		}
	}
	size_t n = vs.size();
	this->m = VVint(n, Vint(n));
	for (size_t i = 0; i < n; ++i) {
		FSM automat(vs[i]);
		for (size_t j = 0; j < n; ++j) {

			m[i][j] = _inf1;
			if (i != j) {
				//olap = overlap(vs[i], vs[j]);
				olap2 = automat.OverlapStr(vs[j]);
				m[i][j] = vs[i].length() + vs[j].length() - olap;
			}
		}
	}
}

inline size_t SumGraph::size() const {
	if (!m.size()) return 0;
	int amount = 0;
	for (size_t i = 0; i < m.size(); i++) {
		if (columns[i]) amount++;
	}
	return m.size() - amount;
}

inline size_t SumGraph::size_normal() const {

	return m.size();
}

// How much does the END of the FIRST line 
// coincide with the BEGINNING of the SECOND
inline int SumGraph::overlap(const std::string& s1, const std::string& s2) {
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

//Item Access
inline int& SumGraph::at(size_t i, size_t j) {
	return m[i][j];
}

inline int SumGraph::at(size_t i, size_t j) const {
	return m[i][j];
}


inline void SumGraph::removeRowColumn(size_t row, size_t column) {
	rows[row] = 1;
	columns[column] = 1;
}

inline void SumGraph::returnRowColumn(size_t row, size_t column) {
	rows[row] = 0;
	columns[column] = 0;
}



inline int SumGraph::getCoefficient(size_t r, size_t c) {
	int rmin, cmin;
	rmin = cmin = _inf1 * 2;
	// îáõîä ñòðîêè è ñòîëáöà
	for (size_t i = 0; i < m.size(); ++i) {

		if (i != r) {
			if (rows[i]) continue;
			rmin = std::min(rmin, m[i][c]);
		}
	}
	for (size_t i = 0; i < m.size(); ++i) {

		if (i != c) {
			if (columns[i]) continue;
			cmin = std::min(cmin, m[r][i]);
		}

	}

	return rmin + cmin;
}

inline PsPss SumGraph::addInfinity() {
	// ìàññèâû ñ èíôîðìàöèåé î òîì, â êàêèõ ñòîëáöàõ è ñòðîêàõ ñîäåðæèòñÿ áåñêîíå÷íîñòü
	std::vector<bool> infRow(m.size(), false), infColumn(m.size(), false);
	// îáõîä âñåé ìàòðèöû

	for (size_t i = 0; i < m.size(); i++) {
		if (rows[i]) continue;
		for (size_t j = 0; j < m.size(); j++) {
			if (columns[j]) continue;
			if (m[i][j] == _inf1) {
				infRow[i] = true;
				infColumn[j] = true;
			}
		}
	}
	// ïîèñê ñòðîêè, íå ñîäåðæàùåé áåñêîíå÷íîñòè
	size_t notInf;
	for (size_t i = 0; i < infRow.size(); i++)
		if (!infRow[i] && !rows[i]) {
			notInf = i;
			break;
		}

	// ïîèñê ñòîëáöà, íå ñîäàðæàùåãî áåñêîíå÷íîñòè è äîáàâëåíèå áåñêîíå÷íîñòè
	for (size_t j = 0; j < infColumn.size(); j++) {
		if (columns[j]) continue;
		if (!infColumn[j]) {
			size_t value = m[notInf][j];
			m[notInf][j] = _inf1;
			return PsPss(value, Pss(notInf, j));
		}
	}
	return PsPss(-1, Pss(-1, -1));
}

//Operator Overloading
inline std::ostream& operator<<(std::ostream& out, const SumGraph& g) {
	int s = g.size_normal();
	for (int i = 0; i < s; i++)
	{
		if (g.rows[i]) continue;
		for (int j = 0; j < s; j++)
		{
			if (g.columns[j]) continue;
			printf("%5d ", g.at(i, j));
		}
		printf("\n");
	}
	out << "\n--------------------------\n";
	return out;
}

inline std::ostream& operator<<(std::ostream& out, const VVint& m) {
	int s = m.size();
	for (size_t i = 0; i < s; i++) {
		for (size_t j = 0; j < s; j++)
			printf("%5d ", m[i][j]);
		out << std::endl;
	}
	out << "\n--------------------------\n";
	return out;
}
