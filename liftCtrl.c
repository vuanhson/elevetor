#include "sigs.h"

pid_t* pid_list;
int des=0;

void up_request(int sigNo){	
	printf("up_request_get %d \n",sigNo );
	switch(sigNo-SIGRTMIN){
		case F1_CALL: des=1;
		printf("Back to floor %d\n",des);
		kill(pid_list[LIFT_BODY],SIGRTMIN+LIFT_DOWN);break;
		case F2_CALL: des=2;
		printf("Request up to floor %d\n",des);
		kill(pid_list[LIFT_BODY],SIGRTMIN+LIFT_UP);break;
		case F3_CALL: des=3;
		printf("Request up to floor %d\n",des);
		kill(pid_list[LIFT_BODY],SIGRTMIN+LIFT_UP);
		break;
		case F4_CALL: des=4;
		printf("Request up to floor %d\n",des);
		kill(pid_list[LIFT_BODY],SIGRTMIN+LIFT_UP);
		break;
		case F5_CALL: des=5;
		printf("Request up to floor %d\n",des);
		kill(pid_list[LIFT_BODY],SIGRTMIN+LIFT_UP);
		break;
		default: break;
	}
	
}
void sensor_change(int sigNo){	
	// printf("sensor_change_get %d \n",sigNo );
	switch(sigNo-SIGRTMIN){
		case F1_ARRIVAL:
		puts("toi tang 1");
		if(des==1){
			kill(pid_list[LIFT_BODY],SIGRTMIN+LIFT_STOP);			
			puts("bao stop ve MNG");
			kill(pid_list[LIFT_MNG],SIGRTMIN+F1_ARRIVAL);
		}
		// else kill(pid_list[LIFT_MNG],SIGRTMIN+MOVING);
		break;
		case F2_ARRIVAL:
		puts("toi tang 2");
		if(des==2){
			kill(pid_list[LIFT_BODY],SIGRTMIN+LIFT_STOP);
			puts("2chuyen hang trong 3s");
			sleep(3);
			des=1;
			kill(pid_list[LIFT_BODY],SIGRTMIN+LIFT_DOWN);
			// puts("bao stop ve MNG");
			// kill(pid_list[LIFT_MNG],SIGRTMIN+F2_ARRIVAL);
		}
		// else kill(pid_list[LIFT_MNG],SIGRTMIN+MOVING);
		break;
		case F3_ARRIVAL:
		puts("toi tang 3");
		if(des==3){
			kill(pid_list[LIFT_BODY],SIGRTMIN+LIFT_STOP);
			puts("3chuyen hang trong 3s");
			sleep(3);
			des=1;
			kill(pid_list[LIFT_BODY],SIGRTMIN+LIFT_DOWN);
			// puts("bao stop ve MNG");
			// kill(pid_list[LIFT_MNG],SIGRTMIN+F3_ARRIVAL);
		}
		// else kill(pid_list[LIFT_MNG],SIGRTMIN+MOVING);
		break;
		case F4_ARRIVAL:
		puts("toi tang 4");
		if(des==4){
			kill(pid_list[LIFT_BODY],SIGRTMIN+LIFT_STOP);
			puts("4chuyen hang trong 3s");
			sleep(3);
			des=1;
			kill(pid_list[LIFT_BODY],SIGRTMIN+LIFT_DOWN);
			// puts("bao stop ve MNG");			
			// kill(pid_list[LIFT_MNG],SIGRTMIN+F4_ARRIVAL);
		}
		// else kill(pid_list[LIFT_MNG],SIGRTMIN+MOVING);
		break;
		case F5_ARRIVAL:
		puts("toi tang 5");
		if(des==5){
			kill(pid_list[LIFT_BODY],SIGRTMIN+LIFT_STOP);
			puts("5chuyen hang trong 3s");
			sleep(3);
			des=1;
			kill(pid_list[LIFT_BODY],SIGRTMIN+LIFT_DOWN);
			// puts("bao stop ve MNG");
			// kill(pid_list[LIFT_MNG],SIGRTMIN+F5_ARRIVAL);
		}
		// else kill(pid_list[LIFT_MNG],SIGRTMIN+MOVING);
		break;		
		default:			
		break;

	}
	// signal(SIGRTMIN+F1_ARRIVAL,sensor_change);signal(SIGRTMIN+F2_ARRIVAL,sensor_change);signal(SIGRTMIN+F3_ARRIVAL,sensor_change);signal(SIGRTMIN+F4_ARRIVAL,sensor_change);signal(SIGRTMIN+F5_ARRIVAL,sensor_change);
}
int main(int argc, char const *argv[]){
	
	signal(SIGRTMIN+F2_CALL,up_request);signal(SIGRTMIN+F3_CALL,up_request);signal(SIGRTMIN+F4_CALL,up_request);signal(SIGRTMIN+F5_CALL,up_request);
	signal(SIGRTMIN+F1_ARRIVAL,sensor_change);signal(SIGRTMIN+F2_ARRIVAL,sensor_change);signal(SIGRTMIN+F3_ARRIVAL,sensor_change);signal(SIGRTMIN+F4_ARRIVAL,sensor_change);signal(SIGRTMIN+F5_ARRIVAL,sensor_change);
	pid_list=update_pid(LIFT_CTR);
	printf("Ctr: %d\n",getpid());			
	while(1){
		sleep(3);		
	}		
	return 0;
}