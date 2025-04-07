#include "road.h"

/* ---------------------------------- 一般道路 ---------------------------------- */
RoadNormal::RoadNormal(const double& r_width) {
  Rwidth = r_width;
  left_boundary = SWIDTH / 2 - Rwidth;
  right_boundary = SWIDTH / 2 + Rwidth;
}

void RoadNormal::showRoad() {
  setlinestyle(PS_SOLID, 4); // 设置线型及宽度
  setlinecolor(BLACK);
  line(left_boundary, 0, left_boundary, SHEIGHT); // 左边界
  line(right_boundary, 0, right_boundary, SHEIGHT); // 右边界
}