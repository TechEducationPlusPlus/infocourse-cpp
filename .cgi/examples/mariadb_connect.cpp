#include <iostream>
#include <mysql/mysql.h>  // require libmysqlclient-dev
#include <string>

using namespace std;

class Proc
{
    const char* MY_HOSTNAME;
    const char* MY_DATABASE;
    const char* MY_USERNAME;
    const char* MY_PASSWORD;
    const char* MY_SOCKET;
    enum 
	{
        MY_PORT_NO = 3306,
        MY_OPT     = 0
    };

    MYSQL     *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

public:
    Proc ();
    bool execMain();
};

Proc::Proc()
{
    MY_HOSTNAME = "localhost";
    MY_DATABASE = "mysql";
    MY_USERNAME = "root";
    MY_PASSWORD = "tts2002";
    MY_SOCKET   = NULL;
}

bool Proc::execMain()
{
    try 
	{
        conn = mysql_init(NULL);

        if (!mysql_real_connect (
									conn,
									MY_HOSTNAME, MY_USERNAME,
									MY_PASSWORD, MY_DATABASE,
									MY_PORT_NO, MY_SOCKET, MY_OPT
								)
			) 
		{
            cerr << mysql_error (conn) << endl;
            return false;
        }

        if (mysql_query (conn, "SHOW TABLES")) 
		{
            cerr << mysql_error (conn) << endl;
            return false;
        }

        res = mysql_use_result(conn);

        cout << "* MySQL - SHOW TABLES in `"
             << MY_DATABASE << "`" << endl;
        
		while ((row = mysql_fetch_row(res)) != NULL)
            cout << row[0] << endl;

        mysql_free_result(res);

        mysql_close (conn);
    } 
	catch (char* e) 
	{
        cerr << "[EXCEPTION] " << e << endl;
        return false;
    }
    return true;
}

int main ()
{
    try 
	{
        Proc objMain;
        bool bRet = objMain.execMain ();
        if (!bRet) 
			cout << "ERROR!" << endl;
    }
	catch (char* e) 
	{
        cerr << "[EXCEPTION] " << e << endl;
        return 1;
    }
    return 0;
}
