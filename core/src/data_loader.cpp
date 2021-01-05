/*
 * @Author: Liu Weilong
 * @Date: 2021-01-05 08:26:32
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-01-05 08:31:48
 * @Description: 
 */
#include <fstream>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "omp.h"

#define _S_FRONT_END_SELF namespace front_end_self{
#define _E_FRONT_END_SELF };

using namespace std;

_S_FRONT_END_SELF

class DataLoader
{
    public:
    DataLoader(const string & all_path);
    
    bool LoadName();
    bool LoadImg();

    private:
    const string all_path;
    ifstream fin;
};







_E_FRONT_END_SELF