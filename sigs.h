#ifndef _SIGS_H_
#define _SIGS_H_
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>

enum {LIFT_MNG,LIFT_CTR,LIFT_BODY,LIFT_SENSOR,OPE_PANE1,OPE_PANEX,LIFT_POSITION};
#define CLOCK 500000
#define TRUE 1
#define FALSE 0
#define SUCCESS 1
#define FAILED 0
#define UP 1
#define DOWN -1
#define SHARE_KEY 6789
#define F1_CALL 11
#define F2_CALL 12
#define F3_CALL 13
#define F4_CALL 14
#define F5_CALL 15
#define MOVING 9
#define FINISHED 10
#define ARRIVAL 58
#define LIFT_UP 6
#define LIFT_DOWN 7
#define LIFT_STOP 8
#define SENSOR_TOP_ON 54
#define SENSOR5_ON 53
#define SENSOR4_ON 52
#define SENSOR3_ON 51
#define SENSOR2_ON 50
#define SENSOR1_ON 49
#define SENSOR_BOT_ON 48
#define SENSOR5_OFF 47
#define SENSOR4_OFF 46
#define SENSOR3_OFF 45
#define SENSOR2_OFF 44
#define SENSOR1_OFF 43

#define F1_ARRIVAL 1
#define F2_ARRIVAL 2
#define F3_ARRIVAL 3
#define F4_ARRIVAL 4
#define F5_ARRIVAL 5

int kbhit(void);
pid_t* update_pid(int i);
#endif