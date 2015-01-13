#include "Version.h"
#include "NotImplementedException.h"

Version::Version()
{
}
Version::Version(initializer_list<int> Args)
{
	for (int versionPart : Args)
		versionNumbers.push_back(versionPart);
}
Version::Version(const string &versionString)
{
	// do something smart with strings
	throw(BaseExceptions::NotImplementedException(__FILE__, __LINE__));
}