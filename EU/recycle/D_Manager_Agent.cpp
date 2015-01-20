/*
 * =====================================================================================
 *
 *       Filename:  D_Manager_Agent.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/27/12 21:20:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#ifndef _D_MANAGER_AGENT_CPP
#define _D_MANAGER_AGENT_CPP
#include "D_Manager_Agent.h"
D_Manager_Agent::D_Manager_Agent()
{
    d_agent_num = 0;
    MESGbuff.new_buff(MESG_HEAD_LEN);
    //read_stat = READ_MESGHEAD;
}

D_Manager_Agent::~D_Manager_Agent()
{
}

int D_Manager_Agent::add_d_agent(class D_Agent* register_d_agent)
{
    if(d_agent_num == 10)
    {
        cout << "too many agent"<< endl;
        return -1;
    }
    else if(d_agent_num < 10)
    {
        d_agents[d_agent_num] = register_d_agent;
        d_agent_num ++;
        return 0;
    }
}
int D_Manager_Agent::read_cmnd(struct iscsi_scsi_cmd_hdr* read_pdu)
{
    unsigned int addr;
    unsigned short read_len;
    unsigned int itt;
    
    memcpy(&addr,read_pdu->scb+2,4);
    addr = ntohl(addr);
    memcpy(&read_len,read_pdu->scb + 7, 2);
    read_len = ntohs(read_len);
    itt = read_pdu-> itt;

    if(htonl(read_pdu->cmd_sn) > i_manager_agent.max_cmd_sn)
        i_manager_agent.max_cmd_sn = htonl(read_pdu->cmd_sn);

    disk_cmnd.i_o_cmnd = *read_pdu;
    disk_cmnd.i_o_buff = new class Buffermanager;
    disk_cmnd.i_o_buff->new_buff(read_len * BLOCK_SIZE);
   /* disk_cmnd.state = NO_BLOCK;
    if(read_len == 1)
    {
        if(addr % 2 == 1) 
            disk_cmnd.state = EVEN_BLOCK;
        else if(addr % 2 == 0)
            disk_cmnd.state = ODD_BLOCK;
    }*/
    disk_cmnd.cmnd_len = read_len;
    disk_cmnd.cmnd_addr = addr;

    scsi_cmnd_list.insert(make_pair(itt,disk_cmnd));

    struct mesg_head head;
    head.itt = itt;
    head.opcode = READ_DISK;

    int d_agents_index;
    int remainder = read_len % d_agent_num;
    for(int i = 0 ; i < d_agent_num; i++)
    {
        if(read_len <= i )
        {
            break;
        }
        d_agents_index = (addr % d_agent_num + i)%d_agent_num;
        head.addr = (addr +i) / d_agent_num;
        if(remainder > 0)
        {
            head.len = read_len / d_agent_num + 1;
            remainder --;
        }
        else
            head.len = read_len/d_agent_num;

        d_agents[d_agents_index]->Writebuff.add_buff(&head,sizeof(struct mesg_head));
        if(m_epoll.epoll_modify(EPOLLOUT,d_agents[d_agents_index]) < 0)
        {
            cout <<"epoll.modify error"<<endl;
            return -1;
        }
    }
    return 0;
}

