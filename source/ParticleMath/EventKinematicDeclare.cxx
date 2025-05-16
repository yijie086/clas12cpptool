#include "EventKinematicDeclare.h"
#include "MathKinematicVariable.h"

// 定义 initializeEventKinematics 函数
EventKinematics initializeEventKinematics() {
    // 初始化运动学变量
    return EventKinematics{0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
}

// 定义 calculateEventKinematics 函数
void calculateEventKinematics(EventKinematics& kinematics, const TLorentzVector& p4_beam, const TLorentzVector& p4_electron, double target_mass) {
    // 计算运动学变量
    kinematics.Q2 = math_Q2(p4_beam, p4_electron);
    kinematics.Nu = math_Nu(p4_beam, p4_electron);
    kinematics.xB = math_xB(p4_beam, p4_electron, target_mass);
    kinematics.W = math_W(p4_beam, p4_electron, target_mass);
    kinematics.s = math_s(p4_beam, target_mass);
    kinematics.y = math_y(p4_beam, p4_electron, target_mass);
}

// 定义 SetKinematicsInTree 函数
void SetKinematicsInTree(TTree* tree, EventKinematics& kinematics) {
    // 将运动学变量添加到 TTree
    tree->Branch("Q2", &kinematics.Q2, "Q2/D");
    tree->Branch("Nu", &kinematics.Nu, "Nu/D");
    tree->Branch("xB", &kinematics.xB, "xB/D");
    tree->Branch("W", &kinematics.W, "W/D");
    tree->Branch("s", &kinematics.s, "s/D");
    tree->Branch("y", &kinematics.y, "y/D");
}

// 定义 initializeEventKinematicsForT 函数
EventKinematicsForT initializeEventKinematicsForT() {
    // 初始化 t 变量
    return EventKinematicsForT{0.0};
}

// 定义 calculateEventKinematicsForT 函数
void calculateEventKinematicsForT(EventKinematicsForT& kinematicsForT, const TLorentzVector& p4_recoil, double target_mass) {
    // 计算 t 变量
    kinematicsForT.t = math_t(p4_recoil, target_mass);
}

// 定义 SetKinematicsInTreeForT 函数
void SetKinematicsInTreeForT(TTree* tree, EventKinematicsForT& kinematicsForT) {
    // 将 t 变量添加到 TTree
    tree->Branch("t", &kinematicsForT.t, "t/D");
}
