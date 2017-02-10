#include <mysql/mysql.h>
#include <stdlib.h>
#include <stdio.h>

void finish_with_error(MYSQL *con)
{
	fprintf(stderr, "%s\n", mysql_error(con));
	mysql_close(con);
	exit(1);        
}

int main(int argc, char **argv)
{
	MYSQL *con = mysql_init(NULL);

	if (con == NULL) 
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}  

	if (mysql_real_connect(con, "localhost", "root", "tts2002", 
				"mysql", 0, NULL, 0) == NULL) 
	{
		finish_with_error(con);
	}    

	if (mysql_query(con, "DROP TABLE IF EXISTS users")) 
	{
		finish_with_error(con);
	}

	if (mysql_query(con, "CREATE TABLE users (ID int, FirstName varchar(255), LastName varchar(255), Username varchar(255), Password BINARY(32), GitHub varchar(255), Rank int)")) 
	{      
		finish_with_error(con);
	}

	//if (mysql_query(con, "INSERT INTO Cars VALUES(1,'Audi',52642)")) 
	//{
	//	finish_with_error(con);
	//}

////if (mysql_query(con, "INSERT INTO users VALUES(1, 'Alex', 'Tsvetanov', 'alex_ts', 'Alex-Tsvetanov', 100)")) 
////{
////	finish_with_error(con);
////}


////mysql_query(con, "SELECT * FROM users");
////MYSQL_RES *res = mysql_use_result(con);
////printf("id\tfirst name\tlast name\tusername\tgithub\trank\n");
////MYSQL_ROW row;
////while ((row = mysql_fetch_row(res)) != NULL)
////{
////	printf("%s\t%s\t%s\t%s\t%s\t%s\n", row[0], row[1], row[2], row[3], row[4], row[5]);
////}
////mysql_free_result(res);

	mysql_close(con);
	exit(0);
}
