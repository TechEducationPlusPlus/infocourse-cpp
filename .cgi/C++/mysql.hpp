#ifndef __mysqlpp
#define __mysqlpp

#include <mysql/mysql.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>

struct mysql
{
	MYSQL *con;
	mysql ()
	{
		con = mysql_init(NULL);
		if (con == NULL) 
		{
			throw mysql_error (con);
		}  
	}

	void connect_to_db (const char* db)
	{
		if (mysql_real_connect(con, "localhost", "root", "tts2002", db, 0, NULL, 0) == NULL) 
		{
			this->error ();
		}    
	}

	void drop (std::string type, std::string name)
	{
		std::string command = "DROP " + type + " IF EXISTS " + name;
		if (mysql_query (con, command.c_str ())) 
		{
			this->error();
		}
	}

	void create (std::string type, std::string name, std::string kind)
	{
		std::string command = "CREATE " + type + " " + name + " " + kind;
		if (mysql_query(con, command.c_str ())) 
		{      
			this->error ();
		}
	}

	void insert (std::string where, std::string val)
	{
		std::string command = "INSERT INTO " + where + " VALUES " + val;
		if (mysql_query (con, command.c_str ())) 
		{
			this->error ();
		}
	}

	void error ()
	{
		std::string str = mysql_error(con);
		mysql_close (con);
		throw str;
	}

	void close ()
	{
		mysql_close (con);
	}
};

#endif
