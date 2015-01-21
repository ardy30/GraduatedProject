/*
 * =====================================================================================
 *
 *       Filename:  tool.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/12/14 19:48:41
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include "Tool.h"

string Tool::IntToString(int number)
{
    stringstream ss;
    ss << number;
    string temp = ss.str();
    return temp;
}
