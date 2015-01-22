/*
 * =====================================================================================
 *
 *       Filename:  head.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/16/12 15:45:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yushiyao (), yushiyaogg@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#ifndef  _HEADER_H
#define  _HEADER_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <utility>
#include <vector>
#include <set>
#include <map>
#include <signal.h>
#include <dlfcn.h>

#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <byteswap.h>
#include <sstream>
#include <fstream>
#include "Buffermanager.h"
#include "./protobuff/bc_master.protocol.pb.h"
#include "./protobuff/bc_eu.protocol.pb.h"
using namespace std;


#define EU_PORT 32600
#define LOCAL_IP "192.168.9.111"



#define  MAXEPOLL  100
#define  LISTENQ  100
#define  SA struct sockaddr

#define  CMND_SIZE 64

//state
#define STATE_FREE 0
#define STATE_SECURITY 1
#define STATE_SECURITY_LOGIN 4
#define STATE_LOGIN 6
#define STATE_LOGIN_FULL 8
#define STATE_NORMAL 9
#define STATE_DISCOVER 10

//size
#define DISK_BLOCK_NUMBER 1000*100
#define BLOCK_SIZE 512
#define MAX_TRANSFER_BLOCK_NUMBER 16
//session type
#define NORMAL 0
#define DISCOVERY 1

//
#define MSGHEAD_LEN 20
#define TCP_SOCKET_SIZE 64*1024

//readtype
#define BHS 0
#define AHS 1
#define DATA 2
//readstat
#define READ_BHS 0
#define READ_DATA 1
#define READ_DONE 2

#define READ_MESGHEAD 0
//read return value
#define READ_ERROR -1
#define READ_END    0
#define READ_BLOCK  1
#define READ_SUCCESS 2

//write return value
#define WRITE_ERROR -1
#define WRITE_BLOCK  1
#define WRITE_SUCCESS 2

//client to server opcode values
#define ISCSI_OP_NOP_OUT  0x00
#define ISCSI_OP_SCSI_CMD 0x01
#define ISCSI_OP_LOGIN_CMD 0x03
#define ISCSI_OP_TEXT_CMD 0x04
#define ISCSI_OP_LOGOUT_CMD 0x06
#define ISCSI_OP_DATAOUT_CMD 0x05
#define ISCSI_OPCODE_MASK 0x3F

//server to client opcode values
#define ISCSI_OP_NOP_IN   0x20
#define ISCSI_OP_SCSI_RSP 0x21
#define ISCSI_OP_LOGIN_RSP 0x23
#define ISCSI_OP_TEXT_RSP 0X24
#define ISCSI_OP_DATAIN_RSP 0x25
#define ISCSI_OP_LOGOUT_RSP 0x26
#define ISCSI_OP_R2T_RSP  0x31

//scsi cmnd opcode values
#define SCSI_OP_REPORT_LUN 0xa0
#define SCSI_OP_INQUIRY_LUN 0x12
#define SCSI_OP_READ_CAPACITY 0x25
#define SCSI_OP_MODE_SENSE 0x1a
#define SCSI_OP_READ10 0x28
#define SCSI_OP_WRITE10 0x2a
#define SCSI_OP_TEST 0x00

//CSG
#define ISCSI_FLG_CSG_MASK 0X0c
#define ISCSI_FLG_CSG_LOGIN 0x04
#define ISCSI_FLG_CSG_SECURITY 0x00

//mode sense page code
#define ALL_PAGE 0x3f
#define DISCONNECT_RECONNECT_PAGE 0x02
#define FORMAT_DEVICE_MODE_PAGE 0x03
#define RIGID_DISK_GEOMETRY_MODE_PAGE 0x04
#define CACHING_PAGE 0x08
#define CONTROL_PAGE 0x0a
#define EXCEPTION_CONTROL_MODE_PAGE 0x1c
//PDU

struct iscsi_hdr{
    unsigned char opcode;
    unsigned char flag;
    unsigned char spec1[2];
    unsigned char ahslength;
    unsigned char datalength[3];
    unsigned short lun[4];
    unsigned int itt;
    unsigned int ttt;
    unsigned int sn;
    unsigned int exp_sn;
    unsigned int max_sn;
    unsigned int spec3[3];
};

union iscsi_sid{
    struct{
        unsigned char isid[6];
        unsigned short tsih;
    }id;
    unsigned int id64;
};

struct iscsi_login_req_hdr{
    unsigned char opcode;
    unsigned char flag;
    unsigned char max_version;
    unsigned char min_version;
    unsigned char ahslength;
    unsigned char datalength[3];
    union iscsi_sid sid;
    unsigned int itt;
    unsigned short cid;
    unsigned short rsvd1;
    unsigned int cmd_sn;
    unsigned int exp_stat_sn;
    unsigned int rsvd2[4];
};

struct iscsi_login_rsp_hdr{
    unsigned char opcode;
    unsigned char flag;
    unsigned char max_version;
    unsigned char active_version;
    unsigned char ahslength;
    unsigned char datalength[3];
    union iscsi_sid sid;
    unsigned int itt;
    unsigned int rsvd1;
    unsigned int stat_sn;
    unsigned int exp_cmd_sn;
    unsigned int max_cmd_sn;
    unsigned char status_class;
    unsigned char status_detail;
    unsigned char rsvd2[10];
};

struct iscsi_text_req_hdr{
    unsigned char opcode;
    unsigned char flag;
    unsigned short rsvd1;
    unsigned char ahslength;
    unsigned char datalength[3];
    unsigned int rsvd2[2];
    unsigned int itt;
    unsigned int ttt;
    unsigned int cmd_sn;
    unsigned int exp_stat_sn;
    unsigned int rsvd3[4];
};

struct iscsi_text_rsp_hdr{
    unsigned char opcode;
    unsigned char flag;
    unsigned short rsvd1;
    unsigned char ahslength;
    unsigned char datalength[3];
    unsigned int rsvd2[2];
    unsigned int itt;
    unsigned int ttt;
    unsigned int stat_sn;
    unsigned int exp_cmd_sn;
    unsigned int max_cmd_sn;
    unsigned int rsvd3[3];
};

struct iscsi_logout_req_hdr{
    unsigned char opcode;
    unsigned char flag;
    unsigned short rsvd1;
    unsigned char ahslength;
    unsigned char datalength[3];
    unsigned int rsvd2[2];
    unsigned int itt;
    unsigned short cid;
    unsigned short rsvd3;
    unsigned int cmd_sn;
    unsigned int exp_stat_sn;
    unsigned rsvd4[4];
};

struct iscsi_logout_rsp_hdr{
    unsigned char opcode;
    unsigned char flag;
    unsigned char response;
    unsigned char rsvd1;
    unsigned char ahslength;
    unsigned char datalength[3];
    unsigned int rsvd2[2];
    unsigned int itt;
    unsigned int rsvd3;
    unsigned int stat_sn;
    unsigned int exp_cmd_sn;
    unsigned int max_cmd_sn;
    unsigned int rsvd4;
    unsigned short time2wait;
    unsigned short time2retain;
    unsigned int rsvd5;
};

struct iscsi_scsi_cmd_hdr{
    unsigned char opcode;
    unsigned char flag;
    unsigned short rsvd1;
    unsigned char ahslength;
    unsigned char datalength[3];
    unsigned short lun[4];
    unsigned int itt;
    unsigned int data_length;
    unsigned int cmd_sn;
    unsigned int exp_stat_sn;
    unsigned char scb[16];
};

struct iscsi_scsi_rsp_hdr{
    unsigned char opcode;
    unsigned char flag;
    unsigned char response;
    unsigned char cmd_status;
    unsigned char ahslength;
    unsigned char datalength[3];
    unsigned int rsvd1[2];
    unsigned int itt;
    unsigned int snack;
    unsigned int stat_sn;
    unsigned int exp_cmd_sn;
    unsigned int max_cmd_sn;
    unsigned int exp_data_sn;
    unsigned int bi_residual_count;
    unsigned int residual_count;
};

struct iscsi_data_out_hdr{
    unsigned char opcode;
    unsigned char flag;
    unsigned short rsvd1;
    unsigned char ahslength;
    unsigned char datalength[3];
    unsigned short lun[4];
    unsigned int itt;
    unsigned int ttt;
    unsigned int rsvd2;
    unsigned int exp_stat_sn;
    unsigned int rsvd3;
    unsigned int data_sn;
    unsigned int buffer_offset;
    unsigned int rsvd4;
};

struct iscsi_data_in_hdr{
    unsigned char opcode;
    unsigned char flag;
    unsigned char rsvd1;
    unsigned char cmd_status;
    unsigned char ahslength;
    unsigned char datalength[3];
    unsigned int rsvd2[2];
    unsigned int itt;
    unsigned int ttt;
    unsigned int stat_sn;
    unsigned int exp_cmd_sn;
    unsigned int max_cmd_sn;
    unsigned int data_sn;
    unsigned int buffer_offset;
    unsigned int residual_count;

};

struct iscsi_nop_out_hdr{
    unsigned char opcode;
    unsigned char flag;
    unsigned short rsvd1;
    unsigned char ahslength;
    unsigned char datalength[3];
    unsigned short lun[4];
    unsigned int itt;
    unsigned int ttt;
    unsigned int cmd_sn;
    unsigned int exp_stat_sn;
    unsigned int rsvd2[4];
};

struct iscsi_nop_in_hdr{
    unsigned char opcode;
    unsigned char flag;
    unsigned short rsvd1;
    unsigned char ahslength;
    unsigned char datalength[3];
    unsigned short lun[4];
    unsigned int itt;
    unsigned int ttt;
    unsigned int stat_sn;
    unsigned int exp_cmd_sn;
    unsigned int max_cmd_sn;
    unsigned int rsvd2[3];
};

struct iscsi_r2t_hdr{
    unsigned char opcode;
    unsigned char flag;
    unsigned short rsvd1;
    unsigned char ahslength;
    unsigned char datalength[3];
    unsigned short lun[4];
    unsigned int itt;
    unsigned int ttt;
    unsigned int stat_sn;
    unsigned int exp_cmd_sn;
    unsigned int max_cmd_sn;
    unsigned int r2t_sn;
    unsigned int buffer_offset;
    unsigned int data_length;
};


struct PDU{
    struct iscsi_hdr* bhs;
    void *ahs;
    unsigned int ahsize;
    void *Data;
    unsigned int Datasize;
};

struct scsi_reportlun{
    unsigned char opcode;
    unsigned char rsvd1[5];
    unsigned int  allocation_length;
    unsigned char rsvd2;
    unsigned char control;
};

struct scsi_inquirylun{
    unsigned char opcode;
    unsigned char flag;
    unsigned char page_operationcode;
    unsigned char rsvd;
    unsigned char allocation_length;
    unsigned char control;
};

struct scsi_readcapacity{
    unsigned opcode;
    unsigned rsvd1;
    unsigned int logical_block_address;
    unsigned char rsvd2;
    unsigned char rsvd3;
    unsigned char rsvd4;
    unsigned char control;
};

struct scsi_modesense{
    unsigned char opcode;
    unsigned char flag1;
    unsigned char flag2;
    unsigned char rsvd;
    unsigned char allocation_length;
    unsigned char control;
};

struct scsi_write{
    unsigned char opcode;
    unsigned char flag1;
    unsigned int  logical_block_address;
    unsigned char flag2;
    unsigned short transfer_length;
    unsigned char control;
};

struct scsi_read{
    unsigned char opcode;
    unsigned char flag1;
    unsigned int  logical_block_address;
    unsigned char flag2;
    unsigned short transfer_length;
    unsigned char control;
};

struct response_reportlun{
    unsigned int lun_list_length;
    unsigned int rsvd1;
    unsigned long firstlun;
    //lun list
};

struct responseall_inquirylun{
    unsigned char flag1;
    unsigned char flag2;
    unsigned char version;
    unsigned char flag3;
    unsigned char additional_length;
    unsigned char flag4;
    unsigned char flag5;
    unsigned char flag6;
    char vendor_identification[8];
    char product_identification[16];
    char product_revision_level[4];
    char vendor_specific[20];
    unsigned short rsvd;
    unsigned short version_descriptor1;
    unsigned short version_descriptor2;
    unsigned short version_descriptor3;
    
};

struct response00_inquirylun{
    unsigned char flag1;
    unsigned char pagecode;
    unsigned char rsvd1;
    unsigned char page_length;
    unsigned char firstpagecode;
    unsigned char secondpagecode;
    unsigned char thirdpagecode;
    unsigned char rsvd2;//my adding
};

struct response80_inquirylun{
    unsigned char flag1;
    unsigned char pagecode;
    unsigned char rsvd;
    unsigned char page_length;
    char product_serial_number;
};

struct response83_inquirylun{
    unsigned char flag1;
    unsigned char pagecode;
    unsigned char rsvd1;
    unsigned char page_length;
    unsigned char flag2;
    unsigned char flag3;
    unsigned char rsvd2;
    unsigned char identifier_length;
    char* identifier;
};

struct response_readcapacity{
    unsigned int logical_block_address;
    unsigned int block_length_in_byte;
};

struct mode_parameter_header{
    unsigned char mode_data_length;
    unsigned char medium_type;
    unsigned char device_specific_parameter;
    unsigned char block_descriptor_length;
    unsigned int number_of_blocks;
    unsigned int block_length;
};

struct dis_reconnect_page{
    unsigned char pagecode;
    unsigned char page_length;
    unsigned char buffer_full_ratio;
    unsigned char buffer_empty_ratio;
    unsigned short bus_inactivity_limit;
    unsigned short disconnect_time_limit;
    unsigned short connect_time_limit;
    unsigned short maximum_burst_size;
    unsigned char flag;
    unsigned char rsvd;
    unsigned short first_burst_size;
};

struct format_device_mode_page{
    unsigned char pagecode;
    unsigned char page_length;
    unsigned short tracks_per_zone;
    unsigned short alternate_sectors_per_zone;
    unsigned short alternate_tracks_per_zone;
    unsigned short alternate_tracks_per_logical_unit;
    unsigned short sectors_per_track;
    unsigned short data_bytes_per_physical_sector;
    unsigned short interleave;
    unsigned short track_skew_factor;
    unsigned short cylinder_skew_factor;
    unsigned char  flag;
    unsigned char rsvd[3];
};

struct rigid_disk_geometry_mode_page{
    unsigned char pagecode;
    unsigned char page_length;
    unsigned char number_of_cylinder[3];
    unsigned char number_of_heads;
    unsigned char starting_cylinder_writer_precompensation[3];
    unsigned char starting_cylinder_reduced_write_current[3];
    unsigned short device_step_rate;
    unsigned char landing_zone_cylinder[3];
    unsigned char rsvd1;
    unsigned char rotational_offset;
    unsigned char rsvd2;
    unsigned short medium_totaltion_rate;
    unsigned char rsvd3;
    unsigned char rsvd4;
};

struct caching_mode_page{
    unsigned char pagecode;
    unsigned char page_length;
    unsigned char flag1;
    unsigned char flag2;
    unsigned short disable_pre_fetch_transfer_length;
    unsigned short minimum_pre_fetch;
    unsigned short maximum_pre_fetch;
    unsigned short maximum_pre_fetch_ceiling;
    unsigned char flag3;
    unsigned char number_of_cache_segments;
    unsigned short cache_segment_size;
    unsigned char rsvd;
    unsigned char non_cache_segment_size[3];
};

struct control_mode_page{
    unsigned char pagecode;
    unsigned char page_length;
    unsigned char flag1;
    unsigned char flag2;
    unsigned char flag3;
    unsigned char flag4;
    unsigned short reay_aer_holdoff_period;
    unsigned short busy_timeout_period;
    unsigned short extended_self_test_completion_time;
};

struct exeptions_control_mode_page{
    unsigned char pagecode;
    unsigned char page_length;
    unsigned char flag1;
    unsigned char flag2;
    unsigned int  interval_timer;
    unsigned int report_count;
};

//mesglen
#define MESG_HEAD_LEN 12

//mesg_head:opcode
#define READ_DISK 0x00
#define WRITE_DISK 0x01
#define RESPONSE_READ 0x10
#define RESPONSE_WRITE 0x11

//mesg_head:status
#define WRITE_CMND 0x00
#define DATA_OUT_CMND 0x10

#define WRITE_RESPONSE_SUCESS 0x01
#define WRITE_RESPONSE_FAILD 0x00
#define DATA_OUT_RESPONSE_SUCCESS 0x11
#define DATA_OUT_RESPONSE_FAILD 0x10

//opcode :0x00-read  0x01-write  0x10-response of read 0x11-response of write
/*status:for write  write_10 0x10 data_out 0x10 response: false 0x*0 sucess 0x*1 */
struct mesg_head{
    uint32_t cmd;
    uint32_t length;
    uint32_t error;
    uint32_t para1;
    uint32_t para2;
};

