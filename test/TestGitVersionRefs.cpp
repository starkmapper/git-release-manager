#include "TestGitVersionRefs.h"
#include "GitVersionRefs.h"
#include "FileLineException.h"
#include <algorithm>
#define THROW_IF_EQUAL(A,B) if (A==B) throw(BaseExceptions::FileLineException("GitVersionTest failed",__FILE__,__LINE__))
#define THROW_IF_UNEQUAL(A,B) if (A!=B) throw(BaseExceptions::FileLineException("GitVersionTest failed",__FILE__,__LINE__))
#define THROW_IF_NOTEQUAL(A,B) if (!(A==B)) throw(BaseExceptions::FileLineException("GitVersionTest failed",__FILE__,__LINE__))

/// Test class to allow data injection
class GVRTest : public GitVersionRefs
{
public:
	GVRTest(VersionRefList in)
	{
		refs = in;
		sort(refs.begin(), refs.end());
	};
};

TestGitVersionRefs::TestGitVersionRefs()
{
	initTestData();
	testTags();
	testGetLatest();
}
void TestGitVersionRefs::initTestData()
{
	testRefs.push_back({25,17});
	Version testVersion = {0, 0};
	for (int count = 1; count <= 5; ++count)
		testRefs.push_back(++testVersion);
	testVersion.demote();
	++testVersion;
	testVersion.promote();
	for (int count = 1; count <= 5; ++count)
		testRefs.push_back(++testVersion);
		testVersion.demote();
	++testVersion;
	testVersion.promote();
	for (int count = 1; count <= 5; ++count)
		testRefs.push_back(++testVersion);
		testVersion.demote();
	++testVersion;
	testVersion.promote();
	for (int count = 1; count <= 5; ++count)
		testRefs.push_back(++testVersion);
		testVersion.demote();
	++testVersion;
	testVersion.promote();
	for (int count = 1; count <= 5; ++count)
		testRefs.push_back(++testVersion);

}
void TestGitVersionRefs::testTags()
{
	VersionRefList localRefs;
	for (int count = 1; count <= 5; ++count)
		localRefs.push_back({ 0, count });
	GitVersionRefs refs;
	THROW_IF_UNEQUAL(refs.getRefs(), localRefs);

}

void TestGitVersionRefs::testGetLatest()
{
	GVRTest refTest = testRefs;
	THROW_IF_UNEQUAL(refTest.getLatest(), Version({25,17}));
	for (int i = 0; i < 5; i++)
		THROW_IF_UNEQUAL(refTest.getLatest({i}), Version({i,5}));

	// What to do when the requested release doesn't exist yet?
}

TestGitVersionRefs::~TestGitVersionRefs()
{
}
