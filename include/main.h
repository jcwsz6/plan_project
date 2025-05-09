#pragma once
#include "scene_straight.h"
#include "scene_obs_pass.h"
#include "scene_park.h"
#include "scene_drift.h"

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

  //泊车
  ParkReverse1Type, //倒车入库1
  ParkReverse2Type, //倒车入库2
  ParkParallelType, //侧方停车

  //漂移
  DriftPointType, //定点漂移
  DriftParkType, //漂移泊车
};