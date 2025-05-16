#ifndef FILES2CHAIN_H
#define FILES2CHAIN_H

#include <iostream>
#include <string>
#include <filesystem>
#include "HipoChain.h" // 确保包含 clas12root::HipoChain 的头文件

namespace fs = std::filesystem;

// 声明 addFilesToChain 函数
int addFilesToChain(clas12root::HipoChain& chain, const std::string& directory);

#endif // FILES2CHAIN_H