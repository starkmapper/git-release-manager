#include <iostream>
#include <exception>
#include "VersionTests.h"

using namespace std;
int main(void)
{
	try
	{
		VersionTests TestVersions;
	}
	catch (exception &e)
	{
		cerr << "Test failed!" << endl << e.what()<< endl;
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}