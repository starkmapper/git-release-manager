#include "TestGitVersionRefs.h"
#include "GitVersionRefs.h"
#include "FileLineException.h"
#define THROW_IF_EQUAL(A,B) if (A==B) throw(BaseExceptions::FileLineException("GitVersionTest failed",__FILE__,__LINE__))
#define THROW_IF_UNEQUAL(A,B) if (A!=B) throw(BaseExceptions::FileLineException("GitVersionTest failed",__FILE__,__LINE__))
#define THROW_IF_NOTEQUAL(A,B) if (!(A==B)) throw(BaseExceptions::FileLineException("GitVersionTest failed",__FILE__,__LINE__))

TestGitVersionRefs::TestGitVersionRefs()
{
	testTags();
}
void TestGitVersionRefs::testTags()
{
	for (int count = 1; count <= 5; ++count)
		testRefs.push_back({ 0, count });
	GitVersionRefs refs;
	THROW_IF_UNEQUAL(refs.getRefs(), testRefs);

}


TestGitVersionRefs::~TestGitVersionRefs()
{
}
