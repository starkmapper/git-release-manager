#pragma once
#include "Version.h"
#include <vector>
class TestGitVersionRefs
{
public:
	TestGitVersionRefs();
	~TestGitVersionRefs();
	void testTags();
private:
	vector<Version> testRefs;
};

