/*
 * =====================================================================================
 *
 *       Filename:  Buffermanager.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/20/12 09:23:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yushiyao (), yushiyaogg@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include "Buffermanager.h"

Buffermanager::Buffermanager()
{
    bufferptr = NULL;
    buff_length = 0;
}

Buffermanager::Buffermanager(int len)
{
    buff_length = len;
    bufferptr = new(unsigned char[len]);
}

Buffermanager::~Buffermanager()
{
    delete bufferptr;
    bufferptr = NULL;
}

int Buffermanager::new_buff(int len)
{
    if((bufferptr = new (unsigned char[len])) == NULL)
    {
        cout <<"new error"<<endl;
        return -1;
    }
    buff_length = len;
    return 0;
}

/*int Buffermanager::new_buff(int len,void* ptr)
{
    bufferptr = new(unsigned char[len]);
    memcpy(bufferptr,ptr,len);
    buff_length = len;

}*/
int Buffermanager::delete_buff()
{
    if(this->bufferptr != NULL)
        delete bufferptr;
    this->bufferptr = NULL;
    buff_length = 0;
    return 0;
}

int Buffermanager::front_truncation(int len)
{
    if(len > buff_length)
    {
        cout << "front_truncation error"<< endl;
        return -1;
    }
    else if(len == buff_length)
    {
        delete bufferptr;
        bufferptr = NULL;
        buff_length = 0;
        return 0;
    }
    
    unsigned char* temp;
    temp = new(unsigned char[buff_length - len]);
    memcpy(temp,bufferptr + len,buff_length -len);
    delete bufferptr;
    bufferptr = temp;
    buff_length = buff_length - len;
    return 0;
}

int Buffermanager::add_buff(void* ptr ,int len)
{
    if(this->bufferptr == NULL)
    {
        this->bufferptr = new(unsigned char[len]);
        buff_length = len;
        memcpy(bufferptr,ptr,len);
        return 0;
    }
    else
    {
        unsigned char* temp;
        temp = new(unsigned char[len + buff_length]);
        memcpy(temp,bufferptr,buff_length);
        memcpy(temp+buff_length, ptr,len);
        delete bufferptr;
        bufferptr = temp;
        buff_length = len + buff_length;
    }
}
int Buffermanager::add_buff(int offset,void* ptr,int len)
{
    if(this ->buff_length < offset + len)
    {
        cout <<"out of range"<<endl;
        return -1;
    }
    memcpy(this->bufferptr + offset,ptr,len);
    return 0;
}

int Buffermanager::buff_catenate(class Buffermanager* buff1, class Buffermanager* buff2)
{
    if(bufferptr != NULL)
    {
        delete bufferptr;
        bufferptr = NULL;
        buff_length = 0;
    }
    if((bufferptr = new(unsigned char[buff1->buff_length + buff2->buff_length])) == NULL)
    {
        return -1;
    }
    buff_length = buff1->buff_length + buff2->buff_length;
    memcpy(bufferptr, buff1->bufferptr, buff1->buff_length);
    memcpy(bufferptr + buff1->buff_length, buff2->bufferptr, buff2->buff_length);
    return 0;

}
