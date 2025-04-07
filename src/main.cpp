#include "main.h"

bool process(const int& type) { //总过程
  switch (type) {
    case PlanType::StraightStopOBSType: {
      unique_ptr<SceneBase> plan_obj = make_unique<StraightStopOBS>();
      return plan_obj->planning_process();
    }
    case PlanType::StraightStationType: {

    }
    case PlanType::StraightFollowType: {
        
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
  initgraph(SWIDTH, SHEIGHT, EW_SHOWCONSOLE); //初始化窗口,打开命令行窗口
  setbkcolor(WHITE); //设置背景颜色
  cleardevice(); //清屏

  if (process(PlanType::StraightStopOBSType)) {
    std::cout << "process success!" << std::endl;
  }
  system("pause");
  closegraph(); //关闭窗口
  return 0;
}