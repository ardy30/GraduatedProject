/*
 * =====================================================================================
 *
 *       Filename:  DataSet.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/12/14 06:11:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#ifndef _DATASET_H_
#define _DATASET_H_
#include "head.h"
#include "BusinessController.h"
class DataSet
{
     public:   
        string name;//InstanceID_Data+time
        string path;//源数据文件
        //string IP[5];//数据分配到的机器地址
        //vector<class DataSetSplit> Data;
        string lib;//可执行文件名
        vector<string> arg;//参数
        DataSet*  next;//执行计划的下一个单元
        DataSet*  prev;//执行计划的上一个单元
        int ReferCount;
        int IsInitial;//是否申请到资源
        int State;
        class BusinessController  *BC;
        DataSet();
        DataSet* map(string lib, vector<string> arg);
        DataSet* shuffle();
        vector<string> reduce();
    
};


#endif
