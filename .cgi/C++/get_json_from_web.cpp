#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <sstream>
 
#include <iostream>
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>
#include <string>

int main(int argc, char *argv[])
{
	std::ostringstream os;
	os << curlpp::options::Url(std::string("http://infocourse.techedu.cf/test/index.json"));

	std::string asAskedInQuestion = os.str();
	
	std::cout << asAskedInQuestion << "\n";

	Json::Value root;   
	Json::Reader reader;
	bool parsingSuccessful = reader.parse (asAskedInQuestion.c_str (), root);
	if (not parsingSuccessful)
	{
		std::cout  << "Failed to parse"
			<< reader.getFormattedErrorMessages();
		return 0;
	}

    for (const Json::Value& person : root["contest"])
    {
		std::cout << person.get ("name", "").asString () << " " << person.get ("points", "").asString () << "\n";
    }
	return 0;
}
