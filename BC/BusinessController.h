/*
 * =====================================================================================
 *
 *       Filename:  BusinessController.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/12/14 06:05:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#ifndef _BUSINESSCONTROLLER_H
#define _BUSINESSCONTROLLER_H
#include "head.h"
#include "DataSet.h"
#include "Tool.h"
class BusinessController
{
public:
        int DataNumber;
        BusinessController(string In_ID);
        class DataSet* Original_DataSet;
        class Tool tool;
        vector<string> Container;//申请到的资源
        string InstanceID;
        DataSet* InitialDataSet(string);
        string IntToString(int);
};




#endif
