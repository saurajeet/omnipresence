/*
#include<stdio.h>
#include<gtk/gtk.h>
#include<mysql/mysql.h>
#include<string.h>
#include"parser1.h"
*/

//**************************************GLOBAL VARIABLE DECLARATION********************************
int PRScols,PRSrows,flag_SMD=0;
const char *empid="",*ASname="";
char srchempid[15]="",attendanceSheet_SMD[20] = "attendanceSheet",temp_SMD[25]="";
GtkWidget *entry_ASname,*entry_empid;


//*****************************************GLOBAL FUNCTION DECLARATION********************************

void window_main_SMD();
void srch(GtkWidget *widget,GtkWidget *window);
static void back_SMD(GtkWidget *widget,GtkWidget *window);
static void quit_back_SMD(GtkWidget *widget, GtkWidget *window);
void back_window_SMD();
void window_main_SMD();
void window_scrolled();
int sheetquery();

void back_SMD(GtkWidget *widget, GtkWidget *window)
{
	gtk_widget_hide(window);
	gtk_main_quit();
	flag_SMD=2;
	//printf("\nSMD::hiding this window and showing main ");
	return;
	
}	

static void quit_back_SMD(GtkWidget *widget, GtkWidget *window)
{
	gtk_widget_hide(window);
	gtk_main_quit();
	flag_SMD=0;
	return;
}

void back_window_SMD()
{
	GtkWidget *window;
	GtkWidget *label1;
	GtkWidget *bck_button, *quit_button;
	GtkWidget *hbox1, *hbox2, *vbox;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"Attendance for the month");
	gtk_container_set_border_width(GTK_CONTAINER(window),20);
	g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(quit_back_SMD),(gpointer)window);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);

	vbox = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),vbox);
	
	hbox1 = gtk_hbox_new(FALSE,10);
	gtk_container_add(GTK_CONTAINER(vbox),hbox1);
	
	label1 = gtk_label_new("No results found !!");
	gtk_box_pack_start(GTK_BOX(hbox1),label1,FALSE,FALSE,10);
	
	hbox2 = gtk_hbox_new(FALSE,10);
	gtk_container_add(GTK_CONTAINER(vbox),hbox2);
	
	bck_button = gtk_button_new_with_label("<< BACK");
	g_signal_connect(G_OBJECT(bck_button),"clicked",G_CALLBACK(back_SMD),(gpointer)window);
	gtk_box_pack_start(GTK_BOX(hbox2),bck_button,FALSE,FALSE,10);
	
	quit_button = gtk_button_new_with_label("Quit");
	g_signal_connect(G_OBJECT(quit_button),"clicked",G_CALLBACK(quit_back_SMD),(gpointer)window);
	gtk_box_pack_start(GTK_BOX(hbox2),quit_button,FALSE,FALSE,10);
	
	gtk_widget_show_all(window);
	
}

