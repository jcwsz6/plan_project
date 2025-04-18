#include "car.h" // 包含自己写的头文件用引号


/* ----------------------------------- 车基类 ---------------------------------- */
void CarBase::initCar(const double& pos_x, const double& pos_y, const double& heading,
    const double& width, const double& length) {
        car_width = width;
        car_length = length;
        heading_theta = heading;

        R0 = hypot(car_width/2, car_length/2);
        theta0 = atan(car_length / car_width);

        pmid = make_unique<Point>(pos_x, pos_y); // 几何中心点
        plf = make_unique<Point>(pos_x - car_width / 2, pos_y - car_length / 2, PI - theta0, R0); // 左前角点
        prf = make_unique<Point>(pos_x + car_width / 2, pos_y - car_length / 2, theta0, R0); // 右前角点
        plr = make_unique<Point>(pos_x - car_width / 2, pos_y + car_length / 2, PI + theta0, R0); // 左后角点
        prr = make_unique<Point>(pos_x + car_width / 2, pos_y + car_length / 2, -theta0, R0); // 右后角点

        plf->pointTurn(*plf, heading_theta);
        prf->pointTurn(*prf, heading_theta);
        plr->pointTurn(*plr, heading_theta);
        prr->pointTurn(*prr, heading_theta);

        updatePmidf();
        updatePmidr();
    }

    void CarBase::updatePmidf() {
        double x = (plf->x + prf->x) / 2.0;
        double y = (plf->y + prf->y) / 2.0;
        if (pmidf) {
            pmidf->x = x;
            pmidf->y = y;
        } else {
            pmidf = make_unique<Point>(x, y);
        }
    }

    void CarBase::updatePmidr() {
        double x = (plr->x + prr->x) / 2.0;
        double y = (plr->y + prr->y) / 2.0;
        if (pmidr) {
            pmidr->x = x;
            pmidr->y = y;
        } else {
            pmidr = make_unique<Point>(x, y);
        }
    }

    void CarBase::updatePmid() {
        double x = (plf->x + prr->x) / 2.0;
        double y = (plf->y + prr->y) / 2.0;
        if (pmid) {
            pmid->x = x;
            pmid->y = y;    
        } else {
            pmid = make_unique<Point>(x, y);
        }
    }

    void CarBase::showCar(const COLORREF& color) {
        setlinestyle(PS_SOLID, 4); //设置线的样式和宽度
        setlinecolor(color); //设置线的颜色
        line(plf->x, plf->y, prf->x, prf->y);
        line(prf->x, prf->y, prr->x, prr->y);
        line(prr->x, prr->y, plr->x, plr->y);
        line(plr->x, plr->y, plf->x, plf->y);
    }

    void CarBase::showCircle() {
        setlinestyle(PS_SOLID, 2); //设置线的样式和宽度
        setlinecolor(MAGENTA); //设置线的颜色
        circle(p_center->x, p_center->y, Rof);
        circle(p_center->x, p_center->y, Ror);
        circle(p_center->x, p_center->y, Rif);
        circle(p_center->x, p_center->y, Rir);
    }

    void CarBase::coutInfo() {
        cout << "pmidr->x = " << pmidr->x << " pmidr->y = " << pmidr->y << "pmidr->Rp" << pmidr->Rp <<
             "pmidr->thetaP" << pmidr->thetaP << endl;
        cout << "pmidf->x = " << pmidf->x << " pmidf->y = " << pmidf->y << "pmidf->Rp" << pmidf->Rp <<
             "pmidf->thetaP" << pmidf->thetaP << endl;
        cout << "pmid->x = " << pmid->x << " pmid->y = " << pmid->y << "pmid->Rp" << pmid->Rp <<
             "pmid->thetaP" << pmid->thetaP << endl;
        cout << "plf->x = " << plf->x << " plf->y = " << plf->y << "plf->Rp" << plf->Rp <<
             "plf->thetaP" << plf->thetaP << endl;
        cout << "plr->x = " << plr->x << " plr->y = " << plr->y << "plr->Rp" << plr->Rp <<
             "plr->thetaP" << plr->thetaP << endl;
        cout << "prf->x = " << prf->x << " prf->y = " << prf->y << "prf->Rp" << prf->Rp <<
             "prf->thetaP" << prf->thetaP << endl;
        cout << "prr->x = " << prr->x << " prr->y = " << prr->y << "prr->Rp" << prr->Rp <<
             "prr->thetaP" << prr->thetaP << endl;
        cout << "speed = " << speed << " a = " << a << " delta_theta = " << delta_theta / PI << 
            " delta_theta_rot = " << delta_theta_rot / PI << endl;
    }

    void CarBase::moveStraightStep() {
        plf->pointMove(speed_x, speed_y);
        plr->pointMove(speed_x, speed_y);
        prf->pointMove(speed_x, speed_y);
        prr->pointMove(speed_x, speed_y);
        pmidf->pointMove(speed_x, speed_y);
        pmidr->pointMove(speed_x, speed_y);
        pmid->pointMove(speed_x, speed_y);
    }

    void CarBase::carTurnStep() {
        pmidr->pointTurn(*p_center, delta_theta);
        plf->pointTurn(*p_center, delta_theta);
        plr->pointTurn(*p_center, delta_theta);
        prf->pointTurn(*p_center, delta_theta);
        prr->pointTurn(*p_center, delta_theta);
        heading_theta += delta_theta;
    }

    void CarBase::updateXYva() {
        speed_x = speed * sin(heading_theta);
        speed_y = speed * cos(heading_theta);

        a_x = a * sin(heading_theta);
        a_y = a * cos(heading_theta);
        cout << "speed_x = " << speed_x << " speed_y = " << speed_y << " a_x = " << 
            a_x << " a_y = " << a_y << endl;
    }

    void CarBase::updateStraightInfo() {
        updatePmidr();
        updatePmidf();
        updatePmid();
        updateXYva();
        p_center.reset(); //指针指向空，直行不需要有转向中心，释放掉这块内存

        Ror = 0.0; //直行，四个转向半径归为0
        Rir = 0.0;
        Rof = 0.0;
        Rif = 0.0;

        pmidf->thetaP = 0.0; //涉及到转弯的点的参数都归为0
        pmidf->Rp = 0.0;

        pmid->thetaP = 0.0;
        pmid->Rp = 0.0;

        pmidr->thetaP = 0.0;
        pmidr->Rp = 0.0;

        plf->thetaP = 0.0;
        plf->Rp = 0.0;

        plr->thetaP = 0.0;
        plr->Rp = 0.0;

        prf->thetaP = 0.0;
        prf->Rp = 0.0;

        prr->thetaP = 0.0;
        prr->Rp = 0.0;

        delta_theta = 0.0; //与转向相关的角速度，角加速度归为0
        delta_theta_rot = 0.0;
    }

    /* ----------------------------------- 一般车 ---------------------------------- */
    CarNormal::CarNormal(const double& pos_x, const double& pos_y, const double& heading,
        const double& width, const double& length) {
            initCar(pos_x, pos_y, heading, width, length);
        }