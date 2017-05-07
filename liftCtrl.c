#include "sigs.h"

pid_t *pid_list,sensor_process_id,body_process_id;
int des=0;

void up_request(int sigNo){	
	printf("up_request_get %d \n",sigNo );
	switch(sigNo-SIGRTMIN){
		case F1_CALL: des=1;
		printf("Back to floor %d\n",des);
		send_signal(body_process_id,SIGRTMIN+LIFT_DOWN);break;
		case F2_CALL: des=2;
		printf("Request up to floor %d\n",des);
		send_signal(body_process_id,SIGRTMIN+LIFT_UP);break;
		case F3_CALL: des=3;
		printf("Request up to floor %d\n",des);
		send_signal(body_process_id,SIGRTMIN+LIFT_UP);
		break;
		case F4_CALL: des=4;
		printf("Request up to floor %d\n",des);
		send_signal(body_process_id,SIGRTMIN+LIFT_UP);
		break;
		case F5_CALL: des=5;
		printf("Request up to floor %d\n",des);
		send_signal(body_process_id,SIGRTMIN+LIFT_UP);
		break;
		default: break;
	}
	
}
void sensor_change(int sigNo){	
	// printf("sensor_change_get %d \n",sigNo );
	switch(sigNo-SIGRTMIN){
		case F1_ARRIVAL:
		puts("di qua tang 1");
		send_signal(pid_list[LIFT_MNG],SIGRTMIN+F1_ARRIVAL);
		if(des==1){
			send_signal(body_process_id,SIGRTMIN+LIFT_STOP);			
			puts("thong bao chuyen hang xong ve mng");			
		}
		// else send_signal(pid_list[LIFT_MNG],SIGRTMIN+MOVING);
		break;
		case F2_ARRIVAL:
		puts("di qua tang 2");
		send_signal(pid_list[LIFT_MNG],SIGRTMIN+F2_ARRIVAL);
		if(des==2){
			send_signal(body_process_id,SIGRTMIN+LIFT_STOP);
			puts("Tai tang 2, chuyen hang trong 3s");
			sleep(3);
			des=1;
			send_signal(body_process_id,SIGRTMIN+LIFT_DOWN);			
		}
		// else send_signal(pid_list[LIFT_MNG],SIGRTMIN+MOVING);
		break;
		case F3_ARRIVAL:
		puts("di qua tang 3");
		send_signal(pid_list[LIFT_MNG],SIGRTMIN+F3_ARRIVAL);
		if(des==3){
			send_signal(body_process_id,SIGRTMIN+LIFT_STOP);
			puts("Tai tang 3, chuyen hang trong 3s");
			sleep(3);
			des=1;
			send_signal(body_process_id,SIGRTMIN+LIFT_DOWN);			
		}
		// else send_signal(pid_list[LIFT_MNG],SIGRTMIN+MOVING);
		break;
		case F4_ARRIVAL:
		puts("di qua tang 4");
		send_signal(pid_list[LIFT_MNG],SIGRTMIN+F4_ARRIVAL);
		if(des==4){
			send_signal(body_process_id,SIGRTMIN+LIFT_STOP);
			puts("Tai tang 4, chuyen hang trong 3s");
			sleep(3);
			des=1;
			send_signal(body_process_id,SIGRTMIN+LIFT_DOWN);			
		}
		// else send_signal(pid_list[LIFT_MNG],SIGRTMIN+MOVING);
		break;
		case F5_ARRIVAL:
		puts("di qua tang 5");
		send_signal(pid_list[LIFT_MNG],SIGRTMIN+F5_ARRIVAL);
		if(des==5){
			send_signal(body_process_id,SIGRTMIN+LIFT_STOP);
			puts("Tai tang 5, chuyen hang trong 3s");
			sleep(3);
			des=1;
			send_signal(body_process_id,SIGRTMIN+LIFT_DOWN);			
		}
		// else send_signal(pid_list[LIFT_MNG],SIGRTMIN+MOVING);
		break;		
		default:			
		break;
	}	
}
void sensor_process_run(){	
	int control_process_id=getppid();
	printf("Sensor: %d of  Ctrl: %d \n",getpid(),control_process_id);
	int previous_position=pid_list[LIFT_POSITION];
	printf("init value: %d\n",pid_list[LIFT_POSITION] );
	int t=0;
	while(1){
		usleep(CLOCK);
		//printf("%d\n",pid_list[LIFT_POSITION] );
		if(previous_position ^ pid_list[LIFT_POSITION]){
			switch(pid_list[LIFT_POSITION]){			
				case 15:			 
				//printf("send_signal F1_ARRIVAL%d to %d \n",SIGRTMIN+F1_ARRIVAL,pid_list[LIFT_CTR]);
				send_signal(control_process_id,SIGRTMIN+F1_ARRIVAL);break;
				case 45:
				//printf("send_signal F2_ARRIVAL%d to %d \n",SIGRTMIN+F2_ARRIVAL,pid_list[LIFT_CTR]);
				send_signal(control_process_id,SIGRTMIN+F2_ARRIVAL);break;
				case 75: 
				//printf("send_signal F3_ARRIVAL%d to %d \n",SIGRTMIN+F3_ARRIVAL,pid_list[LIFT_CTR]);
				send_signal(control_process_id,SIGRTMIN+F3_ARRIVAL);break;
				case 105: 
				//printf("send_signal F4_ARRIVAL%d to %d \n",SIGRTMIN+F4_ARRIVAL,pid_list[LIFT_CTR]);
				send_signal(control_process_id,SIGRTMIN+F4_ARRIVAL);break;
				case 135: 
				//printf("send_signal F5_ARRIVAL%d to %d \n",SIGRTMIN+F5_ARRIVAL,pid_list[LIFT_CTR]);
				send_signal(control_process_id,SIGRTMIN+F5_ARRIVAL);break;			
				default:break;
			}
			previous_position=pid_list[LIFT_POSITION];
		}					
	}
}

