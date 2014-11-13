OBJ :=main.o Buffermanager.o Epoll.o S_Agent.o ReadAgent.o WriteAgent.o BusinessController.o DataSet.o Tool.o bc_master.protocol.pb.o 

storage:$(OBJ)
	g++ $(OBJ) -o BC -g -I./protobuff -I/usr/local/protobuf/include -L/usr/local/lib -lprotobuf

main.o : main.cpp
	g++ -c -g main.cpp
Buffermanager.o:Buffermanager.cpp
	g++ -c -g Buffermanager.cpp
Epoll.o:Epoll.cpp
	g++ -c -g Epoll.cpp
WriteAgent.o:WriteAgent.cpp
	g++ -c -g WriteAgent.cpp 
#S_Manager_Agent.o:S_Manager_Agent.cpp
#	g++ -c -g S_Manager_Agent.cpp
S_Agent.o:S_Agent.cpp
	g++ -c -g S_Agent.cpp
ReadAgent.o:ReadAgent.cpp
	g++ -c -g ReadAgent.cpp
BusinessController.o:BusinessController.cpp
	g++ -c -g BusinessController.cpp
bc_master.protocol.pb.o:./protobuff/bc_master.protocol.pb.cc
	g++ -c -g ./protobuff/bc_master.protocol.pb.cc
DataSet.o:DataSet.cpp
	g++ -c -g DataSet.cpp
Tool.o:Tool.cpp
	g++ -c -g Tool.cpp
#DataSetSplit.o:DataSetSplit.cpp
#	g++ -c -g DataSetSplit.cpp
clean:
	rm *.o

