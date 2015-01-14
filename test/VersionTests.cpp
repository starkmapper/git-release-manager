#include "VersionTests.h"
#include "Version.h"

VersionTests::VersionTests()
{
	Version SingleNumeric{ 1 };
	Version bareSingleString{ "1" };
	
	Version numeric{ 21, 22, 23, 24 };
	Version bareString{ "21.22.23.24" };

	Version seperated{ 1, 2, 3, 4, 123, 15 };
	Version seperatedString{ "1/2-3.4_123+15" };

	Version prefixed{ 15, 9, 3, 18, 3 };
	Version prefixedString{ "release/15.9/3.18-3" };

	Version postfixed{ 1, 2, 3 };
	Version postfixedString{ "1.2.3-killmenow" };

	Version gitDescribe{ 1, 2, 3 , 123 };
	Version gitDescribeString{ "1.2.3-123-ac1337ff" };
}
