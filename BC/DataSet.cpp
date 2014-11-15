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
         BuildData(-1);
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
        
        
            /* 若无指定分片
             * 发送请求  
             * 如果成功 修改下一片的IsInitial的值和数据分片情况
             * 如果失败
             * map
             * 1.全部都是不存在，或者其中有连接失败 pre-> BuildData(-1)
             * 2.部分成功，一个连接失败，pre->BuildData(splitnumber)*/
               
            return 0; 
        
    }
    else
    {
        if(this -> IsInitial == UNINIT)
        {
            int MachineNumber;
            if((Lines = CaculateSize()) < 0)
            {
                cout << "empty file"<<endl;
                exit(0);
            }
            if((Lines % FILE_LINE) == 0)
            {
                MachineNumber = Lines / 500;
            }
            else
                MachineNumber = Lines / 500 + 1;
            BC -> ApplyResource(MachineNumber);
            for(int i = 0; i < BC->Container.size();i++)
            {
                class DataSetSplit temp;
                temp.IP = BC -> Container.at(i);
                temp.SequenceNumber = i;
                Data.push_back(temp);
            }
            IsInitial = INIT;
            //修改该分片数据，修改INIT
                      
        }
            BuildInitialDataMsg(SplitNumber);
            return 0;
            //若无指定的分片，给所有分片发送初始化请求，如果失败，换机器重新发送，如果成功，修改next的IsInitial的值和分片数据
            //若有指定分片，重新初始化指定的分片，同上
    }
}

int DataSet::BuildInitialDataMsg(int SplitNumber)
{
    if(SplitNumber == -1)
    {
        int size = Data.size();
        for(int i = 0; i< size; i ++)
        {
            S_Agent *TempAgent = new S_Agent(&(BC->m_epoll));
            BC->BCAgentList.push_back(TempAgent);
            if((TempAgent -> connect_server((char*)(Data.at(i).IP).c_str(),EU_PORT)) < 0)
            {   
                cout << "connect EU error";
                TempAgent -> error =1;
                continue;
            }   
            struct mesg_head SendInitmsghead;
            SendInitmsghead.cmd = MSG_BC_EU_INIT_DATA;//初始化头部

            bc_eu::pb_MSG_BC_EU_INIT_DATA mesg_body;
            mesg_body.set_instanceid(BC-> InstanceID);
            mesg_body.set_path(path);
            mesg_body.set_splitname(name);
            mesg_body.set_splitnumber(i);
            mesg_body.set_starline(i*FILE_LINE+1);
            if(i == size - 1)
                mesg_body.set_endline(Lines);
            else
                mesg_body.set_endline(i*FILE_LINE + FILE_LINE);
            string temp;
            mesg_body.SerializeToString(&temp);//使用protobuff序列化负载

            SendInitmsghead.length = temp.length();//初始化头部长度字段

            TempAgent->Writebuff.add_buff(&SendInitmsghead,sizeof(SendInitmsghead));
            char* body = new char[temp.size()];
            memcpy(body,temp.c_str(),temp.length());//将负载信息转换为char*类型

            TempAgent -> Writebuff.add_buff(body,temp.length());
            delete body;
            TempAgent -> m_epoll -> epoll_modify(EPOLLOUT,TempAgent);        
        }
        while(CheckFinish() < 0)
        {
            if((BC->m_epoll.epollwait()) < 0)
            {
                //  delete s_agent;
                cout << "epollwaiterror"<< endl;
                return -1;
                        
            }
        }
        int ret = 0;
        if((ret = CheckInitFaild()) < 0)
        {
            for(int i = BC -> BCAgentList.size(); i > 0;i --)
            {
                delete BC -> BCAgentList.at(i - 1);
                BC -> BCAgentList.at(i -1) = NULL;
                BC-> BCAgentList.pop_back();
            }
            return 0;
        }
        else 
        {
            for(int i = BC -> BCAgentList.size(); i > 0;i --)
            {
                delete BC -> BCAgentList.at(i - 1);
                BC -> BCAgentList.at(i -1) = NULL;
                BC-> BCAgentList.pop_back();
                BuildData(ret);
            }
            return 0;
        }

    }
    else
    {
        string OldIP = Data.at(SplitNumber).IP;
        string NewIP;
        for(int i = 0 ; i < BC -> Container.size(); i ++)
        {
            NewIP = BC -> Container.at(i);
            if(NewIP == OldIP)
                continue;
            else
                break;
        }
        Data.at(SplitNumber).IP = NewIP;
        S_Agent *TempAgent = new S_Agent(&(BC -> m_epoll)) ;
        BC -> BCAgentList.push_back(TempAgent);
        if(TempAgent -> connect_server((char*)(Data.at(SplitNumber).IP).c_str(), EU_PORT) < 0)
        {
            cout << "reconnect EU error"<<endl;
            cout << "fatal error"<< endl;
            exit(0);
        }
        struct mesg_head SendInitmsghead;
        SendInitmsghead.cmd = MSG_BC_EU_INIT_DATA;

        bc_eu::pb_MSG_BC_EU_INIT_DATA mesg_body;
        mesg_body.set_instanceid(BC -> InstanceID);
        mesg_body.set_path(path);
        mesg_body.set_splitname(name);
        mesg_body.set_splitnumber(SplitNumber);
        mesg_body.set_starline(SplitNumber*FILE_LINE + 1);
        if(SplitNumber == Data.size() -1)
            mesg_body.set_endline(Lines);
        else
            mesg_body.set_endline(SplitNumber* FILE_LINE + FILE_LINE);
        string temp;
        mesg_body.SerializeToString(&temp);

        SendInitmsghead.length = temp.length();
        TempAgent ->Writebuff.add_buff(&SendInitmsghead,sizeof(SendInitmsghead));
        char* body = new char[temp.size()];
        memcpy(body,temp.c_str(),temp.length());

        TempAgent -> Writebuff.add_buff(body,temp.length());
        while(TempAgent -> finish ==0 && TempAgent -> error == 0)
        {
            if((BC -> m_epoll.epollwait()) < 0)
            {
                cout << "reconnect epollwaiteeror"<< endl;
                exit(0);
            }
        }
        if(TempAgent -> error == 1)
        {
            cout << "reconnect error"<< endl;
            exit(0);
        }
        else if(TempAgent -> finish == 1)
        {
            delete TempAgent;
            BC -> BCAgentList.pop_back();
            (next -> Data).at(SplitNumber).IP = (this -> Data).at(SplitNumber).IP;
            return 0;
        }
    }
}

int DataSet::CheckInitFaild()
{
    for(int i = 0; i < BC -> BCAgentList.size();i ++)
    {
        if(BC -> BCAgentList.at(i)-> error = 1)
            return i;
    }
    return -1;
}

int DataSet::CheckFinish()
{
    for(int i = 0; i < BC ->BCAgentList.size(); i++)
    {
        if(BC->BCAgentList.at(i)->error == 0 && BC-> BCAgentList.at(i)->finish == 0)
            return -1;
    }
    return 0;
}


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
