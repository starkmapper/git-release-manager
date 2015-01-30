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
template<class C>
std::ostream& operator<<(std::ostream& os, const C &c)
{
	if(c.size() > 0)
	{
		std::ostream_iterator<typename C::value_type> stream_iterator(os,"\n");
		std::copy(c.cbegin(),c.cend()-1, stream_iterator);
		os << *c.rend();
	}
	
	return os;
}