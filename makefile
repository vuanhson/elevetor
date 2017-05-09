all:
	rm -f *.o main mng ctr op1 opx gui
	gcc -c sigs.c
	gcc -o main main.c sigs.o
	gcc -o mng liftMng.c sigs.o `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
	gcc -o ctr liftCtrl.c sigs.o	
	gcc -o op1 opePanel1.c sigs.o `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
	gcc -o opx opePanelX.c sigs.o `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
main: main.c
	rm -f main
	gcc -o main main.c sigs.o
mng: liftMng.c
	rm -f mng
	gcc -o mng liftMng.c sigs.o `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
ctr: liftCtrl.c
	rm -f ctr
	gcc -o ctr liftCtrl.c sigs.o
op1: opePanel1.c
	rm -f op1
	gcc -o op1 opePanel1.c sigs.o `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
opx: opePanelX.c
	rm -f opx
	gcc -o opx opePanelX.c sigs.o `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
gui: gui.c
	rm -f gui
	gcc -o gui gui.c sigs.o `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
shutdown: shutdown.c
	gcc -o shutdown shutdown.c sigs.o
clean:
	rm -f *.o main mng ctr op1 opx gui
