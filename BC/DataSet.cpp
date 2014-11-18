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
    caching = 0;
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
    temp -> next = NULL;
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
            if(this -> op == "map")
                BuildMapData(-1);
            else if(this -> op == "shuffle")
                BuildShuffleData(-1);
        }
        else
        {
            if(this -> op == "map")
                BuildMapData(SplitNumber);
            else if(this -> op == "shuffle")
                BuildShuffleData(SplitNumber);
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

int DataSet::BuildMapData(int SplitNumber)
{
    S_Agent * TempAgent = NULL;
    struct mesg_head SendInitmsghead;
    bc_eu::pb_MSG_BC_EU_MAP mesg_body;
    string temp;
    char* body = NULL;
    int ret = 0;
    if(SplitNumber == -1)
    {
        int size = Data.size();
        for(int i = 0; i < size; i++)
        {
            TempAgent = new S_Agent(&(BC -> m_epoll));
            BC -> BCAgentList.push_back(TempAgent);
            if((TempAgent -> connect_server((char*)(Data.at(i).IP).c_str(),EU_PORT))<0)
            {
                cout << "connect EU error";
                TempAgent -> error = 1;
                continue;
            }
            mesg_head SendMapmsghead;
            SendMapmsghead.cmd = MSG_BC_EU_MAP;

            bc_eu::pb_MSG_BC_EU_MAP mesg_body;
            mesg_body.set_cmd(lib);
            for(int i = 0; i < arg.size();i ++)
                mesg_body.add_para(arg.at(i));
            mesg_body.set_instanceid(BC -> InstanceID);
            mesg_body.set_sourcesplitname(prev -> name);
            mesg_body.set_sourcesplitnumber(i);
            mesg_body.set_destsplitname(name);
            mesg_body.set_destsplitnumber(i);

            mesg_body.SerializeToString(&temp);
            SendMapmsghead.length = temp.length();
            TempAgent->Writebuff.add_buff(&SendMapmsghead,sizeof(SendMapmsghead));
            body = new char[temp.size()];
            memcpy(body,temp.c_str(),temp.length());
            
            TempAgent -> Writebuff.add_buff(body,temp.length());
            delete body;
            body = NULL;
            TempAgent -> m_epoll -> epoll_modify(EPOLLOUT,TempAgent);
        }
        while(CheckFinish()< 0)
        {
            if((BC -> m_epoll.epollwait()) < 0)
            {
                cout << "epollwaiterror"<< endl;
                return -1;
            }
        }
        ret = CheckMapFaild();
        
        for(int j = BC -> BCAgentList.size();j > 0; j --)
        {
            delete BC -> BCAgentList.at(j - 1);
            BC -> BCAgentList.at(j-1) = NULL;
            BC -> BCAgentList.pop_back();
        }
        if(ret == -2)
        {
        }
        else if(ret == -1)
        {
            prev->BuildData(-1);
            BuildMapData(-1);
            return 0;
        }
        else
        {
            BuildMapData(ret);
        }
        if(next != NULL)
            {
                if(next -> IsInitial == UNINIT)
                {
                    for(int i = 0;i < Data.size();i ++) 
                    {
                        class DataSetSplit temp;
                        temp.IP = Data.at(i).IP;
                        temp.SequenceNumber = i;
                        next -> Data.push_back(temp) ;   
                    }
                    next -> IsInitial = INIT;
                }
            }
        
            if(prev -> caching == 0)
            {
                int size = Data.size();
                for(int i = 0;i < size; i ++)
                {
                    TempAgent = new S_Agent(&(BC -> m_epoll));
                    BC -> BCAgentList.push_back(TempAgent);
                    if((TempAgent -> connect_server((char*)(Data.at(i).IP).c_str(),EU_PORT)) < 0)
                    {
                        cout << "connect EU error";
                        TempAgent -> error =1;
                        continue;
                    }
                    mesg_head SendDeletemsghead;
                    SendDeletemsghead.cmd = MSG_BC_EU_DELETE_DATA;
                    bc_eu::pb_MSG_BC_EU_DELETE_DATA mesg_body;
                    mesg_body.set_instanceid(BC -> InstanceID);
                    mesg_body.set_sourcesplitname(prev-> name);
                    mesg_body.set_sourcesplitnumber(i);

                    mesg_body.SerializeToString(&temp);
                    SendDeletemsghead.length = temp.length();
                    TempAgent -> Writebuff.add_buff(&SendDeletemsghead,sizeof(SendDeletemsghead));
                    body = new char[temp.size()];
                    memcpy(body,temp.c_str(),temp.length());
                    TempAgent -> Writebuff.add_buff(body,temp.length());
                    delete body;
                    body=NULL;
                    TempAgent-> m_epoll ->epoll_modify(EPOLLOUT,TempAgent);

                }
                while((CheckFinish()) < 0)
                {
                    if((BC -> m_epoll.epollwait()) < 0)
                    {
                        cout << "epollwaiterror"<< endl;
                        return -1;
                    }
                }
                for(int i = BC -> BCAgentList.size();i > 0; i--)
                {
                    delete BC -> BCAgentList.at(i -1);
                    BC -> BCAgentList.at(i-1) = NULL;
                    BC -> BCAgentList.pop_back();
                }
            }
        return 0;
    }
    if(SplitNumber != -1)
    {
        prev -> BuildData(ret);
        TempAgent = new S_Agent(&(BC -> m_epoll));
        BC -> BCAgentList.push_back(TempAgent);
        if(TempAgent -> connect_server((char*)(Data.at(SplitNumber).IP).c_str(),EU_PORT) < 0)
        {
            cout << "reconnect EU error" << endl;
            cout << "fatal error"<< endl;
            exit(0);
        }
        mesg_head SendMapmsghead;
        SendMapmsghead.cmd = MSG_BC_EU_MAP;
       
        bc_eu::pb_MSG_BC_EU_MAP mesg_body;
        mesg_body.set_cmd(lib);
        for(int i = 0; i < arg.size(); i++)
            mesg_body.add_para(arg.at(i));
        mesg_body.set_instanceid(BC -> InstanceID);
        mesg_body.set_sourcesplitname(prev -> name);
        mesg_body.set_sourcesplitnumber(SplitNumber);
        mesg_body.set_destsplitname(name);
        mesg_body.set_destsplitnumber(SplitNumber);

        mesg_body.SerializeToString(&temp);
        SendMapmsghead.length = temp.length();
        TempAgent -> Writebuff.add_buff(&SendMapmsghead,sizeof(SendMapmsghead));
        body = new char[temp.size()];
        memcpy(body,temp.c_str(),temp.length());

        TempAgent -> Writebuff.add_buff(body,temp.length());
        delete body;
        body = NULL;
        TempAgent -> m_epoll -> epoll_modify(EPOLLOUT,TempAgent);
        while(TempAgent -> finish == 0 && TempAgent -> error == 0)
        {
            if((BC -> m_epoll.epollwait())< 0)
            {
                cout << "map reconnect epollwaiterror"<< endl;
                exit(0);
            }
        }
        if(TempAgent -> error == 1)
        {
            cout << "reconnect error map"<< endl;
            exit(0);
        }
        else if(TempAgent -> finish == 1)
        {
            delete TempAgent;
            BC -> BCAgentList.pop_back();
            if(next -> IsInitial == INIT)
                (next -> Data).at(SplitNumber).IP = (this -> Data).at(SplitNumber).IP;
            /*  if(prev -> caching == 0)
            {
                TempAgent = new S_Agent(&(BC -> m_epoll));
                BC -> BCAgentList.push_back(TempAgent);
                if(TempAgent -> connect_server((char*)(Data.at(SplitNumber).IP).c_str(),EU_PORT) < 0)
                {
                    cout << "rebuild delete data error should not happen"<< endl;
                    exit(0);
                }
                mesg_head SendDeletemsghead;
                SendDeletemsghead.cmd = MSG_BC_EU_DELETE_DATA;
                bc_eu::pb_MSG_BC_EU_DELETE_DATA mesg_body;
                mesg_body.set_instanceid(BC -> InstanceID);
                mesg_body.set_sourcesplitname(prev -> name);
                mesg_body.set_sourcesplitnumber(SplitNumber);
            
                mesg_body.SerializeToString(&temp);
                SendDeletemsghead.length = temp.length();
                TempAgent -> Writebuff.add_buff(&SendDeletemsghead,sizeof(SendDeletemsghead));
                body = new char[temp.size()];
                memcpy(body,temp.c_str(),temp.length());
                TempAgent -> Writebuff.add_buff(body,temp.length());
                delete body;
                body = NULL;
                TempAgent -> m_epoll -> epoll_modify(EPOLLOUT,TempAgent);
                
                while((CheckFinish()) < 0)
                {
                    if((BC -> m_epoll.epollwait()) < 0)
                    {
                        cout << "epollwaiterror in map rebuild"<< endl;
                        exit(1);
                    }
                }
                for(int i = BC -> BCAgentList.size(); i > 0;i--)
                {
                    delete BC -> BCAgentList.at(i -1);
                    BC -> BCAgentList.at(i -1) = NULL;
                    BC -> BCAgentList.pop_back();
                }
            }*/
               return 0;
        }
    }
}
int DataSet::BuildShuffleData(int SplitNumber)
{
    S_Agent *TempAgent = NULL;
    struct mesg_head SendShufflemsghead;
    bc_eu::pb_MSG_BC_EU_SHUFFLE mesg_body;
    string temp;
    char* body = NULL;
    int ret = 0;
    if(SplitNumber == -1)
    {
        int size = Data.size();
        for(int i = 0;i < size; i ++)
        {
            TempAgent = new S_Agent(&(BC -> m_epoll));
            BC -> BCAgentList.push_back(TempAgent);
            if((TempAgent ->connect_server((char*)(Data.at(i).IP).c_str(),EU_PORT)) < 0)
            {
                cout << "shuffle connect EU error";
                TempAgent -> error =1;
                continue;
            }
            mesg_head SendShufflemsghead;
            SendShufflemsghead.cmd = MSG_BC_EU_SHUFFLE;

            bc_eu::pb_MSG_BC_EU_SHUFFLE mesg_body;
            mesg_body.set_instanceid(BC -> InstanceID);
            mesg_body.set_sourcesplitname(prev -> name);
            mesg_body.set_sourcesplitnumber(i);
            mesg_body.set_destsplitname(name);
            mesg_body.set_destsplitnumber(i);
            mesg_body.set_mo(size);
            for(int i = 0; i < size; i ++)
            {
                bc_eu::pb_MSG_BC_EU_SHUFFLE_IP_info *info;
                //info.set_key(i);
                //info.set_ip(Data.at(i).IP);
                info = mesg_body.add_ipinfolist();
                info -> set_key(i);
                info -> set_ip(Data.at(i).IP);
            }

            mesg_body.SerializeToString(&temp);
            SendShufflemsghead.length = temp.length();
            TempAgent -> Writebuff.add_buff(&SendShufflemsghead,sizeof(SendShufflemsghead));
            body = new char[temp.size()];
            memcpy(body,temp.c_str(),temp.length());

            TempAgent -> Writebuff.add_buff(body,temp.length());
            delete body;
            body = NULL;
            TempAgent -> m_epoll -> epoll_modify(EPOLLOUT,TempAgent);
        }
        while(CheckFinish() < 0)
        {
            if((BC -> m_epoll.epollwait()) < 0)
            {
                cout << "shuffle epollwaiterror" << endl;
                return -1;
            }
        }
        ret = CheckShuffleFaild();
        
        for(int j = BC -> BCAgentList.size(); j > 0; j --)
        {
            delete BC -> BCAgentList.at(j -1);
            BC -> BCAgentList.at(j -1) = NULL;
            BC -> BCAgentList.pop_back();
        }
        if(ret == -2)
        {}
        else if(ret == -1)
        {
            prev -> BuildData(-1);
            BuildShuffleData(-1);
            return 0;
        }
        else
        {
            BuildShuffleData(ret);
        }
        if(next != NULL)
        {
            if(next -> IsInitial == UNINIT)
            {
                for(int i = 0;i< Data.size();i ++)
                {
                    class DataSetSplit temp;
                    temp.IP = Data.at(i).IP;
                    temp.SequenceNumber = i;
                    next -> Data.push_back(temp);
                }
                next -> IsInitial =INIT;
            }
        }
        if(prev -> caching == 0)
        {
            int size = Data.size();
            for(int i = 0; i < size; i++)
            {
                TempAgent = new S_Agent(&(BC -> m_epoll));
                BC -> BCAgentList.push_back(TempAgent);
                if((TempAgent -> connect_server((char*)(Data.at(i).IP).c_str(),EU_PORT)) < 0)
                {
                    cout << "connect EU error";
                    TempAgent -> error =1;
                    continue;
                }
                mesg_head SendDeletemsghead;
                SendDeletemsghead.cmd = MSG_BC_EU_DELETE_DATA;
                bc_eu::pb_MSG_BC_EU_DELETE_DATA mesg_body;
                mesg_body.set_instanceid(BC -> InstanceID);
                mesg_body.set_sourcesplitname(prev->name);
                mesg_body.set_sourcesplitnumber(i);

                mesg_body.SerializeToString(&temp);
                SendDeletemsghead.length = temp.length();
                TempAgent -> Writebuff.add_buff(&SendDeletemsghead,sizeof(SendDeletemsghead));
                body = new char[temp.size()];
                memcpy(body,temp.c_str(),temp.length());
                TempAgent -> Writebuff.add_buff(body,temp.length());
                delete body;
                body = NULL;
                TempAgent -> m_epoll -> epoll_modify(EPOLLOUT,TempAgent);
            }
            while((CheckFinish()) < 0)
            {
                if((BC -> m_epoll.epollwait()) < 0)
                {
                    cout << "epollwaiteroor"<< endl;
                    return -1;
                }
            }
            for(int i = BC -> BCAgentList.size();i > 0;i --)
            {
                delete BC -> BCAgentList.at(i-1);
                BC -> BCAgentList.at(i -1) = NULL;
                BC -> BCAgentList.pop_back();
            }
            
        }
    return 0;
    }
    if(SplitNumber != -1)
    {
    
    }
}
int DataSet::BuildInitialDataMsg(int SplitNumber)
{
    S_Agent *TempAgent = NULL;
    struct mesg_head SendInitmsghead;
    bc_eu::pb_MSG_BC_EU_INIT_DATA mesg_body;
    string temp;
    char* body = NULL;
    int ret = 0;
    if(SplitNumber == -1)
    {
        int size = Data.size();
        for(int i = 0; i< size; i ++)
        {
            TempAgent = new S_Agent(&(BC->m_epoll));
            BC->BCAgentList.push_back(TempAgent);
            if((TempAgent -> connect_server((char*)(Data.at(i).IP).c_str(),EU_PORT)) < 0)
            {   
                cout << "connect EU error";
                TempAgent -> error =1;
                continue;
            }   
            mesg_head SendInitmsghead;
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
            
            mesg_body.SerializeToString(&temp);//使用protobuff序列化负载

            SendInitmsghead.length = temp.length();//初始化头部长度字段

            TempAgent->Writebuff.add_buff(&SendInitmsghead,sizeof(SendInitmsghead));
            body = new char[temp.size()];
            memcpy(body,temp.c_str(),temp.length());//将负载信息转换为char*类型

            TempAgent -> Writebuff.add_buff(body,temp.length());
            delete body;
            body = NULL;
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
        
        if((ret = CheckInitFaild()) < 0)
        {
            for(int i = BC -> BCAgentList.size(); i > 0;i --)
            {
                delete BC -> BCAgentList.at(i - 1);
                BC -> BCAgentList.at(i -1) = NULL;
                BC-> BCAgentList.pop_back();
            }
            
        }
        else 
        {
            for(int i = BC -> BCAgentList.size(); i > 0;i --)
            {
                delete BC -> BCAgentList.at(i - 1);
                BC -> BCAgentList.at(i -1) = NULL;
                BC-> BCAgentList.pop_back();
            }
                BuildData(ret);
        }
        if(next -> IsInitial == UNINIT)
        {
            for(int i = 0; i < Data.size();i ++)
            {
                class DataSetSplit temp;
                temp.IP = Data.at(i).IP;
                temp.SequenceNumber = i;
                next -> Data.push_back(temp);
            }
            next -> IsInitial = INIT;
        }
        return 0;

    }
    else
    {
        //是否先要在OldIP上build该数据？
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
        TempAgent = new S_Agent(&(BC->m_epoll));
        //new BusinessController("asdf");
        //class S_Agent TempAgent1(&(BC -> m_epoll));
        BC -> BCAgentList.push_back(TempAgent);
        if(TempAgent -> connect_server((char*)(Data.at(SplitNumber).IP).c_str(), EU_PORT) < 0)
        {
            cout << "reconnect EU error"<<endl;
            cout << "fatal error"<< endl;
            exit(0);
        }
        mesg_head SendInitmsghead;
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
        
        mesg_body.SerializeToString(&temp);

        SendInitmsghead.length = temp.length();
        TempAgent ->Writebuff.add_buff(&SendInitmsghead,sizeof(SendInitmsghead));
        body = new char[temp.size()];
        memcpy(body,temp.c_str(),temp.length());

        TempAgent -> Writebuff.add_buff(body,temp.length());

        TempAgent -> m_epoll -> epoll_modify(EPOLLOUT,TempAgent);        
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
            if(next -> IsInitial == INIT)
                (next -> Data).at(SplitNumber).IP = (this -> Data).at(SplitNumber).IP;
            return 0;
        }
    }
}

int DataSet::CheckInitFaild()
{
    for(int i = 0; i < BC -> BCAgentList.size();i ++)
    {
        if(BC -> BCAgentList.at(i)-> error == 1)
            return i;
    }
    return -1;
}
int DataSet::CheckShuffleFaild()//-2未出错 -1无源数据 其他为出错的片
{
    int check = -1;
    for(int i = 0; i < BC -> BCAgentList.size();i ++)
    {
        if((BC -> BCAgentList.at(i) -> error) == 1)
        {
            check = i;
        }
        if(((BC -> BCAgentList.at(i) -> message_head).error) == -2)
        {
            return -1;//无数据源
        }
        if(((BC -> BCAgentList.at(i) -> message_head).error) >= 0)
        {
            check = (BC -> BCAgentList.at(i) -> message_head).error;
        }
    }
    if(check >= 0)
        return check;
    else
        return -2;


}
int DataSet::CheckMapFaild()//单个片出错返回序号，-1无数据源重做 -2 成功
{
    int check = -1;
    for(int i = 0;i < BC -> BCAgentList.size();i ++)
    {
        if((BC -> BCAgentList.at(i)->error) == 1)
        {
            check  = i;
        }
        if(((BC -> BCAgentList.at(i) -> message_head).error) == -1)
        {
            return -1;//无数据源
        }

    }
    if(check == -1)
        return -2;
    else
        return check;
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
