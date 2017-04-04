all:
	gcc -c sigs.c
	gcc -o o main.c sigs.o
	gcc -o mng liftMng.c sigs.o
	gcc -o ctr liftCtrl.c sigs.o
	gcc -o bod liftBody.c sigs.o
	gcc -o sen liftSensor.c sigs.o
	gcc -o op1 opePanel1.c sigs.o
	gcc -o opx opePanelX.c sigs.o
clean:
	rm -f *.o o mng ctr bod sen op1 opx
