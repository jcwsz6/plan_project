#include "scene_straight.h"

/* ----------------------------------- 停障 ----------------------------------- */
StraightStopOBS::StraightStopOBS() {
  road0 = make_unique<RoadNormal>();
  cone = make_unique<Cone>(SWIDTH / 2.0, SWIDTH / 4.0, 50);

  car0 = make_unique<CarNormal>(SWIDTH / 2.0, SHEIGHT - 70.0);
  car0->speed_y = -5.0;

  car0->coutInfo();
  showScene();
  system("pause");
}

void StraightStopOBS::showScene() {
  BeginBatchDraw(); // 开始批量绘图
  cleardevice(); // 清屏

  road0->showRoad();
  cone->showCone(); // 显示障碍物，比基类多的
  car0->showCar(BLACK);

  EndBatchDraw(); // 结束批量绘图
  delay(DELAYTIME); // 延时
}

bool StraightStopOBS::planning_process() { // 规划过程
  double stop_line = cone->p_center->y + cone->r + safe_dis;
  uniformAccByDis(car0->pmidf->y - stop_line, 0.0);
  return true;
}
