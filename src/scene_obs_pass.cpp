#include "scene_obs_pass.h"

/* ---------------------------------- 静态绕障 ---------------------------------- */
StaticObs::StaticObs()
{
  road0 = make_unique<RoadNormal>(250.0);
  cone = make_unique<Cone>(SHEIGHT / 2.0, SWIDTH / 2.0, 50.0);

  car0 = make_unique<CarNormal>(SWIDTH / 2.0, SHEIGHT - 70.0, 0.0, 80.0, 160.0);
  car0->speed = -4.0;

  car0->coutInfo();
  showScene();
  system("pause");
}

void StaticObs::showScene()
{
  BeginBatchDraw();
  cleardevice();

  road0->showRoad();
  cone->showCone();
  car0->showCar(BLACK);

  if (SHOWCIRCLE && car0->p_center)
  {
    car0->showCircle();
  }

  EndBatchDraw();
  delay(DELAYTIME);
}

bool StaticObs::planning_process()
{
  double start_line = cone->p_center->y + cone->r + start_dis + car0->car_length;
  uniformStraight(car0->pmidr->y - start_line); // 直行到要绕障的位置

  // 计算目标点
  double dis_l_L = cone->p_center->x - cone->r - road0->left_boundary;  // 左间距
  double dis_r_L = road0->right_boundary - cone->p_center->x - cone->r; // 右间距
  double target_l_x = road0->left_boundary + dis_l_L / 2.0;             // 左目标点x坐标
  double target_r_x = road0->right_boundary - dis_r_L / 2.0;            // 右目标点x坐标
  double target_y = cone->p_center->y;                                  // 目标点y坐标
  Point targert_l_point(target_l_x, target_y);                          // 左目标点
  Point targert_r_point(target_r_x, target_y);                          // 右目标点
  cout << "dis_l_L = " << dis_l_L << " , dis_r_L = " << dis_r_L << ", target_l_x = " << 
          target_l_x << ", target_r_x = " << target_r_x << " , target_y = " << target_y << endl;

  if (dis_l_L > car0->car_width * 1.2) { // 左侧有足够空间
    laneChange(targert_l_point, LaneChangeType::doubleType);
  } else { // 左侧不够宽
    if (dis_r_L > car0->car_width * 1.2) { // 右侧有足够空间
      laneChange(targert_r_point, LaneChangeType::doubleType);
    } else { // 左右都不够宽
      cout << "both side is not enough width" << endl;
      double stopline = cone->p_center->y + cone->r + 5.0;
      uniformAccByDis(car0->pmidf->y - stopline, 0.0);
      return false;
    }
  }

  car0->updatePmidr();
  uniformStraight(car0->pmidr->y - 0.0);
  return true;
}

/* ---------------------------------- 超车绕障 ---------------------------------- */
OvertakeObs::OvertakeObs()
{
  double Rwidth = 100.0;
  road0 = make_unique<RoadDoubleLane>(Rwidth);
  carObs = make_unique<CarNormal>(SWIDTH / 2.0 + Rwidth / 2.0, SHEIGHT - 600.0, 0.0, 30.0, 60.0);
  car0 = make_unique<CarNormal>(SWIDTH / 2.0 + Rwidth / 2.0, SHEIGHT - 200.0, 0.0, 20.0, 40.0);

  carObs->speed = -1.0;
  car0->speed = -6.0;

  carObs->updateStraightInfo();

  car0->coutInfo();
  carObs->coutInfo();

  showScene();
  system("pause");
}

void OvertakeObs::showScene()
{
  BeginBatchDraw();
  cleardevice();

  road0->showRoad();
  carObs->showCar(RED);
  car0->showCar(BLACK);

  if (SHOWCIRCLE && car0->p_center) {
    car0->showCircle();
  }

  EndBatchDraw();
  delay(DELAYTIME);
}

void OvertakeObs::obsMoveStep()
{
  carObs->moveStraightStep();
}

