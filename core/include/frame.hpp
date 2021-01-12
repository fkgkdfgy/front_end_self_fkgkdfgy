/*
 * @Author: Liu Weilong
 * @Date: 2021-01-09 19:50:36
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-01-12 07:57:28
 * @Description: 
 */

#include <iostream>
#include "opencv2/core/core.hpp"

#define _S_FRONT_END_SELF_ namespace front_end_self{
#define _E_FRONT_END_SELF_ };

_S_FRONT_END_SELF_

class Frame
{
    public:

    Frame(cv::Mat img):img_(img){}
    
    const cv::Mat GetImage()const {return img_;}
    


    private:
    cv::Mat img_;
};




_E_FRONT_END_SELF_