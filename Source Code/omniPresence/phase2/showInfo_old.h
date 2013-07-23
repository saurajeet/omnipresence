
#ifndef _SHOWINFO_H_
	#define _SHOWINFO_H_
/*INCLUDE GLIBC HEADERS
#include<gtk/gtk.h>
#include<mysql/mysql.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
  END INCLUSION
*/
const char *value_SI;
GtkWidget *check1_SI;
GtkWidget *check2_SI;
GtkWidget *check3_SI;
GtkWidget *hbox3_SI;
GtkWidget *hbox4_SI;
GtkWidget *hbox5_SI;
char str1_SI[1024];
char str2_SI[1024];
char str3_SI[1024];
int flag_SI=0;

void hide_win_SI(GtkWidget *widget, GtkWidget *window)
{
	gtk_widget_hide(window);
	gtk_main_quit();
}
void window_1_SI();
static void back_SI(GtkWidget *widget,GtkWidget *window)
{
        gtk_widget_hide(window);
        gtk_main_quit();
        window_1_SI();
        gtk_main();
}
void window_3_SI()
{
	GtkWidget *window;
        GtkWidget *vbox;
        GtkWidget *hbox;
        GtkWidget *label;
        GtkWidget *button;
        GtkWidget *separator;

        window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(window),"results");
        gtk_container_set_border_width(GTK_CONTAINER(window),10);
        g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
//        gtk_widget_show(window);
	

        vbox=gtk_vbox_new(FALSE,0);
        gtk_container_add(GTK_CONTAINER(window),vbox);
        gtk_widget_show(vbox);

        hbox=gtk_hbox_new(FALSE,0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox,TRUE,TRUE,5);
        gtk_widget_show(hbox);

        label=gtk_label_new("NO RESULTS FOUND");
        gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,5);
        gtk_widget_show(label);

        separator=gtk_hseparator_new();
        gtk_box_pack_start(GTK_BOX(vbox),separator,TRUE,TRUE,5);
        gtk_widget_show(separator);

	hbox=gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox,TRUE,TRUE,5);
	gtk_widget_show(hbox);

	button=gtk_button_new_with_label("back");
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(back_SI),window);
	gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,5);
	gtk_widget_show(button);
	
	button=gtk_button_new_with_label("close");
        g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(hide_win_SI),(gpointer)window);
        gtk_box_pack_end(GTK_BOX(hbox),button,FALSE,FALSE,5);
        gtk_widget_show(button);

	gtk_widget_show(window);
}


void search_with_empID(int a)
{
        MYSQL *connection_WDB_SI;
        MYSQL_RES *res1;
        MYSQL_ROW row1;
        char query1[1024]="select * from workersDB where empID='";
        int t,r;
	flag_SI=0;
        connection_WDB_SI=mysql_init(NULL);
        if(!mysql_real_connect(connection_WDB_SI,"localhost","root","omni","omniPresence",0,NULL,0))
        {
                printf("\nompi::Error in connection");
                return ;
        }
        strcat(query1,value_SI);
        strcat(query1,"'");
        
        t=mysql_query(connection_WDB_SI,query1);
        if(t)
        {
                printf("\nompi::Error in query...%s",mysql_error(connection_WDB_SI));
                return ;
        }
        
        res1=mysql_use_result(connection_WDB_SI);
        row1=mysql_fetch_row(res1);
        if(row1)
        {
		flag_SI=1;
                if(a==1)     
			strcpy(str1_SI,row1[0]);
                if(a==2)
                        strcpy(str2_SI,row1[1]);
		if(a==3)
                        strcpy(str3_SI,row1[4]);
		
	}
        else
                printf("\nompi::the empid doesnot exist");
        mysql_close(connection_WDB_SI);
        return ;
}


static void get_entry_SI(GtkWidget *widget, GtkWidget *entry)
{
        value_SI=gtk_entry_get_text(GTK_ENTRY(entry));
}


