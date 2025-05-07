#include "planning_base.h"

/* ------------------------------------ 点 ----------------------------------- */
Point::Point(const double& p_x, const double& p_y, const double& p_theta, const double& p_R)
        : x(p_x), y(p_y), thetaP(p_theta), Rp(p_R) {

}

void Point::showPoint() {
    setfillcolor(BLACK);
    solidcircle(x, y, r);
}

void Point::pointMove(const double& speed_x, const double& speed_y) {
    x += speed_x;
    y += speed_y;
}

void Point::pointTurn(const Point& center, const double& turn_speed) {
    thetaP += turn_speed; // turn_speed > 0, 为绕着center逆时针行驶；<0 则为绕着center顺时针行驶
    x = Rp * cos(thetaP) + center.x;
    y = -Rp * sin(thetaP) + center.y; // 坐标系 x右、y下为正
}

double Point::distanceTo(const Point& p) const {
    return hypot(x - p.x, y - p.y); // 返回平方根的函数
}

double Point::thetaTo(const Point& p) const { // 类中点相对于p点的角度
    if (x >= p.x && y == p.y) { // 正x轴方向，包括重合
        return 0.0; 
    } else if (x < p.x && y == p.y) { // 负x轴方向
        return PI;
    }else if (x == p.x && y < p.y) { // 负y轴方向
        return PI / 2;
    } else if (x == p.x && y > p.y) { // 正y轴方向
        return -PI / 2;
    } else if (x > p.x) { // 第一、四象限
        return -atan((y - p.y) / (x - p.x)); // 考虑eaxyX坐标系方向，右下，取负号
    } else if (x < p.x) { // 第二、三象限
        return PI - atan((y - p.y) / (x - p.x));
    }
    return 0.0;
}

/* ----------------------------------- 向量 ----------------------------------- */
Vec2d::Vec2d(const double &new_x, const double &new_y, const bool &flag) : x(new_x), y(new_y) { //通过两个值构造向量，flag用于区分另一个构造函数

}

Vec2d::Vec2d(const Point &p_start, const Point &p_end) { //通过两个点构造向量
    x = p_end.x - p_start.x;
    y = -(p_end.y - p_start.y); //向量的值切换为y轴向上的直角坐标
}

Vec2d::Vec2d(const double &length, const double &angele){ // 通过长度和方向构造向量
    x = length * cos(angele);
    y = length * sin(angele);
}

double Vec2d::length() {
    return hypot(x, y);
}

double Vec2d::crossProd(const Vec2d& other) const {
    return x * other.y - y * other.x;
}

double Vec2d::dotProd(const Vec2d& other) const {
    return x * other.x + y * other.y;
}

/* ---------------------------------- 全局函数 ---------------------------------- */
void delay(const int& time) { //延时函数
    clock_t now = clock();
    while (clock() - now < time) {
        
    }
}

double normalizeAngle(const double& theta) { // 角度修正到[-PI, PI]之间
    double theta_new =  fmod(theta + PI, 2 * PI); // fmod函数返回两个浮点数相除的余数,这里取余数结果在[-2PI, 2PI)之间
    if (theta_new < 0.0) {
        theta_new += 2 * PI; //返回[0, 2PI)
    }
    return theta_new - PI; //然后减去PI，使得结果在[-PI, PI)之间
}

void correctAngleError(double& target_theta, const double& delta_theta) { // 修正角度误差
    if (delta_theta > 0.0) {
        if (target_theta > 0.0) {
            target_theta -= delta_theta;
        } else if (target_theta < 0.0) {
            target_theta += delta_theta;
        }
    }
}

double disPointToLine(const Point& p, const Point& p_start, const Point& p_end) { // 计算点到直线的距离
    Vec2d line(p_start, p_end);
    Vec2d line_p(p_start, p);

    if (line.length() < 1e-6) {
        return line_p.length();
    }

    return fabs(line.crossProd(line_p)) / line.length();
}