/*
 * =====================================================================================
 *
 *       Filename:  I_Manager_Agent.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/22/12 17:51:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yushiyao (), yushiyaogg@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include "I_Manager_Agent.h"

I_Manager_Agent::I_Manager_Agent()
{
    //this->fd = I_fd;
    //state = 0;
    Msgheadbuff.new_buff(MSGHEAD_LEN);
    max_cmd_sn = 0;
    i_agent = NULL;
    read_stat = READ_BHS;

    //I_read.read_type = BHS;
    //I_read.read_len = BHS_LEN;

    //I_write.write_type = BHS;
    //I_write.write_len = BHS;
}

I_Manager_Agent::~I_Manager_Agent()
{
    Msgheadbuff.delete_buff();
    Databuff.delete_buff();
}

/*int I_Manager_Agent::getfd()
{
    return fd;
}*/

/*int I_Manager_Agent::init_read(int len, class Buffermanager* buff)
{
    delete buff->bufferptr;
    buff->bufferptr = new(unsigned char[len]);
    buff->buff_length = len;
    I_read.read_len = len;
    I_read.read_complete = false;
}*/

char* I_Manager_Agent::find_key(char* searchkey, void* text,int text_len)
{
    char *_data_, *key, *value;
    int keylen, datasize;
    keylen = strlen(searchkey);
    _data_ =(char *) text;
    datasize = text_len;

    while(1)
    {
        for(key = _data_; datasize > 0 && *_data_ != '='; _data_ ++ , datasize--)
            ;
        if(!datasize)
            return NULL;
        _data_ ++;
        datasize --;

        for(value = _data_; datasize > 0&& *_data_ != 0; _data_++, datasize--)
            ;
        _data_++;
        datasize --;

        if(keylen == value - key - 1 && !strncmp(key,searchkey,keylen))
            return value;
    }

}

int I_Manager_Agent::exec()
{
      //  memcpy(BHSbuff.bufferptr,i_agent->Readbuff_head.bufferptr,BHS_LEN);
        pdu.bhs = (struct iscsi_hdr*)(Msgheadbuff.bufferptr);
        pdu.Datasize =(( pdu.bhs->datalength[0]<<16) +(pdu.bhs->datalength[1]<<8)+pdu.bhs->datalength[2]);
        Databuff.delete_buff();
        if(pdu.Datasize > 0)
        {
            Databuff.new_buff(pdu.Datasize);
            memcpy(Databuff.bufferptr,i_agent->Readbuff_data.bufferptr,pdu.Datasize);
        }
        if(0 > cmnd_exec())
        {
            cout <<"cmnd_exec error"<< endl;
            return -1;
        }
        return 0;
}



int I_Manager_Agent::cmnd_exec()
{
    switch(pdu.bhs->opcode & ISCSI_OPCODE_MASK)
    {
    case ISCSI_OP_LOGIN_CMD:
       /* if(state == STATE_LOGIN_FULL)
        {
            cout <<"login error"<<endl;
            return -1;
        }*/
        if(cmnd_exec_login() < 0)
        {
            cout <<"cmnd_exec_login error "<< endl;
            return -1;
        }
        else
            return 0;
        
    case ISCSI_OP_TEXT_CMD:
       if(cmnd_exec_text() < 0)
       {
            cout <<"cmnd_exec_text error"<<endl;
            return -1;
       } 
       else
           return 0;
    case ISCSI_OP_SCSI_CMD:
       if(cmnd_exec_scsi() < 0)
       {
            cout << "cmnd_exec_scsi error"<< endl;
            return -1;
       }
       else
           return 0;
    case ISCSI_OP_DATAOUT_CMD:
        if(cmnd_exec_dataout() < 0)
        {
            cout << "cmnd_exec_dataout error"<<endl;
        }
        else
            return 0;
    case ISCSI_OP_LOGOUT_CMD:
       if(cmnd_exec_logout() < 0)
       {
            cout << "cmnd_exec_logout error" << endl;
            return -1;
       }
       return 0;
    case ISCSI_OP_NOP_OUT:
       if(cmnd_exec_nop_out() < 0)
       {
            cout << "cmnd_exec_nop_out error" << endl;
            return -1;
       }
       return 0;
    default:
       cout << "other kinds of command"<< endl;
       return 0;
    }
}

int I_Manager_Agent::cmnd_exec_login()
{
        return 0;
}


int I_Manager_Agent::state_exec_login()
{
        
}

int I_Manager_Agent::cmnd_exec_text()
{
}

int I_Manager_Agent::cmnd_exec_dataout()
{

}

int I_Manager_Agent::cmnd_exec_logout()
{
}
int I_Manager_Agent::cmnd_exec_nop_out()
{
}

int I_Manager_Agent::cmnd_exec_scsi()
{
}

int I_Manager_Agent::scsi_cmnd_exec_report()
{

}

int I_Manager_Agent::scsi_cmnd_exec_inquiry()
{
            return 0;
}

int I_Manager_Agent::scsi_cmnd_exec_read_capacity()
{
}

int I_Manager_Agent::scsi_cmnd_exec_mode_sense()
{

}

int I_Manager_Agent::scsi_cmnd_exec_read10()
{


}

int I_Manager_Agent::continue_data_in()
{
    return 0;
}

int I_Manager_Agent::scsi_cmnd_exec_write10()
{
        return 0;
}

int I_Manager_Agent::scsi_cmnd_exec_test()
{
    scsi_rsp_hdr.opcode = 0x21;
    scsi_rsp_hdr.flag = 0x80;
    scsi_rsp_hdr.response = 0x00;
    scsi_rsp_hdr.cmd_status = 0x00;
    scsi_rsp_hdr.ahslength = 0x00;
    scsi_rsp_hdr.itt = scsi_cmd_hdr->itt;


    if(htonl(scsi_cmd_hdr->cmd_sn) > max_cmd_sn)
        max_cmd_sn = htonl(scsi_cmd_hdr->cmd_sn);

    scsi_rsp_hdr.exp_cmd_sn = htonl(max_cmd_sn + 1);
    scsi_rsp_hdr.max_cmd_sn = htonl(max_cmd_sn + 33);
       
    Databuff.delete_buff();

    Msgheadbuff.delete_buff();
    //BHSbuff.add_buff(&(scsi_rsp_hdr), BHS_LEN);

    //i_agent->Writebuff.add_buff(BHSbuff.bufferptr,BHS_LEN);
    return 0;
}


class I_Manager_Agent i_manager_agent;
