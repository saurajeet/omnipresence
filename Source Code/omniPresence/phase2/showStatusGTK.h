
#ifndef _SHOWSTATUSGTK_H_
	#define _SHOWSTATUSGTK_H_
/*
INCLUDE GLIBC HEADERS
#include <stdio.h>
#include <gtk/gtk.h>
#include<mysql/mysql.h>
END INCLUSION
*/
const char *value_SSG;
char str_SSG[10]="";
char day_SSG[10]="1";
char mon_SSG[10]="1";
char year_SSG[10]="9";
char status_SSG[10]="";
int flag_SSG=0,d1_SSG,d2_SSG,d3_SSG;
GtkWidget *hbox2_SSG;
GtkWidget *hbox3_SSG;

void window_1_SSG();
void window_2_SSG();
void window_3_SSG();

void hide_win_SSG(GtkWidget *widget , GtkWidget *window)
{
	gtk_widget_hide(window);
	gtk_main_quit();
}

static void switch_win_SSG(GtkWidget *widget, GtkWidget *window)
{
	gtk_widget_hide(window);
	window_1_SSG();
}

void returnStatus_SSG()
{
	char retstr[1024]="",query[1024]="select attend";
	MYSQL *connection_AS_SSG;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int t;
	char * server = "localhost";
	printf("\nSHOWSTAT:: ReturnStatus  ");
	if(d1_SSG<10)
		strcat(query,"0");
	strcat(query,day_SSG);
	strcat(query," from ");
	strcat(query,"attendanceSheet");
	if(d2_SSG<10)
                strcat(query,"0");
	strcat(query,mon_SSG);
	if(d3_SSG<10)
                strcat(query,"0");
	strcat(query,year_SSG);
	strcat(query,",workersDB  where workersDB.empID='");
	strcat(query,value_SSG);
	strcat(query,"' and workersDB.rNad=");
	strcat(query,"attendanceSheet");
	if(d2_SSG<10)
                strcat(query,"0");
	strcat(query,mon_SSG);
	if(d3_SSG<10)
                strcat(query,"0");
	strcat(query,year_SSG);
	strcat(query,".rNAD ");
	

	connection_AS_SSG=mysql_init(NULL);
	if(!mysql_real_connect(connection_AS_SSG, server, user, password, "omniPresence",0,NULL,0))
	{
		printf("\nSHOWSTAT:: Error in connection...............%s", mysql_error(connection_AS_SSG));
		return ;
	}
	
	t=mysql_query(connection_AS_SSG, query);
	if(t)
	{
		printf("\nSHOWSTAT:: Error in query");
		return ;
	}
	
	res=mysql_use_result(connection_AS_SSG);
	row=mysql_fetch_row(res);
	if(row)
	{
		flag_SSG=1;
		strcpy(retstr,row[0]);
		
		switch(retstr[0])
		{
			case 'P':
				strcpy(status_SSG,"present");
				break;
			case 'A':
				strcpy(status_SSG,"absent");
				break;
			case 'L':
				strcpy(status_SSG,"on leave");
				break;
			default :
				strcpy(status_SSG,"holiday");
		}
		
	}
           	
	mysql_close(connection_AS_SSG);
	
}
	

static void get_entry_SSG(GtkWidget *widget, GtkWidget *entry)
{	
        value_SSG=gtk_entry_get_text(GTK_ENTRY(entry));
}

static void get_spin_val_1(GtkWidget *widget, GtkWidget *spinner)
{
	d1_SSG=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(spinner));
	sprintf(day_SSG,"%d",d1_SSG);		
}

static void get_spin_val_2(GtkWidget *widget, GtkWidget *spinner)
{
	d2_SSG=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(spinner));
	sprintf(mon_SSG,"%d",d2_SSG);   
}

static void get_spin_val_3(GtkWidget *widget, GtkWidget *spinner)
{
        d3_SSG=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(spinner));
	d3_SSG=d3_SSG%100;
	sprintf(year_SSG,"%d",d3_SSG);
}

static void find_status_SSG(GtkWidget *widget,GtkWidget *window)
{	
	gtk_widget_hide(window);
	
	if(value_SSG)
	{
		returnStatus_SSG();
		window_2_SSG();
		if(flag_SSG==1)
	        	gtk_widget_hide(hbox2_SSG);
		
		else
	             	gtk_widget_hide(hbox3_SSG);		
	}
	else
		window_3_SSG();
}



