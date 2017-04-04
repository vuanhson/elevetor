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
	int floor;
	// signal(SIGRTMIN+F2_CALL,SIG_IGN);	signal(SIGRTMIN+F3_CALL,SIG_IGN);	signal(SIGRTMIN+F4_CALL,SIG_IGN);	signal(SIGRTMIN+F5_CALL,SIG_IGN);
	// signal(SIGRTMIN+MOVING,SIG_IGN);signal(SIGRTMIN+F1_ARRIVAL,SIG_IGN);signal(SIGRTMIN+F2_ARRIVAL,SIG_IGN);signal(SIGRTMIN+F3_ARRIVAL,SIG_IGN);signal(SIGRTMIN+F4_ARRIVAL,SIG_IGN);signal(SIGRTMIN+F5_ARRIVAL,SIG_IGN);
	enqueue(sigNo);
	show();
	switch(sigNo-SIGRTMIN){
		case F2_CALL: floor=2;break;
		case F3_CALL: floor=3;break;
		case F4_CALL: floor=4;break;
		case F5_CALL: floor=5;break;
		default: break;
	}
	printf("Request up to floor %d\n",floor);	
}
void lift_arrival(int sigNo){
	// signal(SIGRTMIN+F2_CALL,SIG_IGN);	signal(SIGRTMIN+F3_CALL,SIG_IGN);	signal(SIGRTMIN+F4_CALL,SIG_IGN);	signal(SIGRTMIN+F5_CALL,SIG_IGN);
	// signal(SIGRTMIN+MOVING,SIG_IGN);signal(SIGRTMIN+F1_ARRIVAL,SIG_IGN);signal(SIGRTMIN+F2_ARRIVAL,SIG_IGN);signal(SIGRTMIN+F3_ARRIVAL,SIG_IGN);signal(SIGRTMIN+F4_ARRIVAL,SIG_IGN);signal(SIGRTMIN+F5_ARRIVAL,SIG_IGN);
	//puts("Da nhan duoc thogn bao tu CTR");
	switch(sigNo-SIGRTMIN){
		case F1_ARRIVAL:
			//kill(pid_list[OPE_PANE1],sigNo);
			// sigNo=dequeue();
			// if(sigNo!=-1) kill(pid_list[LIFT_CTR],sigNo);
			puts("Lift stopped!");
			lift_is_moving=FALSE;			
			break;
		case F2_ARRIVAL:		
		case F3_ARRIVAL:		
		case F4_ARRIVAL:		
		case F5_ARRIVAL:
			// puts("Lift stopped!");
			// lift_is_moving=FALSE;
			//kill(pid_list[OPE_PANEX],sigNo);
			// puts("DANG CHUYEN HANG 3s");
			// sleep(3);
			// kill(pid_list[LIFT_CTR],SIGRTMIN+F1_CALL);
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
	pid_list=update_pid(LIFT_MNG);
	printf("Mng: %d\n",getpid());
	int sigNo,count=0;	
	while(1){
		sleep(1);
		if(!lift_is_moving){
			sigNo=dequeue();			
			//printf("Head %d %d and Tail %d %d and Next %d\n",head,queue[head],tail,queue[tail],sigNo );
			//show();
			if(sigNo>0) {
				lift_is_moving=TRUE;
				kill(pid_list[LIFT_CTR],sigNo);
			}
		}
		else if(++count%5==0) puts("Lift moving...");
					
	}
	// for(int i=1;i<10;i++){
	// 	enqueue(i*10);
	// 	show();
	// 	puts("");
	// 	if(i==3||i==7||i==8) printf("De %d\n",dequeue() );
	// }			
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
}