void window_scrolled()
{
	GtkWidget *window;
	GtkWidget *scrolled_window;
	GtkWidget *table;
	GtkWidget *label,*label1;
	GtkWidget *button;
	GtkWidget *vbox;
	int t=-1,r;
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(quit_back_SMD),(gpointer)window);
	gtk_window_set_title(GTK_WINDOW(window),"Attendance for the month");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(window),10);
	gtk_widget_set_size_request(window,450,600);
	
	vbox = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),vbox);
	
	scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_container_set_border_width(GTK_CONTAINER(scrolled_window),10);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
	gtk_box_pack_start(GTK_BOX(vbox),scrolled_window,TRUE,TRUE,0);
	
	table = gtk_table_new(PRScols,PRSrows,TRUE);
	gtk_table_set_row_spacings(GTK_TABLE(table),10);
	gtk_table_set_col_spacings(GTK_TABLE(table),10);
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window),table);
	
     	label = gtk_label_new("STATUS");
        label1= gtk_label_new("DAY");
	gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,t+1,t+2);
        gtk_table_attach_defaults(GTK_TABLE(table),label1,1,2,t+1,t+2);
	t++;

	label = gtk_label_new(parsedfield1);
	label1= gtk_label_new("01");
        gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,t+1,t+2);
        gtk_table_attach_defaults(GTK_TABLE(table),label1,1,2,t+1,t+2);
        t++;

	label = gtk_label_new(parsedfield2);
        label1= gtk_label_new("02");
        gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,t+1,t+2);
        gtk_table_attach_defaults(GTK_TABLE(table),label1,1,2,t+1,t+2);
        t++;

	label = gtk_label_new(parsedfield3);
  	label1= gtk_label_new("03");
        gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,t+1,t+2);
        gtk_table_attach_defaults(GTK_TABLE(table),label1,1,2,t+1,t+2);
        t++;        

	label = gtk_label_new(parsedfield4);
       	label1= gtk_label_new("04");
        gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,t+1,t+2);
        gtk_table_attach_defaults(GTK_TABLE(table),label1,1,2,t+1,t+2);
        t++;

	label = gtk_label_new(parsedfield5);
       	label1= gtk_label_new("05");
        gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,t+1,t+2);
        gtk_table_attach_defaults(GTK_TABLE(table),label1,1,2,t+1,t+2);
        t++;

	label = gtk_label_new(parsedfield6);
       	label1= gtk_label_new("06");
        gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,t+1,t+2);
        gtk_table_attach_defaults(GTK_TABLE(table),label1,1,2,t+1,t+2);
        t++;

	label = gtk_label_new(parsedfield7);
       	label1= gtk_label_new("07");
        gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,t+1,t+2);
        gtk_table_attach_defaults(GTK_TABLE(table),label1,1,2,t+1,t+2);
        t++;

	label = gtk_label_new(parsedfield8);
       	label1= gtk_label_new("08");
        gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,t+1,t+2);
        gtk_table_attach_defaults(GTK_TABLE(table),label1,1,2,t+1,t+2);
        t++;

	label = gtk_label_new(parsedfield9);
        label1= gtk_label_new("09");
        gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,t+1,t+2);
        gtk_table_attach_defaults(GTK_TABLE(table),label1,1,2,t+1,t+2);
        t++;

	label = gtk_label_new(parsedfield10);
        label1= gtk_label_new("10");
        gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,t+1,t+2);
        gtk_table_attach_defaults(GTK_TABLE(table),label1,1,2,t+1,t+2);
        t++;

	label = gtk_label_new(parsedfield11);
        label1= gtk_label_new("11");
        gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,t+1,t+2);
        gtk_table_attach_defaults(GTK_TABLE(table),label1,1,2,t+1,t+2);
        t++;

	label = gtk_label_new(parsedfield12);
        label1= gtk_label_new("12");
        gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,t+1,t+2);
        gtk_table_attach_defaults(GTK_TABLE(table),label1,1,2,t+1,t+2);
        t++;
        
	label = gtk_label_new(parsedfield13);
        label1= gtk_label_new("13");
        gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,t+1,t+2);
        gtk_table_attach_defaults(GTK_TABLE(table),label1,1,2,t+1,t+2);
        t++;
        
	label = gtk_label_new(parsedfield14);
        label1= gtk_label_new("14");
        gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,t+1,t+2);
        gtk_table_attach_defaults(GTK_TABLE(table),label1,1,2,t+1,t+2);
        t++;
        
	label = gtk_label_new(parsedfield15);
        label1= gtk_label_new("15");
        gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,t+1,t+2);
        gtk_table_attach_defaults(GTK_TABLE(table),label1,1,2,t+1,t+2);
        t++;
        
	label = gtk_label_new(parsedfield16);
        label1= gtk_label_new("16");
        gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,t+1,t+2);
        gtk_table_attach_defaults(GTK_TABLE(table),label1,1,2,t+1,t+2);
        t++;

	label = gtk_label_new(parsedfield17);
        label1= gtk_label_new("17");
        gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,t+1,t+2);
        gtk_table_attach_defaults(GTK_TABLE(table),label1,1,2,t+1,t+2);
        t++;
        
	label = gtk_label_new(parsedfield18);
        label1= gtk_label_new("18");
        gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,t+1,t+2);
        gtk_table_attach_defaults(GTK_TABLE(table),label1,1,2,t+1,t+2);
        t++;
        
	label = gtk_label_new(parsedfield19);
        label1= gtk_label_new("19");
        gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,t+1,t+2);
        gtk_table_attach_defaults(GTK_TABLE(table),label1,1,2,t+1,t+2);
        t++;
        
	label = gtk_label_new(parsedfield20);
        label1= gtk_label_new("20");
        gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,t+1,t+2);
        gtk_table_attach_defaults(GTK_TABLE(table),label1,1,2,t+1,t+2);
        t++;
        
	label = gtk_label_new(parsedfield21);
        label1= gtk_label_new("21");
        gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,t+1,t+2);
        gtk_table_attach_defaults(GTK_TABLE(table),label1,1,2,t+1,t+2);
        t++;
        
	label = gtk_label_new(parsedfield22);
        label1= gtk_label_new("22");
        gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,t+1,t+2);
        gtk_table_attach_defaults(GTK_TABLE(table),label1,1,2,t+1,t+2);
        t++;

	label = gtk_label_new(parsedfield23);
        label1= gtk_label_new("23");
        gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,t+1,t+2);
        gtk_table_attach_defaults(GTK_TABLE(table),label1,1,2,t+1,t+2);
        t++;

	label = gtk_label_new(parsedfield24);
        label1= gtk_label_new("24");
        gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,t+1,t+2);
        gtk_table_attach_defaults(GTK_TABLE(table),label1,1,2,t+1,t+2);
        t++;

	label = gtk_label_new(parsedfield25);
        label1= gtk_label_new("25");
        gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,t+1,t+2);
        gtk_table_attach_defaults(GTK_TABLE(table),label1,1,2,t+1,t+2);
        t++;

	label = gtk_label_new(parsedfield26);
        label1= gtk_label_new("26");
        gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,t+1,t+2);
        gtk_table_attach_defaults(GTK_TABLE(table),label1,1,2,t+1,t+2);
        t++;

	label = gtk_label_new(parsedfield27);
        label1= gtk_label_new("27");
        gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,t+1,t+2);
        gtk_table_attach_defaults(GTK_TABLE(table),label1,1,2,t+1,t+2);
        t++;

	label = gtk_label_new(parsedfield28);
        label1= gtk_label_new("28");
        gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,t+1,t+2);
        gtk_table_attach_defaults(GTK_TABLE(table),label1,1,2,t+1,t+2);
        t++;

	label = gtk_label_new(parsedfield29);
        label1= gtk_label_new("29");
        gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,t+1,t+2);
        gtk_table_attach_defaults(GTK_TABLE(table),label1,1,2,t+1,t+2);
        t++;

	label = gtk_label_new(parsedfield30);
        label1= gtk_label_new("30");
        gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,t+1,t+2);
        gtk_table_attach_defaults(GTK_TABLE(table),label1,1,2,t+1,t+2);
        t++;
        
	label = gtk_label_new(parsedfield31);
        label1= gtk_label_new("31");
        gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,t+1,t+2);
        gtk_table_attach_defaults(GTK_TABLE(table),label1,1,2,t+1,t+2);
        t++;
        
	label = gtk_label_new(parsedfield32);
        label1= gtk_label_new("TOTAL");
        gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,t+1,t+2);
        gtk_table_attach_defaults(GTK_TABLE(table),label1,1,2,t+1,t+2);
                	
	button = gtk_button_new_with_label("close");
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(quit_back_SMD),(gpointer)window);
//	GTK_WIDGET_SET_FLAGS(button,GTK_CAN_DEFAULT);
	gtk_box_pack_start(GTK_BOX(vbox),button,FALSE,TRUE,0);

	button = gtk_button_new_with_label("back");
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(back_SMD),(gpointer)window);
	gtk_box_pack_start(GTK_BOX(vbox),button,FALSE,TRUE,0);
	
