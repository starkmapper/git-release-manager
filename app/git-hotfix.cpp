#include <iostream>
#include "GitVersionRefs.h"
#include "NotImplementedException.h"
#include "ExecuteCommand.h"
#include <boost/program_options.hpp>
#include "GitFlowHelpers.h"
namespace po = boost::program_options;
using namespace std;
int main(int ac, char* av[])
{
	po::options_description desc("Supported options");
	desc.add_options()
	("help", "Print this help message, but you knew that already")
	("auto,a", "Auto increment latest release version and start a new Hotfix for it using git-flow");

	try
	{
		po::variables_map vars;
		po::store(po::parse_command_line(ac, av, desc), vars);
		po::notify(vars);

		GitVersionRefs refs;
		if (vars.size() == 0)
		{
			cout << refs;
			return 0;
		}
		if (vars.count("help"))
		{
			cout << desc << "\n";
			return 0;
		}
		if (vars.count("auto"))
		{
			Version hotfix = refs.getLatest();
			hotfix.increment();
			Hotfix::start(hotfix);
		}
	}
	catch (po::unknown_option)
	{
		cout << desc << endl;
	}
	catch (exception& e)
	{
		cerr << "error: " << e.what() << endl;
		return 1;
	}
	catch (...)
	{
		cerr << "unknown error" << endl;
	}
}

