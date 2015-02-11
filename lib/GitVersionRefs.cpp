#include "GitVersionRefs.h"
#include "FileLineException.h"
#include "ExecuteCommand.h"
#include "to_string.hpp"
#include <algorithm>

using namespace std;
GitVersionRefs::GitVersionRefs()
{
	vector<string> tagStrings = ExecuteCommand("git tag");
	for (auto& tag : tagStrings)
	{
		try
		{
			refs.emplace_back(tag);
		}
		catch (exception& e)
		{
			// not every line is an actual version string
		}
	}
	sort(refs.begin(), refs.end());
}

void GitVersionRefs::demote()
{
	for (Version& version : refs)
		version.demote();

	VersionRefList::iterator newEnd = unique(refs.begin(), refs.end());
	refs.erase(newEnd, refs.end());
}

GitVersionRefs::~GitVersionRefs()
{
}

Version GitVersionRefs::getLatest()
{
	return *refs.crbegin();
}
ostream& operator<<(ostream& os, const GitVersionRefs& refs)
{
	os << refs.refs << endl;
	return os;
}

