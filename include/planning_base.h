#pragma once //防止头文件重复
#include <iostream>
#include <graphics.h>
#include <cmath>
#include <ctime>
#include <string>
#include <vector>
using namespace std;

/*********************全局变量************************* */
constexpr auto SWIDTH = 1200.0; // 窗口宽
constexpr auto SHEIGHT = 1200.0; // 窗口宽
constexpr auto PI = 3.14159265358979323846; // 圆周率
constexpr auto SHOWCIRCLE = false; // 是否绘制轨迹
constexpr auto DELAYTIME = 20; // 间隔时间,ms
constexpr auto CHANGETIME = 1000; // 换挡时间,ms

class Point{
public:
    Point() = default;
    Point(const double& p_x, const double& p_y, const double& p_theta = 0.0, const double& p_R = 0.0);
    void showPoint(); // 绘制点
    void pointMove(const double& speed_x, const double& speed_y); // 点的移动
    void pointTurn(const Point& center, const double& turn_speed); // 点绕center旋转，turn_speed为角速度
    double distanceTo(const Point& p) const; // p点到类中点的距离

public:
    double x;
    double y;
    double thetaP = 0.0; // 角度
    double Rp = 0.0; // 旋转半径
    int r = 5;  // 绘制半径
};

/* ---------------------------------- 延时函数 ---------------------------------- */
void delay(const int& time); //延时函数






