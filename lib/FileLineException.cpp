#include "FileLineException.h"
#include <sstream>
namespace BaseExceptions
{
	using namespace std;
	FileLineException::FileLineException(string inMessage, string inFile, int inLine) :line(inLine), file(inFile), message(inMessage)
	{
		// Remove directory part of string
		file.erase(0,file.find_last_of("/\\")+1);
		stringstream messageFormatter;
		messageFormatter << file << " line " << line << ": " << message;
		this->message = messageFormatter.str();
	}

	const char* FileLineException::what() const noexcept
	{
		return message.c_str();
	}
}
