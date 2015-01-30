#pragma once
#include <sstream>
#include <string>
#include <vector>
template <typename T>
std::string to_string(const T &ver)
{
	std::stringstream os;
	os << ver;
	return os.str();
}
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T> v)
{
	for(const T& in: v)
		os << in << endl;
	return os;
}