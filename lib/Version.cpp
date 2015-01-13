#include "Version.h"
#include "NotImplementedException.h"
#include <regex>
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
	string digitsString("([[:digit:]]+)(.*)");
	string regexString = digitsString;
	regex versionRegex(regexString);
	int nrOfDigits;
	//find the number of digits
	for (nrOfDigits = 0; regex_search(versionString, regex(regexString)); ++nrOfDigits)
		regexString += digitsString;
	
	throw(BaseExceptions::NotImplementedException(__FILE__, __LINE__));
}