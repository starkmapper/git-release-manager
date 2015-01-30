#pragma once
#include <vector>
#include <string>
#include <ostream>
using namespace std;
class Version
{
public:
	Version();
	Version(initializer_list<int>);
	Version(const string&);
private:
	void normalizeVersionNumber();
	void normalizeSeperators();
	vector<int> versionNumbers;
	vector<string> seperators;
	string prefix;
	string suffix;
public:
	// Comparison operators compare versionNumber values only!
	friend bool operator==(const Version& Left, const Version& Right);
	friend bool operator!=(const Version& Left, const Version& Right);
	friend bool operator>(const Version& Left, const Version& Right);
	friend bool operator>=(const Version& Left, const Version& Right);
	friend bool operator<(const Version& Left, const Version& Right);
	friend bool operator<=(const Version& Left, const Version& Right);
	
	friend ostream& operator<<(ostream& os, const Version& Right);
};

