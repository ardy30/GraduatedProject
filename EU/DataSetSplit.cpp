/*
 * =====================================================================================
 *
 *       Filename:  DataSetSplit.c
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
#include "DataSetSplit.h"

DataSetSplit::DataSetSplit()
{

}
DataSetSplit::DataSetSplit(string name, string instanceid,string path,string splitname, int splitnumber)
{
    this -> Name = name;
    this -> InstanceID = instanceid;
    this -> Path = path;
    this -> Splitname = splitname;
    this -> Splitnumber = splitnumber;
}

DataSetSplit::DataSetSplit(string name, string instanceid,string splitname, int splitnumber)
{
    this -> Name = name;
    this -> InstanceID = instanceid;
    this -> Splitname = splitname;
    this -> Splitnumber = splitnumber;
}
