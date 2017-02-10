#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <sstream>
#include <string>
#include <iostream>

int main ()
{

	std::ostringstream os;
	os << curlpp::options::Url(std::string("http://tsalex.tk"));

	std::string asAskedInQuestion = os.str();
	
	std::cout << asAskedInQuestion << "\n";
}
