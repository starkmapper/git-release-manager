#include "FileLineException.h"
#define NOT_IMLEMENTED_YET() BaseExceptions::NotImplementedException(__FILE__, __LINE__)
namespace BaseExceptions
{
	class NotImplementedException : public FileLineException
	{
	private:
		NotImplementedException() {};
	public:
		NotImplementedException(string file, int line) : FileLineException("Not implemented (yet)", file, line) {};
	};
}

