#include "sigs.h"

pid_t* pid_list;

int main(int argc, char const *argv[])
{
	
	int choose;	
	
	pid_list=update_pid(OPE_PANE1);	
	do{
		printf("<2>|<3>|<4>|<5>|<0>Quit\n");
		scanf("%d",&choose);while(getchar()!='\n');
		
		switch(choose){
			case 2:
				kill(pid_list[LIFT_MNG],SIGRTMIN+F2_CALL);
			break;
			case 3:
				kill(pid_list[LIFT_MNG],SIGRTMIN+F3_CALL);
			break;
			case 4:
				kill(pid_list[LIFT_MNG],SIGRTMIN+F4_CALL);
			break;
			case 5:
				kill(pid_list[LIFT_MNG],SIGRTMIN+F5_CALL);
			break;
			default:
			break;
		}
	}while(choose!=0);
	return 0;
}