#pragma once
#include <memory>
#include "planning_base.h" // 包含自己写的头文件用引号

/* ----------------------------------- 状态机 ---------------------------------- */
enum Shift { // 档位
    m_D, // 前进档
    m_N, // 空档
    m_R, // 后退档
    m_P, // 驻车档
};

enum TurnDirection { // 方向
    TurnRight, // 右转
    TurnLeft, // 左转
};

/* ----------------------------------- 车基类 ---------------------------------- */
class CarBase {
public:
    virtual ~CarBase() = default;
    void initCar(const double& pos_x, const double& pos_y, const double& heading,
                 const double& width, const double& length); // 初始化车辆
    void updatePmidf(); //更新前中点xy值
    void updatePmidr(); //更新后中点xy值
    void updatePmid(); //更新几何中点xy值
    void showCar(const COLORREF& color); //绘制车辆矩形
    void showCircle(); //绘制轨迹线
    void coutInfo(); //打印车辆信息

    void moveStraightStep(); //单帧直行
    void carTurnStep(); //单帧转向
    
    void updateXYva(); //更新车辆速度及加速度信息
    void updateStraightInfo(); //更新直行信息

public:
    double car_width = 80.0;
    double car_length = 160.0;

    unique_ptr<Point> plf; //左前点
    unique_ptr<Point> plr; //左后点
    unique_ptr<Point> prf; //右前点
    unique_ptr<Point> prr; //右后点
    unique_ptr<Point> p_center; //转向中心点

    unique_ptr<Point> pmidf; //前轮中心点
    unique_ptr<Point> pmidr; //后轮中心点
    unique_ptr<Point> pmid; //几何中心点

    double Rmin = 100.0; //最小转弯半径
    double Rof = 0.0; //外前半径
    double Ror = 0.0; //外后半径
    double Rif = 0.0; //内前半径
    double Rir = 0.0; //内后半径

    double R0; //半斜长，自转半径
    double theta0; //atan(car_length/car_width)

    double speed = 0.0; //合速度，负代表前进，正代表后退
    double speed_x = 0.0; //x方向速度，负代表向左，正代表向右
    double speed_y = 0.0; //y方向速度，负代表向上，正代表向下

    double a = 0.0; //合加速度
    double a_x = 0.0; //x方向加速度
    double a_y = 0.0; //y方向加速度

    double delta_theta = 0.0; //角速度，负代表顺时针，正代表逆时针
    double delta_theta_rot = 0.0; //自转角速度，负代表顺时针，正代表逆时针 
    double heading_theta = 0.0; //航向角，0时竖直向上，负代表向左偏航，正代表向右偏航

    int Gear = m_P; // 档位
};

/* ----------------------------------- 一般车 ---------------------------------- */
class CarNormal : public CarBase {
public:
    CarNormal(const double& pos_x, const double& pos_y, const double& heading = 0.0,
              const double& width = 80.0, const double& length = 160.0);
};

