#include "main.h"

bool process(const int& type) { //总过程
  switch (type) {
    case PlanType::StraightStopOBSType: {
      unique_ptr<SceneBase> plan_obj = make_unique<StraightStopOBS>();
      return plan_obj->planning_process();
    }
    case PlanType::StraightStationType: {
      unique_ptr<SceneBase> plan_obj = make_unique<StraightStation>();
      return plan_obj->planning_process();
    }
    case PlanType::StraightFollowType: {
      unique_ptr<SceneBase> plan_obj = make_unique<StraightFollow>();
      return plan_obj->planning_process();
    }
    case PlanType::StraightCrosswalkType: {
      unique_ptr<SceneBase> plan_obj = make_unique<StraightCrosswalk>();
      return plan_obj->planning_process();
    }
    case PlanType::ObsPassStaticType: {
      unique_ptr<SceneBase> plan_obj = make_unique<StaticObs>();
      return plan_obj->planning_process();
    }
    case PlanType::ObsPassOvertakeType: {
      unique_ptr<SceneBase> plan_obj = make_unique<OvertakeObs>();
      return plan_obj->planning_process();
    }
    case PlanType::ObsPassMeetingType: {
      unique_ptr<SceneBase> plan_obj = make_unique<MeetingObs>();
      return plan_obj->planning_process();
    }
    case PlanType::ParkReverse1Type: {
      unique_ptr<SceneBase> plan_obj = make_unique<ReverseParking1>();
      return plan_obj->planning_process();
    }
    case PlanType::ParkReverse2Type: {
      unique_ptr<SceneBase> plan_obj = make_unique<ReverseParking2>();
      return plan_obj->planning_process();
    }
    case PlanType::ParkParallelType: {
      unique_ptr<SceneBase> plan_obj = make_unique<ParallelParking>();
      return plan_obj->planning_process();
    }
    case PlanType::DriftPointType: {
      unique_ptr<SceneBase> plan_obj = make_unique<DriftPoint>();
      return plan_obj->planning_process();
    }
    case PlanType::DriftParkType: {
      unique_ptr<SceneBase> plan_obj = make_unique<DriftParking>();
      return plan_obj->planning_process();
    }
    default: {
        break;
    }
  }
  std::cout << "plan type is not right!" << std::endl;
  return false;
}

int main()
{
  initgraph(SWIDTH, SHEIGHT, 0); //初始化窗口,不打开命令行窗口
  setbkcolor(WHITE); //设置背景颜色
  cleardevice(); //清屏

  if (process(PlanType::DriftParkType)) {
    std::cout << "process success!" << std::endl;
  }
  system("pause");
  closegraph(); //关闭窗口
  return 0;
}