void window_2_SI(char str1[],char str2[],char str3[])
{
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *hbox1,*hbox2,*hbox6;
	GtkWidget *label;
	GtkWidget *button;
	GtkWidget *separator;
		
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"results");
	gtk_container_set_border_width(GTK_CONTAINER(window),10);
	g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_widget_show(window);

	vbox=gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),vbox);
	gtk_widget_show(vbox);

	hbox1=gtk_hbox_new(FALSE,0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox1,TRUE,TRUE,5);
        gtk_widget_show(hbox1);

        label=gtk_label_new("THE RESULT OF THE QUERY");
        gtk_box_pack_start(GTK_BOX(hbox1),label,FALSE,FALSE,5);
        gtk_widget_show(label);	
	
	separator=gtk_hseparator_new();
        gtk_box_pack_start(GTK_BOX(vbox),separator,TRUE,TRUE,5);
        gtk_widget_show(separator);	

	hbox2=gtk_hbox_new(FALSE,0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox2,TRUE,TRUE,5);
        gtk_widget_show(hbox2);

        label=gtk_label_new("EMPID      :");
        gtk_box_pack_start(GTK_BOX(hbox2),label,FALSE,FALSE,5);
        gtk_widget_show(label);

        label=gtk_label_new(value_SI);
        gtk_box_pack_start(GTK_BOX(hbox2),label,FALSE,FALSE,5);
        gtk_widget_show(label);

	hbox3_SI=gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox3_SI,TRUE,TRUE,5);
	gtk_widget_show(hbox3_SI);
	
	label=gtk_label_new("MAC         :");
	gtk_box_pack_start(GTK_BOX(hbox3_SI),label,FALSE,FALSE,5);
	gtk_widget_show(label);

	label=gtk_label_new(str1_SI);
        gtk_box_pack_start(GTK_BOX(hbox3_SI),label,FALSE,FALSE,5);
        gtk_widget_show(label);
	
	hbox4_SI=gtk_hbox_new(FALSE,0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox4_SI,TRUE,TRUE,5);
        gtk_widget_show(hbox4_SI);

        label=gtk_label_new("NAME       :");
        gtk_box_pack_start(GTK_BOX(hbox4_SI),label,FALSE,FALSE,5);
        gtk_widget_show(label);

        label=gtk_label_new(str2_SI);
        gtk_box_pack_start(GTK_BOX(hbox4_SI),label,FALSE,FALSE,5);
        gtk_widget_show(label);
		
	hbox5_SI=gtk_hbox_new(FALSE,0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox5_SI,TRUE,TRUE,5);
        gtk_widget_show(hbox5_SI);

        label=gtk_label_new("PHNO       :");
        gtk_box_pack_start(GTK_BOX(hbox5_SI),label,FALSE,FALSE,5);
        gtk_widget_show(label);

        label=gtk_label_new(str3_SI);
        gtk_box_pack_start(GTK_BOX(hbox5_SI),label,FALSE,FALSE,5);
        gtk_widget_show(label);
	
	separator=gtk_hseparator_new();
        gtk_box_pack_start(GTK_BOX(vbox),separator,TRUE,TRUE,5);
        gtk_widget_show(separator);
	
	hbox6=gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox6,TRUE,TRUE,5);
	gtk_widget_show(hbox6);
	
	button=gtk_button_new_with_label("back");
        g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(back_SI),window);
        gtk_box_pack_start(GTK_BOX(hbox6),button,FALSE,FALSE,5);
        gtk_widget_show(button);
	
	button=gtk_button_new_with_label("close");
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(hide_win_SI),(gpointer)window);
	gtk_box_pack_end(GTK_BOX(hbox6),button,FALSE,FALSE,5);
	gtk_widget_show(button);
}


