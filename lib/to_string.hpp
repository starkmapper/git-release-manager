#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
template <typename T>
std::string to_string(const T &ver)
{
	std::stringstream os;
	os << ver;
	return os.str();
}
template<typename C>
std::ostream& operator<<(std::ostream& os, const vector<C> &c)
{
	if(c.size() > 0)
	{
		std::ostream_iterator<C> stream_iterator(os,"\n");
		std::copy(c.cbegin(),c.cend()-1, stream_iterator);
		os << *c.rbegin();
	}
	
	return os;
}