#include "GitFlowHelpers.h"
#include "ExecuteCommand.h"
#include "to_string.hpp"
#include <iostream>
using namespace std;
void Hotfix::start(Version in)
{
	string command = "git flow hotfix start ";
	command += to_string(in);
	try
	{
		vector<string> results = ExecuteCommand(command);
		cout << results << endl;
	}
	catch (exception& e)
	{
		cout << "Error running command: " << command << endl;
	}
}
