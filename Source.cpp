#pragma once
#include "Superstring.cpp"

#include <time.h> 



int main() {
	std::vector<std::string> vs ;
	std::string s;
	std::string line;
	std::ifstream in("D:\\tests2.txt"); // окрываем файл для чтения
	if (in.is_open())
	{
		while (getline(in, line))
		{
			vs.push_back(line);
		}
	}
	in.close();

	clock_t start = clock();
	SumGraph g(vs);
	std::string super_str = superString(vs);
	clock_t end = clock();

	std::cout << super_str << std::endl;

	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	std::cout << "Time : " << seconds << std::endl;

	return 0;
}