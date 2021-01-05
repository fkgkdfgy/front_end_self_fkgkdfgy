/*
 * @Author: Liu Weilong
 * @Date: 2021-01-03 10:49:41
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-01-05 08:26:04
 * @Description: 
 */
#include "front_end_self.hpp"

_S_FRONT_END_SELF

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










_E_FRONT_END_SELF