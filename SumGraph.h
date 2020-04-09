#pragma once

#include <vector>
#include <string>
#include <list>

typedef std::vector<int> Vint;
typedef std::vector<Vint> VVint;

typedef std::vector<std::string> Vstr;

typedef std::pair<size_t, size_t > Pss;
typedef std::list<Pss> LPss;
typedef std::pair<size_t, Pss> PsPss;

class SumGraph {
public:
	Vint columns;
	Vint rows;
	VVint m;

	SumGraph();
	SumGraph(size_t n);
	SumGraph(Vstr&);
	SumGraph(VVint & vi);
	~SumGraph();

	void overlaps(Vstr&);

	size_t size() const;
	size_t size_normal() const;

	friend std::ostream& operator<<(std::ostream&, const SumGraph&);

	int& at(size_t i, size_t j);
	int at(size_t i, size_t j) const;

	//int SubtractFromMatrix();
	int getCoefficient(size_t r, size_t c);
	void removeRowColumn(size_t i, size_t j);
	void returnRowColumn(size_t row, size_t column);
	PsPss addInfinity();

private:
	int overlap(const std::string&, const std::string&);
};
