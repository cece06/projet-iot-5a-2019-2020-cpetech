ReceiverEX: main.o rwops.o mainops.o
	gcc -o ReceiverEX main.o rwops.o mainops.o -lwiringPi -l bcm2835
rwops.o: rwops.c
	gcc -o rwops.o -c rwops.c -lwiringPi

mainops.o: mainops.c rwops.h register.h
	gcc -o mainops.o -c mainops.c -lwiringPi

main.o: main.c rwops.h mainops.h register.h
	gcc -o main.o -c main.c -lwiringPi -l bcm2835