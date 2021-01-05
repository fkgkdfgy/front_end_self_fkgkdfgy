/*
 * @Author: Liu Weilong
 * @Date: 2021-01-03 10:04:02
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-01-05 08:20:56
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

#define _S_FRONT_END_SELF namespace front_end_self{
#define _E_FRONT_END_SELF };

_S_FRONT_END_SELF
class FrontEndSelfOptions;
class FrontEndSelf
{
    public:

    FrontEndSelf(const string & config_path)
    {
        
    }
    void Run();
    
    private:

    bool ReadImg(cv::Mat & img_l,cv::Mat & img_r);
    void ComputeStereoMatching(cv::Mat & img_l,cv::Mat & img_r);
    
    FrontEndSelfOptions front_end_self_options_;

    cv::Mat pre_img_,cur_img_,forw_img_;
    cv::Mat Rrl_;
    vector<cv::Point2d> pre_uv_, cur_uv_,forw_uv_;
    bool first_img_ = false;
    
};

class ImgDisplayer
{
    public:
    
    using features = vector<cv::Point2d>;
    // interface 
    void Run();
    void ShowCurImg();
    void SetCurImg(cv::Mat & img_l);
    void SetCurImg(cv::Mat & img_l, features & feature_l);
    void SetCurImg(cv::Mat & img_l,cv::Mat & img_r, features & feature_l, features & feature_r);

    cv::Mat img_cur;
    std::mutex img_lock_;
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

_E_FRONT_END_SELF

