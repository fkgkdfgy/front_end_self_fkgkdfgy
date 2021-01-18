/*
 * @Author: Liu Weilong
 * @Date: 2021-01-10 08:54:48
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-01-18 07:59:56
 * @Description: 
 */
#pragma once

#include <iostream>
#include <string>

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/detail/distortion_model.hpp"
#include "opencv2/core/core.hpp"
#include "eigen3/Eigen/Eigen"

using namespace std;

#define _S_FRONT_END_SELF_ namespace front_end_self{
#define _E_FRONT_END_SELF_ };

_S_FRONT_END_SELF_

class CameraModel
{
    public:
    using UV    = Eigen::Vector2d;
    using Point = Eigen::Vector3d;
    virtual bool LoadCameraModel(const string & camera_path) =0;
    virtual bool ProjectToPixel(const Point& point, UV & uv) =0;
    virtual bool UnprojectFromPixel(const UV & uv, Point & point) =0;
};

class PinholeCameraConfig
{
    public:

    PinholeCameraConfig(const string & config_path);

    const cv::Mat GetKl() const{return K_l_;};
    const cv::Mat GetKr() const{return K_r_;};
    const cv::Mat GetTrl()const = delete; 
    const cv::Mat GetD()  const = delete;

    bool init_ = false;
    bool left_ ;
    bool stereo_;
    bool calibrate_;
    cv::Mat K_l_, K_r_, P_l_, P_r_, R_l_, R_r_, D_l_, D_r_;
    cv::Mat M1l_,M1r_,M2l_,M2r_;
};


class PinholeCameraModel:public CameraModel
{
    public:
    PinholeCameraModel(const string & camera_config);
    
    virtual bool LoadCameraModel(const string & camera_config) override;
    
    virtual bool ProjectToPixel(const Point& point, UV & uv) override;
    virtual bool UnprojectFromPixel(const UV & uv, Point & point) override;
    PinholeCameraConfig * camera_config_;
};

PinholeCameraConfig::PinholeCameraConfig(const string & config_path)
{
    cv::FileStorage fin(config_path.c_str(),CV_STORAGE_READ);

    fin["Camera.bStereo"]>>stereo_;
    fin["Camera.bCalibrate"]>>calibrate_;
    
    if(calibrate_)
    {
        fin["LEFT.K"] >> K_l_;
        fin["RIGHT.K"] >> K_r_;

        fin["LEFT.P"] >> P_l_;
        fin["RIGHT.P"] >> P_r_;

        fin["LEFT.R"] >> R_l_;
        fin["RIGHT.R"] >> R_r_;

        fin["LEFT.D"] >> D_l_;
        fin["RIGHT.D"] >> D_r_;

        int rows_l = fin["LEFT.height"];
        int cols_l = fin["LEFT.width"];
        int rows_r = fin["RIGHT.height"];
        int cols_r = fin["RIGHT.width"];

        if(K_l_.empty() || K_r_.empty() || P_l_.empty() || P_r_.empty() ||
           R_l_.empty() || R_r_.empty() || D_l_.empty() || D_r_.empty() ||
                rows_l==0 || rows_r==0 || cols_l==0 || cols_r==0)
        {
            cerr << "ERROR: Calibration parameters to rectify stereo are missing!" << endl;
            abort();
        }

        cv::initUndistortRectifyMap(K_l_,D_l_,R_l_,P_l_.rowRange(0,3).colRange(0,3),
                                    cv::Size(cols_l,rows_l),CV_32F,M1l_,M2l_);
        cv::initUndistortRectifyMap(K_r_,D_r_,R_r_,P_r_.rowRange(0,3).colRange(0,3),
                                    cv::Size(cols_r,rows_r),CV_32F,M1r_,M2r_);
    }

    std::cout<<"print out the type of config matrix "<< K_l_.type()<<endl; 
}

PinholeCameraModel::PinholeCameraModel(const string & camera_config)
{
    camera_config_ = new PinholeCameraConfig(camera_config);
}

_E_FRONT_END_SELF_