#include "TestGitVersionRefs.h"
#include "GitVersionRefs.h"
#include "FileLineException.h"
#include <algorithm>
#include <iostream>
#include "to_string.hpp"
#define THROW_IF_EQUAL(A,B) { std::cout << "Testing \t" << A << " != " << B<<endl; if (A==B) throw(BaseExceptions::FileLineException("VersionTest failed\n"+to_string(A)+"\t==\t"+to_string(B),__FILE__,__LINE__)); }
#define THROW_IF_UNEQUAL(A,B) { std::cout << "Testing \t" << A << " == " << B <<endl; if (A!=B) throw(BaseExceptions::FileLineException("VersionTest failed\n"+to_string(A)+"\t!=\t"+to_string(B),__FILE__,__LINE__)); }
#define THROW_IF_NOTEQUAL(A,B) { std::cout << "Testing \t" << A << " == " << B<<endl; if (!(A==B)) throw(BaseExceptions::FileLineException("VersionTest failed\n"+to_string(A)+"\tNOT ==\t"+to_string(B),__FILE__,__LINE__)); }

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
	for (int major = 1;major <= 5; major++)
		for (int count = 0; count <= 5; ++count)
			testRefs.push_back({major,count});
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
	// If the version number is lower than the lowest version available, the lowest existing release is returned
	THROW_IF_UNEQUAL(refTest.getLatest({0}), Version({1,0}));
	
	for (int i = 1; i < 6; i++)
		THROW_IF_UNEQUAL(refTest.getLatest({i}), Version({i,5}));
	
	// There is no version 6, so it should return the last version not higher, or should it?
	THROW_IF_UNEQUAL(refTest.getLatest({6}), Version({5,5}));
	
	// Should return the highest version number when a crazy high version number is queried for
	THROW_IF_UNEQUAL(refTest.getLatest({5000}), refTest.getLatest());
	
}

TestGitVersionRefs::~TestGitVersionRefs()
{
}
