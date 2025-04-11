#pragma once
#include "traffic.h"

/* ---------------------------------- 道路基类 ---------------------------------- */
class RoadBase {
public:
  virtual ~RoadBase() = default; //虚析构
  virtual void showRoad() = 0; //显示道路
  virtual double getUpLine() {
    return 0.0;
  }
  virtual double getMidLine() {
    return 0.0;
  }
  virtual double getDownLine() {
    return 0.0;
  }
public:
  double Rwidth = 200.0; //车道宽，或半宽
  double up_boundary = 0.0; //道路上限
  double down_boundary = 0.0; //道路下限
  double left_boundary = 0.0; //道路左限
  double right_boundary = 0.0; //道路右限
};

/* ---------------------------------- 一般道路 ---------------------------------- */
class RoadNormal : public RoadBase {
public:
  RoadNormal(const double& r_width = 200.0);
  void showRoad() override; //显示道路，重写
};

/* ---------------------------------- 斑马线 ---------------------------------- */
class RoadCrosswalk : public RoadBase {
public:
  RoadCrosswalk(const double& r_width = 200.0);
  void showRoad() override; //显示道路，重写
  double getUpLine() {
    return this->up_line;
  }
  double getMidLine() {
    return this->mid_line;
  }
  double getDownLine() {
    return this->down_line;
  }

public:
  double up_line = 0.0; //斑马线上限
  double mid_line = 0.0;  //斑马线中心线
  double down_line = 0.0; //斑马线下限
  double disRec = 20.0; //间距
};
