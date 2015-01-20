/*
 * =====================================================================================
 *
 *       Filename:  Socket_I_O_Buff.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/23/12 17:26:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include "Socket_I_O_Buff.h"

Socket_I_O_Buff::Socket_I_O_Buff()
{
    head = NULL;
    rear = NULL;    
}

Socket_I_O_Buff::~Socket_I_O_Buff()
{
    struct data_list* temp;
    while(head != NULL)
    {
        temp = head;
        delete(head->ptr);
        head = head-> next_data_block;
        delete temp;
    }
    rear = NULL;
}

int Socket_I_O_Buff::new_buff(int len)
{
    struct data_list* temp = new(struct data_list);
    temp -> len = len;
    temp -> ptr = new(char[len]);
    temp -> next_data_block = NULL;
    if(head == NULL)
    {
        head = temp;
        rear = temp;
    }
    else
    {
        rear-> next_data_block = temp;
        rear = rear -> next_data_block;
    }
    return 0;
}

int Socket_I_O_Buff::delete_buff()
{
    struct data_list* temp;
    while(head != NULL)
    {
        temp = head;
        delete(head -> ptr);
        head = head-> next_data_block;
        delete temp;
    }
    rear = NULL;
    return 0;
}

int Socket_I_O_Buff::add_buff(void * ptr,int len)
{
    struct data_list* temp = new(struct data_list);
    temp -> len = len;
    if((temp-> ptr = new( char[len])) == NULL)
    {
        cout << "new buff error"<<endl;
        return -1;
    }
    memcpy(temp-> ptr, ptr, len);
    temp -> next_data_block = NULL;
    if(head == NULL)
    {
        head = temp;
        rear = temp;
    }
    else
    {
        rear-> next_data_block = temp;
        rear  = rear -> next_data_block;
    }
    return 0;
}
