
//*************************************GLOBAL VARIABLE DECLARATION********************************

static char uname[14]="",pswd[6]="";
const char *uname_entry,*pswd_entry;

//************************************GLOBAL FUNCTION DECLARATION*********************************

static void submit_uname(GtkWidget *widget,GtkWidget *entry)
{
	uname_entry = gtk_entry_get_text(GTK_ENTRY(entry));
	strcpy(uname,uname_entry);
}

static void submit_pswd(GtkWidget *widget,GtkWidget *entry)
{
	pswd_entry = gtk_entry_get_text(GTK_ENTRY(entry));
	strcpy(pswd,pswd_entry);
}

static void submit(GtkWidget *widget,GtkWidget *window)
{
	gtk_widget_hide(window);
	gtk_main_quit();
}

void login_window_content()
{
	GtkWidget *window;
	GtkWidget *label1,*label2;
	GtkWidget *entry1,*entry2;
	GtkWidget *submit_button, *quit_button;
	GtkWidget *hbox1,*hbox2,*hbox3,*vbox;
	GtkWidget *hseparator;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"Login Window");
	gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(window),20);
	g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);

	vbox = gtk_vbox_new(FALSE,10);
	gtk_container_add(GTK_CONTAINER(window),vbox);
	gtk_widget_show(vbox);

	hbox1 = gtk_hbox_new(FALSE,10);
	gtk_container_add(GTK_CONTAINER(vbox),hbox1);
	gtk_widget_show(hbox1);

	label1 = gtk_label_new("User Name");
	gtk_box_pack_start(GTK_BOX(hbox1),label1,TRUE,TRUE,0);
	gtk_widget_show(label1);

	entry1 = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(entry1),14);
	gtk_entry_set_text(GTK_ENTRY(entry1),uname);
	g_signal_connect(G_OBJECT(entry1),"changed",G_CALLBACK(submit_uname),(gpointer)entry1);
	gtk_box_pack_start(GTK_BOX(hbox1),entry1,FALSE,FALSE,0);
	gtk_widget_show(entry1);

	hbox2 = gtk_hbox_new(FALSE,10);
	gtk_container_add(GTK_CONTAINER(vbox),hbox2);
	gtk_widget_show(hbox2);

	label2 = gtk_label_new("Password");
	gtk_box_pack_start(GTK_BOX(hbox2),label2,TRUE,TRUE,0);
	gtk_widget_show(label2);

	entry2 = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(entry2),6);
	gtk_entry_set_visibility(GTK_ENTRY(entry2),FALSE);
	g_signal_connect(G_OBJECT(entry2),"changed",G_CALLBACK(submit_pswd),(gpointer)entry2);
	gtk_box_pack_start(GTK_BOX(hbox2),entry2,FALSE,FALSE,0);
	gtk_widget_show(entry2);

	hseparator = gtk_hseparator_new();
	gtk_container_add(GTK_CONTAINER(vbox),hseparator);
	gtk_widget_show(hseparator);

	hbox3 = gtk_hbox_new(FALSE,10);
	gtk_container_add(GTK_CONTAINER(vbox),hbox3);
	gtk_widget_show(hbox3);	

	submit_button = gtk_button_new_with_label("Enter");
	g_signal_connect(G_OBJECT(submit_button),"clicked",G_CALLBACK(submit),window);
	gtk_box_pack_start(GTK_BOX(hbox3),submit_button,TRUE,FALSE,0);
	gtk_widget_show(submit_button);

	quit_button = gtk_button_new_with_label("Quit");
	g_signal_connect_swapped(G_OBJECT(quit_button),"clicked",G_CALLBACK(gtk_main_quit),G_OBJECT(window));
	gtk_box_pack_start(GTK_BOX(hbox3),quit_button,TRUE,FALSE,0);
	gtk_widget_show(quit_button);

	gtk_widget_show(window);
	
}
//***********************************MAIN FUNCTION STARTS HERE************************************

int login_window(int argc,char *argv[])
{
	void window_content();
	gtk_init(&argc,&argv);
	login_window_content();
	gtk_main();
	printf("User Name: %s\n",uname);
	printf("Password : %s\n",pswd);
	if(strcmp(uname,"root")!=0 || strcmp(pswd,"omni")!=0)
	  return 1;
	else
	  return 0;
}
