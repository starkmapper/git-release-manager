#include "Version.h"
#include "FileLineException.h"
#include <regex>
#include <sstream>
#include <iomanip>
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
	normalize();
}
/**
 * Initializes the version object using a version string, formatted with supported seperators.
 * The longest substring matching only numbers an seperators is used to extract the versio information.
 * Prefix and suffix are ignored, but stored for now. This will most likely prove to be useless, so don't count on it.
 *
 * Supported seperators are: -._+/
 * @code
 * Version stringVersion("1.2/3-4") // Creates version 1.2.3.4 whilst preserving seperators
 * @endcode
 * @param[in] versionString Formatted version string
 */
Version::Version(const string& versionString)
{
	// Don't accept empty version
	if (versionString.size() == 0)
		throw(VersionException);
	// helper strings to easy searching
	string digits = "0123456789";
	string seperatorsString = "._/+";

	//Find the version info
	size_t start = versionString.find_first_of(digits);
	// No digits found
	if (start == string::npos)
	{
		throw VersionException;
	}
	else
	{
		try
		{
			// Basically while not break
			size_t stringSize = versionString.size();
			while (start < stringSize)
			{
				size_t end = versionString.find_first_not_of(digits, start);
				string element = versionString.substr(start, end - start);
				elementWidth.push_back(element.size());
				versionNumbers.push_back(stoi(element));
				// continue until no more seperators and digits are found
				if (end == string::npos)
				{
					seperators.push_back("");
					break;
				}
				else if (seperatorsString.find(versionString[end]) != string::npos
				         && digits.find(versionString[end + 1]) != string::npos) // when end+1 == size() [] operator returns "\0" in c++11 (http://en.cppreference.com/w/cpp/string/basic_string/operator_at)
				{
					start = end + 1;
					seperators.push_back(versionString.substr(end, 1));
				}
				else
					break;
			}
		}
		catch (exception& e)
		{
			throw (RethrownVersionException(e.what()));
		}
	}
	normalize();
}

void Version::normalize()
{
	normalizeVersionNumber();
	normalizeSeperators();
	normalizeWidth();
}
void Version::normalizeSeperators()
{
	// Set the last seperator to be an empty string
	if (!seperators.empty() && versionNumbers.size() <= seperators.size())
		seperators.pop_back();
	seperators.push_back("");
}

void Version::normalizeVersionNumber()
{
	//remove trailing zero's, allow only single 0 as version number
	while (versionNumbers.size() > 1 && versionNumbers.back() == 0)
		versionNumbers.pop_back();
}
void Version::normalizeWidth()
{
	while(versionNumbers.size() > elementWidth.size() || seperators.size() > elementWidth.size())
		elementWidth.push_back(0);
}

void Version::demote()
{
	if (versionNumbers.size() == seperators.size())
		versionNumbers.pop_back();
	seperators.pop_back();
	normalizeSeperators();

}

void Version::promote()
{
	seperators.pop_back();
	seperators.push_back(".");
	seperators.push_back(".");
	normalizeSeperators();
}

void Version::increment()
{
	// Re-add trailing zero's
	while (versionNumbers.size() < seperators.size())
		versionNumbers.push_back(0);
	// increment lease significant version element
	++versionNumbers.back();
}

Version& Version::operator++()
{
	increment();
	return *this;
}

Version Version::operator++(int)
{
	Version out = *this;
	increment();
	return out;
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
	const vector<int>& versionNumbers = Right.versionNumbers;
	const vector<string>& seperators = Right.seperators;
	const vector<int>& elementWidth = Right.elementWidth;
	vector<int>::const_iterator 	number 		= versionNumbers.cbegin();
	vector<string>::const_iterator	seperator 	= seperators.cbegin();
	vector<int>::const_iterator		width 		= elementWidth.cbegin();
	streamsize oldWidth = os.width();
	char oldFill = os.fill();
	os.fill('0');
	while (number != versionNumbers.cend())
		os << setw(*width++) << *number++ << setw(oldWidth) << *seperator++;

	while (seperator != seperators.cend())
		os << setw(*width++) << 0 << setw(oldWidth) << *seperator++;
	os.width(oldWidth);
	os.fill(oldFill);
	return os;
}

