#include "ExecuteCommand.h"
#include <cstdlib>
#include <fstream>
#include "FileLineException.h"
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
using namespace std;
/**
 * Uses system() from the C std lib to execute the command, and redirects it to a temporary file.
 *
 * @param[in] inCommand Commandline to execute
 * @return Vector of strings, one per line of output by executing the command
 */
vector<string> ExecuteCommand(const string& inCommand)
{
	vector<string> refs;
	if (system(NULL))
	{
		tempFile tmp;
		string command = inCommand;
		command += " >> ";
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
			errorMessage += inCommand + "\"";
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
					refs.push_back(std::move(line));
				}
				catch (...) {}
			}
		}
	}
	else
	{
		throw (FileLineExceptionMessage("No command processor available!"));
	}

	return refs;
}