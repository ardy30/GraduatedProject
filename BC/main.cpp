/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/15/12 15:21:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yushiyao (), yushiyaogg@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include "head.h"
#include "DataSet.h"
#include "BusinessController.h"

int main(int argc, char **argv)
{

    string InstanceID = "Kmeans";
    string data_path = "./data";
    string lib1 = "lib1.so";
    vector<string> para1;
    string lib2 = "lib2";
    vector<string> para2;
    vector<string> result;
    
    fstream ReadFile;  
    string point1; 
    string point2; 
    ReadFile.open(data_path.c_str(),ios::in);//以只读的方式读取文件  
    if(ReadFile.fail())//文件打开失败:返回-1
    {   
        return -1;  
    }   
    else//文件存在  
    {   
        getline(ReadFile,point1);
        getline(ReadFile,point2);
        para1.push_back(point1);
        para1.push_back(point2);
           
    }   

    class BusinessController *BC = new BusinessController(InstanceID);
    class DataSet *DataSet1 = BC -> InitialDataSet(data_path);
    DataSet1 -> caching = 1;
    DataSet *DataSet2 = DataSet1->map(lib1,para1);
    DataSet *DataSet3 = DataSet2->shuffle();
    DataSet *DataSet4 = DataSet3 -> map(lib2,para2);
    result = DataSet4 -> reduce();
    result = DataSet4 -> reduce();
    cout << "123"<< endl;

    /*   if(argc != 2)
    {
        cout << "input the IP address"<<endl;
        return -1;
    }
    if((m_epoll.epoll_init()) < 0)
        return -1;
    S_Agent* s_agent = new S_Agent();
    if((s_agent -> connect_server(argv[1])) < 0)
    {
        cerr <<"connect_server error"<<errno<<endl;
        delete s_agent;
        return -1;
    }
    struct mesg_head head;
    head.NewOpcode = MAPOP;
    s_agent->Writebuff.add_buff(&head,sizeof(mesg_head));
    if((m_epoll.epollwait()) < 0)
    {
        delete s_agent;
        return -1;
    }
    delete s_agent;
    return 0;*/
}
