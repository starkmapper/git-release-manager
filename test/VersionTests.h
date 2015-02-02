#pragma once
#include "Version.h"
#include <string>
class VersionTests
{
public:
	VersionTests();
	void InitTestData();
	void TestEquals();
	void TestConstructor();
	void TestGreaterLess();
	void TestToString();
	void TestDemotion();
private:
	vector<Version> numericalVersions;
	vector<std::string>  stringVersions;
	vector<std::string>  versionStrings;
};

