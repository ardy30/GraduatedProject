/*
 * =====================================================================================
 *
 *       Filename:  BusinessController.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/12/14 06:32:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include "BusinessController.h"
#include "DataSet.h"
BusinessController::BusinessController(string In_ID)
{
    this -> InstanceID = In_ID;
    DataNumber = 0;
}

DataSet* BusinessController::InitialDataSet(string path)
{   
    class DataSet *temp = new DataSet();
    temp -> path = path;
    
    temp -> name = this -> InstanceID + tool.IntToString(DataNumber);
    DataNumber ++; 
    Original_DataSet = temp;
    temp -> BC = this;
    temp -> next = NULL;
    temp -> prev = NULL;
    return temp;
}