static void search_SI(GtkWidget *widget,GtkWidget *window)
{
	int arr[3]={0,0,0};
	int count=0;
	
	if(GTK_TOGGLE_BUTTON(check1_SI)->active==TRUE)
	{
		count++;
		arr[0]=1;
	}
	if(GTK_TOGGLE_BUTTON(check2_SI)->active==TRUE)
	{
		count++;
		arr[1]=1;
	}
	if(GTK_TOGGLE_BUTTON(check3_SI)->active==TRUE)
	{
		count++;
		arr[2]=1;
	}
	
	gtk_widget_hide(window);
	gtk_main_quit();	
	
	if(count!=0)
	{        
		if(arr[0]==1)
			search_with_empID(1);
			
                if(arr[1]==1)
                        search_with_empID(2);
			
		if(arr[2]==1)
               		search_with_empID(3); 
		
		if(flag_SI==1)
		{
			window_2_SI(&str1_SI[0],&str2_SI[0],&str3_SI[0]);
			if(arr[0]!=1)
				gtk_widget_hide(hbox3_SI);
			if(arr[1]!=1)
				gtk_widget_hide(hbox4_SI);
			if(arr[2]!=1)
				gtk_widget_hide(hbox5_SI);
		}
		else
			window_3_SI();
		gtk_main();
	}
	
	return;
}

void window_1_SI()
{
	GtkWidget *window;
	GtkWidget *vbox1;
	GtkWidget *hbox1;
	GtkWidget *hbox2;
	GtkWidget *button;
	GtkWidget *label1;
	GtkWidget *entry1;
	GtkWidget *separator1;
	GtkWidget *separator2;
	
	
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Show Information:: OmniPresence");
	gtk_container_set_border_width(GTK_CONTAINER(window),10);
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_widget_show(window);
	
	vbox1=gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),vbox1);	
	gtk_widget_show(vbox1);

	hbox1=gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox1),hbox1,TRUE,TRUE,5);
	gtk_widget_show(hbox1);

	label1=gtk_label_new("Enter employee ID ");
	gtk_box_pack_start(GTK_BOX(hbox1),label1,FALSE,FALSE,5);
	gtk_widget_show(label1);	

	entry1=gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(entry1),50);
	gtk_box_pack_start(GTK_BOX(hbox1),entry1,FALSE,FALSE,5);
	g_signal_connect(G_OBJECT(entry1),"changed",G_CALLBACK(get_entry_SI),(gpointer)entry1);
	gtk_widget_show(entry1);

	separator1=gtk_hseparator_new();
	gtk_box_pack_start(GTK_BOX(vbox1),separator1,TRUE,TRUE,5);
	gtk_widget_show(separator1);

	check1_SI=gtk_check_button_new_with_label("MAC");
	gtk_box_pack_start(GTK_BOX(vbox1),check1_SI,FALSE,FALSE,5);
	gtk_widget_show(check1_SI);
	
	check2_SI=gtk_check_button_new_with_label("NAME");
        gtk_box_pack_start(GTK_BOX(vbox1),check2_SI,FALSE,FALSE,5);
        gtk_widget_show(check2_SI);
	
	check3_SI=gtk_check_button_new_with_label("PHONE NO");
        gtk_box_pack_start(GTK_BOX(vbox1),check3_SI,FALSE,FALSE,5);
        gtk_widget_show(check3_SI);

	separator2=gtk_hseparator_new();
	gtk_box_pack_start(GTK_BOX(vbox1),separator2,TRUE,TRUE,5);
	gtk_widget_show(separator2);
	
	hbox2=gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox1),hbox2,TRUE,TRUE,5);
	gtk_widget_show(hbox2);

	button=gtk_button_new_with_label("next");
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(search_SI),window);
        gtk_box_pack_start(GTK_BOX(hbox2),button,FALSE,FALSE,5);
        gtk_widget_show(button);

	button=gtk_button_new_with_label("close");
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(hide_win_SI),(gpointer)window);
	gtk_box_pack_end(GTK_BOX(hbox2),button,FALSE,FALSE,5);
	gtk_widget_show(button);

	
}

int showInfoMain()
{	window_1_SI();
	gtk_main();
	return 0;
}

#endif //_SHOWINFO_H_