//////////////////////BC_EU/////////////////////////
const uint32_t MSG_BC_EU_INIT_DATA = 0x00010010;
const uint32_t MSG_BC_EU_INIT_DATA_ACK = 0x00010011;

const uint32_t MSG_BC_EU_MAP = 0x00010020;
const uint32_t MSG_BC_EU_MAP_ACK = 0x00010021;

const uint32_t MSG_BC_EU_SHUFFLE = 0x00010030;
const uint32_t MSG_BC_EU_SHUFLLE_ACK = 0x00010031;

const uint32_t MSG_BC_EU_REDUCE = 0x00010040;
const uint32_t MSG_BC_EU_REDUCE_ACK = 0x00010041;

const uint32_t MSG_BC_EU_DELETE_DATA = 0x00010050;
const uint32_t MSG_BC_EU_DELETE_DATA_ACK = 0x00010051;
///////////////////////////////////////////////////////
#define NO_BLOCK 0x00
#define ODD_BLOCK 0x01
#define EVEN_BLOCK 0x10
#define ALL_BLOCK 0x11
//stat: no_page 0x00  odd_page 0x01 even_page 0x10 all_page 0x11*
/*struct DISK_cmnd{
    struct iscsi_scsi_cmd_hdr i_o_cmnd;
    class Buffermanager i_o_buff;
    unsigned char state;
    unsigned short cmnd_len;
    unsigned int cmnd_addr; 
};*/
struct data_list
{
    int len;
    char* ptr;
    struct data_list* next_data_block;
};


#endif