void window_1_SSG()
{
	GtkWidget *window;
	GtkWidget *frame;
	GtkWidget *hbox;
	GtkWidget *main_vbox;
	GtkWidget *vbox;
	GtkWidget *vbox2;
	GtkWidget *spinner;
	GtkWidget *button;
	GtkWidget *label;
	GtkWidget *entry;
	GtkWidget *separator;
	GtkAdjustment *adj;
  /* Initialise GTK */	

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), NULL);
	gtk_window_set_title (GTK_WINDOW (window), "Attendance Status");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);

	main_vbox = gtk_vbox_new (FALSE, 5);
	gtk_container_set_border_width (GTK_CONTAINER (main_vbox), 10);
	gtk_container_add (GTK_CONTAINER (window), main_vbox);

	frame = gtk_frame_new ("Select date");
	gtk_box_pack_start (GTK_BOX (main_vbox), frame, TRUE, TRUE, 0);

	vbox = gtk_vbox_new (FALSE, 0);
	gtk_container_set_border_width (GTK_CONTAINER (vbox), 5);
	gtk_container_add (GTK_CONTAINER (frame), vbox);

  /* Day, month, year spinners */
	hbox = gtk_hbox_new (FALSE, 0);
	gtk_box_pack_start (GTK_BOX (vbox), hbox, TRUE, TRUE, 5);

	vbox2 = gtk_vbox_new (FALSE, 0);
	gtk_box_pack_start (GTK_BOX (hbox), vbox2, TRUE, TRUE, 5);

	label = gtk_label_new ("Day :");
	gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
	gtk_box_pack_start (GTK_BOX (vbox2), label, FALSE, TRUE, 0);

	adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 1.0, 31.0, 1.0, 5.0, 0.0);

	spinner = gtk_spin_button_new (adj, 0, 0);
	gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner), TRUE);
	gtk_box_pack_start (GTK_BOX (vbox2), spinner, FALSE, TRUE, 0);
	g_signal_connect(G_OBJECT(adj),"value_changed",G_CALLBACK(get_spin_val_1),(gpointer)spinner);

	vbox2 = gtk_vbox_new (FALSE, 0);
	gtk_box_pack_start (GTK_BOX (hbox), vbox2, TRUE, TRUE, 5);

	label = gtk_label_new ("Month :");
	gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
	gtk_box_pack_start (GTK_BOX (vbox2), label, FALSE, TRUE, 0);

	adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 1.0, 12.0, 1.0, 5.0, 0.0);

	spinner = gtk_spin_button_new (adj, 0, 0);
	gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner), TRUE);
	gtk_box_pack_start (GTK_BOX (vbox2), spinner, FALSE, TRUE, 0);
	g_signal_connect(G_OBJECT(adj),"value_changed",G_CALLBACK(get_spin_val_2),(gpointer)spinner);

	vbox2 = gtk_vbox_new (FALSE, 0);
	gtk_box_pack_start (GTK_BOX (hbox), vbox2, TRUE, TRUE, 5);

	label = gtk_label_new ("Year :");
	gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
	gtk_box_pack_start (GTK_BOX (vbox2), label, FALSE, TRUE, 0);

	adj = (GtkAdjustment *) gtk_adjustment_new (2009.0, 2001.0, 2099.0, 1.0, 100.0, 0.0);

	spinner = gtk_spin_button_new (adj, 0, 0);
	gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner), FALSE);
	gtk_widget_set_size_request (spinner, 55, -1);
	gtk_box_pack_start (GTK_BOX (vbox2), spinner, FALSE, TRUE, 0);
	g_signal_connect(G_OBJECT(adj),"value_changed",G_CALLBACK(get_spin_val_3),(gpointer)spinner);

	separator=gtk_hseparator_new();
	gtk_box_pack_start(GTK_BOX(main_vbox),separator,TRUE,TRUE,5);

	hbox=gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(main_vbox), hbox,TRUE,TRUE,5);

	label=gtk_label_new("Enter employee ID");
	gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,5);

	entry=gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(entry),50);
	gtk_box_pack_start(GTK_BOX(hbox),entry,FALSE,FALSE,5);
	g_signal_connect(G_OBJECT(entry),"changed",G_CALLBACK(get_entry_SSG),(gpointer)entry);

	separator=gtk_hseparator_new();
	gtk_box_pack_start(GTK_BOX(main_vbox),separator,TRUE,TRUE,5);

	hbox = gtk_hbox_new (FALSE, 0);
	gtk_box_pack_start (GTK_BOX (main_vbox), hbox, TRUE, TRUE, 5);

	button=gtk_button_new_with_label("Find status");
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(find_status_SSG),(gpointer)window);
	gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,5);

	button = gtk_button_new_with_label ("(X) Close");
	g_signal_connect(G_OBJECT (button), "clicked", G_CALLBACK (hide_win_SSG), (gpointer)window);
	gtk_box_pack_end (GTK_BOX (hbox), button, FALSE, FALSE, 5);
	gtk_widget_show_all (window);
  
}

