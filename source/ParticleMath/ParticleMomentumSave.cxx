#include "ParticleMomentumSave.h"
#include "ParticleMomentDeclare.h"
#include <iostream>
#include <unordered_map>
#include "ParticleMassTable.h"

// 使用全局变量存储动量和计数
extern std::unordered_map<std::string, std::vector<float>> momentumMapX;
extern std::unordered_map<std::string, std::vector<float>> momentumMapY;
extern std::unordered_map<std::string, std::vector<float>> momentumMapZ;
extern std::unordered_map<std::string, std::vector<float>> energyMap;
extern std::unordered_map<std::string, std::vector<float>> pMap;
extern std::unordered_map<std::string, std::vector<float>> thetaMap;
extern std::unordered_map<std::string, int> particleCountMap;
extern std::unordered_map<std::string, TLorentzVector> lorentzVectorMap;

// 定义 ParticlePushBack 函数
void ParticlePushBack(const std::string& particleName, int pid, float px, float py, float pz, bool cut) {
    // 检查粒子名称是否已初始化
    if (momentumMapX.find(particleName) == momentumMapX.end()) {
        std::cerr << "Error: Particle " << particleName << " is not initialized. Call declareParticleMomentum first." << std::endl;
        return;
    }

    // 根据 pid 判断是否匹配
    if ((particleName == "Electron" && pid == 11 && cut) ||
        (particleName == "Proton" && pid == 2212 && cut) ||
        (particleName == "Photon" && pid == 22 && cut)) {
        // 存储动量分量
        momentumMapX[particleName].push_back(px);
        momentumMapY[particleName].push_back(py);
        momentumMapZ[particleName].push_back(pz);

        // 更新粒子计数
        particleCountMap[particleName]++;

        float energy = std::sqrt(px * px + py * py + pz * pz + getParticleMass(pid) * getParticleMass(pid));
        energyMap[particleName].push_back(energy);

        // 更新四维动量
        lorentzVectorMap[particleName].SetPxPyPzE(px, py, pz, std::sqrt(px * px + py * py + pz * pz + getParticleMass(pid) * getParticleMass(pid) ));
        float p = lorentzVectorMap[particleName].P(); // 动量模
        float theta = lorentzVectorMap[particleName].Theta() * 180.0 / M_PI; // 转换为角度
        pMap[particleName].push_back(p);
        thetaMap[particleName].push_back(theta);
    }
}