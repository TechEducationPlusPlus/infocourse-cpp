#include "C++/mysql.hpp"
#include "C++/table.hpp"

int main ()
{
	mysql client;

	client.connect_to_db ("mysql");

	printf ("%s\n", certificates::GetType ().c_str ());
	client.drop ("TABLE", "users");
	client.drop ("TABLE", "certificates");

	client.create ("TABLE", "users", users::GetType ());
	client.create ("TABLE", "certificates", certificates::GetType ());

	printf ("certificates: %s\n", certificate ("1", "Alex Tsvetanov", "C%2B%2B%26Algorithms", "100", "12 January 2016").GetValue ().c_str ());
	client.insert ("certificates", certificate ("1", "Alex Tsvetanov", "C%2B%2B%26Algorithms", "100", "12 January 2016").GetValue ());
	printf ("OK\n");

	auto rows = certificates::GetTable (client, "certificates");
	for (auto& x : rows)
	{
		printf ("%s %s %s %s %s\n", x.id.c_str (), x.name.c_str (), x.course.c_str (), x.score.c_str (), x.date.c_str ());
	}
	client.close ();
}
