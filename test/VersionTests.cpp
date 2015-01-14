#include "VersionTests.h"
#include "Version.h"
#include "FileLineException.h"
#define THROW_IF_UNEQUAL(A,B) if (A!=B) throw(BaseExceptions::FileLineException("Test failed@",__FILE__,__LINE__))

VersionTests::VersionTests()
{
	Version SingleNumeric{ 1 };
	Version bareSingleString{ "1" };
	THROW_IF_UNEQUAL(SingleNumeric, bareSingleString);
	
	Version numeric{ 21, 22, 23, 24 };
	Version bareString{ "21.22.23.24" };
	THROW_IF_UNEQUAL(numeric,bareString);
	
	Version seperated{ 1, 2, 3, 4, 123, 15 };
	Version seperatedString{ "1/2-3.4_123+15" };
	THROW_IF_UNEQUAL(seperated,seperatedString);
	
	Version prefixed{ 15, 9, 3, 18, 3 };
	Version prefixedString{ "release/15.9/3.18-3" };
	THROW_IF_UNEQUAL(prefixed,prefixedString);
	
	Version postfixed{ 1, 2, 3 };
	Version postfixedString{ "1.2.3.4-killmenow" };
	THROW_IF_UNEQUAL(postfixed,postfixedString);
	
	Version gitDescribe{ 1, 2, 3 , 123 };
	Version gitDescribeString{ "1.2.3.4-123-ac1337ff" };
	THROW_IF_UNEQUAL(gitDescribe,gitDescribeString);
}
