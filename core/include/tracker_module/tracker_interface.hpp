/*
 * @Author: Liu Weilong
 * @Date: 2021-01-09 20:11:40
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-01-12 07:46:56
 * @Description:  TrackerInterface 确定接口和底层算法
 */
#pragma once


#include <iostream>

#include "opencv2/core/core.hpp"
#include "eigen3/Eigen/Eigen"


#include "frame.hpp"

#define _S_FRONT_END_SELF_ namespace front_end_self{
#define _E_FRONT_END_SELF_ };


_S_FRONT_END_SELF_

class TrackerInterface
{
    public:
    
    using Transform   = Eigen::Matrix<double,4,4>;
    using Rotation    = Eigen::Matrix<double,3,3>;
    using Translation = Eigen::Vector3d; 

    virtual void Match( Frame & img_pre, Frame & img_cur,
                       const Transform & predict_tf, Transform & tf) =0;   
    Frame frame_pre;
};
_E_FRONT_END_SELF_