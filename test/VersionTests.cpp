#include "VersionTests.h"
#include "Version.h"
#include "FileLineException.h"
#define THROW_IF_UNEQUAL(A,B) if (A!=B) throw(BaseExceptions::FileLineException("Test failed@",__FILE__,__LINE__))

VersionTests::VersionTests()
{
	// comparison object
	Version numeric{ 1, 2, 3, 4 };
	Version bareString{ "1.2.3.4" };
    THROW_IF_UNEQUAL(numeric,bareString);
	Version seperatedString{ "1/2-3.4" };
	THROW_IF_UNEQUAL(numeric,seperatedString);
	Version prefixedString{ "release/1.2/3-4" };
	THROW_IF_UNEQUAL(numeric,prefixedString);
	Version postfixedString{ "1.2.3.4-killmenow" };
	THROW_IF_UNEQUAL(numeric,postfixedString);
	Version gitDescribeString{ "1.2.3.4-123-ac1337ff" };
	THROW_IF_UNEQUAL(numeric,gitDescribeString);
}
