#include <fstream>

#include <C++/mysql.hpp>
#include <C++/table.hpp>

#include <C++/sha256.hpp>
#include <C++/the-judgata.hpp>
#include <C++/chat.hpp>

using namespace std;

void register_user (Process& proc)
{
//fname, lname, email, password
	mysql client;

	client.connect_to_db ("mysql");

	string output_html = "";
	string BACK = "<br>" + proc.query_string["password"] + " -> " + sha256::GetHashCode (proc.query_string ["password"]) + "<br>";
	string fname = proc.query_string ["fname"];
	string lname = proc.query_string ["lname"];
	string email = proc.query_string ["email"];
	string password = proc.query_string ["password"];
	string github = proc.query_string ["github"];
	int rank = 0;
	auto rows = users::GetTable (client, "users");
	for (auto& x : rows)
	{
		if (x.email == proc.query_string ["email"])
		{
			output_html = "I'm sorry this email already exists!";
			break;
		}
	}

	cout << "<head><TITLE>MySQL test</TITLE>\n";
	fstream fin ("./help_files/removeParams.js");
	string b;
	getline (fin, b);
	cout << b << "\n</head>";

	if (output_html == "")
	{
		bool in_judgata = ("Found. Redirecting to /" == judge::registration ("email=" + email + "&password=" + password + "&password2=" + password));

		bool in_chat = (chat::registration ("username=" + fname + lname + "&email=" + email + "&display-name=" + fname + lname + "&first-name=" + fname + "&last-name=" + lname + "&password=" + password + "&password-confirm=" + password).find ("success") == string::npos);
		
		password = sha256::GetHashCode (proc.query_string ["password"]);
		client.insert ("users", user (rows.size (), fname, lname, email, password, github, rank).GetValue ());
		cout << "Adding (" << rows.size () << ", " << fname << ", " << lname << ", " << email << ", " << password << ", " << github << ", " << rank << ")\n";
	}
	else //exists
	{
		cout << output_html << "\n";
	}
}
