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
static void
call_func(GtkWidget *widget,
      gpointer data)
{   // Set id cho button de su dung css #red_btn
    gtk_widget_set_name(call_btn, "red_btn");

    int this_floor=*(int*)data;
    //g_print("Ban da click call_btn at floor: %d\n",this_floor-SIGRTMIN-10);
    send_signal(pid_list[LIFT_MNG],this_floor);    
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


    //printf("%d\n",*(int*)user_data );
    int floor_number=*(int*)user_data-SIGRTMIN-F1_CALL+1;
    //printf("%d\n",floor_number);
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), window_title);
    gtk_window_set_default_size(GTK_WINDOW(window), 150, 100);
    gtk_window_move(GTK_WINDOW(window),150*(floor_number-1),100);
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
    // button x
    call_btn = gtk_button_new_with_label("CALL");
    g_signal_connect(call_btn, "clicked", G_CALLBACK(call_func), user_data);
    gtk_container_add(GTK_CONTAINER(button_box), call_btn);

     // close_btn
    close_btn = gtk_button_new_with_label("Close");
    g_signal_connect(close_btn, "clicked", G_CALLBACK(quit), NULL);
    //g_signal_connect_swapped(close_btn, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    gtk_container_add(GTK_CONTAINER(button_box), close_btn);
    // show all widget
    gtk_widget_show_all(window);
}
void current_floor_change(int sigNo){
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
            gtk_widget_set_name(call_btn, "ready_btn");
            gtk_button_set_label(GTK_BUTTON(up_down_btn),"STAND");
            break;
        case LIFT_DOWN:
            gtk_widget_set_name(call_btn, "default_btn");            
            gtk_button_set_label(GTK_BUTTON(up_down_btn),"DOWN");
            break;          
        default:            
            break;
    }
}
int main(int argc, char *argv[])
{	
	GtkApplication *app;
    int status;
    signal(SIGRTMIN+F1_ARRIVAL,current_floor_change);signal(SIGRTMIN+F2_ARRIVAL,current_floor_change);signal(SIGRTMIN+F3_ARRIVAL,current_floor_change);signal(SIGRTMIN+F4_ARRIVAL,current_floor_change);signal(SIGRTMIN+F5_ARRIVAL,current_floor_change);    
	signal(SIGRTMIN+LIFT_UP,direction_change);signal(SIGRTMIN+LIFT_DOWN,direction_change);signal(SIGRTMIN+LIFT_STOP,direction_change);
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
    g_signal_connect(app, "activate", G_CALLBACK(activate), &this_floor);
    status = g_application_run(G_APPLICATION(app), 0, NULL);
    g_object_unref(app);
    return status;    
}