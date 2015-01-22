#ifndef _PLUGIN_INTERFACE_H
#define _PLUGIN_INTERFACE_H
#include <string>
#include <vector>
#include <map>
#include <utility>
using namespace std;
//#include "Tcp_socket.h"
//#include "Sock_addr.h"
extern "C"
class Plugin_interface
{
	public:

        Plugin_interface();


		vector<pair<string,string> > map(vector<pair<string,string> >sourcedata, vector<string> para);

        int UserDefine();

        

        int GetIterm(pair<string,string>&);
        int PutIterm(pair<string,string>);

        vector<pair<string,string> > SourceData;
        vector<pair<string,string> > DestData;
        int access_ptr;

};

#endif

