#include <iostream>
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>
#include <string>

void contest(const Json::Value& root) 
{
    for (size_t i = 0 ; i < root.size () ; i ++)
    {
		std::cout << root [i].get ("name", "").asString () << " " << root [i].get ("points", "").asString () << "\n";
    }
}

int main (int argc, const char* argv[])
{
	{
		std::string strJson = "{\"mykey\" : \"myvalue\"}"; // need escape the quotes

		Json::Value root;   
		Json::Reader reader;
		bool parsingSuccessful = reader.parse( strJson.c_str(), root );     //parse process
		if ( !parsingSuccessful )
		{
			std::cout  << "Failed to parse"
				   << reader.getFormattedErrorMessages();
			return 0;
		}
		std::cout << root.get("mykey", "A Default Value if not exists" ).asString() << std::endl;
	}
	{
		std::string strJson = "{\"contest\": [{\"name\": \"Mico\", \"points\": 1000},{\"name\": \"TTC\", \"points\": 100},{\"name\": \"Ro6aff\", \"points\": 12}]}";

		Json::Value root;   
		Json::Reader reader;
		bool parsingSuccessful = reader.parse( strJson.c_str(), root );     //parse process
		if ( !parsingSuccessful )
		{
			std::cout  << "Failed to parse"
				   << reader.getFormattedErrorMessages();
			return 0;
		}
		contest (root);
	}
}
