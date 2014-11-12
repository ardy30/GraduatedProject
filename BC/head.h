/*
 * =====================================================================================
 *
 *       Filename:  head.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/15/12 09:45:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yushiyao (), yushiyaogg@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#ifndef _HEADER_H
#define _HEADER_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <utility>

#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <byteswap.h>
#include <sstream>
#include <fstream>

using namespace std;

#define MAXEPOLL 100
#define SA struct sockaddr
#define TCP_SOCKET_SIZE 64*1024
#define DISK_BLOCK_NUMBER 128*1024
#define MESG_HEAD_LEN 20
#define BLOCK_SIZE 512
#define SERV_PORT 32600
#define FILE_LINE 500
/*  
//read return value
#define READ_ERROR -1
#define READ_END    0
#define READ_BLOCK  1
#define READ_SUCCESS 2

//write return value
#define WRITE_ERROR -1
#define WRITE_BLOCK  1
#define WRITE_SUCCESS 2
*/


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

//////////////////////BC_MASTER//////////////////////////
const uint32_t MSG_BC_MASTER_APPLY_SOURCE =0x00020010;
const uint32_t MSG_BC_MASTER_APPLY_SOURCE_ACK = 0x00020011;
///////////////////////////////////////////////////////////
///////////DataSet State///////////////
const uint32_t NOT_BUILDING = 0;
const uint32_t BUILDING = 1;
////////////DataSet IsInitial////////////
const uint32_t UNINIT = 0;
const uint32_t INIT = 1;

#endif
