// ParticleMomentum.cpp

#include "ParticleMomentum.h"
#include <TH1.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <cmath>

// 从 HIPO 文件中提取粒子的动量信息
// Extract particle momentum information from HIPO file
void getParticleMomentum(clas12::clas12reader &reader, std::vector<std::vector<float>> &momentumList) {
    // 获取 HIPO 事件数量
    // Get the number of events
    int nEntries = reader.getEntries(); // 获取事件数量 / Get the number of events

    // 遍历所有事件
    // Loop through all events
    for (int i = 0; i < nEntries; ++i) {
        reader.next(); // 获取下一个事件 / Get the next event

        // 获取粒子数量
        // Get the number of particles
        std::vector<clas12::region_particle*> particles = reader.getByID(-1); // 获取所有粒子

        // 遍历所有粒子
        // Loop through all particles
        for (auto particle : particles) {
            int pid = particle->getPid(); // 读取粒子ID / Read the particle ID
            float px = particle->getPx(); // 读取 px 分量 / Read the px component
            float py = particle->getPy(); // 读取 py 分量 / Read the py component
            float pz = particle->getPz(); // 读取 pz 分量 / Read the pz component

            // 存储电子、质子和光子的动量
            // Store momentum for electrons, protons, and photons
            if (pid == 11 || pid == 2212 || pid == 22) { // PID: 11=e-, 2212=p, 22=γ
                momentumList.push_back({static_cast<float>(pid), px, py, pz}); // 存储粒子信息 / Store particle information
            }
        }
    }
}

// 绘制粒子动量分布直方图
// Plot the histogram of particle momentum distribution
void plotParticleMomentum(const std::vector<std::vector<float>> &momentumList, int pid) {
    // 创建直方图
    // Create a histogram
    TH1D* hist = new TH1D("hist", "Particle Momentum Distribution; Momentum (GeV/c); Events", 100, 0, 5);

    // 将动量填充到直方图
    // Fill the histogram with momentum values
    for (const auto &momentum : momentumList) {
        if (static_cast<int>(momentum[0]) == pid) { // 根据粒子 ID 选择 / Select based on particle ID
            float magnitude = sqrt(momentum[1] * momentum[1] + momentum[2] * momentum[2] + momentum[3] * momentum[3]); // 计算动量大小 / Calculate momentum magnitude
            hist->Fill(magnitude); // 填充直方图 / Fill the histogram
        }
    }

    // 创建画布并绘制直方图
    // Create a canvas and draw the histogram
    TCanvas* canvas = new TCanvas("canvas", "Particle Momentum Distribution", 800, 600);
    hist->Draw();
    
    // 保存结果
    // Save the result
    std::string filename = "particle_momentum_histogram_pid_" + std::to_string(pid) + ".png";
    canvas->SaveAs(filename.c_str());

    // 清理
    // Clean up
    delete hist;
}
