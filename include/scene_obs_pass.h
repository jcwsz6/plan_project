#pragma once
#include "scene_base.h"

/* ---------------------------------- 静态绕障 ---------------------------------- */
class StaticObs : public SceneBase {
public:
  StaticObs();
  void showScene(); // 显示场景
  bool planning_process() override; // 整个过程

public:
  unique_ptr<Cone> cone; //锥桶
  double start_dis = 200.0;  //开始绕障的距离
};

/* ---------------------------------- 超车绕障 ---------------------------------- */
class OvertakeObs : public SceneBase {
public:
  OvertakeObs();
  void showScene(); // 显示场景
  void obsMoveStep(); // 障碍物移动
  bool planning_process() override; // 整个过程

public:
  unique_ptr<CarNormal> carObs; //前障碍车
  double start_dis = 0.0;  //开始绕障的距离
};

/* ---------------------------------- 会车绕障 ---------------------------------- */
class MeetingObs : public SceneBase {
public:
  MeetingObs();
  void obsMoveStep(); // 障碍物移动
  void showScene(); // 显示场景
  bool planning_process() override; // 整个过程

public:
  unique_ptr<CarNormal> carObs; //障碍车
  double start_dis = 200.0;  //开始绕障的距离
};
