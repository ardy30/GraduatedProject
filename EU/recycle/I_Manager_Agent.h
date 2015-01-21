/*
 * =====================================================================================
 *
 *       Filename:  I_Manager_Agent.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/16/12 16:34:47
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yushiyao (), yushiyaogg@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#ifndef _I_MANAGER_AGENT_H
#define _I_MANAGER_AGENT_H

#include "head.h"
#include "Buffermanager.h"
#include "ReadAgent.h"
#include "WriteAgent.h"
#include "Agent.h"
#include "Epoll.h"
#include "I_Agent.h"

class I_Manager_Agent 
{
    public:


       // class ReadAgent I_read;
       // class WriteAgent I_write;
        class Buffermanager Msgheadbuff;
        class Buffermanager Databuff;
        class I_Agent* i_agent; 
       // class Buffermanager Writebuff;
       // class Buffermanager Readbuff;
       // int init_read(int,class Buffermanager*);

       // int readagent();
       // int writeagent();

        char* find_key(char *, void*, int);
        int max_cmd_sn;
        int continue_data_in();
        int read_stat;

        int exec();
        int cmnd_exec();
        int cmnd_exec_login();
        int cmnd_exec_text();
        int cmnd_exec_scsi();
        int cmnd_exec_dataout();
        int cmnd_exec_logout();
        int cmnd_exec_nop_out();

        int state_exec_security();
        int state_exec_login();
            
        int scsi_cmnd_exec_report();
        int scsi_cmnd_exec_inquiry();
        int scsi_cmnd_exec_read_capacity();
        int scsi_cmnd_exec_mode_sense();
        int scsi_cmnd_exec_read10();
        int scsi_cmnd_exec_write10();
        int scsi_cmnd_exec_test();

        int getfd();
        I_Manager_Agent();
        ~I_Manager_Agent();

    private:
        //int state;
        int session_type;


        unsigned int data_out_addr;
        unsigned short data_out_len;

        struct PDU pdu;
        struct iscsi_hdr* header;
        struct iscsi_login_req_hdr*  login_req_hdr;
        struct iscsi_text_req_hdr*   text_req_hdr;
        struct iscsi_scsi_cmd_hdr*   scsi_cmd_hdr;
        struct iscsi_logout_req_hdr* logout_req_hdr;
        struct iscsi_data_out_hdr*   data_out_hdr;
        struct iscsi_nop_out_hdr*    nop_out_hdr;

        struct iscsi_nop_in_hdr     nop_in_hdr;
        struct iscsi_login_rsp_hdr  login_rsp_hdr;
        struct iscsi_text_rsp_hdr   text_rsp_hdr;
        struct iscsi_logout_rsp_hdr logout_rsp_hdr;
        struct iscsi_data_in_hdr    data_in_hdr;
        struct iscsi_scsi_rsp_hdr   scsi_rsp_hdr;
        struct iscsi_r2t_hdr        r2t_hdr;

        struct scsi_reportlun*     reportlun_cmd;
        struct scsi_inquirylun*    inquirylun_cmd;
        struct scsi_readcapacity*  readcapacity_cmd;
        struct scsi_modesense*     modesense_cmd;
        struct scsi_write*         write_cmd;
        struct scsi_read*          read_cmd;

        struct response_reportlun      reportlun_rsp;
        struct responseall_inquirylun  inquirylunall_rsp;
        struct response00_inquirylun   inquirylun00_rsp;
        struct response80_inquirylun   inquirylun80_rsp;
        struct response83_inquirylun   inquirylun83_rsp;
        struct response_readcapacity   readcapacity_rsp;
        struct mode_parameter_header   parameter_header;

        struct dis_reconnect_page             dis_reconnect_page_rsp;
        struct format_device_mode_page        format_device_mode_page_rsp;
        struct rigid_disk_geometry_mode_page  rigid_disk_geometry_mode_page_rsp;
        struct caching_mode_page              caching_mode_page_rsp;
        struct control_mode_page              control_mode_page_rsp;
        struct exeptions_control_mode_page    exeptions_control_mode_page_rsp;
};

extern class I_Manager_Agent i_manager_agent;

#endif
