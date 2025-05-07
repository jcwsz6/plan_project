#pragma once
#include "scene_straight.h"
#include "scene_obs_pass.h"

enum PlanType {
  //直行
  StraightStopOBSType, //停障
  StraightStationType, //停靠站点
  StraightFollowType, //跟车 
  StraightCrosswalkType, //通过斑马线

  //绕障
  ObsPassStaticType, //静态障碍物
  ObsPassOvertakeType, //超车
  ObsPassMeetingType, //会车
};