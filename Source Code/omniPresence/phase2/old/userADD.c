#include<gtk/gtk.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<mysql/mysql.h>
#include"rnadgen.h"
#include"login.h"
//************************************GLOBAL VARIABLE DECLARATION**************************
static char MAC[19]="",NAME[50]="",EMPID[15]="",PHNO[15]="",entry_result[25]="";
const char *value_MAC,*value_name,*value_empid,*value_phno;
int ch = 1;

//************************************GLOBAL FUNCTION DECLARATION**************************

static void get_MAC(GtkWidget *widget,GtkWidget *entry)
{
	value_MAC = gtk_entry_get_text(GTK_ENTRY(entry));
	strcpy(MAC,value_MAC);
}

static void get_name(GtkWidget *widget,GtkWidget *entry)
{
        value_name = gtk_entry_get_text(GTK_ENTRY(entry));
        strcpy(NAME,value_name);
}

static void get_empid(GtkWidget *widget,GtkWidget *entry)
{
	value_empid = gtk_entry_get_text(GTK_ENTRY(entry));
	strcpy(EMPID,value_empid);
}

static void get_phno(GtkWidget *widget, GtkWidget *entry)
{
	value_phno = gtk_entry_get_text(GTK_ENTRY(entry));
	strcpy(PHNO,value_phno);
}

static quiting( GtkWidget *widget,GtkWidget *window)
{
//	strcpy(MAC,value_MAC);
//	strcpy(NAME,value_name);	
	ch = 1;
	gtk_widget_hide(window);
	gtk_main_quit();
}

static exiting(GtkWidget *widget, GtkWidget *window)
{
	ch = 0;
	gtk_widget_hide(window);
	gtk_main_quit();
}

void mysqlentry()
{
	rnadGenerator();
	if(strlen(MAC)!=0||strlen(NAME)!=0||strlen(EMPID)!=0||strlen(PHNO)!=0)
	{	
        MYSQL *mysql;
        char query[1024]="INSERT INTO workersDB VALUES ('";
        int t;
        mysql = mysql_init(NULL);
        if(!mysql_real_connect(mysql,"localhost",uname,pswd,"omniPresence",0,NULL,0))
                {
		printf("Error Connecting Database: %s\n",mysql_error(mysql));
		exit(1);
		}
        else
                printf("Connected...\n");
        strcat(query,MAC);
        strcat(query,"','");
        strcat(query,NAME);
	strcat(query,"','");
	strcat(query,EMPID);
	strcat(query,"','");
	strcat(query,rnad);
	strcat(query,"','");
	strcat(query,PHNO);
        strcat(query,"')");

        t = mysql_query(mysql,query);
        if(t)
                {
		printf("Error Making Query.. %s\n",mysql_error(mysql));
		exit(1);
		}
        else
                printf("Query Made..\n");
	strcpy(entry_result,"Entered in Database.");
        printf("%s\n",query);
	strcpy(rnad,"");
        mysql_close(mysql);
	}
	else
	{
	strcpy(entry_result,"Invalid Entry..Try Again.");
	exit(1);
	}
}

