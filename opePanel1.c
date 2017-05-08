#include "sigs.h"
#include <gtk/gtk.h>

pid_t* pid_list;
int current_floor_number=1;
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

static void
func2(GtkWidget *widget,
      gpointer data)
{
    //g_print("Ban da click button2\n");
    // if(strcmp(gtk_widget_get_name(button2),"red_btn")!=0){
        // gtk_widget_set_name(button2, "red_btn");
        send_signal(pid_list[LIFT_MNG],SIGRTMIN+F2_CALL);
    // }    
}
static void
func3(GtkWidget *widget,
      gpointer data)
{
    //g_print("Ban da click button3\n");
    // if(strcmp(gtk_widget_get_name(button3),"red_btn")!=0){
        // gtk_widget_set_name(button3, "red_btn");
        send_signal(pid_list[LIFT_MNG],SIGRTMIN+F3_CALL);
    // }
}
static void
func4(GtkWidget *widget,
      gpointer data)
{
    //g_print("Ban da click button4\n");
    // if(strcmp(gtk_widget_get_name(button4),"red_btn")!=0){
        // gtk_widget_set_name(button4, "red_btn");
        send_signal(pid_list[LIFT_MNG],SIGRTMIN+F4_CALL);
    // }
}
static void
func5(GtkWidget *widget,
      gpointer data)
{
    //g_print("Ban da click button5\n");
    // if(strcmp(gtk_widget_get_name(button5),"red_btn")!=0){
        // gtk_widget_set_name(button5, "red_btn");
        send_signal(pid_list[LIFT_MNG],SIGRTMIN+F5_CALL); 
    // }   
}

static void quit(){    
    send_signal(pid_list[LIFT_MNG],SIGINT);
    send_signal(pid_list[LIFT_CTR],SIGINT);
    int i;
    pid_t this_pid=getpid();
    for(i=OPE_PANE1;i<=OPE_PANE5;i++){
        if(this_pid!=pid_list[i])
            send_signal(pid_list[i],SIGINT);
    }    
    shmdt(pid_list);
    release_shm();
    gtk_widget_destroy(window);
}
static void
activate(GtkApplication *app,
         gpointer user_data)
{
    // <-------------  For add stylesheet.css
    GtkCssProvider* Provider = gtk_css_provider_new();
    GdkDisplay* Display = gdk_display_get_default();
    GdkScreen* Screen = gdk_display_get_default_screen(Display);

    gtk_style_context_add_provider_for_screen(Screen, GTK_STYLE_PROVIDER(Provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_css_provider_load_from_path(GTK_CSS_PROVIDER(Provider), "stylesheet.css", NULL);
    // End add stylesheet.css ---------------->

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), window_title);
    gtk_window_set_default_size(GTK_WINDOW(window), 150, 200);
    gtk_window_move(GTK_WINDOW(window),375,250);
    //   Add Vbox
    main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), main_box);

    button_box = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
    gtk_container_add(GTK_CONTAINER(main_box), button_box);

    up_down_btn = gtk_button_new_with_label("---");
    gtk_widget_set_name(up_down_btn, "info_btn");
    gtk_widget_set_sensitive(up_down_btn, FALSE);
    gtk_container_add(GTK_CONTAINER(button_box), up_down_btn);

    current_floor_btn = gtk_button_new_with_label("1");
    gtk_widget_set_name(current_floor_btn, "info_btn");

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
    g_signal_connect(close_btn, "clicked", G_CALLBACK(quit), NULL);
    //g_signal_connect_swapped(close_btn, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    gtk_container_add(GTK_CONTAINER(button_box), close_btn);
    // show all widget
    gtk_widget_show_all(window);
}
void current_floor_change(int sigNo){
    current_floor_number=sigNo-SIGRTMIN;
	switch(sigNo-SIGRTMIN){
		case F1_ARRIVAL:			
			gtk_button_set_label(GTK_BUTTON(current_floor_btn),"1");
			break;
		case F2_ARRIVAL:			
			gtk_button_set_label(GTK_BUTTON(current_floor_btn),"2");
			break;
		case F3_ARRIVAL:			
			gtk_button_set_label(GTK_BUTTON(current_floor_btn),"3");
			break;
		case F4_ARRIVAL:			
			gtk_button_set_label(GTK_BUTTON(current_floor_btn),"4");
			break;
		case F5_ARRIVAL:			
			gtk_button_set_label(GTK_BUTTON(current_floor_btn),"5");
			break;	
		default:			
			break;
	}	
}
void direction_change(int sigNo){
    switch(sigNo-SIGRTMIN){
        case LIFT_UP:            
            gtk_button_set_label(GTK_BUTTON(up_down_btn),"UP");
            break;
        case LIFT_STOP:            
            gtk_button_set_label(GTK_BUTTON(up_down_btn),"STAND");
            switch(current_floor_number+1){
                case 2:
                    if(strcmp(gtk_widget_get_name(button2),"red_btn")==0){
                        gtk_widget_set_name(button2, "default_btn");                         
                    } 
                break;
                case 3:
                    if(strcmp(gtk_widget_get_name(button3),"red_btn")==0){
                        gtk_widget_set_name(button3, "default_btn");                         
                    } 
                break;
                case 4:
                    if(strcmp(gtk_widget_get_name(button4),"red_btn")==0){
                        gtk_widget_set_name(button4, "default_btn");                         
                    } 
                break;
                case 5:
                    if(strcmp(gtk_widget_get_name(button5),"red_btn")==0){
                        gtk_widget_set_name(button5, "default_btn");                         
                    } 
                break;
                default:break;
            }
            break;
        case LIFT_DOWN:            
            gtk_button_set_label(GTK_BUTTON(up_down_btn),"DOWN");
            break;          
        default:            
            break;
    }
}
int main(int argc, char *argv[])
{
	signal(SIGRTMIN+F1_ARRIVAL,current_floor_change);signal(SIGRTMIN+F2_ARRIVAL,current_floor_change);signal(SIGRTMIN+F3_ARRIVAL,current_floor_change);signal(SIGRTMIN+F4_ARRIVAL,current_floor_change);signal(SIGRTMIN+F5_ARRIVAL,current_floor_change);
	signal(SIGRTMIN+LIFT_UP,direction_change);signal(SIGRTMIN+LIFT_DOWN,direction_change);signal(SIGRTMIN+LIFT_STOP,direction_change);
    pid_list=update_pid(OPE_PANE1);	
    printf("ope1_process_id %d\n",pid_list[OPE_PANE1] );    
	GtkApplication *app;
    int status;
    strcpy(window_title,"Tầng 1");    
    app = gtk_application_new("org.gtk.tang1", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), 0, NULL);
    g_object_unref(app);
    return status;
}