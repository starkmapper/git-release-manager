#pragma once
#include <string>
#include <vector>
#include "Version.h"

class GitVersionRefs
{
public:
	GitVersionRefs();
	virtual ~GitVersionRefs();
	const std::vector<Version> getRefs()
	{
		return refs;
	}
private:
	std::vector<Version> refs;

};

