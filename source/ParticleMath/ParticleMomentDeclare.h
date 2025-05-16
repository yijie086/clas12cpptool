#ifndef PARTICLEMOMENTDECLARE_H
#define PARTICLEMOMENTDECLARE_H

#include <string>
#include <vector>
#include <tuple>
#include <TTree.h>
#include <TLorentzVector.h>
#include <clas12reader.h>

// 定义结构体封装动量变量
struct ParticleMomentum {
    std::vector<float>* Px;
    std::vector<float>* Py;
    std::vector<float>* Pz;
    std::vector<float>* Energy; // 添加 energy 项
    std::vector<float>* Theta; // 添加 theta 项
    std::vector<float>* P;     // 添加 p 项
    int* number_per_event;
    TLorentzVector* LorentzVector;
};

// 声明 declareParticleMomentum 函数
ParticleMomentum declareParticleMomentum(const std::string& particleName);

// 声明 temporaryParticleDeclare 函数
std::tuple<int, float, float, float> temporaryParticleDeclare(const clas12::region_particle* particle);

// 声明 resetParticleMomentum 函数
void resetParticleMomentum(const std::string& particleName);

// 声明 SetMomentumInTree 函数
void SetMomentumInTree(TTree* tree, const std::string& particleName);

#endif // PARTICLEMOMENTDECLARE_H