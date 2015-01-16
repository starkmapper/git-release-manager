#include "Version.h"
#include "FileLineException.h"
#include <regex>
#include <sstream>
#define VersionException BaseExceptions::FileLineException("Illegal version string: "+versionString,__FILE__, __LINE__)
#define RethrownVersionException(M) BaseExceptions::FileLineException(M+versionString,__FILE__, __LINE__)
using namespace std;
Version::Version()
{
}
Version::Version(initializer_list<int> Args)
{
	for (int versionPart : Args)
	{
		versionNumbers.push_back(versionPart);
		seperators.push_back(".");
	}
	
	
}
Version::Version(const string &versionString)
{
	// Find one or more digits with 0 or more trailing characters
	// Concatenating this string finds anything in the form of 1 1.2.3 or even 1,2.3.27-2a0123[12
	string digitsString = "([[:digit:]]+)";
	string seperatorString = "([^[:digit:]]{1}|$)";
	string regexBuilderString = digitsString+seperatorString;
	string regexString;
	int nrOfDigits;
	
	//find the number of digits
	for (nrOfDigits = 0; regex_search(versionString, regex(regexString + regexBuilderString)); ++nrOfDigits)
		regexString += regexBuilderString;

	smatch versionMatch;
	try
	{
		if (regex_search(versionString, versionMatch, regex(regexString)))
		{
			// First result it the entire matched string
			smatch::iterator versionResult = versionMatch.begin() + 1;
			while (versionResult != versionMatch.end())
			{
				versionNumbers.push_back(stoi(*versionResult));
				versionResult++;
				seperators.push_back(*versionResult);
				versionResult++;
			}
			suffix = versionMatch.suffix().str();
			prefix = versionMatch.prefix().str();
		}
		else
		{
			throw(VersionException);
		}
	}
	catch (exception &e)
	{ 
		throw(RethrownVersionException(e.what()));
	}

}

bool operator==(const Version& Left, const Version& Right)
{
	return Left.versionNumbers == Right.versionNumbers;
}

bool operator!=(const Version& Left, const Version& Right)
{
	return Left.versionNumbers != Right.versionNumbers;
}

bool operator>(const Version& Left, const Version& Right)
{
	return Left.versionNumbers > Right.versionNumbers;
}
bool operator>=(const Version& Left, const Version& Right)
{
	return Left.versionNumbers > Right.versionNumbers;
}
bool operator<(const Version& Left, const Version& Right)
{
	return Left.versionNumbers < Right.versionNumbers;	
}
bool operator<=(const Version& Left, const Version& Right)
{
	return Left.versionNumbers < Right.versionNumbers;
}