#include "sigs.h"

pid_t* pid_list;

int main(int argc, char const *argv[])
{
	
	int choose;	
	
	if(argc!=2){
		printf("Usage: opx FLOOR_NUMBER\n"); exit(0);
	}
	pid_list=update_pid(OPE_PANEX);	
	int this_floor;
	switch(atoi(argv[1])){
		case 2: this_floor=F2_CALL;break;
		case 3: this_floor=F3_CALL;break;
		case 4: this_floor=F4_CALL;break;
		case 5: this_floor=F5_CALL;break;
		default:break;
	}
	do{
		printf("<1 CALL LIFT>|<0>Quit\n");
		scanf("%d",&choose);while(getchar()!='\n');		
		switch(choose){
			case 1:				
				kill(pid_list[LIFT_MNG],this_floor);
			break;			
			default:
			break;
		}
	}while(choose!=0);
	return 0;
}