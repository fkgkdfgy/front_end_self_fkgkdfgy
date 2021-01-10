/*
 * @Author: Liu Weilong
 * @Date: 2021-01-06 19:10:28
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-01-09 19:48:22
 * @FilePath: /front_end_self_fkgkdfgy/core/include/displayer.hpp
 * @Description: 
 */


#pragma once

#include <vector>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <atomic>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#define _S_FRONT_END_SELF_ namespace front_end_self{
#define _E_FRONT_END_SELF_ };


_S_FRONT_END_SELF_

using namespace std;
class ImgDisplayer
{
    public:
    
    using features = vector<cv::Point2d>;
    // interface 
    void Run();
    // void ShowCurImg();
    void SetCurImg(const cv::Mat & img_l);
    void SetCurImg(const cv::Mat & img_l, const features & feature_l);
    void SetCurImg(const cv::Mat & img_l, const features & feature_2, 
                   const cv::Mat & img_r, const features & features_r,
                   const std::vector<std::pair<int,int>> & matches);
    
    private:
    cv::Mat img_cur_;
    std::mutex img_lock_;
    std::condition_variable img_cond_var_;
};



// TODO 猜测 imshow 不要放在主线程
void ImgDisplayer::Run()
{

    cv::imshow("tracking", img_cur_);
    cv::waitKey(10);    
}

void ImgDisplayer::SetCurImg( const cv::Mat & img_l)
{
    img_cur_ = img_l.clone();
}

void ImgDisplayer::SetCurImg(const cv::Mat & img_l, const features & feature_l)
{
    img_cur_ = img_l.clone();
    for(auto & feature:feature_l)
    cv::circle(img_cur_,feature,3,cv::Scalar(255,0,0),-1);
}

// TODO 添加前后跟踪和上下对比
void ImgDisplayer::SetCurImg(const cv::Mat & img_l, 
                             const features & features_l, 
                             const cv::Mat & img_r , 
                             const features & features_r,
                             const std::vector<std::pair<int,int>> & matches)
{
    auto tmp_img_1 = img_l.clone();
    for(auto & feature:features_l)
    cv::circle(tmp_img_1,feature,3,cv::Scalar(255,0,0),-1);
    
    auto tmp_img_2 = img_r.clone();
    for(auto & feature:features_r)
    cv::circle(tmp_img_2,feature,3,cv::Scalar(0,0,255),-1);
    
    tmp_img_1.push_back(tmp_img_2);

    img_cur_ = tmp_img_1.clone();
}

_E_FRONT_END_SELF_