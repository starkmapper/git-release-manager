#include "VersionTests.h"
#include "Version.h"
#include "FileLineException.h"
#include <vector>
#include <algorithm>
#include <functional>
#define THROW_IF_EQUAL(A,B) if (A==B) throw(BaseExceptions::FileLineException("VersionTest failed",__FILE__,__LINE__))
#define THROW_IF_UNEQUAL(A,B) if (A!=B) throw(BaseExceptions::FileLineException("VersionTest failed",__FILE__,__LINE__))
#define THROW_IF_NOTEQUAL(A,B) if (!(A==B)) throw(BaseExceptions::FileLineException("VersionTest failed",__FILE__,__LINE__))

VersionTests::VersionTests()
{
	TestEquals();
	TestConstructor();
	TestGreaterLess();
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

	Version SingleNumeric{ 1 };
	Version bareSingleString{ "1" };
	THROW_IF_UNEQUAL(SingleNumeric, bareSingleString);

	Version numeric{ 21, 22, 23, 24 };
	Version bareString{ "21.22.23.24" };
	THROW_IF_UNEQUAL(numeric, bareString);

	Version seperated{ 1, 2, 3, 4, 123, 15 };
	Version seperatedString{ "1/2-3.4_123+15" };
	THROW_IF_UNEQUAL(seperated, seperatedString);

	Version prefixed{ 15, 9, 3, 18, 3 };
	Version prefixedString{ "release/15.9/3.18-3" };
	THROW_IF_UNEQUAL(prefixed, prefixedString);

	Version postfixed{ 1, 2, 3 };
	Version postfixedString{ "1.2.3-killmenow" };
	THROW_IF_UNEQUAL(postfixed, postfixedString);

	Version gitDescribe{ 1, 2, 3, 4, 123 };
	Version gitDescribeString{ "1.2.3.4-123-ac1337ff" };
	THROW_IF_UNEQUAL(gitDescribe, gitDescribeString);
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