#include "scene_park.h"

/* ---------------------------------- 倒车方式1 --------------------------------- */
ReverseParking1::ReverseParking1() {
  road0 = make_unique<RoadNormal>(250.0);
  ob1 = make_unique<CarObsStatic>(road0->right_boundary - 90.0, SHEIGHT / 4.0, PI / 2.0);
  ob2 = make_unique<CarObsStatic>(road0->right_boundary - 90.0, SHEIGHT / 4.0 + 200.0, PI / 2.0);
  park_width = ob2->topPos - ob1->bottomPos;
  dis_in = ob1->car_length * 0.8;
  cout << "park_width: " << park_width << " dis_in: " << dis_in << endl;

  car0 = make_unique<CarNormal>(ob1->leftPos - dis_obs_L, SHEIGHT - 180.0);
  car0->speed = -3.0;
  car0->Gear = Shift::m_D; //前进档

  car0->coutInfo();
  ob1->coutInfo();
  ob2->coutInfo();

  showScene();
  system("pause");
}

void ReverseParking1::showScene() {
  BeginBatchDraw();
  cleardevice();

  road0->showRoad();
  ob1->showCar(RED);
  ob2->showCar(RED);
  car0->showCar(BLACK);

  if (SHOWCIRCLE && car0->p_center) { //绘制轨迹
    car0->showCircle();
  }

  EndBatchDraw();
  delay(DELAYTIME);
}

bool ReverseParking1::planning_process() {
  //判断库宽度是否足够
  if (park_width <= car0->car_width * 1.2) {
    cout << "park_width is not enough" << endl;
    return false;
  }

  //计算R和stopline
  double R = ob1->car_length + dis_obs_L - dis_in; //转向半径
  double dis_obs_S = R - park_width / 2.0; //与障碍车下方的纵向距离
  double stopline = ob1->bottomPos - dis_obs_S; //直行结束位置
  cout << "R = " << R << " dis_obs_S = " << dis_obs_S << " stopline = " << stopline << endl;

  cout << "go straight" << endl;
  uniformStraight(car0->pmidr->y - stopline);
  car0->Gear = Shift::m_R; //倒车档
  delay(CHANGETIME);

  cout << "reverse for right" << endl;
  car0->speed = 2.0; //倒车速度
  car0->delta_theta = car0->speed / R; //角速度
  carTurn(TurnDirection::TurnRight, R, PI / 2.0);

  cout << "reverse straight" << endl;
  car0->speed = 2.0; //倒车速度
  uniformStraight(road0->right_boundary - safe_dis - car0->pmidr->x);
  car0->Gear = Shift::m_P; // 停车档

  cout << "reverse finished" << endl;
  return true;
}

/* ---------------------------------- 倒车方式2 --------------------------------- */
ReverseParking2::ReverseParking2() {
  road0 = make_unique<RoadNormal>(250.0);
  ob1 = make_unique<CarObsStatic>(road0->right_boundary - 90.0, SHEIGHT / 4.0, PI / 2.0);
  ob2 = make_unique<CarObsStatic>(road0->right_boundary - 90.0, SHEIGHT / 4.0 + 200.0, PI / 2.0);
  park_width = ob2->topPos - ob1->bottomPos;
  dis_in = ob1->car_length * 0.8;
  cout << "park_width: " << park_width << " dis_in: " << dis_in << endl;

  car0 = make_unique<CarNormal>(ob1->leftPos - dis_obs_L, SHEIGHT - 180.0);
  car0->speed = -2.0;
  car0->Gear = Shift::m_D; //前进档

  car0->coutInfo();
  ob1->coutInfo();
  ob2->coutInfo();

  showScene();
  system("pause");
}

void ReverseParking2::showScene() {
  BeginBatchDraw();
  cleardevice();

  road0->showRoad();
  ob1->showCar(RED);
  ob2->showCar(RED);
  car0->showCar(BLACK);

  if (SHOWCIRCLE && car0->p_center) { //绘制轨迹
    car0->showCircle();
  }

  EndBatchDraw();
  delay(DELAYTIME);  
}

