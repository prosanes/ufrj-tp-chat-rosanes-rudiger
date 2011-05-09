OBJS = server_main.o grupoClientes.o serverSocket.o

server: $(OBJS)
	g++ -o server $(OBJS) -lpthread

server_main.o: serverSocket.h grupoClientes.h
grupoClientes.o: grupoClientes.h serverSocket.h
serverSocket.o: serverSocket.h

clean:
	rm -rf *.o
