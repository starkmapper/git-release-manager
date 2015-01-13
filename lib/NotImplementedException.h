#include "FileLineException.h"

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