void window_content()
{
	GtkWidget *window;
	GtkWidget *label_MAC, *label_name, *label_empid, *label_phno, *label_result;
	GtkWidget *entry_MAC, *entry_name, *entry_empid, *entry_phno;
	GtkWidget *button1,*quit_button;
	GtkWidget *hbox, *hbox1, *hbox2, *hbox3, *hbox4, *vbox;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"omnitest5");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(window),20);
	g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);

	vbox = gtk_vbox_new(TRUE,10);
	gtk_container_add(GTK_CONTAINER(window),vbox);
	gtk_widget_show(vbox);

	hbox = gtk_hbox_new(TRUE,10);
	gtk_container_add(GTK_CONTAINER(vbox),hbox);
	gtk_widget_show(hbox);

	label_MAC = gtk_label_new("Enter MAC Address");
	gtk_box_pack_start(GTK_BOX(hbox),label_MAC,TRUE,TRUE,0);
	gtk_widget_show(label_MAC);

	entry_MAC = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(entry_MAC),19);
	gtk_entry_set_text(GTK_ENTRY(entry_MAC),MAC);
	g_signal_connect(G_OBJECT(entry_MAC),"changed",G_CALLBACK(get_MAC),(gpointer)entry_MAC);
	gtk_box_pack_start(GTK_BOX(hbox),entry_MAC,TRUE,TRUE,0);
	gtk_widget_show(entry_MAC);

	hbox1 = gtk_hbox_new(TRUE,10);
	gtk_container_add(GTK_CONTAINER(vbox),hbox1);
	gtk_widget_show(hbox1);
	
	label_name = gtk_label_new("Enter Name");
	gtk_box_pack_start(GTK_BOX(hbox1),label_name,TRUE,TRUE,0);
	gtk_widget_show(label_name);

	entry_name = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(entry_name),50);
	gtk_entry_set_text(GTK_ENTRY(entry_name),NAME);
	g_signal_connect(G_OBJECT(entry_name),"changed",G_CALLBACK(get_name),(gpointer)entry_name);
	gtk_box_pack_start(GTK_BOX(hbox1),entry_name,TRUE,TRUE,0);
	gtk_widget_show(entry_name);

	hbox2 = gtk_hbox_new(TRUE,10);
	gtk_container_add(GTK_CONTAINER(vbox),hbox2);
	gtk_widget_show(hbox2);
	
	label_empid = gtk_label_new("Enter EmpID");
	gtk_box_pack_start(GTK_BOX(hbox2),label_empid,TRUE,TRUE,0);
	gtk_widget_show(label_empid);

	entry_empid = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(entry_empid),15);
	gtk_entry_set_text(GTK_ENTRY(entry_empid),EMPID);
	g_signal_connect(G_OBJECT(entry_empid),"changed",G_CALLBACK(get_empid),(gpointer)entry_empid);
	gtk_box_pack_start(GTK_BOX(hbox2),entry_empid,TRUE,TRUE,0);
	gtk_widget_show(entry_empid);

	hbox3 = gtk_hbox_new(TRUE,10);
	gtk_container_add(GTK_CONTAINER(vbox),hbox3);
	gtk_widget_show(hbox3);

	label_phno = gtk_label_new("Enter Phone No.");
	gtk_box_pack_start(GTK_BOX(hbox3),label_phno,TRUE,TRUE,0);
	gtk_widget_show(label_phno);

	entry_phno = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(entry_phno),15);
	gtk_entry_set_text(GTK_ENTRY(entry_phno),PHNO);
	g_signal_connect(G_OBJECT(entry_phno),"changed",G_CALLBACK(get_phno),(gpointer)entry_phno);
	gtk_box_pack_start(GTK_BOX(hbox3),entry_phno,TRUE,TRUE,0);
	gtk_widget_show(entry_phno);

	hbox4 = gtk_hbox_new(TRUE,10);
	gtk_container_add(GTK_CONTAINER(vbox),hbox4);
	gtk_widget_show(hbox4);
  
	button1 = gtk_button_new_with_label("Submit");
	g_signal_connect(G_OBJECT(button1),"clicked",G_CALLBACK(quiting),window);
	gtk_box_pack_start(GTK_BOX(hbox4),button1,TRUE,FALSE,0);
	gtk_widget_show(button1);

	quit_button = gtk_button_new_with_label("Quit");
	g_signal_connect(G_OBJECT(quit_button),"clicked",G_CALLBACK(exiting),window);
	gtk_box_pack_start(GTK_BOX(hbox4),quit_button,TRUE,FALSE,0);
	gtk_widget_show(quit_button);

	label_result = gtk_label_new("");
	gtk_label_set_text(GTK_LABEL(label_result),entry_result);
	gtk_box_pack_start(GTK_BOX(vbox),label_result,TRUE,TRUE,0);
	gtk_widget_show(label_result);

	gtk_widget_show(window);
}
//**********************************MAIN FUNCTION STARTS HERE*****************************

int main(int argc, char *argv[])
{
//	void mysqlentry();
//	void window_content();
	int ret = 0;
	ret = login_window(argc,&argv[0]);
	if(ret!=0)
	      return 1;
	else
	{
		do
		{
			gtk_init(&argc,&argv);
			window_content();
			gtk_main();
			printf("MAC  : %s \t %d\n",MAC,strlen(MAC));
			printf("NAME : %s \t %d\n",NAME,strlen(NAME));
			printf("EMPID: %s \t %d\n",EMPID,strlen(EMPID));
			printf("PHNO : %s \t %d\n",PHNO,strlen(PHNO));
			mysqlentry();	
		//	window_content();
		//	gtk_main();
			//return 0;
		}while(ch == 1);
		return 0;
	}
}
