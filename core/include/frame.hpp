/*
 * @Author: Liu Weilong
 * @Date: 2021-01-09 19:50:36
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-01-13 07:55:44
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

    Frame(cv::Mat img_l,cv::Mat img_r):img_l_(img_l),img_r_(img_r){}
    
    cv::Mat & GetMask() {return mask_;}

    const cv::Mat & GetImageL()const {return img_l_;}
    const cv::Mat & GetImageR()const {return img_r_;}
    
    std::vector<cv::Point2f> & GetCornersUVL(){return pts_uv_l_;}
    std::vector<cv::Point2f> & GetCornersUVR(){return pts_uv_r_;}
    std::vector<cv::Point3f> & GetCornersUnProject(){return pts_un_;}
    std::vector<cv::Point3f> & GetCornersXYZ(){return pts_xyz_;}

    private:
    cv::Mat img_l_;
    cv::Mat img_r_;
    cv::Mat mask_;
    std::vector<cv::Point2f> pts_uv_l_;
    std::vector<cv::Point2f> pts_uv_r_;
    std::vector<cv::Point3f> pts_un_;
    std::vector<cv::Point3d> pts_xyz_;
    std::vector<bool>        pts_tracking_;
};





_E_FRONT_END_SELF_