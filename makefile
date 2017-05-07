all:
	gcc -c sigs.c
	gcc -o main main.c sigs.o
	gcc -o mng liftMng.c sigs.o
	gcc -o ctr liftCtrl.c sigs.o	
	gcc -o op1 opePanel1.c sigs.o `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
	gcc -o opx opePanelX.c sigs.o `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
clean:
	rm -f *.o main mng ctr op1 opx