void window_2_SSG()
{
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *vbox1;
	GtkWidget *hbox;
	GtkWidget *label;
	GtkWidget *button;
	GtkWidget *separator;
		
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"Show Status :: omniPresence");
	gtk_container_set_border_width(GTK_CONTAINER(window),10);
	g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	
	vbox=gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),vbox);

	hbox2_SSG=gtk_hbox_new(FALSE,0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox2_SSG,TRUE,TRUE,5);

        label=gtk_label_new("No entry in database");
        gtk_box_pack_start(GTK_BOX(hbox2_SSG),label,FALSE,FALSE,5);

	hbox3_SSG=gtk_hbox_new(FALSE,0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox3_SSG,TRUE,TRUE,5);

	vbox1=gtk_vbox_new(FALSE,0);
        gtk_box_pack_start(GTK_BOX(hbox3_SSG),vbox1,TRUE,TRUE,5);

	hbox=gtk_hbox_new(FALSE,0);
        gtk_box_pack_start(GTK_BOX(vbox1),hbox,TRUE,TRUE,5);

        label=gtk_label_new("EMPID      :");
        gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,5);

	label=gtk_label_new(value_SSG);
        gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,5);

	hbox=gtk_hbox_new(FALSE,0);
        gtk_box_pack_start(GTK_BOX(vbox1),hbox,TRUE,TRUE,5);

        label=gtk_label_new("DATE       :");
        gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,5);

        label=gtk_label_new(day_SSG);
        gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,5);
	
	label=gtk_label_new("/");
        gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,5);

	label=gtk_label_new(mon_SSG);
        gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,5);

	label=gtk_label_new("/");
        gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,5);

	label=gtk_label_new(year_SSG);
        gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,5);

	hbox=gtk_hbox_new(FALSE,0);
        gtk_box_pack_start(GTK_BOX(vbox1),hbox,TRUE,TRUE,5);

	label=gtk_label_new("STATUS   : ");
	gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,5);

	label=gtk_label_new(status_SSG);
        gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,5);

	hbox=gtk_hbox_new(FALSE,0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,TRUE,5);

	button=gtk_button_new_with_label("(<<) Back");
	gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,5);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(switch_win_SSG),(gpointer)(window));

	button=gtk_button_new_with_label("(X) Close");
        gtk_box_pack_end(GTK_BOX(hbox),button,FALSE,FALSE,5);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(hide_win_SSG),(gpointer)window);
	gtk_widget_show_all(window);
}

void window_3_SSG()
{
	GtkWidget *window;
        GtkWidget *vbox;
        GtkWidget *hbox;
        GtkWidget *label;
        GtkWidget *button;
        GtkWidget *separator;

        window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(window),"Show Status :: omniPresence");
        gtk_container_set_border_width(GTK_CONTAINER(window),10);
        g_signal_connect(G_OBJECT(window),"distroy",G_CALLBACK(gtk_main_quit),NULL);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	vbox=gtk_vbox_new(FALSE,0);
        gtk_container_add(GTK_CONTAINER(window),vbox);

        hbox=gtk_hbox_new(FALSE,0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox,TRUE,TRUE,5);

        label=gtk_label_new("Employee ID  is empty.");
        gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,5);

        hbox=gtk_hbox_new(FALSE,0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox,TRUE,TRUE,5);

	button=gtk_button_new_with_label("(<<) Back");
        gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,5);
        g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(switch_win_SSG),(gpointer)(window));

        button=gtk_button_new_with_label("(X) Close");
        gtk_box_pack_end(GTK_BOX(hbox),button,FALSE,FALSE,5);
        g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(hide_win_SSG),(gpointer)window);
        
	gtk_widget_show_all(window);
}

int showStatusGTKMain()
{	window_1_SSG();
	gtk_main();
	return 0;
}

#endif //_SHOWSTATUSGTK_H_
