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
/**
 * Initializes the Version object with the version elements provided, using a "." as seperator.
 * @code
 * Version someVer{1,2,3,4}; // Creates version 1.2.3.4
 * @endcode
 * 
 * @param[in] Args Comma seperated list of version elements
 * 
 */
Version::Version(initializer_list<int> Args)
{
	for (int versionPart : Args)
	{
		versionNumbers.push_back(versionPart);
		seperators.push_back(".");
	}
	normalizeVersionNumber();
	normalizeSeperators();
	
}
/**
 * Initializes the version object using a version string, formatted with supported seperators. 
 * The longest substring matching only numbers an seperators is used to extract the versio information.
 * Prefix and suffix are ignored, but stored for now. This will most likely prove to be useless, so don't count on it.
 * 
 * Supported seperators are: -._+/
 * @code
 * Version stringVersion("1.2/3-4") // Creates version 1.2.3.4 whilst preserving seperators
 *   
 * @param[in] versionString Formatted version string
 */
Version::Version(const string &versionString)
{
	// Don't accept empty version
	if ( versionString.size() == 0)
		throw(VersionException);
	// Find one or more digits with 0 or more trailing characters
	// Concatenating this string finds anything in the form of 1 1.2.3 or even 1,2.3.27-2a0123[12
	string digitsString = "([[:digit:]]+)";
	/* libstdc++ doesn't handle the ^ operator well (appears to turn it into match any)
	 * string seperatorString = "([^[:digit:]]{1}|$)";
     */
	string seperatorString = "([\\-._+/]{1}|$)";
	string regexBuilderString = digitsString+seperatorString;
	string regexString;
	int nrOfDigits;
	
	//find the number of digits
	for (nrOfDigits = 0; regex_search(versionString, regex(regexString + regexBuilderString), regex_constants::match_not_bol); ++nrOfDigits)
		regexString += regexBuilderString;

	smatch versionMatch;
	try
	{
		if (regex_search(versionString, versionMatch, regex(regexString)))
		{
			// First result it the entire matched string
			smatch::iterator versionResult = versionMatch.begin()+1;
			
			while (versionResult != versionMatch.end() )
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
	normalizeVersionNumber();
	normalizeSeperators();
}

void Version::normalizeSeperators()
{
	// Set the last seperator to be an empty string
	if(!seperators.empty() && versionNumbers.size() <= seperators.size())
		seperators.pop_back();
	seperators.push_back("");
}

void Version::normalizeVersionNumber()
{
	//remove trailing zero's, allow only single 0 as version number
	while ( versionNumbers.size() > 1 && versionNumbers.back() == 0)
		versionNumbers.pop_back();
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


ostream& operator<<(ostream& os, const Version& Right)
{
	const vector<int> &versionNumbers = Right.versionNumbers;
	const vector<string> &seperators = Right.seperators;
	vector<int>::const_iterator number = versionNumbers.cbegin();
	vector<string>::const_iterator seperator = seperators.cbegin();
	while (number != versionNumbers.cend())
		os << *number++ << *seperator++;

	while (seperator != seperators.cend())
		os << 0 << *seperator++;

	return os;
}
