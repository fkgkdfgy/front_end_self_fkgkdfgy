/*
 * @Author: Liu Weilong
 * @Date: 2021-01-06 07:53:31
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-01-09 19:38:36
 * @Description: 
 */

#include <thread>

#include "displayer.hpp"
#include "data_loader.hpp"

using namespace std;

int main()
{
    front_end_self::DataLoader dl("./config/all_path.yaml");
    cv::Mat img_l,img_r;

    front_end_self::ImgDisplayer id;
    
    while(dl.LoadImg(img_l,img_r))
    {
        cout<<"show the rows"<<img_l.rows<<endl;
        cout<<"show the cols"<<img_l.cols<<endl;
        // cv::imshow("imgL",img_l);
        // cv::imshow("imgR",img_r);
        // cv::waitKey(5);
        id.SetCurImg(img_l,front_end_self::ImgDisplayer::features(),
                     img_r,front_end_self::ImgDisplayer::features(),
                     vector<pair<int,int>>());
        id.Run();
    }
}