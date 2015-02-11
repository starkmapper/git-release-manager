#pragma once
#include "Version.h"
#include <vector>
class TestGitVersionRefs
{
public:
	TestGitVersionRefs();
	~TestGitVersionRefs();
	void initTestData();
	void testTags();
	void testGetLatest();

private:
	vector<Version> testRefs;
};

