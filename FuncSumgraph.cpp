#include "Sumgraph.cpp"
#include "OverlapFunc.cpp"

#include <fstream>
#include <stdio.h> 

typedef std::list<int> Lint;
typedef std::list<Lint> LLint;


inline int SubtractFromMatrix(SumGraph & g)
{
	// ����� ���� ��������� ��������
	int subtractSum = 0;
	// ������� � ������������ ���������� ����� � ��������
	std::vector<int> minRow(g.size_normal(), _inf1), minColumn(g.size_normal(), _inf1);
	// ����� ���� �������
	for (size_t i = 0; i < g.size_normal(); ++i) {
		if (g.rows[i])
			continue;
		for (size_t j = 0; j < g.size_normal(); ++j) {
			// ����� ������������ �������� � ������
			if (g.columns[j])
				continue;
			if (g.at(i, j) < minRow[i])
				minRow[i] = g.at(i, j);
		}
		if (minRow[i] >= _inf1) continue;
		for (size_t j = 0; j < g.size_normal(); ++j) {
			// ��������� ����������� ��������� �� ����
			// ��������� ������, ����� ��������������
			if (g.columns[j])
				continue;
			if (g.at(i, j) < _inf1) {
				g.at(i, j) -= minRow[i];
			}
			// ����� ������������ �������� � ������� ����� ��������� �����
			if ((g.at(i, j) < minColumn[j]))
				//if (g.columns[j]) continue;
				minColumn[j] = g.at(i, j);
		}
	}

	// ��������� ����������� ��������� �� ����
	// ��������� �������, ����� ��������������
	for (size_t j = 0; j < g.size_normal(); ++j) {
		if (g.columns[j]) continue;
		for (size_t i = 0; i < g.size_normal(); ++i) {
			if (g.rows[i]) continue;
			if (g.at(i, j) < _inf1) {
				g.at(i, j) -= minColumn[j];
			}
		}
	}

	// ������������ ��������� ��������
	for (size_t i = 0; i < g.size_normal(); i++) {
		if (g.rows[i]) continue;
		subtractSum += minRow[i];
		if (g.columns[i]) continue;
		subtractSum += minColumn[i];
	}

	return subtractSum;
}


inline std::list<std::pair<size_t, size_t>>  FindZeroesCoef(SumGraph g) {

	std::list<std::pair<size_t, size_t>> zeros;
	// ������ �� �������������
	std::list<int> coeffList;

	// ������������ �����������
	int maxCoeff = 0;
	// ����� ������� ���������
	for (size_t i = 0; i < g.size_normal(); ++i) {
		if (g.rows[i]) continue;
		for (size_t j = 0; j < g.size_normal(); ++j) {
			if (g.columns[j]) continue;
			// ���� ����� ����
			if (!g.at(i, j)) {
				// ���������� � ������ ���������
				zeros.emplace_back(i, j);
				// ������ ����������� � ���������� � ������
				coeffList.push_back(g.getCoefficient(i, j));
				// ��������� � ������������
				maxCoeff = std::max(maxCoeff, coeffList.back());
			}
		}
	}

	{ // ������� ��������� ����������
		auto zIter = zeros.begin();
		auto cIter = coeffList.begin();
		while (zIter != zeros.end()) {
			if (*cIter != maxCoeff) {
				// ���� ����������� �� ������������, �������� �������� �� ������
				zIter = zeros.erase(zIter);
				cIter = coeffList.erase(cIter);
			}
			else {
				++zIter;
				++cIter;
			}
		}
	}

	return zeros;

}



