#include <C++/curl.hpp>
#include <C++/json.hpp>
#include <C++/fcgi/contest_api.hpp>
#include <fstream>
#include <iostream>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

using namespace rapidjson;
using namespace std;

void contest (std::string id)
{
	cout << "<head><TITLE>Contest</TITLE>\n";
	fstream fin ("./help_files/removeParams.js");
	string b;
	getline (fin, b);
	cout << b << "\n</head>";
	//std::string json = get_results::to_json (std::string("http://localhost:8000/quiz/results/") + id);
	std::string json = get_results::to_json (std::string("http://localhost/sample.json"));
//	json = "{\"asdf\": 200, \"alex\": 300}";

    Document d;
    d.Parse (json.c_str ());
	const rapidjson::Value& V = d;
	for (Value::ConstMemberIterator iter = V.MemberBegin () ; iter != V.MemberEnd (); ++ iter)
	{
		cout << iter->name.GetString() << "\t" << iter->value.GetInt() << "<br>\n";
	}
}

int main ()
{
	contest ("1");
}
