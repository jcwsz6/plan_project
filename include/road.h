#pragma once
#include "traffic.h"

/* ---------------------------------- 道路基类 ---------------------------------- */
class RoadBase {
  public:
    virtual ~RoadBase() = default; //虚析构
    virtual void showRoad() = 0; //显示道路
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