OBJS = client.o clientSocket.o

client: $(OBJS)
	g++ -o client $(OBJS) -lpthread

client.o: clientSocket.h
clientSocket.o: clientSocket.h

clean:
	rm -rf *.o
