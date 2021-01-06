/*
 * @Author: Liu Weilong
 * @Date: 2021-01-06 19:10:28
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-01-06 19:18:16
 * @FilePath: /front_end_self_fkgkdfgy/core/include/displayer.hpp
 * @Description: 
 */
#include <vector>
#include <iostream>
#include <mutex>
#include <condition_variable>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"


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

    cv::Mat img_cur_;
    std::mutex img_lock_;
    std::condition_variable img_cond_var_;
};


void ImgDisplayer::ShowCurImg()
{
    cv::imread(img_cur_);
}