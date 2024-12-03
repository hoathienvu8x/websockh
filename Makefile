all: main

main: main.o handshake.o websockh.o
	gcc main.o handshake.o websockh.o -lssl -lcrypto -o main

main.o: main.c
	gcc -c main.c -o main.o

handshake.o: src/handshake.c
	gcc -c src/handshake.c -o handshake.o

websockh.o: src/websockh.c
	gcc -c src/websockh.c -o websockh.o

clean:
	rm -rf *.o main
