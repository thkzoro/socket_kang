################ Makefle #################
all : server client

server : server.o
	gcc -o server server.o
server.o : server.c
	gcc -c -o server.o server.c

client : client.o
client.o : client.c
	gcc -c -o client.o client.c

clean:
	-@rm -f *.o server client