OBJ := main.o I_Listenagent.o D_Listenagent.o Socket_I_O_Buff.o Buffermanager.o Epoll.o D_Manager_Agent.o I_Manager_Agent.o D_Agent.o I_Agent.o ReadAgent.o WriteAgent.o 

EU:$(OBJ)
	g++ -pg $(OBJ) -o EU -g

main.o : main.cpp
	g++  -pg -c -g main.cpp

I_Listenagent.o : I_Listenagent.cpp
	g++ -pg -c -g I_Listenagent.cpp

D_Listenagent.o: D_Listenagent.cpp
	g++ -pg -c -g D_Listenagent.cpp

Socket_I_O_Buff.o:Socket_I_O_Buff.cpp
	g++ -pg -c -g Socket_I_O_Buff.cpp
Buffermanager.o : Buffermanager.cpp
	g++ -pg -c -g Buffermanager.cpp

Epoll.o : Epoll.cpp
	g++ -pg -c -g Epoll.cpp

D_Manager_Agent.o : D_Manager_Agent.cpp
	g++ -pg -c -g D_Manager_Agent.cpp

I_Manager_Agent.o : I_Manager_Agent.cpp
	g++ -pg -c -g I_Manager_Agent.cpp

D_Agent.o : D_Agent.cpp
	g++ -pg -c -g D_Agent.cpp

I_Agent.o : I_Agent.cpp
	g++ -pg -c -g I_Agent.cpp


ReadAgent.o : ReadAgent.cpp
	g++ -pg -c -g ReadAgent.cpp

WriteAgent.o : WriteAgent.cpp
	g++ -pg -c -g WriteAgent.cpp

clean :
	rm *.o
