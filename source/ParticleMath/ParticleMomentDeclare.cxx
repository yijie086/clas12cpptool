#include "ParticleMomentDeclare.h"
#include <iostream>
#include <unordered_map>
#include <TTree.h>
#include <TLorentzVector.h>
#include <clas12reader.h>


// 定义全局变量存储动量、能量、数量和四维动量
std::unordered_map<std::string, std::vector<float>> momentumMapX;
std::unordered_map<std::string, std::vector<float>> momentumMapY;
std::unordered_map<std::string, std::vector<float>> momentumMapZ;
std::unordered_map<std::string, std::vector<float>> energyMap; // 添加 energyMap
std::unordered_map<std::string, std::vector<float>> thetaMap; // 添加 thetaMap
std::unordered_map<std::string, std::vector<float>> pMap;     // 添加 pMap
std::unordered_map<std::string, int> particleCountMap;
std::unordered_map<std::string, TLorentzVector> lorentzVectorMap;

// 定义 declareParticleMomentum 函数
ParticleMomentum declareParticleMomentum(const std::string& particleName) {
    // 初始化对应的动量、能量和计数
    momentumMapX[particleName] = std::vector<float>();
    momentumMapY[particleName] = std::vector<float>();
    momentumMapZ[particleName] = std::vector<float>();
    energyMap[particleName] = std::vector<float>(); // 初始化 energy
    thetaMap[particleName] = std::vector<float>(); // 初始化 theta
    pMap[particleName] = std::vector<float>();     // 初始化 p
    particleCountMap[particleName] = 0;
    lorentzVectorMap[particleName] = TLorentzVector();

    // 输出粒子信息
    std::cout << "Initializing momentum, energy, theta, p, and TLorentzVector for particle: " << particleName << std::endl;

    // 返回封装的结构体
    return ParticleMomentum{
        &momentumMapX[particleName],
        &momentumMapY[particleName],
        &momentumMapZ[particleName],
        &energyMap[particleName], // 返回 energy
        &thetaMap[particleName], // 返回 theta
        &pMap[particleName],     // 返回 p
        &particleCountMap[particleName],
        &lorentzVectorMap[particleName]
    };
}

// 定义 resetParticleMomentum 函数
void resetParticleMomentum(const std::string& particleName) {
    // 清空对应的动量和计数
    momentumMapX[particleName].clear();
    momentumMapY[particleName].clear();
    momentumMapZ[particleName].clear();
    energyMap[particleName].clear();
    thetaMap[particleName].clear(); // 清空 theta
    pMap[particleName].clear();     // 清空 p
    particleCountMap[particleName] = 0;
    lorentzVectorMap[particleName] = TLorentzVector();

    //std::cout << "Reset momentum and TLorentzVector for particle: " << particleName << std::endl;
}

// 定义 temporaryParticleDeclare 函数
std::tuple<int, float, float, float> temporaryParticleDeclare(const clas12::region_particle* particle) {
    // 获取粒子的 PID 和动量分量
    int pid = particle->getPid();   // 获取粒子 ID
    float px = particle->getPx();   // 获取 px 分量
    float py = particle->getPy();   // 获取 py 分量
    float pz = particle->getPz();   // 获取 pz 分量

    // 返回 PID 和动量分量
    return std::make_tuple(pid, px, py, pz);
}

// 定义 SetMomentumInTree 函数
void SetMomentumInTree(TTree* tree, const std::string& particleName) {
    // 检查粒子是否已初始化
    if (momentumMapX.find(particleName) == momentumMapX.end()) {
        std::cerr << "Error: Particle " << particleName << " is not initialized. Call declareParticleMomentum first." << std::endl;
        return;
    }

    // 将动量和能量变量添加到 TTree
    tree->Branch((particleName + "_Px").c_str(), &momentumMapX[particleName]);
    tree->Branch((particleName + "_Py").c_str(), &momentumMapY[particleName]);
    tree->Branch((particleName + "_Pz").c_str(), &momentumMapZ[particleName]);
    tree->Branch((particleName + "_E").c_str(), &energyMap[particleName]); // 添加 energy 分支
    tree->Branch((particleName + "_theta").c_str(), &thetaMap[particleName]); // 添加 theta 分支
    tree->Branch((particleName + "_P").c_str(), &pMap[particleName]);         // 添加 p 分支
    tree->Branch((particleName + "_Count").c_str(), &particleCountMap[particleName]);
}