//	gtk_widget_grab_default(button);
	
	gtk_widget_show_all(window);

}



int sheetquery()
{	
	char buffer[5000]="";
	MYSQL *mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char myrow[100]={""};
	char query[400]="";
	int t,k=0,n,i,j,c=0,total=0;
	static char ch;
	mysql=mysql_init(NULL);
	if (!mysql_real_connect(mysql,"localhost","root","omni","omniPresence",0,NULL,0))
		{
		printf("SMD:: Error connecting to database: %s\n",mysql_error(mysql));
		return 1;
		}
 
	strcpy(query,"select attend01, attend02, attend03, attend04, attend05, attend06, attend07, attend08, attend09, attend10, attend11, attend12, attend13, attend14, attend15, attend16, attend17, attend18, attend19, attend20, attend21, attend22, attend23, attend24, attend25, attend26, attend27, attend28, attend29, attend30, attend31, TotalAttend from ");
	strcat(query,attendanceSheet_SMD);
	strcat(query," ats, workersDB wdb where ats.rNAD = wdb.rNad and wdb.empID = '");
	strcat(query,srchempid);
	strcat(query,"'");
	t = mysql_query(mysql,query);
	if (t)
		{
		printf("SMD:: Error making query: %s\n",mysql_error(mysql));
		return 1;
		}
	else
	i = j = 0;
	res = mysql_use_result(mysql);
	if(row = mysql_fetch_row(res))
	{
		for(i=0;i<mysql_num_fields(res);i++)
			{
			sprintf(myrow,"%s ",row[i]);
			if(myrow[0]=='(')
				total++;
			strcat(buffer,"<");
			strcat(buffer,myrow);
			strcat(buffer,">");
			}
	}
	PRScols = i, PRSrows = j;
	n = i;
	parser(buffer,n);
	mysql_close(mysql);
	return 0;
}

