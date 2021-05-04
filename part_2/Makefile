build: compile_client compile_server
compile_client:
	gcc  client/*.c library/*.c  -o client/client.o

compile_server:
	gcc server/*.c library/*.c -o server/server.o

clean:
	(rm *.o)
	(cd client;rm *.o)
	(cd server;rm *.o)

