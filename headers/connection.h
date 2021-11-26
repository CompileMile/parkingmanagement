#include <mysql.h>

static MYSQL * conn;

static MYSQL_RES * res;
static MYSQL_ROW row;

static char * server = "localhost";
static char * user = "root";
static char * password = "root"; /* set me first */
static char * database = "users";

void connect_to_database() {

  conn = mysql_init(NULL);

  /* Connect to database */
  if (!mysql_real_connect(conn, server,
      user, password, database, 0, NULL, 0)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }
}

void all_users() {

  // /* send SQL query */
  if (mysql_query(conn, "select * from users where username='Norah';")) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }

  res = mysql_use_result(conn);

  // /* output table name */
  printf("MySQL Tables in mysql database:\n");
  while ((row = mysql_fetch_row(res)) != NULL)
    printf("%s\t%s\t%s \n", row[0], row[1], row[2]);

  /* close connection */
  mysql_free_result(res);
}

int get_user_id(char username[30], char password[30]) {
  int user_id = 0;
  char sql[1000];
  sprintf(sql, "select id from users where username='%s' and password='%s';", username, password);
  if (mysql_query(conn, sql)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }

  res = mysql_use_result(conn);
  while ((row = mysql_fetch_row(res)) != NULL) {
    // printf("\n%s\n", row[0]);
    user_id = atoi(row[0]);

  }
  /* close connection */
  mysql_free_result(res);

  return user_id;

}

void disconnect() {
  mysql_close(conn);
}