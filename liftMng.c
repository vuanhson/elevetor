#include "sigs.h"
#define MAX_QUEUE 5

pid_t* pid_list;
int lift_is_moving=FALSE;

int queue[MAX_QUEUE];
int head=-1,tail=-1;
void enqueue(int caller);
int dequeue();
void show();

void up_request(int sigNo){	
	enqueue(sigNo);
	show();		
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
	where_is_it(sigNo);
	switch(sigNo-SIGRTMIN){
		case F1_ARRIVAL:			
			puts("Lift stopped!");
			lift_is_moving=FALSE;						
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
	signal(SIGRTMIN+MOVING,lift_arrival);signal(SIGRTMIN+F1_ARRIVAL,lift_arrival);signal(SIGRTMIN+F2_ARRIVAL,lift_arrival);signal(SIGRTMIN+F3_ARRIVAL,lift_arrival);signal(SIGRTMIN+F4_ARRIVAL,lift_arrival);signal(SIGRTMIN+F5_ARRIVAL,lift_arrival);
	signal(SIGRTMIN+LIFT_UP,up_or_down);signal(SIGRTMIN+LIFT_DOWN,up_or_down);signal(SIGRTMIN+LIFT_STOP,up_or_down);
	pid_list=update_pid(LIFT_MNG);
	printf("mng_process_id: %d\n",getpid());
	int sigNo,count=0;	
	while(1){
		sleep(1);
		if(!lift_is_moving){
			sigNo=dequeue();			
			if(sigNo>0) {
				lift_is_moving=TRUE;
				send_signal(pid_list[LIFT_CTR],sigNo);
			}
		}
		else if(++count%5==0) puts("Lift moving...");
					
	}				
	return 0;
}
void enqueue(int caller){
	int next=(tail+1)%MAX_QUEUE;
	if(head==-1){
		head=tail=0;
		queue[head]=caller;
	}
	else{
		if(next==head ){
			//printf("Head %d %d and Tail %d %d and Next %d\n",head,queue[head],tail,queue[tail],next );		
			printf("Queue is full, request is aborted\n");
		}
		else{
			queue[next]=caller;		
			tail=next;
		}	
	}
	
}
int dequeue(){
	if(head==-1){
		return -1;
	}
	else{
		int tmp=queue[head];
		queue[head]=0;
		if(head!=tail) head=(head+1)%MAX_QUEUE;
		return tmp;
	}
}
void show(){	
	int i;
	for(i=0;i<MAX_QUEUE;i++){
		printf("%d ",queue[i]);
	} 
	printf("\n");
}