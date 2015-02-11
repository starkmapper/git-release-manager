#include "GitVersionRefs.h"
#include "FileLineException.h"
#include <cstdlib>
#include <fstream>
#include "to_string.hpp"
#include <algorithm>
using namespace std;
// RAII FTW!
class tempFile
{
public:
	tempFile()
	{
		tmpnam(name);
	}
	~tempFile()
	{
		remove(name);
	}
	char name[L_tmpnam];

};

GitVersionRefs::GitVersionRefs()
{

	if (system(NULL))
	{
		tempFile tmp;
		string command = "git tag >> ";
		command += tmp.name;
		int return_value = system(command.c_str());

		ifstream resultFile(tmp.name, ios::in);
		string line;
		std::vector<std::string> refStrings;
		while (!resultFile.eof())
		{
			getline(resultFile, line);
			refStrings.push_back(move(line));
		}
		if (return_value != 0)
		{
			string errorMessage = "Error executing command: \"";
			errorMessage += command + "\"";
			for (string& line : refStrings)
				errorMessage += line + "\n";
			throw (FileLineExceptionMessage(errorMessage));
		}
		else
		{
			for (string& line : refStrings)
			{
				try
				{
					refs.emplace_back(line);
				}
				catch (...) {}
			}
		}
	}
	else
		throw (FileLineExceptionMessage("No command processor available!"));

}

void GitVersionRefs::demote()
{
	for (Version& version : refs)
		version.demote();

	VersionRefList::iterator newEnd = unique(refs.begin(), refs.end());
	refs.erase(newEnd, refs.end());
}

GitVersionRefs::~GitVersionRefs()
{
}
ostream& operator<<(ostream& os, const GitVersionRefs& refs)
{
	os << refs.refs << endl;
	return os;
}

