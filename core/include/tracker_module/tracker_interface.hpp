/*
 * @Author: Liu Weilong
 * @Date: 2021-01-09 20:11:40
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-01-13 08:04:33
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
    using features    = std::vector<cv::Point2f>;

    virtual void Track( Frame & img_pre, Frame & img_cur,
                        const Transform & predict_tf, Transform & tf) =0;   
    virtual Eigen::Matrix4d GetPredictPose() = 0;

    static void EpipolarCheck(const features & f_uv_1, const features & f_uv_2, 
                               std::vector<bool> & status, std::vector<float> & err);
    static void Triangulate(const features & f_uv_1,const features & f_uv_2,
                            std::vector<cv::Point3f> & f_xyz);
    static void PnP(const std::vector<cv::Point3f> & f_xyz_1 , const features & f_uv_2,
                    Transform & result_tf, Transform predict_tf = Transform::Identity());

    template<typename T>
    void CheckAndReduce(std::vector<T> & T_array,const std::vector<unsigned char> & status);


};



_E_FRONT_END_SELF_