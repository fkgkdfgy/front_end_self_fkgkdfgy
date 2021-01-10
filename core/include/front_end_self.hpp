/*
 * @Author: Liu Weilong
 * @Date: 2021-01-03 10:04:02
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-01-09 20:05:57
 * @Description: 
 */

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;

#define _S_FRONT_END_SELF_ namespace front_end_self{
#define _E_FRONT_END_SELF_ };

_S_FRONT_END_SELF_
class FrontEndSelfOptions;
class FrontEndSelf
{
    public:

    FrontEndSelf(const string & config_path)
    {
        cv::FileStorage fin(config_path,CV_STORAGE_READ);
        string front_end_config_path;
        fin["FrontEndSelf.OptionsPath"]>>front_end_config_path;
        LoadOptions(front_end_config_path);
    }
    void Run();
    
    private:

    bool LoadOptions(const string & front_end_config_path);
    bool ReadImg(cv::Mat & img_l,cv::Mat & img_r);
    void ComputeStereoMatching(cv::Mat & img_l,cv::Mat & img_r);
    
    FrontEndSelfOptions front_end_self_options_;

    cv::Mat pre_img_,cur_img_,forw_img_;
    cv::Mat Rrl_;
    vector<cv::Point2d> pre_uv_, cur_uv_,forw_uv_;
    bool first_img_ = false;
    
};

class FrontEndSelfOptions
{
    public:
    string cam0_path_,cam1_path_;
    string config_path_;
    int max_corner_;
    int min_distance_;
    bool equalize_;
};

void FrontEndSelf::Run()
{
    cv::Mat img_r,img_l;
    if(!ReadImg(img_l,img_r))
    {
        std::cout<<"[WARNING]there might be something wrong with the image loading!"<<std::endl;
        std::abort();   
    }
    
    // TODO 图像灰度预处理

    if(!first_img_)
    {
        cv::goodFeaturesToTrack(img_l,cur_uv_,200,0.01,30);
        
        first_img_ = true;
    }
    ComputeStereoMatching(img_l,img_r);
}

_E_FRONT_END_SELF_

