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
	vector<string> seperators;
	string prefix;
	string suffix;
};

