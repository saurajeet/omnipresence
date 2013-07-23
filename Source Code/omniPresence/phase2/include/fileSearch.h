char filename_BAKP[30]="";
void ok_sel_FS(GtkWidget *widget, GtkFileSelection *FS)
{
	strcpy(filename_BAKP,gtk_file_selection_get_filename(GTK_FILE_SELECTION(FS)));
	printf("filename:: %s\n",filename_BAKP);
	//gtk_widget_hide (FS);
	gtk_main_quit();
}
void filesearch_FS()
{
	GtkWidget *file;
	file = gtk_file_selection_new("omniPresence:: File Selection");
	g_signal_connect(G_OBJECT(file),"destroy",G_CALLBACK(gtk_main_quit),NULL);
	g_signal_connect(G_OBJECT(GTK_FILE_SELECTION(file)->ok_button),"clicked",G_CALLBACK(ok_sel_FS),(gpointer)file);
	g_signal_connect_swapped(G_OBJECT(GTK_FILE_SELECTION(file)->ok_button),"clicked",G_CALLBACK(gtk_widget_destroy),(gpointer)file);
	g_signal_connect_swapped(G_OBJECT(GTK_FILE_SELECTION(file)->cancel_button),"clicked",G_CALLBACK(gtk_widget_destroy),(gpointer)file);
	gtk_file_selection_set_filename(GTK_FILE_SELECTION(file),"*.sql");
	gtk_widget_show(file);
	gtk_main();
	gtk_widget_hide (file);
}