#define VANTOC 5// vận tốc: 0.5m/s
int action=0;
void body(int sigNo){
	// printf("body_get %d \n",sigNo );
	switch(sigNo-SIGRTMIN){
		case LIFT_UP:	action=UP;	break;
		case LIFT_DOWN: action=DOWN;break;
		case LIFT_STOP: action=0;	break;
		default:break;
	}
}
void body_process_run(){
	int control_process_id=getppid();
	signal(SIGRTMIN+LIFT_UP,body);signal(SIGRTMIN+LIFT_DOWN,body);signal(SIGRTMIN+LIFT_STOP,body);	
	pid_list[LIFT_POSITION]=0;
	printf("Body: %d of  Ctrl: %d \n",getpid(),control_process_id );
	pid_t last_value=0;
	while(1){		
		usleep(CLOCK);
		switch(action){
			case DOWN:
				if(pid_list[LIFT_POSITION]>15) {
					pid_list[LIFT_POSITION]-= VANTOC;					
				}
				else action=0;
				break;			
			case UP:
				if(pid_list[LIFT_POSITION]<135) {
					pid_list[LIFT_POSITION]+= VANTOC;					
				}
				else action=0;
				break;
			default:
				break;
		}
		if(last_value!=pid_list[LIFT_POSITION]) {
			printf("Height: %.1f metter\n",pid_list[LIFT_POSITION]/10.0);
			last_value=pid_list[LIFT_POSITION];
		}				
	}
}
int main(int argc, char const *argv[]){
	
	signal(SIGRTMIN+F2_CALL,up_request);signal(SIGRTMIN+F3_CALL,up_request);signal(SIGRTMIN+F4_CALL,up_request);signal(SIGRTMIN+F5_CALL,up_request);
	signal(SIGRTMIN+F1_ARRIVAL,sensor_change);signal(SIGRTMIN+F2_ARRIVAL,sensor_change);signal(SIGRTMIN+F3_ARRIVAL,sensor_change);signal(SIGRTMIN+F4_ARRIVAL,sensor_change);signal(SIGRTMIN+F5_ARRIVAL,sensor_change);
	pid_list=update_pid(LIFT_CTR);
	printf("control_process_id: %d\n",getpid());	
	if((sensor_process_id=fork())==0){
		sensor_process_run();
	}
	else{
		printf("sensor_process_id: %d\n",sensor_process_id );
		if((body_process_id=fork())==0){
			body_process_run();
		}
		else{
			printf("body_process_id: %d\n",body_process_id );
			while(1){
				sleep(5);	
			}
		}			
	}		
	return 0;
}