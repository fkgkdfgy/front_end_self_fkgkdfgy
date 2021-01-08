/*
 * @Author: Liu Weilong
 * @Date: 2021-01-06 19:10:28
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-01-08 08:30:45
 * @FilePath: /front_end_self_fkgkdfgy/core/include/displayer.hpp
 * @Description: 
 */
#include <vector>
#include <iostream>
#include <mutex>
#include <condition_variable>

#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#define _S_IMG_DISPLAYER_ namespace image_displayer {
#define _E_IMG_DISPLAYER_ };


_S_IMG_DISPLAYER_

using namespace std;
class ImgDisplayer
{
    public:
    
    using features = vector<cv::Point2d>;
    // interface 
    void Run();
    void ShowCurImg();
    void SetCurImg(const cv::Mat & img_l);
    void SetCurImg(const cv::Mat & img_l, const features & feature_l);
    void SetCurImg(const cv::Mat & img_l, const features & feature_2, const  cv::Mat & img_r , const features & features_r);
    void SetStop();
    
    
    private:
    bool stop_ = false;
    cv::Mat img_cur_;
    std::mutex img_lock_;
    std::condition_variable img_cond_var_;
    
};


void ImgDisplayer::ShowCurImg()
{
    while(!stop_)
    {
        {
            std::unique_lock<std::mutex> locker(img_lock_);
            img_cond_var_.wait(locker);
            cv::imshow("tracking",img_cur_);
        }
        
    }
}


void ImgDisplayer::SetCurImg( const cv::Mat & img_l)
{
    std::lock_guard<std::mutex> locker(img_lock_);
    img_cur_ = img_l.clone();
    img_cond_var_.notify_one();
}
void ImgDisplayer::SetCurImg(const cv::Mat & img_l, const features & feature_l)
{
    std::lock_guard<std::mutex> locker(img_lock_);
    img_cur_ = img_l.clone();
    for(auto & feature:feature_l)
    cv::circle(img_cur_,feature,3,cv::Scalar(255,0,0),-1);
    img_cond_var_.notify_one();
}

// TODO 添加前后跟踪和上下对比
void ImgDisplayer::SetCurImg(const cv::Mat & img_l, const features & feature_l, const  cv::Mat & img_r , const features & features_r)
{
    std::lock_guard<std::mutex> locker(img_lock_);
    img_cur_ = img_l.clone();
    for(auto & feature:feature_l)
    cv::circle(img_cur_,feature,3,cv::Scalar(255,0,0),0);
    img_cond_var_.notify_one();
}

_E_IMG_DISPLAYER_