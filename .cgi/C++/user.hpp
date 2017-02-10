class user
{
public:
	int id;
	std::string first_name;
	std::string last_name;
	std::string email;
	std::string password;
	std::string github;
	int rank;

	user (char** row)
	{
		id = atoi (row [0]);
		first_name = std::string (row [1]);
		last_name = std::string (row [2]);
		email = std::string (row [3]);
		password = std::string (row [4]);
		github = std::string (row [5]);
		rank = atoi (row [6]);
	}

	user (
	        int _id = 0,
	std::string _first_name = "",
	std::string _last_name = "",
	std::string _email = "",
	std::string _password = "",
	std::string _github = "",
    	    int _rank = 0
		)
	{
		id = _id;
		first_name = _first_name;
		last_name = _last_name;
		email = _email;
		password = _password;
		github = _github;
		rank = _rank;
	}
	
	std::string GetValue ()
	{
		std::stringstream ss;
		ss << "(" << id << ", '" << first_name << "', '" << last_name << "', '" << email << "', '" << password << "', '" << github << "', " << rank << ")";
		return ss.str ();
	}

	static std::string GetType ()
	{
		return "(ID int, FirstName varchar(255), LastName varchar(255), Email varchar(255), Password BINARY(32), GitHub varchar(255), Rank int)";
	}
};


class users
{
public:
	static std::string GetType ()
	{
		return user::GetType ();
	}

	static std::vector < user > GetTable (mysql client, std::string where)
	{
		std::vector < user > ans;

		std::string command = "SELECT * FROM " + where;
		mysql_query (client.con, command.c_str ());
		MYSQL_RES* res = mysql_use_result (client.con);
		MYSQL_ROW row;
		while ((row = mysql_fetch_row(res)) != NULL)
		{
			ans.push_back (user (row));
		}
		mysql_free_result(res);

		return std::move (ans);
	}
};
