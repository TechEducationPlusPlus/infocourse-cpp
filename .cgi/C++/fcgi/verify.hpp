#include <fstream>

#include <C++/mysql.hpp>
#include <C++/table.hpp>

using namespace std;

void verify_certificate (Process& proc)
{
	for (auto& y : user_certs)
	{
		for (auto& z : y.second)
		{
			auto x = z.second;
			if (x.id == proc.query_string ["id"])
			{
				certByCert (x);
				return;
			}
		}
	}

	cout << "This certificate doesn't exist!" << endl;
}

void new_certificate (Process& proc)
{

	user_certs [proc.query_string ["username"]][proc.query_string ["course"]] = 
	certify (
		proc.query_string ["date"],
		proc.query_string ["course"],
		proc.query_string ["score"],
		proc.query_string ["name"],
		proc.query_string ["id"]
	);
	string URL = "/.cgi?type=get_certs&username=" + proc.query_string ["username"];
	fstream fin1 ("./help_files/redirect.html");
	string a;
	getline (fin1, a);
	a.replace (a.find ("$URL$"), (string ("$URL$")).size (), URL);
	a.replace (a.find ("$URL$"), (string ("$URL$")).size (), URL);
	a.replace (a.find ("$URL$"), (string ("$URL$")).size (), URL);
	cout << a << "\n";
}
