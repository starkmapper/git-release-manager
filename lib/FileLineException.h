#pragma once
#include <exception>
#include <string>
namespace BaseExceptions
{
	using namespace std;
	class FileLineException : public exception
	{
	protected:
		FileLineException(){};
		int line;
		string file;
		string message;

	public:
		FileLineException(string message, string file, int line);
		virtual ~FileLineException(){};
		virtual const char* what() const;
	};

};