int D_Manager_Agent::write_cmnd(struct iscsi_scsi_cmd_hdr* write_pdu,class Buffermanager* databuff)
{
   unsigned int addr;
   unsigned short write_len;
   unsigned int itt;

   memcpy(&addr, write_pdu->scb +2,4);
   addr = ntohl(addr);
   memcpy(&write_len,write_pdu->scb + 7,2);
   write_len = ntohs(write_len);
   itt = write_pdu -> itt;

   if(htonl(write_pdu->cmd_sn) > i_manager_agent.max_cmd_sn)
       i_manager_agent.max_cmd_sn = htonl(write_pdu->cmd_sn);

   disk_cmnd.i_o_cmnd = *write_pdu;
   disk_cmnd.state = NO_BLOCK;
   disk_cmnd.cmnd_len = write_len;
   disk_cmnd.cmnd_addr = addr;
   disk_cmnd.i_o_buff = NULL;

   scsi_cmnd_list.insert(make_pair(itt,disk_cmnd));

   if(write_len > MAX_TRANSFER_BLOCK_NUMBER)
   {
       if(r2t_response(itt,write_len-MAX_TRANSFER_BLOCK_NUMBER) < 0)
       {
            cout << "r2t_response error"<<endl;
            return -1;
       }
       write_len = MAX_TRANSFER_BLOCK_NUMBER;
   }

   struct mesg_head head;
   head.itt = itt;
   head.opcode  = WRITE_DISK;
   head.write_status = WRITE_CMND;


   int d_agents_index;
   int remainder = write_len % d_agent_num;
   for(int i = 0 ; i < d_agent_num; i++)
   {
       class Buffermanager temp;
       if(write_len <= i )
       {
           break;
       }
       d_agents_index = (addr % d_agent_num + i) % d_agent_num;   
       head.addr = (addr+i) / d_agent_num;
       if(remainder > 0)
       {
           head.len = write_len / d_agent_num + 1;
           remainder --;
       }
       else
           head.len = write_len/d_agent_num;

       d_agents[d_agents_index]->Writebuff.add_buff(&head,sizeof(struct mesg_head));
       if(temp.new_buff(head.len * BLOCK_SIZE) < 0)
       {
           cout << "temp.new_buff error"<<endl;
           return 0;
       }
       for(int j = 0; j < head.len;j ++)
       {
           memcpy(temp.bufferptr+ j * BLOCK_SIZE,databuff->bufferptr +(j *d_agent_num + i)* BLOCK_SIZE,BLOCK_SIZE);
          /* d_agents[d_agents_index] -> Writebuff.add_buff(databuff->bufferptr + (j * d_agent_num + i) * BLOCK_SIZE, BLOCK_SIZE);*/
       }
       d_agents[d_agents_index] -> Writebuff.add_buff(temp.bufferptr,head.len* BLOCK_SIZE);
       temp.delete_buff();
       if(m_epoll.epoll_modify(EPOLLOUT,d_agents[d_agents_index]) < 0)
       {
           cout <<"epoll.modify error"<<endl;
           return -1;
       }
   }
   return 0;
}

int D_Manager_Agent::data_out_cmnd(struct iscsi_data_out_hdr* data_out_pdu,class Buffermanager* databuff)
{
    unsigned int itt;
    unsigned int offset;
    unsigned int len_byte;
    unsigned short len_block;
    unsigned char temp_len[4];
    unsigned int addr;
    map<unsigned int, struct DISK_cmnd>::iterator it;

    itt = data_out_pdu-> itt;
    offset = ntohl(data_out_pdu -> buffer_offset);

   /* if(offset == 8192)
    {
        cout << "datalength="<< databuff->buff_length<<endl;
    }*/

    memcpy(&temp_len[1],data_out_pdu->datalength,3);
    memcpy(&len_byte,&temp_len[0],4);
    len_byte = ntohl(len_byte);
    len_block = len_byte/BLOCK_SIZE;

    it = scsi_cmnd_list.find(itt);
    if(it == scsi_cmnd_list.end())
    {
        cout << "scsi_cmnd_list.find error"<<endl;
        return -1;
    }
    disk_cmnd = it -> second;
    addr = disk_cmnd.cmnd_addr;
    addr = addr + offset/BLOCK_SIZE;

    struct mesg_head head;
    head.itt = itt;
    head.opcode = WRITE_DISK;
    head.write_status = DATA_OUT_CMND;

    int d_agents_index;
    int remainder = len_block % d_agent_num;
    for(int i = 0 ; i < d_agent_num; i++)
    {
        class Buffermanager temp;
        if(len_block <= i )
        {
            break;
        }
        d_agents_index = (addr % d_agent_num + i) % d_agent_num;   
        head.addr = (addr+i) / d_agent_num;
        if(remainder > 0)
        {
            head.len = len_block / d_agent_num + 1;
            remainder --;
        }
        else
            head.len = len_block/d_agent_num;

        d_agents[d_agents_index]->Writebuff.add_buff(&head,sizeof(struct mesg_head));
        if(temp.new_buff(head.len * BLOCK_SIZE) < 0)
        {
            cout << "temp.new_buff error"<<endl;
            return 0;
        }
        for(int j = 0; j < head.len;j ++)
        {
            memcpy(temp.bufferptr + j * BLOCK_SIZE,databuff->bufferptr+(j * d_agent_num + i) * BLOCK_SIZE,BLOCK_SIZE);
           /* d_agents[d_agents_index] -> Writebuff.add_buff(databuff->bufferptr + (j * d_agent_num + i) * BLOCK_SIZE, BLOCK_SIZE);*/
        }
        d_agents[d_agents_index] -> Writebuff.add_buff(temp.bufferptr,head.len* BLOCK_SIZE);
        temp.delete_buff();    
        if(m_epoll.epoll_modify(EPOLLOUT,d_agents[d_agents_index]) < 0)
        {
            cout <<"epoll.modify error"<<endl;
            return -1;
        }
    }
    return 0;
}

