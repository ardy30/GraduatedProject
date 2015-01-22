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



int DataSet::InitDataSetSplit(string path, int startline, int endline, string name ,string InstanceID, string SplitName, int SplitNumber)
{
    
    class DataSetSplit* ptr = new DataSetSplit(name,InstanceID,path,SplitName,SplitNumber);
    Data.insert(pair<string, class DataSetSplit*>(name,ptr));

    fstream ReadFile;  
    int n=1;  
    string tmp;  
    ReadFile.open(path.c_str(),ios::in);//以只读的方式读取文件  
    if(ReadFile.fail())//文件打开失败:返回-1
    {   
        return -1;  
    }   
    else//文件存在  
    {   
        while(getline(ReadFile,tmp))  
        {  
            if(n >= startline&& n <= endline) 
            {
                ptr-> Data.push_back(pair<string,string>(tool.IntToString(n),tmp));
            }
            else if(n > endline)
                break;
            n++;  
        }   
    }   
    return 0;
}

int DataSet::SeeDataSet(string name)
{
    map<string, class DataSetSplit*>::iterator it;
    it = Data.find(name);
    class DataSetSplit *temp = it -> second;
    for(int i = 0;i < temp -> Data.size(); i ++)
    {
        cout << "key :"<< temp -> Data.at(i).first<< "    ";
        cout << "value :"<< temp -> Data.at(i).second<< endl;
        if(i == temp -> Data.size() -1)
            cout << "size = "<< i+1 << endl;
    }
}

int DataSet::ReturnDataSet(string name, vector<pair<string,string> > &DataSet)
{
    map<string, class DataSetSplit*>:: iterator it;
    it = Data.find(name);
    if(it != Data.end())
    {
        DataSet = it -> second -> Data;
        return 0;
    }
    else 
        return -1;

}
int DataSet::ReturnDataSetptr(string name, class DataSetSplit* &DataSet)
{
    map<string,class DataSetSplit*>::iterator it;
    it = Data.find(name);
    if(it != Data.end())
    {
        DataSet = it -> second;
        return 0;
    }
    else
        return -1;
}

class DataSet g_DataSet;

