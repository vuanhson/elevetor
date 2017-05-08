#include "sigs.h"
#define MAX_QUEUE 5

pid_t* pid_list;
int lift_is_moving=FALSE;
int fifoFd;

void up_request(int sigNo){		
	printf("%d %s\n",sigNo,lift_is_moving ? "TRUE" : "FALSE" );
	if(lift_is_moving){		
		write(fifoFd, &sigNo, sizeof(int));
	}
	else{
		lift_is_moving=send_signal(pid_list[LIFT_CTR],sigNo);		
	}		
}
void where_is_it(int sigNo){// hàm này báo thang máy đang ở tầng nào đến các tầng:
	send_signal(pid_list[OPE_PANE1],sigNo);
	send_signal(pid_list[OPE_PANE2],sigNo);
	send_signal(pid_list[OPE_PANE3],sigNo);
	send_signal(pid_list[OPE_PANE4],sigNo);
	send_signal(pid_list[OPE_PANE5],sigNo);
}
void up_or_down(int sigNo){// hàm này cập nhật hướng di chuyển của thang máy, báo cho các tầng biết:
	send_signal(pid_list[OPE_PANE1],sigNo);
	send_signal(pid_list[OPE_PANE2],sigNo);
	send_signal(pid_list[OPE_PANE3],sigNo);
	send_signal(pid_list[OPE_PANE4],sigNo);
	send_signal(pid_list[OPE_PANE5],sigNo);
}
void lift_arrival(int sigNo){//  hàm này xử lí ngắt nhận được từ liftCtrl:
	// where_is_it(sigNo);
	int sigNumber;
	switch(sigNo-SIGRTMIN){
		case F1_ARRIVAL:			
			if(read(fifoFd, &sigNumber, sizeof(int)) > 0){
				// printf("get queue dc: %d\n",sigNumber );
				lift_is_moving=send_signal(pid_list[LIFT_CTR],sigNumber);
			}
			else{
				lift_is_moving=FALSE;
				printf("Lift stopped!\n");
			}									
			break;
		case F2_ARRIVAL:			
			break;		
		case F3_ARRIVAL:			
			break;		
		case F4_ARRIVAL:			
			break;		
		case F5_ARRIVAL:			
			break;		
		default:
			lift_is_moving=TRUE;
		break;
	}
}
int main(int argc, char const *argv[])
{
	signal(SIGRTMIN+F2_CALL,up_request);	signal(SIGRTMIN+F3_CALL,up_request);	signal(SIGRTMIN+F4_CALL,up_request);	signal(SIGRTMIN+F5_CALL,up_request);
	signal(SIGRTMIN+F1_ARRIVAL,lift_arrival);signal(SIGRTMIN+F2_ARRIVAL,lift_arrival);signal(SIGRTMIN+F3_ARRIVAL,lift_arrival);signal(SIGRTMIN+F4_ARRIVAL,lift_arrival);signal(SIGRTMIN+F5_ARRIVAL,lift_arrival);
	//signal(SIGRTMIN+LIFT_UP,up_or_down);signal(SIGRTMIN+LIFT_DOWN,up_or_down);signal(SIGRTMIN+LIFT_STOP,up_or_down);
	pid_list=update_pid(LIFT_MNG);
	printf("mng_process_id: %d\n",getpid());		

	//Make FIFO file
	remove("queue");
	if ( mkfifo(FIFO_FILE_PATH,0666) == -1 ){
	    perror("mkfifo");
	    exit(1);
	}
	//Open for writing only
	if ( ( fifoFd=open(FIFO_FILE_PATH,O_RDWR|O_NONBLOCK) ) == -1 ){
	    perror("fifofile open");
	    exit(1);
	} 
			
	while(1){
		sleep(1);					
	}
	close(fifoFd);
	unlink(FIFO_FILE_PATH);				
	return 0;
}