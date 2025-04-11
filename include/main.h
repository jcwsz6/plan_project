#pragma once
#include "scene_straight.h"

enum PlanType {
  //直行
  StraightStopOBSType, //停障
  StraightStationType, //停靠站点
  StraightFollowType, //跟车 
  StraightCrosswalkType, //通过斑马线
};