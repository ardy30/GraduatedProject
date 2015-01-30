/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/15/12 15:21:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yushiyao (), yushiyaogg@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include "head.h"
#include "DataSet.h"
#include "BusinessController.h"

int main(int argc, char **argv)
{

    string InstanceID = "Kmeans";
    string data_path = "./data";
    string lib1 = "lib1.so";
    vector<string> para1;
    string lib2 = "lib2.so";
    vector<string> para2;
    vector<string> result;
    
    fstream ReadFile;  
    string point1; 
    string point2; 
    ReadFile.open(data_path.c_str(),ios::in);//以只读的方式读取文件  
    if(ReadFile.fail())//文件打开失败:返回-1
    {   
        return -1;  
    }   
    else//文件存在  
    {   
        getline(ReadFile,point1);
        getline(ReadFile,point2);
        para1.push_back(point1);
        para1.push_back(point2);
           
    }   

    class BusinessController *BC = new BusinessController(InstanceID);
    class DataSet *DataSet1 = BC -> InitialDataSet(data_path);
    DataSet1 -> caching = 1;
    DataSet *DataSet2 = DataSet1->map(lib1,para1);
    DataSet *DataSet3 = DataSet2->shuffle();
    DataSet *DataSet4 = DataSet3 -> map(lib2,para2);
    result = DataSet4 -> reduce();
    for(int i = 0 ;i < 20 ;i ++)
    {
        DataSet2 -> arg.clear();
        DataSet2->arg= result;
        for(int i = 0 ; i < result.size();i ++)
        {
            cout << result.at(i)<< endl;
        }
        cout <<"==================="<< endl;
        result = DataSet4 -> reduce();
    }
}
