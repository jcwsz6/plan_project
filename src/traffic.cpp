#include "traffic.h" // 包含自己写的头文件用引号

/* ----------------------------------- 障碍物 ---------------------------------- */
Cone::Cone(const double& pos_x, const double& pos_y, const double& R) : r(R) {
  p_center = make_unique<Point>(pos_x, pos_y);
}

void Cone::showCone() {
  setfillcolor(RGB(255, 127, 0)); // 设置填充颜色为橙色
  solidcircle(p_center->x, p_center->y, r);
}

Person::Person(const double& pos_x, const double& pos_y) {
  p_center = make_unique<Point>(pos_x, pos_y); //初始化，指针指向创建对象
}

void Person::personMove() {
  p_center->x += speed;
}

void Person::showPerson() {
  setfillcolor(YELLOW);
  fillcircle(p_center->x, p_center->y, r);
}

CarObsStatic::CarObsStatic(const double& pos_x, const double& pos_y,
  const double& heading, const double& width, const double& length) {
  initCar(pos_x, pos_y, heading, width, length);

  topPos = min(min(plf->y, prf->y), min(plr->y, prr->y));
  bottomPos = max(max(plf->y, prf->y), max(plr->y, prr->y));
  leftPos = min(min(plf->x, prf->x), min(plr->x, prr->x));
  rightPos = max(max(plf->x, prf->x), max(plr->x, prr->x));
  cout << "topPos = " << topPos << " bottomPos = " << bottomPos << " leftPos = " << leftPos << 
          " rightPos = " << rightPos << endl;
}