int D_Manager_Agent::exec(class D_Agent* d_agent)
{

       memcpy(&i_o_head, d_agent->Readbuff_head.bufferptr,MESG_HEAD_LEN);
      // i_o_head = (struct mesg_head*)(MESGbuff.bufferptr);
       if (i_o_head.opcode == RESPONSE_READ)
       {
           Databuff.delete_buff();
           Databuff.new_buff(i_o_head.len *BLOCK_SIZE);
           memcpy(MESGbuff.bufferptr,d_agent->Readbuff_head.bufferptr,MESG_HEAD_LEN);
           memcpy(Databuff.bufferptr,d_agent->Readbuff_data.bufferptr,i_o_head.len* BLOCK_SIZE);
                if((response_read(d_agent)) < 0)
                {
                    cout << "response_read error"<<endl;
                    return -1;
                }
       }
       else if(i_o_head.opcode == RESPONSE_WRITE)
       {
            memcpy(MESGbuff.bufferptr,d_agent->Readbuff_head.bufferptr,MESG_HEAD_LEN);
            if(response_write() < 0)
            {
                cout <<"response_write error"<<endl;
                return -1;
            }
                    
                        
       }
       
    return 0;
}


int D_Manager_Agent::response_read(class D_Agent* d_agent)
{
    unsigned int itt;
    unsigned int addr;
    unsigned short len;
    map<unsigned int, struct DISK_cmnd>::iterator it;

    int n_datalen;
    unsigned char datalen[4];

    int d_agents_index;

    itt = i_o_head.itt;
    addr = i_o_head.addr;
    len = i_o_head.len;

    it = scsi_cmnd_list.find(itt);
    if(it == scsi_cmnd_list.end())
    {
        cout << "itt"<< itt <<endl;
        cout <<"scsi_cmnd_list.find error"<< endl;
        return -1;
    }

    disk_cmnd = it ->second;
    disk_cmnd.cmnd_len = disk_cmnd.cmnd_len -len;
    for(int i = 0; i < d_agent_num; i ++)
    {
        if(d_agent == d_agents[i])
        {
            d_agents_index = i;
            break;
        }
    }

    for(int i = 0; i < len; i ++)
    {
        disk_cmnd.i_o_buff->add_buff((i * d_agent_num + addr *d_agent_num + d_agents_index - disk_cmnd.cmnd_addr)*BLOCK_SIZE ,Databuff.bufferptr + i * BLOCK_SIZE,BLOCK_SIZE);
      /*  memcpy(disk_cmnd.i_o_buff->bufferptr +( i*d_agent_num + addr * d_agent_num + d_agents_index - disk_cmnd.cmnd_addr)*BLOCK_SIZE,Databuff.bufferptr+ i * BLOCK_SIZE,BLOCK_SIZE );*/
    }

    Databuff.delete_buff();

    if(disk_cmnd.cmnd_len != 0)
    {
        scsi_cmnd_list.erase(itt);
        scsi_cmnd_list.insert(make_pair(itt,disk_cmnd));
    }
    else
    {
       data_in_hdr.opcode = ISCSI_OP_DATAIN_RSP;
       data_in_hdr.cmd_status = 0;
       data_in_hdr.ahslength = 0;

       data_in_hdr.itt = disk_cmnd.i_o_cmnd.itt;
       data_in_hdr.ttt = 0xffffffff;

       data_in_hdr.residual_count = 0;
       disk_cmnd.cmnd_len = disk_cmnd.i_o_buff-> buff_length/BLOCK_SIZE;
       for(int i = 0;i < disk_cmnd.cmnd_len; i = i + MAX_TRANSFER_BLOCK_NUMBER)
       {
            if((disk_cmnd.cmnd_len - i) <= MAX_TRANSFER_BLOCK_NUMBER)
            {
                data_in_hdr.flag = 0x81;
                data_in_hdr.stat_sn = htonl(i_manager_agent.sn);
                i_manager_agent.sn ++;
                data_in_hdr.data_sn = htonl(i /MAX_TRANSFER_BLOCK_NUMBER);
                data_in_hdr.buffer_offset = htonl(i * BLOCK_SIZE);

                data_in_hdr.exp_cmd_sn = htonl(i_manager_agent.max_cmd_sn + 1);
                data_in_hdr.max_cmd_sn = htonl(i_manager_agent.max_cmd_sn + CMND_SIZE - scsi_cmnd_list.size());

                n_datalen = htonl((disk_cmnd.cmnd_len - i) * BLOCK_SIZE);
                memcpy(datalen,&n_datalen,sizeof(int));
                memcpy(&(data_in_hdr.datalength), &datalen[1], 3);

                i_agent->Writebuff.add_buff(&data_in_hdr, BHS_LEN);
                i_agent->Writebuff.add_buff(disk_cmnd.i_o_buff->bufferptr + i * BLOCK_SIZE,(disk_cmnd.cmnd_len - i) * BLOCK_SIZE);
            }
            else
            {
                data_in_hdr.flag = 0x00;
                data_in_hdr.stat_sn = 0;
                data_in_hdr.data_sn= htonl(i / MAX_TRANSFER_BLOCK_NUMBER);
                data_in_hdr.buffer_offset = htonl(i * BLOCK_SIZE);

                data_in_hdr.exp_cmd_sn = htonl(i_manager_agent.max_cmd_sn + 1);
                data_in_hdr.max_cmd_sn = htonl(i_manager_agent.max_cmd_sn + CMND_SIZE -scsi_cmnd_list.size());

                n_datalen = htonl(MAX_TRANSFER_BLOCK_NUMBER* BLOCK_SIZE);
                memcpy(datalen,&n_datalen,sizeof(int));
                memcpy(&(data_in_hdr.datalength),&datalen[1],3);

                i_agent->Writebuff.add_buff(&data_in_hdr,BHS_LEN);
                i_agent->Writebuff.add_buff(disk_cmnd.i_o_buff->bufferptr+ i*BLOCK_SIZE,MAX_TRANSFER_BLOCK_NUMBER*BLOCK_SIZE);
            }
       }

        if(m_epoll.epoll_modify(EPOLLOUT,i_agent) < 0)
        {
            cout <<"epoll.modify error"<<endl;
            return -1;
        }
       disk_cmnd.i_o_buff->delete_buff();
       scsi_cmnd_list.erase(itt);
    }
    
    return 0;
}

