OBJ := main.o I_Listenagent.o Socket_I_O_Buff.o Buffermanager.o Epoll.o I_Manager_Agent.o  I_Agent.o ReadAgent.o WriteAgent.o  bc_eu.protocol.pb.o

EU:$(OBJ)
	g++ -pg $(OBJ) -o EU -g -I./protobuff -I/usr/local/protobuf/include -L/usr/local/lib -lprotobuf

main.o : main.cpp
	g++  -pg -c -g main.cpp

I_Listenagent.o : I_Listenagent.cpp
	g++ -pg -c -g I_Listenagent.cpp


Socket_I_O_Buff.o:Socket_I_O_Buff.cpp
	g++ -pg -c -g Socket_I_O_Buff.cpp
Buffermanager.o : Buffermanager.cpp
	g++ -pg -c -g Buffermanager.cpp

Epoll.o : Epoll.cpp
	g++ -pg -c -g Epoll.cpp


I_Manager_Agent.o : I_Manager_Agent.cpp
	g++ -pg -c -g I_Manager_Agent.cpp


I_Agent.o : I_Agent.cpp
	g++ -pg -c -g I_Agent.cpp


ReadAgent.o : ReadAgent.cpp
	g++ -pg -c -g ReadAgent.cpp

WriteAgent.o : WriteAgent.cpp

bc_eu.protocol.pb.o:./protobuff/bc_eu.protocol.pb.cc
	    g++ -c -g ./protobuff/bc_eu.protocol.pb.cc

clean :
	rm *.o
