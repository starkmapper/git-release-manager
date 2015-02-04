#include "VersionTests.h"
#include "Version.h"
#include "FileLineException.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <sstream>
#include <iostream>
#include "to_string.hpp"

#define THROW_IF_EQUAL(A,B) { std::cout << "Testing \t" << A << " != " << B<<endl; if (A==B) throw(BaseExceptions::FileLineException("VersionTest failed\n"+to_string(A)+"\t==\t"+to_string(B),__FILE__,__LINE__)); }
#define THROW_IF_UNEQUAL(A,B) { std::cout << "Testing \t" << A << " == " << B <<endl; if (A!=B) throw(BaseExceptions::FileLineException("VersionTest failed\n"+to_string(A)+"\t!=\t"+to_string(B),__FILE__,__LINE__)); }
#define THROW_IF_NOTEQUAL(A,B) { std::cout << "Testing \t" << A << " == " << B<<endl; if (!(A==B)) throw(BaseExceptions::FileLineException("VersionTest failed\n"+to_string(A)+"\tNOT ==\t"+to_string(B),__FILE__,__LINE__)); }

VersionTests::VersionTests()
{
	InitTestData();
	TestEquals();
	TestConstructor();
	TestGreaterLess();
	TestToString();
	TestDemotion();
}
void VersionTests::InitTestData()
{
	numericalVersions.emplace_back(initializer_list<int>{1});
	stringVersions.emplace_back("1.0.0");
	versionStrings.push_back(stringVersions.back());

	numericalVersions.emplace_back(initializer_list<int>{21, 22, 23, 24});
	stringVersions.emplace_back( "21.22.23.24" );
	versionStrings.push_back(stringVersions.back());

	numericalVersions.emplace_back(initializer_list<int>{1, 2, 3, 4, 123, 15});
	stringVersions.emplace_back("1/2-3.4_123+15");
	versionStrings.push_back(stringVersions.back());


	numericalVersions.emplace_back(initializer_list<int>{ 15, 9, 3, 18, 3 });
	stringVersions.emplace_back( "release/15.9/3.18-3" );
	versionStrings.push_back("15.9/3.18-3");

	numericalVersions.emplace_back(initializer_list<int>{ 1, 2, 3 });
	stringVersions.emplace_back( "1.2.3-killmenow" );
	versionStrings.push_back("1.2.3");

	numericalVersions.emplace_back(initializer_list<int>{ 1, 2, 3, 4, 123 });
	stringVersions.emplace_back( "1.2.3.4-123-ac1337ff" );
	versionStrings.push_back("1.2.3.4-123");

}
void VersionTests::TestEquals()
{
	Version One{ 1 };
	Version OneZero{ 1 , 0};
	THROW_IF_NOTEQUAL(One, One);
	THROW_IF_NOTEQUAL(One, OneZero);
		
	Version Two{ 2 };
	THROW_IF_EQUAL(One, Two);

}
void VersionTests::TestConstructor()
{
	for(int i = 0; i < numericalVersions.size();++i)
		THROW_IF_UNEQUAL(numericalVersions[i], stringVersions[i]);
}

void VersionTests::TestToString()
{
	for(int i = 0; i < numericalVersions.size();++i)
		THROW_IF_UNEQUAL(to_string(Version(stringVersions[i])),versionStrings[i]);
}

void VersionTests::TestGreaterLess()
{
	vector<Version> sorted;
	sorted.push_back({ 0, 0, 1 });
	sorted.push_back({ 0, 1 });
	sorted.push_back({ 1 });
	sorted.push_back({ 1, 3 });
	sorted.push_back({ 1, 3, 1 });
	sorted.push_back({ 1, 3, 12 });
	sorted.push_back({ 1, 13 });

	vector<Version> c;
	c.push_back({ 1 , 3 });
	c.push_back({ 0, 1 });
	c.push_back({ 1 });
	c.push_back({ 1, 13 });
	c.push_back({ 0, 0, 1 });
	c.push_back({ 1, 3, 1 });
	c.push_back({ 1, 3, 12 });
	
	//Sort in ascending order
	sort(c.begin(), c.end(), less<Version>());
	THROW_IF_UNEQUAL(sorted, c);
	
	//Sort in descending order
	reverse(begin(sorted),end(sorted));
	sort(c.begin(), c.end(), greater<Version>());
	THROW_IF_UNEQUAL(sorted, c);
}
void VersionTests::TestDemotion()
{
	Version crazyManyVersionComponents{"1.2.3.4.5.6.7.8.9.0"};
	Version DemotedVersion{1,2,3,4,5};
	int i = 6;
	while(--i)
		crazyManyVersionComponents.demote();

	THROW_IF_UNEQUAL(crazyManyVersionComponents,DemotedVersion);
}
