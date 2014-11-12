/*
 * =====================================================================================
 *
 *       Filename:  DataSet.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/12/14 06:42:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include "DataSet.h"

DataSet::DataSet()
{

}

DataSet* DataSet::map(string lib, vector<string> arg)
{
    class DataSet *temp = new DataSet();
    this -> next = temp;
    temp -> prev = this;
    return temp;
}

DataSet* DataSet::shuffle()
{
}

vector<string> DataSet::reduce()
{

}
