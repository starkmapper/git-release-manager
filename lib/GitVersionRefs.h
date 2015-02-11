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
	friend ostream& operator<<(ostream& os, const GitVersionRefs& refs);
private:
	VersionRefList refs;

};

