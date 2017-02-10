#include "mysql.hpp"
#include "table.hpp"

int main ()
{
	mysql client;

	client.connect_to_db ("mysql");

//	client.drop ("TABLE", "certs");

	client.create ("TABLE", "certs", certs::GetType ());

	client.insert ("certs", cert (1, "Alex Tsvetanov", "C++&Algorithms", "100", "12 January 2016").GetValue ());

	auto rows = certs::GetTable (client, "certs");
	for (auto& x : rows)
	{
		printf ("%d %s %s %s %s\n", x.id, x.name.c_str (), x.course.c_str (), x.score.c_str (), x.date.c_str ());
	}

	client.close ();
}
