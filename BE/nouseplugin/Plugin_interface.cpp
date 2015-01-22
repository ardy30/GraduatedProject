#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <vector>
//#include "Plugin.h"
#include "Plugin_interface.h"
#include "DataSetSplit.h"
//#include "Xml_Wrapper.h"

/*extern int g_startPort;
extern std::string g_dllConfig;
extern std::string g_dllPath;
extern std::string g_dllNotify;
*/

class Plugin_interface g_interface;
Plugin_interface::Plugin_interface()
{
    access_ptr = 0;
}

vector<pair<string,string> > Plugin_interface::map(vector<pair<string,string> >& sourcedata, vector<string> para)
{
    access_ptr = 0;
    SourceData = sourcedata;
    UserDefine();
    return DestData;    
}

vector<pair<string,string> > Plugin_interface::map_ptr(class DataSetSplit* sourcedataptr, vector<string> para,int a)
{
    //class DataSetSplit* temp;
    cout << "abc"<<endl;
    vector<pair<string,string> > ret;
    return ret;
}

int Plugin_interface::UserDefine()
{
    pair<string,string> temp;
    if(GetIterm(temp) < 0)
    {
        return 0;
    }
    else
       PutIterm(temp);
}

int Plugin_interface::GetIterm(pair<string,string>& Iterm)
{
    if(access_ptr < SourceData.size())
    {
        Iterm = SourceData.at(access_ptr);
        access_ptr ++;
        return 0;
    }
    else
        return -1;
}

int Plugin_interface::PutIterm(pair<string,string> Iterm)
{
    DestData.push_back(Iterm);
    return 0;
}


