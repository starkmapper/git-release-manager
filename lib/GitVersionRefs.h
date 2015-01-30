#pragma once
#include <string>
#include <vector>
#include "Version.h"
#include <ostream>

class GitVersionRefs
{
public:
	GitVersionRefs();
	virtual ~GitVersionRefs();
	const std::vector<Version> getRefs()
	{
		return refs;
	}
	friend ostream& operator<<(ostream& os, const GitVersionRefs& refs);
private:
	std::vector<Version> refs;

};

