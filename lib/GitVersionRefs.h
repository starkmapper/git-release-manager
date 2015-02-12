#pragma once
#include <string>
#include <vector>
#include "Version.h"
#include <ostream>
typedef std::vector<Version> VersionRefList;
class GitVersionRefs
{
public:
	GitVersionRefs();
	virtual ~GitVersionRefs();
	/// Demotes all the refs in the list.
	void demote();
	/// Allows direct (read-only) access to the list of VersionRefs
	const VersionRefList getRefs()
	{
		return refs;
	}
	/// Returns the highest version number
	Version getLatest();
	/// Returns the highest version number for a specific release version
	Version getLatest(const Version& release);
	friend ostream& operator<<(ostream& os, const GitVersionRefs& refs);
protected:
	VersionRefList refs;
	/// Sorts refs in ascending order and removes duplicates
	void SortAndDedup();
};

