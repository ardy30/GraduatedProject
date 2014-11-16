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
string IntToString(int number)
{
        stringstream ss; 
        ss << number;
        string temp = ss.str();
        return temp;
}
int err_sys(const char * str)
{
    fprintf(stderr,"%s\n",str);
    exit(1);
} 

int main(int argc, char **argv)
{
    int fd;
    struct sockaddr_in servaddr;
    int connfd;
    vector<int> connfdcontainer;
    int flag;
    int ret;
    int i;
    vector<string> datacontainer;
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
    //cout << "abc"<< endl;
    for( i = 0 ; i < connfdcontainer.size(); i++)
    { 
    struct mesg_head ptr;
    int n;
    int number = -1;
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
            char * temp = new char[ptr.length];
           number = read(connfdcontainer.at(i),temp, ptr.length);
           while(number < 0)
           {
                number = read(connfdcontainer.at(i),temp, ptr.length);
           }
           if(number != ptr.length)
           {
               cout << "read error"<< endl;
               cout << "length" << number<< endl;
           }
           number = -1;

            bc_eu::pb_MSG_BC_EU_INIT_DATA Initoperation;
            string load(temp,ptr.length);
            if(Initoperation.ParseFromArray((void*)temp,ptr.length) < 0)
                cout << "parseerror"<< endl;
            string splitname = Initoperation.splitname();
            int    splitnumber = Initoperation.splitnumber();

            string splitid = splitname + IntToString(splitnumber);
            datacontainer.push_back(splitid);
            cout << splitname << endl;
            cout << splitnumber<<endl;
            cout << splitid << endl;

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
            delete temp;
        }
        if(ptr.cmd == MSG_BC_EU_MAP)
        {
            cout << "MSG TYPE: MAPOP, LENGTH:"<< ptr.length<< endl;
            char *temp = new char[ptr.length];
            
            number = read(connfdcontainer.at(i),temp,ptr.length);
            while (number < 0)
            {
                number = read(connfdcontainer.at(i),temp,ptr.length);

            }
            if(number != ptr.length)
            {
                cout << "read error"<< endl;
            }
            number -1;
            bc_eu::pb_MSG_BC_EU_MAP Mapoperation;
            string load(temp,ptr.length);
            Mapoperation.ParseFromString(load);
                
            string sourcedata =Mapoperation.sourcesplitname();   
            int sourcedatasplitnumber = Mapoperation.sourcesplitnumber();
            string destdata = Mapoperation.destsplitname();
            int destdatasplitnumber = Mapoperation.destsplitnumber();
            string sourcedataid = sourcedata+ IntToString(sourcedatasplitnumber) ;
            string destdataid   = destdata + IntToString(destdatasplitnumber);   

            cout << sourcedataid<< endl;
            cout << destdataid << endl;
            struct mesg_head responsemap_ptr;
            responsemap_ptr.cmd = MSG_BC_EU_MAP_ACK;
            responsemap_ptr.error = -1;
            responsemap_ptr.length = 0;
            for(int j = 0; j < datacontainer.size(); j++)
            {
                if(sourcedataid == datacontainer.at(j))
                {
                    responsemap_ptr.error = 0;
                    datacontainer.push_back(destdataid);
                    break;
                }
            }
            write(connfdcontainer.at(i),&responsemap_ptr,20);           
            delete temp;
        }
        if(ptr.cmd == MSG_BC_EU_DELETE_DATA)
        {
            cout << "MSG TYPE: DELETEDATA, LENGTH:"<< ptr.length<< endl;
            char *temp = new char[ptr.length];
            number = read(connfdcontainer.at(i),temp,ptr.length);
            while(number < 0)
            {
                number = read(connfdcontainer.at(i),temp,ptr.length);
            }
            if(number = ptr.length)
            {
                cout << "read error"<< endl;
            }
            number  = -1;
            bc_eu::pb_MSG_BC_EU_DELETE_DATA Deleteoperation;
            string load(temp,ptr.length);
            Deleteoperation.ParseFromString(load);

            string deletesourcedata = Deleteoperation.sourcesplitname();
            int deletesourcedatanumber = Deleteoperation.sourcesplitnumber();
            string deletedataid = deletesourcedata + IntToString(deletesourcedatanumber);
            for(int j = 0 ;j < datacontainer.size();j ++)
            {
                if(deletedataid == datacontainer.at(i))
                    datacontainer.erase(datacontainer.begin()+i);
            }
            cout << deletedataid<< endl;
            struct mesg_head responsedelete_ptr;
            responsedelete_ptr.cmd = MSG_BC_EU_MAP_ACK;
            responsedelete_ptr.error = 0;
            responsedelete_ptr.length = 0;
            write(connfdcontainer.at(i),&responsedelete_ptr,20);
            delete temp;
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
