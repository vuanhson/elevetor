#include "sigs.h"
int main(int argc, char const *argv[])
{
	/* code */
	int status=0;
	pid_t liftMngId,liftBodyId,liftCtrlId,liftSensorId,opePane1Id,opePaneXId,pid;
	//pid=fork();
	
	int shmid = shmget(SHARE_KEY,10*sizeof(pid_t),IPC_CREAT);
	//printf("%d\n",shmid );
	pid_t* shmpointer = (pid_t*)shmat(shmid,0,0);
	//printf("%d ",*shmpointer);
	//puts("ngon");
	while(1){
		sleep(10);
		for(int i=0;i<6;i++){
			printf("%d ",shmpointer[i]);
		}
		printf("\n");
	}
	shmdt(&shmpointer);	
	return 0;
}