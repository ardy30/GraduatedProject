/*
 * =====================================================================================
 *
 *       Filename:  D_Manager_Agent.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/27/12 21:12:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yushiyao (), yushiyaogg@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#ifndef _D_MANAGER_AGENT_H
#define _D_MANAGER_AGENT_H

#include "head.h"
#include "Buffermanager.h"
#include "D_Agent.h"
#include "I_Manager_Agent.h"
#include "Epoll.h"

struct DISK_cmnd{
     struct iscsi_scsi_cmd_hdr i_o_cmnd;
     class Buffermanager* i_o_buff;
     unsigned char state;
     unsigned short cmnd_len;
     unsigned int cmnd_addr;
};

class D_Manager_Agent 
{
    public:
        class D_Agent* d_agents[10];
        int d_agent_num;

        class Buffermanager MESGbuff;
        class Buffermanager Databuff;
        struct mesg_head i_o_head;
        struct DISK_cmnd disk_cmnd;
        struct iscsi_data_in_hdr data_in_hdr;
        struct iscsi_r2t_hdr r2t_hdr;
        struct iscsi_scsi_rsp_hdr scsi_rsp_hdr;
        class I_Agent* i_agent; 
        map<unsigned int,struct DISK_cmnd> scsi_cmnd_list;
        //int read_stat;
        
        int add_d_agent(class D_Agent*);
        int read_cmnd(struct iscsi_scsi_cmd_hdr*);
        int write_cmnd(struct iscsi_scsi_cmd_hdr*, class Buffermanager *);
        int data_out_cmnd(struct iscsi_data_out_hdr*, class Buffermanager*);
        int exec(class D_Agent*);
        int response_read(class D_Agent*);
        int response_write();
        int scsi_response();
        int r2t_response(unsigned int ,unsigned short);

        D_Manager_Agent();
        ~D_Manager_Agent();
    private:

};

extern class D_Manager_Agent d_manager_agent;
#endif
