/*
 * =====================================================================================
 *
 *       Filename:  BusinessController.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/12/14 06:32:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include "BusinessController.h"
#include "DataSet.h"
#include "protobuff/bc_master.protocol.pb.h"

BusinessController::BusinessController(string In_ID)
{
    m_epoll.epoll_init();
    //m_epoll.epoll_wait();
    this -> InstanceID = In_ID;
    DataNumber = 0;
}

DataSet* BusinessController::InitialDataSet(string path)
{   
    class DataSet *temp = new DataSet();
    temp -> path = path;
    
    temp -> name = this -> InstanceID + tool.IntToString(DataNumber);
    DataNumber ++; 
    Original_DataSet = temp;
    temp -> BC = this;
    temp -> next = NULL;
    temp -> prev = NULL;
    return temp;
}

int BusinessController::ApplyResource(int number)
{
    MasterAgent = new S_Agent(&m_epoll);
    if((MasterAgent -> connect_server(MASTERIP,MASTER_PORT)) < 0)
    {
        cout << "connect Master error";
        exit(0);
    }
    struct mesg_head ApplyResourcemsghead;
    ApplyResourcemsghead.cmd = MSG_BC_MASTER_APPLY_SOURCE;//初始化头部

    bc_master::pb_MSG_BC_MASTER_APPLY mesg_body;
    mesg_body.set_instanceid(InstanceID);
    mesg_body.set_number(number);
    string temp;
    mesg_body.SerializeToString(&temp);//使用protobuff序列化负载

    ApplyResourcemsghead.length = temp.length();//初始化头部长度字段

    MasterAgent->Writebuff.add_buff(&ApplyResourcemsghead,sizeof(ApplyResourcemsghead));
    char* body = new char(temp.size());
    memcpy(body,temp.c_str(),temp.length());//将负载信息转换为char*类型

    MasterAgent -> Writebuff.add_buff(body,temp.length());
    delete body;
    MasterAgent -> m_epoll -> epoll_modify(EPOLLOUT,MasterAgent);
    while(MasterAgent->error ==0 && MasterAgent -> finish == 0)
    {
        if((m_epoll.epollwait()) < 0)
        {
      //  delete s_agent;
            return -1;
        }
    }

    ////////////////处理报文////////////////////////
    bc_master::pb_MSG_BC_MASTER_APPLY_ACK ApplyResourceResponce;
    ApplyResourceResponce.ParseFromString(MasterAgent->load);
    for(int i = 0 ;i < ApplyResourceResponce.ip_size(); i++)
    {
        string IP = ApplyResourceResponce.ip(0);
        Container.push_back(IP);

    }
    delete MasterAgent;
    return 0 ;
    
    //////////////////////////////////////////////

            

}

