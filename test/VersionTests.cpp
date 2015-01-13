#include "VersionTests.h"
#include "Version.h"

VersionTests::VersionTests()
{
	Version numeric{ 1, 2, 3, 4 };
	Version bareString{ "1.2.3.4" };
	Version seperatedString{ "1/2-3.4_123+15" };
	Version prefixedString{ "release/15.9/3.18-3" };
	Version postfixedString{ "1.2.3-killmenow" };
	Version gitDescribeString{ "1.2.3-123-ac1337ff" };
}