int D_Manager_Agent::response_write()
{
    unsigned int itt;
    unsigned int addr;
    unsigned short len;
    unsigned char write_status;
    map<unsigned int, struct DISK_cmnd>::iterator it;

    itt = i_o_head.itt;
    addr = i_o_head.addr;
    len = i_o_head.len;
    write_status = i_o_head.write_status;

    it = scsi_cmnd_list.find(itt);
    if(it == scsi_cmnd_list.end())
    {
        cout << "scsi_cmnd_list.find error"<<endl;
        return -1;
    }
    disk_cmnd = it->second;
    if(write_status == WRITE_RESPONSE_FAILD  ||write_status ==DATA_OUT_RESPONSE_FAILD)
    {
        cout << "write error"<<endl;
        return -1;
    }
    else if(write_status ==WRITE_RESPONSE_SUCESS)
    {
        disk_cmnd.cmnd_len = disk_cmnd.cmnd_len - len;
        if(disk_cmnd.cmnd_len == 0)
        {
            //scsi_response
            if(scsi_response()< 0)
            {
                cout << "scsi_response error"<<endl;
                return -1;
            }
            scsi_cmnd_list.erase(itt);
            return 0;
        }
        else
        {    
            scsi_cmnd_list.erase(itt);
            scsi_cmnd_list.insert(make_pair(itt,disk_cmnd));
        }
       /* else
        {
            if(addr % 2 == 1)
                disk_cmnd.state = disk_cmnd.state | ODD_BLOCK;
            else
                disk_cmnd.state = disk_cmnd.state | EVEN_BLOCK;
            if(disk_cmnd.state == ALL_BLOCK)
            {
                //r2t
                if(r2t_response() < 0)
                {
                    cout << "r2t_response error"<< endl;
                    return -1;
                }

                scsi_cmnd_list.erase(itt);
                scsi_cmnd_list.insert(make_pair(itt,disk_cmnd));
                //update disk_cmnd
                return 0;
            }
            else 
                //update disk_cmnd
                scsi_cmnd_list.erase(itt);
                scsi_cmnd_list.insert(make_pair(itt,disk_cmnd));
                return 0;

        }*/
    }
    else if(write_status == DATA_OUT_RESPONSE_SUCCESS)
    {
        disk_cmnd.cmnd_len = disk_cmnd.cmnd_len - len;
        if(disk_cmnd.cmnd_len == 0)
        {
            //scsi_response
            if(scsi_response() < 0)
            {
                cout << "scsi_response error"<< endl;
                return -1;
            }
            scsi_cmnd_list.erase(itt);
            //delete disk_cmnd;
            return 0;
        }
        else

            scsi_cmnd_list.erase(itt);
            scsi_cmnd_list.insert(make_pair(itt,disk_cmnd));
            //update disk_cmnd;
            return 0;
    }
    return 0;
}
int D_Manager_Agent::scsi_response()
{
    scsi_rsp_hdr.opcode = ISCSI_OP_SCSI_RSP;
    scsi_rsp_hdr.flag = 0x80;
    scsi_rsp_hdr.ahslength = 0x00;
    scsi_rsp_hdr.itt = i_o_head.itt;

    scsi_rsp_hdr.stat_sn = htonl(i_manager_agent.sn);
    i_manager_agent.sn ++;

    scsi_rsp_hdr.exp_cmd_sn = htonl(i_manager_agent.max_cmd_sn + 1);
    scsi_rsp_hdr.max_cmd_sn = htonl(i_manager_agent.max_cmd_sn + CMND_SIZE -scsi_cmnd_list.size());
    
    i_agent->Writebuff.add_buff(&(scsi_rsp_hdr), BHS_LEN);

    if(m_epoll.epoll_modify(EPOLLOUT,i_agent) < 0)
    {
        cout <<"epoll.modify error"<<endl;
        return -1;
    }
    return 0;
}

int D_Manager_Agent::r2t_response(unsigned int itt, unsigned short len)
{
    r2t_hdr.opcode = ISCSI_OP_R2T_RSP;
    r2t_hdr.flag = 0x80;
    r2t_hdr.itt = itt;

    r2t_hdr.stat_sn = htonl(i_manager_agent.sn);

    r2t_hdr.exp_cmd_sn = htonl(i_manager_agent.max_cmd_sn + 1);
    r2t_hdr.max_cmd_sn = htonl(i_manager_agent.max_cmd_sn + CMND_SIZE - scsi_cmnd_list.size() );
    //memcpy(&(r2t_hdr.ttt), disk_cmnd.i_o_cmnd.scb+2,4);
    r2t_hdr.buffer_offset = ntohl( MAX_TRANSFER_BLOCK_NUMBER * BLOCK_SIZE);
    r2t_hdr.data_length = ntohl(len * BLOCK_SIZE);

    i_agent->Writebuff.add_buff(&(r2t_hdr),BHS_LEN);
    if(m_epoll.epoll_modify(EPOLLOUT,i_agent) < 0)
    {
        cout <<"epoll.modify error"<<endl;
        return -1;
    }
    return 0;
}

class D_Manager_Agent d_manager_agent;
#endif
