#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char server[] = "localhost";
	char user[] = "root";
	char password[] = "123456";
	char database[] = "mysql";

	conn = mysql_init(NULL);

	if (!mysql_real_connect(conn, server,user, password, database, 0, NULL, 0)) 
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

	if (mysql_query(conn, "show tables")) 
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

	res = mysql_use_result(conn);

	printf("MySQL Tables in mysql database:\n");

	while ((row = mysql_fetch_row(res)) != NULL)
	{
		printf("%s \n", row[0]);
	}

	mysql_free_result(res);
	mysql_close(conn);
	mysql_library_end();//free all the memory, valgrind and vld test pass

	printf("finish! \n");
	return 0;
}
