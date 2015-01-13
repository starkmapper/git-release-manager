#pragma once
#include <vector>
#include <string>
using namespace std;
class Version
{
public:
	Version();
	Version(initializer_list<int>);
	Version(const string&);
private:
	vector<int> versionNumbers;
	vector<wchar_t> seperators;
public:
	// Comparison operators compare versionNumber values only!
	friend bool operator==(const Version& Left, const Version& Right);
	friend bool operator!=(const Version& Left, const Version& Right);
};

