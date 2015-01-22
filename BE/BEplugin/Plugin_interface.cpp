#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <vector>
//#include "Plugin.h"
#include "DataSetSplit.h"
//#include "Xml_Wrapper.h"

/*extern int g_startPort;
extern std::string g_dllConfig;
extern std::string g_dllPath;
extern std::string g_dllNotify;
*/

int access_ptr = 0;
vector<pair<string,string> > SourceData;
vector<pair<string,string> > DestData;

vector<pair<string,string> > map_ptr(class DataSetSplit* sourcedataptr, vector<string> para,int a)
{
    //class DataSetSplit* temp;
    cout << "abc"<<endl;
    vector<pair<string,string> > ret;
    return ret;
}


int GetIterm(pair<string,string>& Iterm)
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

int PutIterm(pair<string,string> Iterm)
{
    DestData.push_back(Iterm);
    return 0;
}

int UserDefine()
{
    pair<string,string> temp;
    if(GetIterm(temp) < 0)
    {
        return 0;
    }
    else
       PutIterm(temp);
}
vector<pair<string,string> > map(vector<pair<string,string> >& sourcedata, vector<string> para)
{
  //  access_ptr = 0;
    SourceData = sourcedata;
   UserDefine();
  // cout <<"abc"<< endl;
    vector<pair<string,string> > ret = DestData;
   access_ptr = 0;
  for(; SourceData.size() > 0;) 
      SourceData.pop_back();
  for(;DestData.size()> 0;)
      DestData.pop_back();
    return ret;    
}

//class Plugin_interface g_interface;
