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
#include "DataSetSplit.h"
#include "Tool.h"
class DataSet
{
     public: 
         
       map<string,class DataSetSplit*> Data;
       class Tool tool;

       int InitDataSetSplit(string path, int startline, int endline,string name, string InstanceID, string SplitName, int SplitNumber);
       
       
       
       int SeeDataSet(string name);
       int ReturnDataSet(string name, vector<pair<string,string> > &DataSet);
};

extern class DataSet g_DataSet;

#endif
