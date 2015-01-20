/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/16/12 17:38:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include <iostream>
#include <string.h>
#include <map>
#include <stdlib.h>
using namespace std;
int function(int &ptr)
{
    cout << "ptr = "<<ptr<<endl;

    ptr = ptr -3;
    if(ptr == 0)
    cout << "ptr = "<<ptr<<endl;
}

int main()
{
    cout <<"the size of void* :"<< sizeof(void*) <<endl;
    cout <<"the size of int :"<< sizeof(int) <<endl;
    cout <<"the size of long :"<< sizeof(long) <<endl;
    cout <<"the size of long long :"<< sizeof(long long) <<endl;
}

