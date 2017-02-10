class certificate
{
public:
	std::string id;
	std::string name;
	std::string score;
	std::string course;
	std::string date;

	certificate (char** row)
	{
		id = std::string (row [0]);
		name = std::string (row [1]);
		course = std::string (row [2]);
		score = std::string (row [3]);
		date = std::string (row [4]);
	}

	certificate (
	        std::string _id = "0",
	std::string _name = "",
	std::string _course = "",
	std::string _score = "",
	std::string _date = ""
		)
	{
		id = _id;
		name = _name;
		course = _course;
		score = _score;
		date = _date;
	}
	
	std::string GetValue ()
	{
		std::stringstream ss;
		ss << "('" << id << "', '" << name << "', '" << course << "', '" << score << "', '" << date << "')";
		return ss.str ();
	}

	static std::string GetType ()
	{
		return "(ID varchar(255), Name varchar(511), Course varchar(255), Score varchar(255), Date varchar(255))";
	}
};


class certificates
{
public:
	static std::string GetType ()
	{
		return certificate::GetType ();
	}

	static std::vector < certificate > GetTable (mysql client, std::string where)
	{
		std::vector < certificate > ans;

		std::string command = "SELECT * FROM " + where;
		mysql_query (client.con, command.c_str ());
		MYSQL_RES* res = mysql_use_result (client.con);
		MYSQL_ROW row;
		while ((row = mysql_fetch_row(res)) != NULL)
		{
			ans.push_back (certificate (row));
		}
		mysql_free_result(res);

		return std::move (ans);
	}
};
