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
#include "Epoll.h"
#include "S_Agent.h"
class BusinessController
{
public:
        int DataNumber;//用于给DataSet编号
        BusinessController(string In_ID);
        class DataSet* Original_DataSet;
        class Tool tool;
        vector<string> Container;//申请到的资源
        vector<class S_Agent*> BCAgentList;
        class S_Agent* MasterAgent;
        class Epoll m_epoll;
        string InstanceID;
        DataSet* InitialDataSet(string);
        string IntToString(int);
        int ApplyResource(int);
        char MasterIP[];
};




#endif
