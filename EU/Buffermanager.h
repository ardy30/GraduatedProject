/*
 * =====================================================================================
 *
 *       Filename:  Buffermanager.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/16/12 15:47:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yushiyaogg (), yushiyaogg@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#ifndef _BUFFERMANAGER_H
#define _BUFFERMANAGER_H
#include "head.h"
class Buffermanager
{
    public:
        Buffermanager();
        Buffermanager(int );
        ~Buffermanager();
        int new_buff(int );
        //int new_buff(int,void*);
        int delete_buff();
        int front_truncation(int);
        int buff_catenate(class Buffermanager*, class Buffermanager*);
       int add_buff(void* ,int );
       int add_buff(int ,void*,int);
        unsigned char* bufferptr;
        int buff_length;
    private:

};


#endif
