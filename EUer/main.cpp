/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/23/12 10:40:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include "head.h"
#include "./protobuff/bc_master.protocol.pb.h"
#include "./protobuff/bc_eu.protocol.pb.h"

static void sighandler(int sig_no)
{
    exit(0);
}
 
int main(int argc, char **argv)
{
  /*  I_Listenagent* i_lisagent = new I_Listenagent();
    if((i_lisagent -> initialserver()) < 0) 
    {
        cerr<< "i_initialserver error"<<endl;
        delete i_lisagent;
        return -1;
    }*/
  /*    D_Listenagent* d_lisagent = new D_Listenagent() ;
    if((d_lisagent -> initialserver()) < 0)
    {
        cerr<< "d_initialserer error"<<endl;
        delete d_lisagent;
        return -1;
    }*/
    int fd;
    struct sockaddr_in servaddr;
    int connfd;
    vector<int> connfdcontainer;
    int flag;
    int ret;
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(32600);
    if((fd = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {   
        cerr<<"socket error:"<<strerror(errno)<<"\n"<<endl;
        return -1; 
    }   
    if(bind(fd,(struct sockaddr *)&servaddr, sizeof(servaddr)) <0) 
    {   
        cerr<<"bind error:"<<strerror(errno)<<"\n"<<endl;
        return -1; 
    }   
    if((flag = fcntl(fd, F_GETFL, 0)) < 0)
    {   
        cerr<<"fcntl error:"<<"\n"<<endl;
        return -1; 
    }   
    if(fcntl(fd,F_SETFL,flag|O_NONBLOCK) < 0)
     {   
        cerr<<"fcntl error:"<<"\n"<<endl;
        return -1; 
     }   
    if(listen(fd,200) < 0)
    {   
        cerr<<"listen error:"<<strerror(errno)<<"\n"<<endl;
        return -1; 
    }

    socklen_t clilen;
    sockaddr_in cliaddr;
    clilen = sizeof(cliaddr);
   while(1)
   { 
    if((connfd = accept(fd, (SA *)&cliaddr,&clilen)) > 0)
    {
    
    if((flag = fcntl(connfd, F_GETFL, 0)) < 0)
    {   
        cerr<<"fcntl error:"<<"\n"<<endl;
        return -1; 
    }   
    if(fcntl(connfd,F_SETFL,flag|O_NONBLOCK) < 0)
     {   
        cerr<<"fcntl error:"<<"\n"<<endl;
        return -1; 
     }   
        connfdcontainer.push_back(connfd);
    }
    for(int i = 0 ; i < connfdcontainer.size(); i++)
    { 
    struct mesg_head ptr;
    int n;
    if((n = read(connfdcontainer.at(i), &ptr,20)) < 0)
    {   
       // cout << "read error"<< endl;
    }   
    

    else if(n == 0)
    {   
        cout << "FIN"<< endl;
        connfdcontainer.erase(connfdcontainer.begin()+i);
        continue;

       // return READ_END;
    }
    else if(n > 0)
    {
        if(ptr.cmd == MSG_BC_EU_INIT_DATA)
        {
            cout << "MSG TYPE: INIT DATA, LENGTH:"<< ptr.length<< endl;
            char * temp;
            read(connfdcontainer.at(i),temp, ptr.length);
            struct mesg_head response_ptr;
            response_ptr.cmd = MSG_BC_EU_INIT_DATA_ACK;
            response_ptr.error = 0;
            response_ptr.length = 0;
            /*  bc_master::pb_MSG_BC_MASTER_APPLY_ACK mesg_body;
            string IP1 = "192.168.9.111";
            string IP2 = "192.168.10.128";
            mesg_body.add_ip(IP1);
            mesg_body.add_ip(IP2);
            string temp;
            mesg_body.SerializeToString(&temp);
            response_ptr.length = temp.length();
            char* body = new char(temp.size());
            memcpy(body,temp.c_str(),temp.length());*/
            write(connfdcontainer.at(i),&response_ptr,20);
            //write(connfd,body,temp.size());
            //cout << "MAPOP"<< endl;
        }
    }
       
}
}
  /*    if((m_epoll.epollwait()) < 0)
    {
      //  delete i_lisagent;
        delete d_lisagent;
        return -1;
    }*/
   // delete d_lisagent;
   // delete i_lisagent;
    return 0;
}
