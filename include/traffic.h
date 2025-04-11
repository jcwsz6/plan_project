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

class Person { //行人
public:
  Person() = default;
  Person(const double& pos_x, const double& pos_y);
  void personMove(); // 行人移动
  void showPerson(); // 绘制行人

public:
  unique_ptr<Point> p_center; //行人中心点，这是个指针，需要在构造函数中初始化
  double r = 20.0; //行人半径
  double speed = 0.0; //行人速度
};
