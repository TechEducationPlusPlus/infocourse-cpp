#include <cstdlib>
#include <cerrno>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>

int main(int argc, char *argv[])
{
	if(argc < 2) 
	{
		std::cerr << "Example 11: Wrong number of arguments" << std::endl 
			<< "Example 11: Usage: example12 url" 
			<< std::endl;
		return EXIT_FAILURE;
	}

	char *url = argv[1];

	try 
	{
		curlpp::Cleanup cleaner;
		curlpp::Easy request;

		request.setOpt(new curlpp::options::Url(url)); 
		request.setOpt(new curlpp::options::Verbose(true)); 

		std::list<std::string> header; 
		header.push_back("Content-Type: application/octet-stream"); 

		request.setOpt(new curlpp::options::HttpHeader(header)); 

		request.setOpt(new curlpp::options::PostFields("abcd"));
		request.setOpt(new curlpp::options::PostFieldSize(5));

		request.perform(); 
	}
	catch ( curlpp::LogicError & e ) 
	{
		std::cout << e.what() << std::endl;
	}
	catch ( curlpp::RuntimeError & e ) 
	{
		std::cout << e.what() << std::endl;
	}

	return EXIT_SUCCESS;
}
