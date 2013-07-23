/*
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<gtk/gtk.h>
#include"login.h"
#include"fileSearch.h"
*/

static int BAKP_win = 0;
//********************************GLOBAL FUNCTIONS*********************************************************

static void quit_BAKP(GtkWidget *widget, GtkWidget *window)
{
	gtk_widget_hide(window);
	gtk_main_quit();
}

static void BAKP(GtkWidget *widget,GtkWidget *windowMain)
{
	gtk_widget_hide(windowMain);
	gtk_main_quit();
	BAKP_win = 5;
/*	char command_BAKP[70]="",BAKP_time[30]="";
	const char BAKP_time_str[30]="%m%d%y_%H%M%S";
	time_t BAKP_time_raw;
	const struct tm *cur_time;
	
	time (&BAKP_time_raw);
	cur_time = localtime(&BAKP_time_raw);
	strftime(&BAKP_time[0],sizeof(BAKP_time),&BAKP_time_str[0],cur_time);
//	printf("\n time:: %s\n",BAKP_time);
	strcpy(command_BAKP,"mysqldump -u ");
	strcat(command_BAKP,uname);
	strcat(command_BAKP," -p omniPresence > omniPresence");
	strcat(command_BAKP,BAKP_time);
	strcat(command_BAKP,".sql");
	printf("BAKP_command :: %s\n",command_BAKP);
	system(command_BAKP);
	printf("BAKP:: Backup created Successfully.\n");

	GtkWidget *window;
	GtkWidget *label, *button;
	GtkWidget *vbox, *hbox1, *hbox2;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_set_border_width(GTK_CONTAINER(window),20);
	gtk_window_set_title(GTK_WINDOW(window),"omniPresence:: BAKP");
	g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	
	vbox = gtk_vbox_new(FALSE,10);
	gtk_container_add(GTK_CONTAINER(window),vbox);
	gtk_widget_show(vbox);

	hbox1 = gtk_hbox_new(FALSE,10);
	gtk_container_add(GTK_CONTAINER(vbox),hbox1);
	gtk_widget_show(hbox1);

	label = gtk_label_new("Backup Created Successfully.");
	gtk_box_pack_start(GTK_BOX(hbox1),label,FALSE,FALSE,10);
	gtk_widget_show(label);

	hbox2 = gtk_hbox_new(FALSE,10);
	gtk_container_add(GTK_CONTAINER(vbox),hbox2);
	gtk_widget_show(hbox2);

	button = gtk_button_new_with_label("OK");
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(quit_BAKP),(gpointer)window);
	gtk_box_pack_start(GTK_BOX(hbox2),button,TRUE,FALSE,10);
	gtk_widget_show(button);
	gtk_widget_show(window);
	gtk_main();
*/	
}

void LOAD(GtkWidget *widget,GtkWidget *windowMain)
{
	gtk_widget_hide(windowMain);
	gtk_main_quit();
	BAKP_win = 6;
/////////////////////////////////////////////////////////////////
}

void BAKP_window()
{
	GtkWidget *window;
	GtkWidget *label_BAKP_LOAD;
	GtkWidget *button_BAKP, *button_LOAD, *quit;
	GtkWidget *vbox, *hbox1, *hbox2, *hbox3;
	GtkWidget *hseparator;
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"omniPresence:: BAKP / RELOAD");
	g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(window),20);

	vbox = gtk_vbox_new(FALSE,10);
	gtk_container_add(GTK_CONTAINER(window),vbox);
	gtk_widget_show(vbox);

	hbox1 = gtk_hbox_new(FALSE,10);
	gtk_container_add(GTK_CONTAINER(vbox),hbox1);
	gtk_widget_show(hbox1);

	label_BAKP_LOAD = gtk_label_new("Click BAKP for creating backup or Click RELOAD to reload");
	gtk_box_pack_start(GTK_BOX(hbox1),label_BAKP_LOAD,FALSE,FALSE,10);
	gtk_widget_show(label_BAKP_LOAD);

	hbox2 = gtk_hbox_new(FALSE,10);
	gtk_container_add(GTK_CONTAINER(vbox),hbox2);
	gtk_widget_show(hbox2);

	button_BAKP = gtk_button_new_with_label("BAKP");
	g_signal_connect(G_OBJECT(button_BAKP),"clicked",G_CALLBACK(BAKP),(gpointer)window);
	gtk_box_pack_start(GTK_BOX(hbox2),button_BAKP,TRUE,FALSE,10);
	gtk_widget_show(button_BAKP);

	button_LOAD = gtk_button_new_with_label("LOAD");
	g_signal_connect(G_OBJECT(button_LOAD),"clicked",G_CALLBACK(LOAD),(gpointer)window);
	gtk_box_pack_start(GTK_BOX(hbox2),button_LOAD,TRUE,FALSE,10);
	gtk_widget_show(button_LOAD);

	hseparator = gtk_hseparator_new();
	gtk_container_add(GTK_CONTAINER(vbox),hseparator);
	gtk_widget_show(hseparator);

	hbox3 = gtk_hbox_new(FALSE,10);
	gtk_container_add(GTK_CONTAINER(vbox),hbox3);
	gtk_widget_show(hbox3);

	quit = gtk_button_new_with_label("Quit");
	g_signal_connect(G_OBJECT(quit),"clicked",G_CALLBACK(quit_BAKP),(gpointer)window);
	gtk_box_pack_start(GTK_BOX(hbox3),quit,TRUE,FALSE,10);
	gtk_widget_show(quit);

	gtk_widget_show(window);
	gtk_main();
}

//********************************MAIN FUNCTION STARTS HERE************************************************
int bckMain()
{	
	int retcode,BAKP_win_code;
	char command_BAKP[300]="", command_LOAD[300]="";
	char BAKP_time[30]="";
	const char BAKP_time_str[30] = "%m%d%y_%H%M%S";
	time_t BAKP_time_raw;
	const struct tm *cur_time;
	//retcode = login_window(argc, &argv[0]);
//	gtk_init(&argc,&argv);
	//if(retcode == 0)
	//	{
			BAKP_window();
			if(BAKP_win == 5)
			{
				time (&BAKP_time_raw);
				cur_time = localtime(&BAKP_time_raw);
				strftime(&BAKP_time[0],sizeof(BAKP_time),&BAKP_time_str[0],cur_time);
//				printf("\n time:: %s\n",BAKP_time);
				strcpy(command_BAKP,"mysqldump -u ");
				strcat(command_BAKP,uname);
				strcat(command_BAKP," -p omniPresence > /usr/share/omniPresence/BACKUP/omniPresence");
				strcat(command_BAKP,BAKP_time);
				strcat(command_BAKP,".sql");
				printf("BAKP :: %s\n",command_BAKP);
				system(command_BAKP);
				return 0;
			}
			if(BAKP_win == 6)
			{
				//printf("LOAD\n");
				filesearch_FS();
				printf("BAKP:: %s\n",filename_BAKP);
				strcpy(command_LOAD,"mysqldump -u ");
				strcat(command_LOAD,uname);
				strcat(command_LOAD," -p omniPresence < ");
				strcat(command_LOAD,filename_BAKP);
				printf("BAKP:: LOAD_command:: %s\n",command_LOAD);
				system(command_LOAD);
				return 0;
			}
		//}
	//else
		return 0;
	
}
