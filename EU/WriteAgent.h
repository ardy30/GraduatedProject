/*
 * =====================================================================================
 *
 *       Filename:  WriteAgent.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/16/12 16:08:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yushiyao (), yushiyaogg@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#ifndef _WRITEAGENT_H
#define _WRITEAGENT_H

#include "head.h"
#include "Socket_I_O_Buff.h"
class WriteAgent
{
    public:
        int write_socket(int fd, class Socket_I_O_Buff*);
        //return value:-1---failure  1---success but not completed  2---success and completed
        WriteAgent();
        ~WriteAgent();
        //int write_type;
        int write_len;
    private:
};
#endif