void srch(GtkWidget *widget,GtkWidget *window)
{
	     
	empid = gtk_entry_get_text(GTK_ENTRY(entry_empid));
	ASname = gtk_entry_get_text(GTK_ENTRY(entry_ASname));
	gtk_widget_hide(window);
	gtk_main_quit();
  
	flag_SMD=1;

	return;
}

void window_main_SMD()
{
        GtkWidget *window;
        GtkWidget *label_ASname,*label_empid;
        GtkWidget *submit_button, *quit;
        GtkWidget *vbox, *hbox1,*hbox2,*hbox3;
        GtkWidget *hseparator;

        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(window),"Attendance for the month");
        g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(quit_back_SMD),(gpointer)window);
        gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
        gtk_container_set_border_width(GTK_CONTAINER(window),20);

        vbox = gtk_vbox_new(TRUE,20);
        gtk_container_add(GTK_CONTAINER(window),vbox);

        hbox1 = gtk_hbox_new(TRUE,20);
        gtk_container_add(GTK_CONTAINER(vbox),hbox1);

        label_empid = gtk_label_new("EmpID");
        gtk_box_pack_start(GTK_BOX(hbox1),label_empid,TRUE,TRUE,10);

        entry_empid = gtk_entry_new();
        gtk_entry_set_max_length(GTK_ENTRY(entry_empid),15);
        gtk_box_pack_start(GTK_BOX(hbox1),entry_empid,TRUE,FALSE,10);

        hbox2 = gtk_hbox_new(TRUE,20);
        gtk_container_add(GTK_CONTAINER(vbox),hbox2);

        label_ASname = gtk_label_new("Enter attendance sheet name\n\t(like 0109)");
        gtk_box_pack_start(GTK_BOX(hbox2),label_ASname,TRUE,TRUE,10);
	entry_ASname = gtk_entry_new();
        gtk_entry_set_max_length(GTK_ENTRY(entry_ASname),4);
        gtk_box_pack_start(GTK_BOX(hbox2),entry_ASname,TRUE,FALSE,10);

        hseparator = gtk_hseparator_new();
        gtk_container_add(GTK_CONTAINER(vbox),hseparator);

        hbox3 = gtk_hbox_new(FALSE,20);
        gtk_container_add(GTK_CONTAINER(vbox),hbox3);

        submit_button = gtk_button_new_with_label("Search month details");
        g_signal_connect(G_OBJECT(submit_button),"clicked",G_CALLBACK(srch),(gpointer)window);
        gtk_box_pack_start(GTK_BOX(hbox3),submit_button,TRUE,TRUE,20);

        quit =  gtk_button_new_with_label("Quit");
	g_signal_connect(G_OBJECT(quit),"clicked",G_CALLBACK(quit_back_SMD),(gpointer)window);
        gtk_box_pack_start(GTK_BOX(hbox3),quit,TRUE,FALSE,0);

        gtk_widget_show_all(window);
}


//**************************************MAIN FUNCTION STARTS HERE**********************************

int SMDmain()
{
	int retcode=0;
        //gtk_init(&argc, &argv);
        window_main_SMD();
        gtk_main();
	while(flag_SMD!=0)
	{
	        if(flag_SMD==1)
		{
			if(empid && ASname)
			{
				strcpy(srchempid,empid);
				strcat(attendanceSheet_SMD,ASname);
				retcode = sheetquery();
				if(retcode == 1)
				{
					back_window_SMD();
					gtk_main();
				}
				else
				{
					window_scrolled();
					gtk_main();
				}
			}
			else
			{
				back_window_SMD();
				gtk_main();
			}
			//flag_SMD=0;
		}
		if(flag_SMD==2)
		{
			strcpy(attendanceSheet_SMD,"attendanceSheet");
			window_main_SMD();
			gtk_main();
			//flag_SMD=0;    
		}
	}
        
}
 
