#ifndef _PLUGIN_INTERFACE_H
#define _PLUGIN_INTERFACE_H
#include <string>
#include <vector>
#include <map>
#include <utility>
using namespace std;
//#include "Tcp_socket.h"
//#include "Sock_addr.h"
#include "DataSetSplit.h"
extern "C"{
class Plugin_interface
{
	public:

        Plugin_interface();


		vector<pair<string,string> > map(vector<pair<string,string> >& sourcedata, vector<string> para);

        vector<pair<string,string> > map_ptr(class DataSetSplit*,vector<string> para,int);

        int UserDefine();

        

        int GetIterm(pair<string,string>&);
        int PutIterm(pair<string,string>);

        vector<pair<string,string> > SourceData;
        vector<pair<string,string> > DestData;
        int access_ptr;

};
}
#endif
extern class Plugin_interface g_interface;
