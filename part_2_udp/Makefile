build: compile_client compile_server
compile_client:
	gcc -I headers client/*.c helper_functions/*.c -o client/client.o

compile_server:
	gcc -I headers server/*.c helper_functions/*.c -o server/server.o

clean:
	(cd server; rm *.o)
	(cd client; rm *.o)
	(cd helper_functions; rm *.o)

