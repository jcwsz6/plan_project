#pragma once
#include "planning_base.h" // 包含自己写的头文件用引号
#include "car.h"

/* ----------------------------------- 锥桶 ----------------------------------- */
class Cone { //锥桶
  public:
    Cone() = default;
    Cone(const double& pos_x, const double& pos_y, const double& R = 20.0);
    void showCone(); // 绘制锥桶

  public:
    unique_ptr<Point> p_center; //锥桶中心
    double r = 20.0; //锥桶半径
};
