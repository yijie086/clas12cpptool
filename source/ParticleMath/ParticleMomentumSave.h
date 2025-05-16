#ifndef PARTICLEMOMENTUMSAVE_H
#define PARTICLEMOMENTUMSAVE_H

#include <string>
#include <vector>
#include <unordered_map>

// 声明 ParticlePushBack 函数
void ParticlePushBack(const std::string& particleName, int pid, float px, float py, float pz, bool cut);

#endif // PARTICLEMOMENTUMSAVE_H