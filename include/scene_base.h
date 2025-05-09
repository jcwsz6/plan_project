#pragma once
#include "car.h"
#include "road.h"

enum LaneChangeType {
  singleType, //单移线
  doubleType, //双移线
};

/* ---------------------------------- 场景基类 ---------------------------------- */
class SceneBase {
  public:
    virtual ~SceneBase() = default; //虚析构函数
    virtual void showScene(); //虚函数，显示场景
    virtual void obsMoveStep() {} //虚函数, 障碍物移动
    virtual bool planning_process() = 0; //整个过程，纯虚函数

    /* ----------------------------------- 直行 ----------------------------------- */
    void uniformStraight(const double& total_s); //直行,行驶指定距离，total_s为正，为累计行驶距离
    void uniformAccBySpeed(const double& target_speed_y); //直行，已知加速度，行驶至指定的速度，匀加(减)速直线运动
    void uniformAccByDis(const double& dis, const double& target_speed_y); //直行，行驶指定的距离时速度达到制定速度，匀加（减）速直线运动
    void uniformAccByTime(const double& target_speed_y, const double& target_time); //直行，在目标时间内达到目标速度，匀加（减）速直线运动

    /* ----------------------------------- 转向 ----------------------------------- */
    void carTurn(const int& turn_state, const double& R, const double& total_theta); //转向，已知半径和角度， total_theta为正，为累计转向角度
    void laneChange(const Point& target_point, const int& type, const double& s = 0.0); //变道，单移线或双移线

    /* ----------------------------------- 漂移 ----------------------------------- */
    void driftStraight(const double& total_s); //直线漂移（自转+直线运动），只考虑指定的位置
    void driftStraightByTheta(const double& total_theta); //直线漂移（自转+直线运动），只考虑转角
    void driftTurnByRot(const double& total_theta, const Point& center); //漂移转向（自转+公转），只考虑自转转角
    void driftTurnByRev(const double& total_theta, const Point& center); //漂移转向（自转+公转），只考虑公转转角

  public:
    unique_ptr<RoadBase> road0; //道路父类指针
    unique_ptr<CarBase> car0; //车辆父类指针
    double speedlimit = -6.0; //道路限速,可正负
};