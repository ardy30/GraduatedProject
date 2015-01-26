plugin.so :  Plugin_interface.o 
	g++ -g -o lib1.so --shared -fPIC Plugin_interface.o 
Plugin_interface.o : Plugin_interface.cpp
	g++ -g -c -fPIC Plugin_interface.cpp
.PHONY : clean
clean :
	rm *.o lib1.so *~
