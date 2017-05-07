#include "sigs.h"
#include <gtk/gtk.h>

pid_t* pid_list;
GtkWidget *window;
GtkWidget *button2;
GtkWidget *button3;
GtkWidget *button4;
GtkWidget *button5;
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
func2(GtkWidget *widget,
      gpointer data)
{
    g_print("Ban da click button2\n");
    kill(pid_list[LIFT_MNG],SIGRTMIN+F2_CALL);
}
static void
func3(GtkWidget *widget,
      gpointer data)
{
    g_print("Ban da click button3\n");
    kill(pid_list[LIFT_MNG],SIGRTMIN+F3_CALL);
}
static void
func4(GtkWidget *widget,
      gpointer data)
{
    g_print("Ban da click button4\n");
    kill(pid_list[LIFT_MNG],SIGRTMIN+F4_CALL);
}
static void
func5(GtkWidget *widget,
      gpointer data)
{
    g_print("Ban da click button5\n");
    kill(pid_list[LIFT_MNG],SIGRTMIN+F5_CALL);    
}

static void
activate(GtkApplication *app,
         gpointer user_data)
{

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
    // button 2
    button2 = gtk_button_new_with_label("2");
    g_signal_connect(button2, "clicked", G_CALLBACK(func2), NULL);
    gtk_container_add(GTK_CONTAINER(button_box), button2);
    // button3
    button3 = gtk_button_new_with_label("3");
    g_signal_connect(button3, "clicked", G_CALLBACK(func3), NULL);
    gtk_container_add(GTK_CONTAINER(button_box), button3);
    // button4
    button4 = gtk_button_new_with_label("4");
    g_signal_connect(button4, "clicked", G_CALLBACK(func4), NULL);
    gtk_container_add(GTK_CONTAINER(button_box), button4);
    // button5
    button5 = gtk_button_new_with_label("5");
    g_signal_connect(button5, "clicked", G_CALLBACK(func5), NULL);
    gtk_container_add(GTK_CONTAINER(button_box), button5);

     // close_btn
    close_btn = gtk_button_new_with_label("Close");
    // g_signal_connect(close_btn, "clicked", G_CALLBACK(print_hello), NULL);
    g_signal_connect_swapped(close_btn, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    gtk_container_add(GTK_CONTAINER(button_box), close_btn);
    // show all widget
    gtk_widget_show_all(window);
}
void current_floor_change(int sigNo){
	switch(sigNo-SIGRTMIN){
		case F1_ARRIVAL:
			puts("1");
			//gtk_button_set_label(GTK_BUTTON(current_floor_btn),"1");
			break;
		case F2_ARRIVAL:
			puts("2");
			//gtk_button_set_label(GTK_BUTTON(current_floor_btn),"2");
			break;
		case F3_ARRIVAL:
			puts("3");
			//gtk_button_set_label(GTK_BUTTON(current_floor_btn),"3");
			break;
		case F4_ARRIVAL:
			puts("4");
			//gtk_button_set_label(GTK_BUTTON(current_floor_btn),"4");
			break;
		case F5_ARRIVAL:
			puts("5");
			//gtk_button_set_label(GTK_BUTTON(current_floor_btn),"5");
			break;	
		default:			
			break;
	}	
}
int main(int argc, char *argv[])
{
	signal(SIGRTMIN+F1_ARRIVAL,current_floor_change);signal(SIGRTMIN+F2_ARRIVAL,current_floor_change);signal(SIGRTMIN+F3_ARRIVAL,current_floor_change);signal(SIGRTMIN+F4_ARRIVAL,current_floor_change);signal(SIGRTMIN+F5_ARRIVAL,current_floor_change);
	pid_list=update_pid(OPE_PANE1);	
	
	GtkApplication *app;
    int status;
    strcpy(window_title,"Tầng 1");
    strcpy(current_floor,"");
    app = gtk_application_new("org.gtk.tang1", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    
    g_object_unref(app);

    return status;
}