#pragma once
#include <vector>
#include <string>
#include <ostream>
using namespace std;
/// Holds version information
class Version
{
public:
	Version();
	/// Create a version object using int list
	Version(initializer_list<int>);
	/// Create a Version object from a string
	Version(const string&);
	/// Removes the last version element
	void demote();
	/// Adds an extra 0
	void promote();
	/// Increments the least-significant version element
	void increment();
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

	Version& operator++();
	Version operator++(int);

};

