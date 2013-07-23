/* THIS PROGRAM IS MADE FOR AUTOMATICALLY DETECT AND MARKING PRESENCE OF DEVICES WITHIN A BLUETOOTH SPACE
 * 	AUTHOR		: Saurajeet Dutta, Amit Abhinav Singh, Anurag Pandey, Jyoti Prakash Nath
 *	CONSULTANCY	: <vention.gothics@gmail.com>, <amitabhaDJ@sify.com>, <anuragbuddy@gmail.com>, <jp2018@gmail.com>
 *	PROGRAM	NAME	: OmniPresence
 *	OCCUPATION	: Just a student man!
 * 	INSTITUTION	: Birla Institute Of Technology, Lalpur, Ranchi - 834001
 *	COMMUNITY	: Research and Development Wing
 *	TEAM		: Advanced C/C++ Research Team
 *	iNsPirAtion	: MY TEAM MEMBERS
 *	TakenAbackBy	: My Typing Speed! (Only 300 cps)
 * 	LICENSE		: Freely Redistributable (FREE) ("GPL v2")
 * WE DONOT COVER ANY RESPONSIBILITY OF HARM CAUSED BY THE USE OF THIS TECHNOLOGY, THOUGH BOUNDS OF THIS S/W HAS BEEN TESTED BEFORE
 * DEPLOYMENT. FOR ANY LEGAL ACTIONS, PROCEEDINGS SHOULD BE IN COURTS OF RANCHI ONLY!
 */
#include <mysql/mysql.h>
#include <stdio.h>

int main(void) {
   MYSQL *conn;
   MYSQL_RES *res;
   MYSQL_ROW row;
  /* Change me */
   char *server = "localhost";
   char *user = "root";
   char *password = "omni";
   char *database = "omniPresence";
   conn = mysql_init(NULL);
   
   /* Connect to database */
   if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) 
   {
      fprintf(stderr, "%s\n", mysql_error(conn));
     return 1;
   }

   /* send SQL query */
   if (mysql_query(conn, "select * from developers")) 
   {
      fprintf(stderr, "%s\n", mysql_error(conn));
      return 1;
   }

   res = mysql_use_result(conn);
   
   /* output table name */
   printf("Developers of omniPresence are:\n");
   while ((row = mysql_fetch_row(res)) != NULL)
      printf("%s\t%s\t\t%s\t%s\t%s\n", row[0], row[1], row[2], row[3], row[4]);
   
   /* close connection */
   mysql_free_result(res);
   mysql_close(conn);
  
  return 0;
}
