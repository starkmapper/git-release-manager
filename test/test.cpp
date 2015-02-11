#include <iostream>
#include <exception>
#include "VersionTests.h"
#include "TestGitVersionRefs.h"

using namespace std;
int main(void)
{
	try
	{
		VersionTests TestVersions;
		TestGitVersionRefs gitRefs;
	}
	catch (exception& e)
	{
		cerr << "Test failed!" << endl << e.what() << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}