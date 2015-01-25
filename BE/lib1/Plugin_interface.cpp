#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <vector>
#include <stdio.h>
//#include "Plugin.h"
#include "DataSetSplit.h"
//#include "Xml_Wrapper.h"
#include <math.h>
#include <sstream>
/*extern int g_startPort;
extern std::string g_dllConfig;
extern std::string g_dllPath;
extern std::string g_dllNotify;
*/

int access_ptr = 0;
vector<pair<string,string> > SourceData;
vector<pair<string,string> > DestData;
vector<string> Para;

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
string IntToString(int number)
{
    stringstream ss; 
    ss << number;
    string temp = ss.str();
    return temp;
}

    struct point
    {
        float x;
        float y;
    };
    int CaculateClosest(struct point* ptr, int size,int x, int y)
    {
        int which_point = 0;
        float closest = sqrt((x - ptr[0].x)*(x-ptr[0].x) + (y - ptr[0].y)*(y -ptr[0].y));

        for(int i = 1; i < size;i ++)
        {
            if((sqrt((x -ptr[i].x)*(x - ptr[i].x) + (y - ptr[i].y)*(y - ptr[i].y)) )  < closest)
                which_point = i;
        }
        return which_point;
    }
int UserDefine()
{

    pair<string,string> source_temp;

    struct point *points = new point[Para.size()];
    int    points_size = Para.size();

    for(int i = 0; i < points_size;i ++)
    {
        string point_temp = Para.at(i);
        string comma = ",";
        int pos = point_temp.find(comma);
        string x = point_temp.substr(0,pos);
        string y = point_temp.substr(pos+1,point_temp.size() - pos -1);
        points[i].x = (float )atoi(x.c_str());
        points[i].y = (float)atoi(y.c_str());
    }
    cout << "abc"<< endl;
    while (GetIterm(source_temp) >= 0)
    {
        string sourcepoint = source_temp.second;
        string comma = ",";
        int pos = sourcepoint.find(comma);
        string x = sourcepoint.substr(0,pos);
        string y = sourcepoint.substr(pos+1,sourcepoint.size() - pos -1);
        int p_x = atoi(x.c_str());
        int p_y = atoi(y.c_str());
        int which_point = CaculateClosest(points,points_size,p_x,p_y);
        PutIterm(pair<string,string>(IntToString(which_point),sourcepoint));

    }
}
vector<pair<string,string> > map(vector<pair<string,string> >& sourcedata, vector<string> para)
{
  //  access_ptr = 0;
    SourceData = sourcedata;
    Para = para;
   UserDefine();
  // cout <<"abc"<< endl;
    vector<pair<string,string> > ret = DestData;
   access_ptr = 0;
  for(; SourceData.size() > 0;) 
      SourceData.pop_back();
  for(;DestData.size()> 0;)
      DestData.pop_back();
  for(;Para.size()> 0;)
      Para.pop_back();
    return ret;    
}

//class Plugin_interface g_interface;
