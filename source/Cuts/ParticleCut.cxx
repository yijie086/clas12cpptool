#include "ParticleCut.h"
#include "../ParticleMath/ParticleMassTable.h"
#include "../ParticleMath/MathKinematicVariable.h"
#include <TLorentzVector.h>
#include <TMath.h>

bool electronDVCScut(double px, double py, double pz, int pid) {
    if (pid != 11) {
        return false;
    }
    // 使用 TLorentzVector 计算四维动量
    TLorentzVector electron;
    electron.SetPxPyPzE(px, py, pz, std::sqrt(px * px + py * py + pz * pz + getParticleMass(pid) * getParticleMass(pid)));
    double energy = electron.E();
    double theta = electron.Theta() * 180.0 / M_PI; // 转换为角度


    if (energy > 1.0 && theta > 7.5 && theta < 35.0) {
        return true; // 满足条件
    }

    return false; // 不满足条件
}

bool protonDVCScut(double px, double py, double pz, int pid, double target_mass) {
    if (pid != 2212) {
        return false;
    }
    // 使用 TLorentzVector 计算四维动量
    TLorentzVector proton;
    proton.SetPxPyPzE(px, py, pz, std::sqrt(px * px + py * py + pz * pz + getParticleMass(pid) * getParticleMass(pid)));
    double energy = proton.E();
    double theta = proton.Theta() * 180.0 / M_PI; // 转换为角度
    double t = math_t(proton, target_mass); // 计算 t 值


    if (TMath::Abs(t) < 1.0 && theta > 6) {
        return true; // 满足条件
    }

    return false; // 不满足条件
}

bool photonDVCScut(double px, double py, double pz, int pid) {
    if (pid != 22) {
        return false;
    }
    // 使用 TLorentzVector 计算四维动量
    TLorentzVector photon;
    photon.SetPxPyPzE(px, py, pz, std::sqrt(px * px + py * py + pz * pz + getParticleMass(pid) * getParticleMass(pid)));
    double energy = photon.E();
    double theta = photon.Theta() * 180.0 / M_PI; // 转换为角度

    if (energy > 2.0 && theta > 2.5 && theta < 35.0) {
        return true; // 满足条件
    }

    return false; // 不满足条件
}