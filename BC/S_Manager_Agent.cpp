/*
 * =====================================================================================
 *
 *       Filename:  S_Manager_Agent.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/15/12 12:01:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include "S_Manager_Agent.h"
S_Manager_Agent::S_Manager_Agent()
{
    for(int i = 0; i< DISK_BLOCK_NUMBER/2;i ++)
    {
        buff[i].new_buff(512);
    }
    MESGHEADbuff.new_buff(MESG_HEAD_LEN);
}

S_Manager_Agent::~S_Manager_Agent()
{
    for(int i = 0;i < DISK_BLOCK_NUMBER/2;i ++)
    {
        buff[i].delete_buff();
    }
}

int S_Manager_Agent::exec()
{
    while(s_agent -> Readbuff.buff_length >= MESG_HEAD_LEN)
    {
        memcpy(MESGHEADbuff.bufferptr,s_agent->Readbuff.bufferptr,MESG_HEAD_LEN);
        i_o_head = (struct mesg_head*)(MESGHEADbuff.bufferptr);
        if(i_o_head -> opcode == READ_DISK)
        {
            s_agent->Readbuff.front_truncation(MESG_HEAD_LEN);
            if(read_from_disk() < 0)
            {
                cout << "read_from_disk error"<<endl;
                return -1;
            }
        }
        else 
        {
            if(s_agent->Readbuff.buff_length < (i_o_head -> len)*BLOCK_SIZE)
                return 0;
            else
            {
                Databuff.delete_buff();
                Databuff.new_buff(i_o_head->len *BLOCK_SIZE);
                memcpy(Databuff.bufferptr,s_agent->Readbuff.bufferptr+MESG_HEAD_LEN,i_o_head->len*BLOCK_SIZE);
                s_agent->Readbuff.front_truncation(MESG_HEAD_LEN+i_o_head->len*BLOCK_SIZE);
            }
            if(write_to_disk() < 0)
            {
                cout << "write_to_disk error"<<endl;
                return -1;
            }
        }
    } 
    return 0;   
}

int S_Manager_Agent::read_from_disk()
{
    //s_agent->Writebuff.add_buff(Databuff.bufferptr,Databuff.buff_length);
    return 0;
}

int S_Manager_Agent::write_to_disk()
{
}
class S_Manager_Agent s_manager_agent;
