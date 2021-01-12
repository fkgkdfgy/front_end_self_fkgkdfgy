/*
 * @Author: Liu Weilong
 * @Date: 2021-01-12 07:40:18
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-01-12 07:56:14
 * @Description: 
 */
#include "tracker_interface.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#define _S_FRONT_END_SELF_ namespace front_end_self{
#define _E_FRONT_END_SELF_ };


_S_FRONT_END_SELF_

class OpenCVKLTTracker:public TrackerInterface
{
    public:
    virtual void Match(Frame & img_pre,Frame & img_cur,
                       const Transform & predict_tf, Transform & tf) ;
    std::vector<cv::Point2f> pts_pre_;

};

void OpenCVKLTTracker::Match( Frame & img_pre, Frame & img_cur,
                             const Transform & predict_tf, Transform & tf)
{
    
    cv::goodFeaturesToTrack(img_pre.GetImage(),)
}

_E_FRONT_END_SELF_
