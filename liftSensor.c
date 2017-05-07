#include "sigs.h"

pid_t* pid_list;

int main(int argc, char const *argv[])
{	
	pid_list=update_pid(LIFT_SENSOR);
	printf("Sensor: %d\n",getpid());
	int previous_position=pid_list[LIFT_POSITION];
	printf("init value: %d\n",pid_list[LIFT_POSITION] );
	int t=0;
	while(1){
		usleep(CLOCK);
		//printf("%d\n",pid_list[LIFT_POSITION] );
		if(previous_position ^ pid_list[LIFT_POSITION]){
			switch(pid_list[LIFT_POSITION]){			
				case 15:			 
				//printf("kill F1_ARRIVAL%d to %d \n",SIGRTMIN+F1_ARRIVAL,pid_list[LIFT_CTR]);
				kill(pid_list[LIFT_CTR],SIGRTMIN+F1_ARRIVAL);break;
				case 45:
				//printf("kill F2_ARRIVAL%d to %d \n",SIGRTMIN+F2_ARRIVAL,pid_list[LIFT_CTR]);
				kill(pid_list[LIFT_CTR],SIGRTMIN+F2_ARRIVAL);break;
				case 75: 
				//printf("kill F3_ARRIVAL%d to %d \n",SIGRTMIN+F3_ARRIVAL,pid_list[LIFT_CTR]);
				kill(pid_list[LIFT_CTR],SIGRTMIN+F3_ARRIVAL);break;
				case 105: 
				//printf("kill F4_ARRIVAL%d to %d \n",SIGRTMIN+F4_ARRIVAL,pid_list[LIFT_CTR]);
				kill(pid_list[LIFT_CTR],SIGRTMIN+F4_ARRIVAL);break;
				case 135: 
				//printf("kill F5_ARRIVAL%d to %d \n",SIGRTMIN+F5_ARRIVAL,pid_list[LIFT_CTR]);
				kill(pid_list[LIFT_CTR],SIGRTMIN+F5_ARRIVAL);break;			
				default:break;
			}
			previous_position=pid_list[LIFT_POSITION];
		}					
	}		
	return 0;
}