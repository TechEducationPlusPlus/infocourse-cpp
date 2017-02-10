#include <fstream>

using namespace std;

void cert (Process& proc)
{
	cout << "<head><TITLE>Certificate</TITLE>\n";
	fstream fin ("./help_files/removeParams.js");
	string b;
	getline (fin, b);
	cout << b << "\n</head>";

	fstream fin1 ("./help_files/big_cert_one_line.html");
	string a;
	getline (fin1, b);
	a += b;
	a.replace (a.find ("$date$"), (string ("$date$")).size (), proc.query_string ["date"]);
	a.replace (a.find ("$course$"), (string ("$course$")).size (), proc.query_string ["course"]);
	a.replace (a.find ("$score$"), (string ("$score$")).size (), proc.query_string ["score"]);
	a.replace (a.find ("$name$"), (string ("$name$")).size (), proc.query_string ["name"]);
	a.replace (a.find ("$ID$"), (string ("$ID$")).size (), proc.query_string ["id"]);
	cout << a << "\n";
}

struct certify 
{
	string date;
	string course;
	string score;
	string name;
	string id;

	certify (string d = "", string c = "", string s = "", string n = "", string i = "")
	{
		date = d;
		course = c;
		score = s;
		name = n;
		id = i;
	}

	string get ()
	{
		fstream fin1 ("./help_files/big_cert_one_line.html");
		string a;
		getline (fin1, a);
		a.replace (a.find ("$date$"), (string ("$date$")).size (), date);
		a.replace (a.find ("$course$"), (string ("$course$")).size (), course);
		a.replace (a.find ("$score$"), (string ("$score$")).size (), score);
		a.replace (a.find ("$name$"), (string ("$name$")).size (), name);
		a.replace (a.find ("$ID$"), (string ("$ID$")).size (), id);
		return move (a);
	}
};

void certByCert (certify& proc)
{
	cout << "<head><TITLE>Certificate</TITLE>\n";
	fstream fin ("./help_files/removeParams.js");
	string b;
	getline (fin, b);
	cout << b << "\n</head>";

	fstream fin1 ("./help_files/big_cert_one_line.html");
	string a;
	getline (fin1, b);
	a += b;
	a.replace (a.find ("$date$"), (string ("$date$")).size (), proc.date);
	a.replace (a.find ("$course$"), (string ("$course$")).size (), proc.course);
	a.replace (a.find ("$score$"), (string ("$score$")).size (), proc.score);
	a.replace (a.find ("$name$"), (string ("$name$")).size (), proc.name);
	a.replace (a.find ("$ID$"), (string ("$ID$")).size (), proc.id);
	cout << a << "\n";
}