bool ReverseParking2::planning_process() {
  //判断库宽度是否足够
  if (park_width <= car0->car_width * 1.2) {
    cout << "park_width is not enough" << endl;
    return false;
  }

  //计算倒车半径，左转目标转角，stopline
  double stopline = ob2->topPos; //直行结束的位置
  double R1 = 200.0; //初始化左转半径
  double center_x = car0->pmidr->x - R1;
  double M = park_width / 2.0;
  double N = road0->right_boundary - dis_in - center_x;
  double Rr = (pow(R1, 2) - pow(M, 2) - pow(N, 2)) / (M * 2 - R1 * 2); //右转倒车半径
  double target_theta = atan((Rr + M) / N); //左转目标转角
  cout << "M = " << M << " N = " << N << " Rr = " << Rr << " target_theta = " << target_theta / PI << 
          " R1 = " << R1 << " stopline = " << stopline << endl;

  cout << "go straight" << endl;
  uniformStraight(car0->pmidr->y - stopline);

  cout << "turn left" << endl;
  car0->delta_theta = -car0->speed / R1; //左转，逆时针旋转，正的角速度
  carTurn(TurnDirection::TurnLeft, R1, target_theta);
  car0->Gear = Shift::m_R; //倒车档
  delay(CHANGETIME);

  cout << "reverse for right" << endl;
  car0->delta_theta = -car0->speed / Rr; //右转，逆时针旋转，正的角速度
  carTurn(TurnDirection::TurnRight, Rr, PI / 2.0 - target_theta);

  cout << "reverse straight" << endl;
  car0->speed = 2.0;
  uniformStraight(road0->right_boundary - safe_dis - car0->pmidr->x);
  car0->Gear = Shift::m_P; // 停车档

  cout << "reverse finished" << endl;
  return true;
}

/* ---------------------------------- 侧方位停车 --------------------------------- */
ParallelParking::ParallelParking() {
  road0 = make_unique<RoadNormal>(180.0);
  ob1 = make_unique<CarObsStatic>(road0->right_boundary - 50.0, SHEIGHT / 4.0);
  ob2 = make_unique<CarObsStatic>(road0->right_boundary - 50.0, SHEIGHT / 4.0 + 410.0);
  park_length = ob2->topPos - ob1->bottomPos;
  cout << "park_length: " << park_length << endl;

  car0 = make_unique<CarNormal>(ob1->leftPos - dis_obs_L, SHEIGHT - 180.0);
  car0->speed = -3.0;
  car0->Gear = Shift::m_D; //前进档

  car0->coutInfo();
  ob1->coutInfo();
  ob2->coutInfo();

  showScene();
  system("pause");
}

void ParallelParking::showScene() {
  BeginBatchDraw();
  cleardevice();

  road0->showRoad();
  ob1->showCar(RED);
  ob2->showCar(RED);
  car0->showCar(BLACK);

  if (SHOWCIRCLE && car0->p_center) { //绘制轨迹
    car0->showCircle();
  }

  EndBatchDraw();
  delay(DELAYTIME);  
}

bool ParallelParking::planning_process() {
  //判断库的长度是否足够
  if (park_length <= car0->car_length * 1.2) {
    cout << "park_length is not enough" << endl;
    return false;
  }

  //计算R，目标转角和stopline
  double stopline = ob1->bottomPos; //直行停车位置
  double L = (dis_obs_L + ob1->car_width / 2.0 ) / 2.0;
  double h = (park_length - safe_dis) / 2.0;
  double R = (pow(L, 2) + pow(h, 2)) / L / 2.0; //转向半径
  double target_theta = asin(h / R); //目标转角
  cout << "stopline: " << stopline << " L: " << L << " R: " << R << " target_theta: " << target_theta << endl;

  cout << "go straight" << endl;
  uniformStraight(car0->pmidr->y - stopline);
  car0->Gear = Shift::m_R;
  delay(CHANGETIME);

  cout << "reverse for right" << endl;
  car0->speed = 2.0;
  car0->delta_theta = car0->speed / R;
  carTurn(TurnDirection::TurnRight, R, target_theta);

  cout << "reverse for left" << endl;
  car0->delta_theta = -car0->speed / R;
  carTurn(TurnDirection::TurnLeft, R, target_theta);
  car0->Gear = Shift::m_D;
  delay(CHANGETIME);

  cout << "go straight" << endl;
  car0->speed = -2.0;
  uniformStraight(30.0);
  car0->Gear = Shift::m_P;

  cout << "ParallelPark finished" << endl;

  return true;
}