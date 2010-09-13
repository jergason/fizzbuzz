#include <csignal>
#include <boost/program_options.hpp>
#include <boost/cstdlib.hpp>
#include "tut/tut.hpp"
#include "tut/tut_reporter.hpp"

///@file
///All tests are auto-included through linking thanks to the TUT Unit Test frame-work
///@see tut

namespace tut 
{ 
	test_runner_singleton gRunner;
}

namespace
{
	const std::string gTestGroupDefault = "all";
	const int gTestDefault = -1;
}

std::string gCurrentTest = "";


void segfault_handler(int num)
{
	std::cout << "Died during the test \"" << gCurrentTest << "\"" << std::endl;
	exit(-1);
}


namespace po = boost::program_options;

void print_tests ()
{
	std::cout << "CS 240 Collections Pass Off" << std::endl;
	std::cout << std::endl << "Tests: " << std::endl;
	
	tut::groupnames names = tut::runner.get().list_groups();
	tut::groupnames::iterator nameItr = names.begin();
	for (; nameItr != names.end(); ++nameItr)
		std::cout << "\t\"" << *nameItr << "\"" << std::endl;
}

bool run (const std::string &testGroup, int test)
{
	std::cout << "CS 240 Collections Pass Off" << std::endl;
	tut::reporter reportPresenter;
	tut::runner.get().set_callback(&reportPresenter);

	if (testGroup == gTestGroupDefault)
		tut::runner.get().run_tests (); 
	else if (test == gTestDefault)
		tut::runner.get().run_tests (testGroup);
	else
		tut::runner.get().run_test (testGroup, test);
	
	std::cout << std::endl << "Finished" << std::endl;
	
	return true;
}


int main(int argc, char* argv[]) 
{
	bool success = true;

	try
	{
		std::string testGroup;
		int test;
	
		po::options_description optionList ("Allowed options");
		optionList.add_options()
			("test,t", po::value<std::string>(&testGroup)->default_value(gTestGroupDefault), "Selects which test group to run")
			("number,n", po::value<int>(&test)->default_value(gTestDefault), "Select a test within a group")
			("list-tests,l", "List available tests")
			("disable-seg,d", "Disable the seg-fault handler to make debugging easier")
			("help,h", "Prints this message")
			;
	
		po::positional_options_description positionalOptions;
		positionalOptions.add("test", -1);
	
		po::variables_map parsedOptions;
		po::store (po::command_line_parser (argc, argv).options(optionList).positional(positionalOptions).run(), parsedOptions);
		po::notify (parsedOptions);

		if (parsedOptions.count("disable-seg") == 0)
			std::signal(SIGSEGV, segfault_handler);
	
		if (0 < parsedOptions.count("help"))
		{
			std::cout << "CS 240 Collections Pass Off" << std::endl;
			std::cout << optionList << std::endl;
		}
		else if (0 < parsedOptions.count("list-tests"))
			print_tests();
		else
			success = run(testGroup, test);
	
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		std::cerr << "Abborting" << std::endl;
		success = false;;
	}

	return success? boost::exit_success : boost::exit_failure;
}
