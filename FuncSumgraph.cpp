#include "Sumgraph.cpp"
#include "OverlapFunc.cpp"

#include <fstream>
#include <stdio.h> 

typedef std::list<int> Lint;
typedef std::list<Lint> LLint;


inline int SubtractFromMatrix(SumGraph & g)
{
	// сумма всех вычтенных значений
	int subtractSum = 0;
	// массивы с минимальными элементами строк и столбцов
	std::vector<int> minRow(g.size_normal(), _inf1), minColumn(g.size_normal(), _inf1);
	// обход всей матрицы
	for (size_t i = 0; i < g.size_normal(); ++i) {
		if (g.rows[i])
			continue;
		for (size_t j = 0; j < g.size_normal(); ++j) {
			// поиск минимального элемента в строке
			if (g.columns[j])
				continue;
			if (g.at(i, j) < minRow[i])
				minRow[i] = g.at(i, j);
		}
		if (minRow[i] >= _inf1) continue;
		for (size_t j = 0; j < g.size_normal(); ++j) {
			// вычитание минимальных элементов из всех
			// элементов строки, кроме бесконечностей
			if (g.columns[j])
				continue;
			if (g.at(i, j) < _inf1) {
				g.at(i, j) -= minRow[i];
			}
			// поиск минимального элемента в столбце после вычитания строк
			if ((g.at(i, j) < minColumn[j]))
				//if (g.columns[j]) continue;
				minColumn[j] = g.at(i, j);
		}
	}

	// вычитание минимальных элементов из всех
	// элементов столбца, кроме бесконечностей
	for (size_t j = 0; j < g.size_normal(); ++j) {
		if (g.columns[j]) continue;
		for (size_t i = 0; i < g.size_normal(); ++i) {
			if (g.rows[i]) continue;
			if (g.at(i, j) < _inf1) {
				g.at(i, j) -= minColumn[j];
			}
		}
	}

	// суммирование вычтенных значений
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
	// список их коэффициентов
	std::list<int> coeffList;

	// максимальный коэффициент
	int maxCoeff = 0;
	// поиск нулевых элементов
	for (size_t i = 0; i < g.size_normal(); ++i) {
		if (g.rows[i]) continue;
		for (size_t j = 0; j < g.size_normal(); ++j) {
			if (g.columns[j]) continue;
			// если равен нулю
			if (!g.at(i, j)) {
				// добавление в список координат
				zeros.emplace_back(i, j);
				// расчет коэффициена и добавление в список
				coeffList.push_back(g.getCoefficient(i, j));
				// сравнение с максимальным
				maxCoeff = std::max(maxCoeff, coeffList.back());
			}
		}
	}

	{ // область видимости итераторов
		auto zIter = zeros.begin();
		auto cIter = coeffList.begin();
		while (zIter != zeros.end()) {
			if (*cIter != maxCoeff) {
				// если коэффициент не максимальный, удаление элемента из списка
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



