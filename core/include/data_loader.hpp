/*
 * @Author: Liu Weilong
 * @Date: 2021-01-05 08:26:18
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-01-09 16:38:31
 * @Description: 
 */
#pragma once

#include <fstream>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"


#define _S_FRONT_END_SELF_ namespace front_end_self{
#define _E_FRONT_END_SELF_ };

using namespace std;

_S_FRONT_END_SELF_

class DataLoader
{
    public:
    DataLoader(const string & all_path);
    
    bool LoadIndex(const string & index_file, 
                   const string & image_path_left,
                   const string & image_path_right);
    bool LoadImg(cv::Mat & img_l , cv::Mat & img_r);

    private:
    
    const string all_path_;

    string index_file_;
    string image_path_left_;
    string image_path_right_;
    
    vector<string> image_path_left_array_;
    vector<string> image_path_right_array_;
    vector<double> image_time_array_;
    unsigned int cur_index_ = 0;
};

DataLoader::DataLoader(const string & all_path):all_path_(all_path)
{
    cv::FileStorage config_fin;
    config_fin.open(all_path_.c_str(),CV_STORAGE_READ);
    if(!config_fin.isOpened())
    {
        std::cerr<<"[ERROR]: DataLoader cannot open the config file!"<<std::endl;
        abort();
    }
    config_fin["DataLoader.IndexFile"]>>index_file_;
    config_fin["DataLoader.ImagePath.Left"]>>image_path_left_;
    config_fin["DataLoader.ImagePath.Right"]>>image_path_right_;

    LoadIndex(index_file_,image_path_left_,image_path_right_);
    

    cout<<"DataLoader.IndexFile : "<<index_file_.c_str()<<endl;
    cout<<"DataLoader.ImagePath.Left : "<<image_path_left_.c_str()<<endl;
    cout<<"DataLoader.ImagePath.Right : "<<image_path_right_.c_str()<<endl;

}


bool DataLoader::LoadIndex(const string & index_file, 
                           const string & image_path_left,
                           const string & image_path_right)
{
    ifstream fin;
    fin.open(index_file.c_str());
    if(!fin.is_open())
    {
        std::cerr<<"[ERROR]: DataLoader cannot load the index!"<<std::endl;
        abort();
        return false;
    }
    image_time_array_.reserve(5000);
    image_path_left_array_.reserve(5000);
    image_path_right_array_.reserve(5000);
    while(!fin.eof())
    {
        string s;
        getline(fin,s);
        if(!s.empty())
        {
            stringstream ss;
            ss << s;
            image_path_left_array_.push_back(image_path_left + "/" + ss.str() + ".png");
            image_path_right_array_.push_back(image_path_right + "/" + ss.str() + ".png");
            double t;
            ss >> t;
            image_time_array_.push_back(t/1e9);
        }
    }
    return true;
}

bool DataLoader::LoadImg(cv::Mat & img_l , cv::Mat & img_r)
{
    if(cur_index_>=image_path_left_array_.size())
    return false;
    img_l = cv::imread(image_path_left_array_[cur_index_],CV_LOAD_IMAGE_UNCHANGED);
    img_r = cv::imread(image_path_right_array_[cur_index_],CV_LOAD_IMAGE_UNCHANGED);
    cur_index_ ++;
    return true;
}


_E_FRONT_END_SELF_