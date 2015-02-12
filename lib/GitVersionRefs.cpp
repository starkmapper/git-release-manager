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
	SortAndDedup();
}
void GitVersionRefs::SortAndDedup()
{
	sort(begin(refs), end(refs));
	VersionRefList::iterator newEnd = unique(refs.begin(), refs.end());
	refs.erase(newEnd, refs.end());
}

void GitVersionRefs::demote()
{
	for (Version& version : refs)
		version.demote();

	SortAndDedup();

}

GitVersionRefs::~GitVersionRefs()
{
}

Version GitVersionRefs::getLatest()
{
	return *refs.crbegin();
}
Version GitVersionRefs::getLatest(const Version& release)
{
	Version HighestVersion = release;
	// Increment release version
	HighestVersion.increment();
	// Find lowest version of the next release
	VersionRefList::iterator HigherVersion = lower_bound(refs.begin(), refs.end(), HighestVersion);
	// Check if this actually exists
	// Throw something when it doesn't exist yet
	if (HigherVersion != refs.begin())
		--HigherVersion;

	HighestVersion = *HigherVersion;
	return HighestVersion;
}
ostream& operator<<(ostream& os, const GitVersionRefs& refs)
{
	os << refs.refs << endl;
	return os;
}

