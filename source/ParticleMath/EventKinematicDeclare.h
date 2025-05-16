#ifndef EVENTKINEMATICDECLARE_H
#define EVENTKINEMATICDECLARE_H

#include <TLorentzVector.h>
#include <TTree.h>

// 定义结构体封装运动学变量
struct EventKinematics {
    double Q2;
    double Nu;
    double xB;
    double W;
    double s;
    double y;
};

// 声明初始化函数
EventKinematics initializeEventKinematics();

// 声明计算函数
void calculateEventKinematics(EventKinematics& kinematics, const TLorentzVector& p4_beam, const TLorentzVector& p4_electron, double target_mass);

void SetKinematicsInTree(TTree* tree, EventKinematics& kinematics);

// 定义结构体封装 t 变量
struct EventKinematicsForT {
    double t;
};

// 声明与 t 相关的函数
EventKinematicsForT initializeEventKinematicsForT();
void calculateEventKinematicsForT(EventKinematicsForT& kinematicsForT, const TLorentzVector& p4_recoil, double target_mass);
void SetKinematicsInTreeForT(TTree* tree, EventKinematicsForT& kinematicsForT);

#endif // EVENTKINEMATICDECLARE_H