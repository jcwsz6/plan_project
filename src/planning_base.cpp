#include "planning_base.h"

/************点****************/
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

/* ---------------------------------- 延时函数 ---------------------------------- */
void delay(const int& time) {
    clock_t now = clock();
    while (clock() - now < time) {
        
    }
}