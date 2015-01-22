plugin.so : Plugin.cpp Plugin_interface.o Sock_addr.o Tcp_socket.o Xml_Wrapper.o handle_error.o
	g++ -g -o plugin.so --shared -fPIC Plugin.cpp Plugin_interface.o Sock_addr.o Tcp_socket.o Xml_Wrapper.o handle_error.o
Plugin_interface.o : Plugin_interface.cpp
	g++ -g -c -fPIC Plugin_interface.cpp
Sock_addr.o : Sock_addr.cpp
	g++ -g -c -fPIC Sock_addr.cpp
Tcp_socket.o : Tcp_socket.cpp
	g++ -g -c -fPIC Tcp_socket.cpp
Xml_Wrapper.o : Xml_Wrapper.cpp
	g++ -g -c -fPIC Xml_Wrapper.cpp
handle_error.o : handle_error.cpp
	g++ -g -c -fPIC handle_error.cpp

.PHONY : clean
clean :
	rm *.o plugin.so *~
