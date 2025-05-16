// ParticleMomentum.h

#ifndef PARTICLEMOMENTUM_H
#define PARTICLEMOMENTUM_H

#include <vector>
#include "clas12reader.h"  // HIPO 读取器 / HIPO reader

// 函数声明
// Function declaration
void getParticleMomentum(clas12::clas12reader &reader, std::vector<std::vector<float>> &momentumList);
void plotParticleMomentum(const std::vector<std::vector<float>> &momentumList, int pid);

#endif // PARTICLEMOMENTUM_H
