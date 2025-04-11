#pragma once
#include "scene_base.h"

class StraightStopOBS : public SceneBase { //直行障碍物停车
  public:
    StraightStopOBS();
    void showScene();
    bool planning_process() override; //纯虚函数需要加override重写关键字
  
  public:
    unique_ptr<Cone> cone; //锥桶
    double safe_dis = 50.0; //安全距离
};

class StraightStation : public SceneBase { //停靠站点
  public:
    StraightStation();
    void showScene(); //显示场景,继承来的
    bool planning_process() override; //纯虚函数需要加override重写关键字

  public:
    unique_ptr<Point> station; //停靠站点
    int stop_time = 3; //停车时间,单位为秒
};

class StraightFollow : public SceneBase { //跟车
  public:
    StraightFollow();
    void showScene();//显示场景,继承来的
    bool planning_process() override; //纯虚函数需要加override重写关键字

  public:
    unique_ptr<CarNormal> carObs; //障碍车
    double safe_dis = 120.0; //安全距离
};

class StraightCrosswalk : public SceneBase { //通过斑马线
public:
  StraightCrosswalk();
  bool peopleInCross(); //判断斑马线上是否有人
  void showScene(); //显示场景,继承来的
  bool planning_process() override; //纯虚函数需要加override重写关键字

public:
  int people_num = 5; //斑马线上的人数
  vector<unique_ptr<Person>> people; //斑马线上的行人
  double speedlimit_cross = -3.0; //斑马线上的限速
  double safe_dis = 7.0; //安全距离
};

