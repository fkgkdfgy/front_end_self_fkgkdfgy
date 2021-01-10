/*
 * @Author: Liu Weilong
 * @Date: 2021-01-09 20:11:40
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-01-10 08:54:24
 * @Description:  TrackerInterface 确定接口和底层算法
 */
#pragma once


#include <iostream>

#include "opencv2/core/core.hpp"
#include "Eigen/Eigen"

#define _S_FRONT_END_SELF_ namespace front_end_self{
#define _E_FRONT_END_SELF_ };


_S_FRONT_END_SELF_

class TrackerInterface
{
    public:
    
    using Transform   = Eigen::Matrix<double,4,4>;
    using Rotation    = Eigen::Matrix<double,3,3>;
    using Translation = Eigen::Vector3d; 

    Match(const cv::Mat & img_l,const cv::Mat & img_r,Transform & tf);    


};
_E_FRONT_END_SELF_