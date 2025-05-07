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

/* ---------------------------------- 停靠站点 ---------------------------------- */
StraightStation::StraightStation() {
  road0 = make_unique<RoadNormal>();
  station = make_unique<Point>(SWIDTH / 2.0, SHEIGHT / 2.0);
  car0 = make_unique<CarNormal>(SWIDTH / 2.0, SHEIGHT - 70.0);
  car0->speed_y = -5.0;

  car0->coutInfo();
  showScene();
  system("pause");
}

void StraightStation::showScene() {
  BeginBatchDraw(); // 开始批量绘图
  cleardevice(); // 清屏

  road0->showRoad();
  station->showPoint(); // 显示停靠站点
  car0->showCar(BLACK);

  EndBatchDraw(); // 结束批量绘图
  delay(DELAYTIME); // 延时
}

bool StraightStation::planning_process() { // 规划过程
  uniformAccByDis(car0->pmid->y - station->y, 0.0); // 减速进站
  delay(stop_time * 1000); // 停车等待
  uniformAccByTime(speedlimit, 2.0); // 加速出站
  return true;
}

/* ---------------------------------- 跟车 ---------------------------------- */
StraightFollow::StraightFollow() {
  road0 = make_unique<RoadNormal>();
  carObs = make_unique<CarNormal>(SWIDTH / 2.0, SHEIGHT / 2.0, 0.0);
  car0 = make_unique<CarNormal>(SWIDTH / 2.0, SHEIGHT - 70.0);
  carObs->speed_y = -2.0;
  car0->speed_y = -5.0;

  carObs->coutInfo();
  car0->coutInfo();
  showScene();
  system("pause");
}

void StraightFollow::showScene() {
  BeginBatchDraw(); // 开始批量绘图
  cleardevice(); // 清屏

  road0->showRoad();
  carObs->showCar(RED);
  car0->showCar(BLACK);

  EndBatchDraw(); // 结束批量绘图
  delay(DELAYTIME); // 延时
}

bool StraightFollow::planning_process() {
  double dis = car0->pmidf->y - carObs->pmidr->y; //初始间距
  double delta_dis = dis - safe_dis; // 初始间距-目标间距
  double delta_speed_y = car0->speed_y - carObs->speed_y; // 速度差
  if (dis <= 0.0 || delta_dis <= 0.0 || delta_speed_y > 0.0) {
    return false;
  }

  car0->a_y = pow(delta_speed_y, 2) / (2 * delta_dis);
  while (car0->pmidr->y > 0.0) {
    car0->moveStraightStep();
    carObs->moveStraightStep();

    if (fabs(car0->speed_y - carObs->speed_y) > fabs(car0->a_y)) {
      car0->speed_y += car0->a_y;
    } else {
      car0->speed_y = carObs->speed_y;
      car0->a_y = 0.0;
    }
    showScene();
  }
  car0->coutInfo();
  return true;
}

StraightCrosswalk::StraightCrosswalk() {
  road0 = make_unique<RoadCrosswalk>();
  car0 = make_unique<CarNormal>(SWIDTH / 2.0, SHEIGHT - 70.0);
  car0->speed_y = -4.0;
  
  for (int i = 0; i < people_num; ++i) {
    unique_ptr<Person> ps = make_unique<Person>(road0->right_boundary + 20.0 * (i * 3 + 1), 
                                                road0->getMidLine());
    ps->speed = -2; //向左边走
    people.emplace_back(move(ps));
  }
  car0->coutInfo();
  showScene();
  system("pause");
}

bool StraightCrosswalk::peopleInCross() {
  for (auto& i : people) {
    if (i->p_center->x >= road0->left_boundary - i->r && i->p_center->x <= road0->right_boundary + i->r) {
      return true;
    }
  }
  return false;
}

void StraightCrosswalk::showScene() {
  BeginBatchDraw(); //开始批量绘图
  cleardevice(); //清屏

  road0->showRoad();

  car0->showCar(BLACK);
  car0->moveStraightStep();
  car0->speed_y += car0->a_y;

  for (auto& i : people) {
    i->showPerson();
    i->personMove();
  }

  EndBatchDraw(); //结束批量绘图
  delay(DELAYTIME); //延时
}

bool StraightCrosswalk::planning_process() {
  //进入斑马线场景，一律先减速
  double dis = car0->pmidf->y - road0->getDownLine();
  car0->a_y = pow(car0->speed_y, 2) / (2 * dis);
  
  while (dis > 0) { //当车头还未到达斑马线时
    dis = car0->pmidf->y - road0->getDownLine();
    if (!peopleInCross()) { //没有人进入斑马线
      if (car0->speed_y >= speedlimit_cross) { //当速度小于限速时，保持匀速
        car0->a_y = 0.0; //当速度小于限速时，加速度为0
      }
    } else { //有人进入斑马线
      if (dis <= safe_dis) {
        car0->speed_y = 0.0; //当距离小于安全距离时，速度为0
        car0->a_y = 0.0; //当距离小于安全距离时，加速度为0
        break;
      }
    }
    cout << "dis: " << dis << ", car_speed_y: " << car0->speed_y << ", car_a_y: " << car0->a_y << endl;
    showScene();
  }

  //限速通过斑马线
  while (car0->pmidr->y > road0->getUpLine()) { //当车处于斑马线区间，即车尾还没通过斑马线上界
    double dis = car0->pmidr->y - road0->getUpLine();
    if (!peopleInCross()) { //没有人进入斑马线
      if (car0->speed_y > speedlimit_cross) { //没达到斑马线的限速
        car0->a_y = (pow(car0->speed_y, 2) - pow(speedlimit_cross, 2)) / (2 * dis); 
      } else {
        car0->a_y = 0.0; //当速度达到限速时，加速度为0
      }
    }
    cout << "car_speed_y: " << car0->speed_y << ", car_a_y: " << car0->a_y << endl;
    showScene();
  }

  //过了斑马线，继续加速，直到达到道路限速
  while (car0->pmidr->y > 0.0) {
    if (car0->speed_y > speedlimit) {
      car0->a_y = (pow(car0->speed_y, 2) - pow(speedlimit_cross, 2)) / (2 * car0->pmidr->y); 
    } else {
      car0->speed_y = speedlimit; //当速度达到限速时，保持为限速
      car0->a_y = 0.0; //加速度为0
    }
    cout << "car_speed_y: " << car0->speed_y << ", car_a_y: " << car0->a_y << endl;
    showScene();
  }

  return true;
}