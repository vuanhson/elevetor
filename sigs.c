#include "sigs.h"
int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}
pid_t* update_pid(int i){
	int shmid = shmget(SHARE_KEY,10*sizeof(pid_t),IPC_CREAT);
	pid_t *shmpointer = (pid_t*)shmat(shmid,0,0);
	if(shmpointer==(int*)-1){perror("shmat");exit(0);}
	shmpointer[i]=getpid();
	return shmpointer;
}