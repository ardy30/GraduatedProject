/*
 * =====================================================================================
 *
 *       Filename:  DataSetSplit.h
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
#ifndef _DATASETSPLIT_H_
#define _DATASETSPLIT_H_
class DataSetSplit
{
     public: 
         
        string Name;//InstanceID_Data+time

        string InstanceID;
        string Path;//源数据文件

        string Splitname;
        int Splitnumber;
        //string IP[5];//数据分配到的机器地址
        vector<pair<string,string> > Data;
        
        
        string lib;//可执行文件名
        vector<string> arg;//参数

       DataSetSplit(); 
       DataSetSplit(string,string,string,string,int); 
       DataSetSplit(string,string,string,int); 
   
};


#endif
