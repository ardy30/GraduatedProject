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
#include <map>
#include <signal.h>

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

using namespace std;

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
#define DISK_BLOCK_NUMBER 1000
#define BLOCK_SIZE 512
#define MAX_TRANSFER_BLOCK_NUMBER 16
//session type
#define NORMAL 0
#define DISCOVERY 1

//
#define BHS_LEN 48
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


//mesglen
#define MESG_HEAD_LEN 16

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
    unsigned char opcode1;
    unsigned char write_status;
    unsigned short len;
    unsigned int addr;
    unsigned int itt;
    unsigned int NewOpcode;
};

#define NO_BLOCK 0x00
#define ODD_BLOCK 0x01
#define EVEN_BLOCK 0x10
#define ALL_BLOCK 0x11

#define MAPOP         0x00000000
#define MAPOP_ACK     0x00000001
#define SHUFFLEOP     0x00000010
#define SHUFFLEOP_ACK 0x00000011
#define INITOP        0x00000100
#define INITOP_ACK    0x00000101
#define REDUCE        0x00000110
#define REDUCE_ACK    0x00000111
#define HEARTBEAT     0x10000000


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
