#include "sigs.h"
#include <gtk/gtk.h>

pid_t* pid_list;

GtkWidget *window;
GtkWidget *call_btn;
GtkWidget *close_btn;
GtkWidget *button_box;
GtkWidget *main_box;
GtkWidget *up_down_btn;
GtkWidget *current_floor_btn;
char window_title[10],current_floor[10],current_label[5];
// Thay doi trang thai len xuong cua thang may
static void
set_status(gchar *status){
    gtk_button_set_label(GTK_BUTTON(up_down_btn), status);
}
static void
call_func(GtkWidget *widget,
      gpointer data)
{
    int this_floor=*(int*)data;
    g_print("Ban da click call_btn at floor: %d\n",this_floor-SIGRTMIN-10);
    kill(pid_list[LIFT_MNG],this_floor);
    set_status("default");
}
static void
activate(GtkApplication *app,
         gpointer user_data)
{

    //printf("%d\n",*(int*)user_data );
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), window_title);
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
    //   Add Vbox
    main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), main_box);

    button_box = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
    gtk_container_add(GTK_CONTAINER(main_box), button_box);

    up_down_btn = gtk_button_new_with_label("---");
    gtk_widget_set_sensitive(up_down_btn, FALSE);
    gtk_container_add(GTK_CONTAINER(button_box), up_down_btn);

    current_floor_btn = gtk_button_new_with_label(current_floor);
    gtk_widget_set_sensitive(current_floor_btn, FALSE);
    gtk_container_add(GTK_CONTAINER(button_box), current_floor_btn);
    // button x
    call_btn = gtk_button_new_with_label(current_label);
    g_signal_connect(call_btn, "clicked", G_CALLBACK(call_func), user_data);
    gtk_container_add(GTK_CONTAINER(button_box), call_btn);

     // close_btn
    close_btn = gtk_button_new_with_label("Close");
    // g_signal_connect(close_btn, "clicked", G_CALLBACK(print_hello), NULL);
    g_signal_connect_swapped(close_btn, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    gtk_container_add(GTK_CONTAINER(button_box), close_btn);
    // show all widget
    gtk_widget_show_all(window);
}

int main(int argc, char *argv[])
{	
	GtkApplication *app;
    int status;

	if(argc!=2){
		printf("Usage: opx FLOOR_NUMBER\n"); exit(0);
	}		
	int this_floor;
	switch(atoi(argv[1])){
		case 2: 
		pid_list=update_pid(OPE_PANE2);
		this_floor=SIGRTMIN+F2_CALL;
		strcpy(window_title,"Tầng 2");
		app = gtk_application_new("org.gtk.tang2", G_APPLICATION_FLAGS_NONE);
		break;
		case 3: 
		pid_list=update_pid(OPE_PANE3);
		this_floor=SIGRTMIN+F3_CALL;
		strcpy(window_title,"Tầng 3");
		app = gtk_application_new("org.gtk.tang3", G_APPLICATION_FLAGS_NONE);
		break;
		case 4:
		pid_list=update_pid(OPE_PANE4);
		this_floor=SIGRTMIN+F4_CALL;
		strcpy(window_title,"Tầng 4");
		app = gtk_application_new("org.gtk.tang4", G_APPLICATION_FLAGS_NONE);
		break;
		case 5:
		pid_list=update_pid(OPE_PANE5); 
		this_floor=SIGRTMIN+F5_CALL;
		strcpy(window_title,"Tầng 5");
		app = gtk_application_new("org.gtk.tang5", G_APPLICATION_FLAGS_NONE);
		break;
		default:break;
	}

	strcpy(current_floor,"");
	strcpy(current_label,"CALL");
    g_signal_connect(app, "activate", G_CALLBACK(activate), &this_floor);

    status = g_application_run(G_APPLICATION(app), 0, NULL);
    
    g_object_unref(app);

    return status;    
}