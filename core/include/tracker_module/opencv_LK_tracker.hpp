/*
 * @Author: Liu Weilong
 * @Date: 2021-01-12 07:40:18
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-01-13 08:08:55
 * @Description: 
 */
#include "tracker_interface.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/tracking.hpp"
#define _S_FRONT_END_SELF_ namespace front_end_self{
#define _E_FRONT_END_SELF_ };
using namespace std;

_S_FRONT_END_SELF_
class OpenCVLKTrackerOptions
{
    public:

    OpenCVLKTrackerOptions(const std::string & config_path)
    {
        cv::FileStorage fin(config_path.c_str(),CV_STORAGE_READ);
        fin["OpenCVLKTracker.PyramidLevel"]>>pyramid_level_;
        fin["OpenCVLKTracker.TemplateSize"]>>template_size_;
        fin["OpenCVLKTracker.MinDistance"]>>min_distance_;
        fin["OpenCVLKTracker.MaxPts"]>>max_pts_;

        cout<<"OpenCVLKTracker.PyramidLevel : "<<pyramid_level_<<endl;
        cout<<"OpenCVLKTracker.TemplateSize : "<<template_size_<<endl;
        cout<<"OpenCVLKTracker.MinDistance : " <<min_distance_<<endl;
        cout<<"OpenCVLKTracker.MaxPts : "<<max_pts_;
        
    }
    int pyramid_level_;
    int template_size_;
    int min_distance_;
    int max_pts_;
};

class OpenCVLKTracker:public TrackerInterface
{
    public:

    OpenCVLKTracker(const std::string & config_path):options_(config_path){}
    
    virtual void Track(Frame & img_pre,Frame & img_cur,
                       const Transform & predict_tf, Transform & tf);
    
    void StereoCompute(Frame & frame);


    private:
    
    void TrackWithOpticalLK(Frame & img_pre, Frame & img_cur);
    
    OpenCVLKTrackerOptions options_;
    

};


void OpenCVLKTracker::Track( Frame & img_pre, Frame & img_cur,
                             const Transform & predict_tf, Transform & tf)
{
    if(img_pre.GetCornersUVL().size()==0)
        StereoCompute(img_pre);

    TrackWithOpticalLK(img_pre,img_cur);

    Eigen::Matrix4d tf = Eigen::Matrix4d::Identity();
    PnP(img_pre.GetCornersXYZ(),img_cur.GetCornersUVL(),tf);
    
    

   
    
}

void OpenCVLKTracker::StereoCompute(Frame & frame)
{
    TrackWithOpticalLK(frame,frame);
    
    
}

void OpenCVLKTracker::TrackWithOpticalLK(Frame & img_pre, Frame & img_cur)
{
    std::vector<unsigned char> status;
    std::vector<float> err;
    cv::calcOpticalFlowPyrLK(img_pre.GetImageL(),img_cur.GetImageR(),
                             img_pre.GetCornersUVL(),img_cur.GetCornersUVL(),
                             status,err,cv::Size(options_.template_size_,options_.template_size_),
                             options_.template_size_);
    CheckAndReduce(img_pre.GetCornersUVL(),status);
    CheckAndReduce(img_cur.GetCornersUVL(),status);

    err.resize(options_.max_pts_,0.0);
    status.resize(options_.max_pts_,0);
    EpipolarCheck(img_pre.GetCornersUVL(),img_cur.GetCornersUVL(),status,err);
    CheckAndReduce(img_pre.GetCornersUVL(),status);
    CheckAndReduce(img_cur.GetCornersUVL(),status);
}

_E_FRONT_END_SELF_
