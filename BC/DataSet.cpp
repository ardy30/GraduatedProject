/*
 * =====================================================================================
 *
 *       Filename:  DataSet.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/12/14 06:42:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include "DataSet.h"

DataSet::DataSet()
{
    IsInitial = UNINIT;
}

DataSet* DataSet::map(string lib, vector<string> arg)
{
    class DataSet *temp = new DataSet();
    temp -> name = BC -> InstanceID +  tool.IntToString(BC->DataNumber) ;
    BC-> DataNumber++;
    temp -> op = "map";
    temp-> BC = this-> BC;
    this -> next = temp;
    temp -> prev = this;
    return temp;
}

DataSet* DataSet::shuffle()
{
    class DataSet *temp = new DataSet();
    temp -> name = BC -> InstanceID + tool.IntToString(BC-> DataNumber);
    BC -> DataNumber++;
    temp ->op ="shuffle";
    temp -> BC = this -> BC;
    this -> next = temp;
    temp -> prev = this;
    return temp;
}

vector<string> DataSet::reduce()
{
   if(this ->IsInitial == UNINIT ) 
   {
         prev-> BuildData(-1);
   }
   vector<string> temp;
    return temp; 
}

int DataSet::BuildData(int SplitNumber)
{
    if(path.empty())
    {
        if( IsInitial == UNINIT)
        {
            prev->BuildData(-1);
        }
        else
        {
            /* 发送请求 */
            return 0; 
        }
    }
    else
    {
        if(this -> IsInitial == UNINIT)
        {
            int Lines;
            int MachineNumber;
            if((Lines = CaculateSize()) < 0)
            {
                cout << "empty file"<<endl;
                exit(0);
            }
            if((Line % FILE_LINE) == 0)
            {
                MachineNumber = Line / 500;
            }
            else
                MachineNumber = Line / 500 + 1;
            MasterAgent = new S_Agent();
            BC -> ApplyResource();
            //S_Agent* s_agent = new S_Agent(this);
            if((MasterAgent -> connect_server(MASTERIP)) < 0)
            {
                 cerr <<"connect_server error"<<errno<<endl;
                 delete s_agent;
                 return -1;
            }
            
            //struct mesg_head head;
            //head.NewOpcode = MAPOP;
            //s_agent->Writebuff.add_buff(&head,sizeof(mesg_head));
                      
        }
    }
}

int DataSet::
int DataSet::CaculateSize()
{
   fstream ReadFile;  
   int n=0;  
   string tmp;  
    ReadFile.open(path.c_str(),ios::in);//以只读的方式读取文件  
    if(ReadFile.fail())//文件打开失败:返回-1
    {  
        return -1;  
    }  
    else//文件存在  
    {  
        while(getline(ReadFile,tmp))  
        {  
            n++;  
        } 
    } 
   return n;   
}