bool OvertakeObs::planning_process()
{
  double delta_speed = fabs(car0->speed) - fabs(carObs->speed); //速度差
  cout << "delta_speed = " << delta_speed << endl;
  if (delta_speed <= 0.0) { //追不上
    cout << "our car can't overtake the obstacle car, delta_speed <= 0.0" << endl;
    return false;
  }

  double dis_l_L = carObs->plr->x - road0->left_boundary; //障碍车左边界到左车道边界距离
  double target_l_x = road0->left_boundary + dis_l_L / 2.0; //左目标点位置
  cout << "dis_l_L = " << dis_l_L << ", target_l_x = " << target_l_x << endl;

  if (dis_l_L <= car0->car_width * 1.2) {
    cout << "our car can't overtake the obstacle car, dis_l_L <= car0->car_width * 1.2" << endl;
    return false;
  }

  start_dis = car0->car_length * 3.5;
  double dis0 = car0->pmidr->y - carObs->pmidr->y; //两车起始距离
  cout << "start_dis = " << start_dis << ", dis0 = " << dis0 << endl;
  if (dis0 <= start_dis) { //起始距离太近
    cout << "our car can't overtake the obstacle car, dis0 <= start_dis" << endl;
    return false;
  }

  uniformStraight(dis0 - start_dis); //直行到安全距离
  double time_lane_change = dis0 /delta_speed; //换道时间
  double dis_target = carObs->car_length; //换道后目标距离，拉开一个车身长度
  double target_y = car0->pmidr->y + car0->speed * time_lane_change; //行驶到并排的位置，左目标点y
  double time_straight = dis_target / delta_speed; //直行时间
  double s = fabs(car0->speed) * time_straight; //直行距离
  cout << "dis_target = " << dis_target << ", target_y = " << target_y << ", time_straight = " << time_straight << ", s = " << s << endl;

  Point target_l_point(target_l_x,target_y); //左目标点
  laneChange(target_l_point,LaneChangeType::doubleType, s); //换道

  car0->updatePmidr();
  uniformStraight(car0->pmidr->y - 0.0);

  return true;
}

/* ---------------------------------- 会车绕障 ---------------------------------- */
MeetingObs::MeetingObs()
{
  road0 = make_unique<RoadNormal>(200.0);
  carObs = make_unique<CarNormal>(SWIDTH / 2.0, 100.0, PI, 50.0, 100.0);
  car0 = make_unique<CarNormal>(SWIDTH / 2.0, 700.0, 0.0, 40.0, 80.0);
  carObs->speed = -3.0;
  car0->speed = -4.0;

  carObs->updateStraightInfo();

  car0->coutInfo();
  carObs->coutInfo();
  showScene();
  system("pause");
}

void MeetingObs::obsMoveStep() {
  carObs->moveStraightStep();
}

void MeetingObs::showScene()
{
  BeginBatchDraw();
  cleardevice();

  road0->showRoad();
  carObs->showCar(RED);
  car0->showCar(BLACK);

  if (SHOWCIRCLE && car0->p_center) {
    car0->showCircle();
  }

  EndBatchDraw();
  delay(DELAYTIME);
}

bool MeetingObs::planning_process()
{
  double total_speed = fabs(car0->speed) + fabs(carObs->speed);
  double dis0 = fabs(car0->pmidf->y - carObs->pmidf->y); //初始距离

  if (total_speed <= 0) {
    cout << "total_speed <= 0" << endl;
    return false;
  }

  double dis_r_L = road0->right_boundary - carObs->plr->x; //右侧边界距离
  double target_r_x = road0->right_boundary - dis_r_L /  2.0; //右目标点x
  cout << "dis_r_L: " << dis_r_L << " target_r_x: " << target_r_x << endl;
  if (dis_r_L <= car0->car_width * 1.2) {
    cout << "dis_r_L <= car0->car_width * 1.2" << endl;
    return false;
  }

  double time = dis0 / total_speed; // 到碰撞的时间
  double meeting_point_y = car0->pmidf->y + car0->speed * time; //碰撞点y
  double s0 = car0->pmidf->y - (meeting_point_y + start_dis); //直行到绕障点的距离
  cout << "total_speed: " << total_speed << " dis0: " << dis0 << " time: " << time << 
          " meeting_point_y: " << meeting_point_y << " s0: " << s0 << endl;
  if (s0 < 0.0) {
    cout << "s0 < 0.0" << endl;
    return false;
  }

  uniformStraight(s0); // 直行到绕障点
  Point target_r_point(target_r_x, meeting_point_y); // 右目标点
  laneChange(target_r_point, LaneChangeType::doubleType);

  car0->updatePmidr();
  uniformStraight(car0->pmidr->y - 0.0);

  return true;
}
