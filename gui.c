#include <gtk/gtk.h>

GdkPixbuf *create_pixbuf(const gchar * filename) {
    
   GdkPixbuf *pixbuf;
   GError *error = NULL;
   pixbuf = gdk_pixbuf_new_from_file(filename, &error);
   
   if (!pixbuf) {
       
      fprintf(stderr, "%s\n", error->message);
      g_error_free(error);
   }

   return pixbuf;
}
static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *progress_bar;
  GtkWidget *next_entry;
  GtkWidget *window_grid;
  GtkEntryBuffer *buffer;
  
  
  GtkWidget *label_status, *label_next_request;

  float progress_bar_value = 0.8;
  char status[]="tang 4";
  char next_request[]="1,2,3,4,5";
  //create windows
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Elevator Management Panel");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
  gtk_window_move(GTK_WINDOW(window),250,450);    
  gtk_window_set_icon(GTK_WINDOW(window), create_pixbuf("icon"));
  //create list and attach to windows
  window_grid = gtk_grid_new();
  gtk_container_add (GTK_CONTAINER (window), window_grid);
  //create Label
  label_status = gtk_label_new("Current floor:");
  label_next_request = gtk_label_new ("Cac request tiep theo:");
  //print(attach) label status
  gtk_grid_attach(GTK_GRID(window_grid),label_status,2,1,4,1);
  //create progress bar
  progress_bar = gtk_progress_bar_new();
  gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress_bar), progress_bar_value);
  gtk_progress_bar_set_show_text (GTK_PROGRESS_BAR(progress_bar), TRUE);
  gtk_progress_bar_set_text (GTK_PROGRESS_BAR(progress_bar),status);
  //attach progressbar
  gtk_grid_attach(GTK_GRID(window_grid),progress_bar,2,2,4,1);
  //print(attach) label next request
  gtk_grid_attach(GTK_GRID(window_grid),label_next_request,2,3,4,1);
  //create entry
  next_entry = gtk_entry_new();
  gtk_entry_set_text (GTK_ENTRY(next_entry), next_request);
  //attach entry
  gtk_grid_attach(GTK_GRID(window_grid),next_entry,2,5,4,1);

 

  gtk_widget_show_all (window);
}

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}