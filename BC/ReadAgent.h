/*
 * =====================================================================================
 *
 *       Filename:  ReadAgent.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/16/12 15:55:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yushiyao (), yushiyaogg@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#ifndef _READAGENT_H
#define _READAGENT_H

#include "head.h"
#include "Buffermanager.h"
class ReadAgent
{
    public:
        int read_socket(int fd, class Buffermanager* );
        //return value: -1 ---failure  0---connect is failed 1----success but no complete 2---success and complete
        ReadAgent();
        ~ReadAgent();
        bool read_complete;
       // int read_type;//0----BHS  1---AHS 2---DATA
       int read_len;
    private:
};

#endif 
