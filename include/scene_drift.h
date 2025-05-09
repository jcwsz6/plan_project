#pragma once
#include "scene_base.h"

class DriftPoint : public SceneBase{ //定点漂移
public:
  DriftPoint();
  void showScene();
  bool planning_process() override;

public:
  unique_ptr<Cone> cone; //锥桶
  int lap = 0; //绕桩的圈数
};

class DriftParking : public SceneBase{ //漂移停车
public:
  DriftParking();
  void showScene();
  bool planning_process() override;

public:
  unique_ptr<CarObsStatic> ob1;
  unique_ptr<CarObsStatic> ob2;
  double park_length = 0.0; //库的长度
};