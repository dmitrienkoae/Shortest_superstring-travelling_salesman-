#pragma once
#include "Superstring.cpp"

int main() {
	std::vector<std::string> vs = {"eab", "fgh", "ghf", "hed", "abc", "cde"};
	std::cout << "Sum length : "<< superString(vs).size() << std::endl;
	std::cout << "Superstring : " <<superString(vs) << std::endl;
	vs = { "a", "aa", "sdf", "fa", "ahg", "hju", "ut" };
	std::cout << "Sum length : " << superString(vs).size() << std::endl;
	std::cout << "Superstring : " << superString(vs) << std::endl;
return 0;
}
