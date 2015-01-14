#include "Version.h"
#include "NotImplementedException.h"
#include <regex>
#include <sstream>

using namespace std;
Version::Version()
{
}
Version::Version(initializer_list<int> Args)
{
	for (int versionPart : Args)
		versionNumbers.push_back(versionPart);
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
	regex_search(versionString, versionMatch, regex(regexString));
	int versionRegexMatches = distance(versionMatch.begin(), versionMatch.end());
	for (auto index = 1; index < versionMatch.size(); index+=2)
		versionNumbers.push_back(stoi(versionMatch[index]));
	
	for (auto index = 2; index < versionMatch.size(); index += 2)
		seperators.push_back(versionMatch[index]);
	suffix = versionMatch.suffix().str();
	prefix = versionMatch.prefix().str();

	//throw(BaseExceptions::NotImplementedException(__FILE__, __LINE__));
}