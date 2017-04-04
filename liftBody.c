#include "sigs.h"

#define VANTOC 5// vận tốc: 0.5m/s

pid_t* pid_list;
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
int main(int argc, char const *argv[])
{
	signal(SIGRTMIN+LIFT_UP,body);signal(SIGRTMIN+LIFT_DOWN,body);signal(SIGRTMIN+LIFT_STOP,body);	
	pid_list=update_pid(LIFT_BODY);
	pid_list[LIFT_POSITION]=0;
	printf("Body: %d\n",getpid());
	pid_t t=0;
	while(1){
		sleep(1);
		switch(action){
			case DOWN:
				if(pid_list[LIFT_POSITION]>15) pid_list[LIFT_POSITION]-= VANTOC;
				else action=0;
				break;			
			case UP:
				if(pid_list[LIFT_POSITION]<135) pid_list[LIFT_POSITION]+= VANTOC;
				else action=0;
				break;
			default:
				break;
		}
		printf("Height: %.1f metter\n",pid_list[LIFT_POSITION]/10.0);				
	}		
	return 0;
}