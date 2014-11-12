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
#include <string>
#include <vector>
#include <map>
#include "DataSet.h"
class BusinessController
{
public:
        BusinessController(string In_ID);
        class DataSet* Original_DataSet;
        vector<string> Container;//申请到的资源
        string InstanceID;
        DataSet* InitialDataSet(string);
};




#endif
