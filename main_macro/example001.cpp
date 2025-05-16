#include <cstdlib> // 包含标准库 / Include standard library
#include <iostream> // 包含输入输出库 / Include input-output library
#include <vector> // 包含向量库 / Include vector library
#include <TFile.h> // ROOT 文件操作 / ROOT file operations
#include <TTree.h> // ROOT 树结构 / ROOT tree structure
#include <TApplication.h> // ROOT 应用程序 / ROOT application
#include <TLorentzVector.h> // Lorentz 向量 / Lorentz vector
#include "clas12reader.h" // HIPO 读取器 / HIPO reader
#include "HipoChain.h" // HIPO 读取链 / HIPO chain
#include <filesystem> // 文件系统库 / File system library

#include "./../source/Files2Chain/Files2Chain.h"
#include "./../source/ParticleMath/MathKinematicVariable.h"
#include "./../source/ParticleMath/ParticleMomentDeclare.h"
#include "./../source/ParticleMath/ParticleMassTable.h"
#include "./../source/ParticleMath/ParticleMomentumSave.h"
#include "./../source/ParticleMath/EventKinematicDeclare.h"
#include "./../source/Cuts/ParticleCut.h"

using namespace std; // 使用标准命名空间 / Use standard namespace

int main(int argc, char **argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <beam_energy> <hipo_file_directory_path::can traverse nested folders>" << std::endl;
        return 1;
    }
    // 获取用户输入的 beam_energy 和路径
    double beam_energy = std::atof(argv[1]); // 将第一个参数转换为 double
    std::string directoryPath = argv[2];    // 第二个参数是路径

    
    // 创建 HIPO 链对象 / Create HIPO chain object
    clas12root::HipoChain chain; 
    // 添加 HIPO 文件到链 / Add HIPO files to the chain
    int num_file_total = addFilesToChain(chain, directoryPath); // 添加目录中的所有 HIPO 文件，可遍历嵌套的文件夹 / Add all HIPO files in the directory, can traverse nested folders

    // 创建 ROOT 文件和 TTree / Create ROOT file and TTree
    TFile *rFile = TFile::Open("output.root", "RECREATE"); // 打开或创建 ROOT 文件 / Open or create ROOT file
    TTree *trackTree = new TTree("trackTree", "Track Data"); // 创建新的 TTree / Create new TTree
    
    // 声明动量变量 / Declare momentum variables
    auto [Electron_Px, Electron_Py, Electron_Pz, Electron_E, Electron_theta, Electron_P, number_Electron_per_event, Electron_LorentzVector] = declareParticleMomentum("Electron");
    auto [Proton_Px, Proton_Py, Proton_Pz, Proton_E, Proton_theta, Proton_P, number_Proton_per_event, Proton_LorentzVector] = declareParticleMomentum("Proton");
    auto [Photon_Px, Photon_Py, Photon_Pz, Photon_E, Photon_theta, Photon_P, number_Photon_per_event, Photon_LorentzVector] = declareParticleMomentum("Photon");

    // 将动量信息加入 TTree / Add momentum information to TTree
    SetMomentumInTree(trackTree, "Electron");
    SetMomentumInTree(trackTree, "Proton");
    SetMomentumInTree(trackTree, "Photon");

    double target_mass = getParticleMass(2212); // 靶核质量（质子质量，单位：GeV/c^2）/ Target mass (proton mass, in GeV/c^2)
    TLorentzVector p4_beam(0.0, 0.0, beam_energy, beam_energy); // 入射电子 / Incident electron

    EventKinematics kinematics = initializeEventKinematics();
    SetKinematicsInTree(trackTree, kinematics); // 将运动学变量加入 TTree / Add kinematic variables to TTree
    EventKinematicsForT kinematicsForT = initializeEventKinematicsForT();
    SetKinematicsInTreeForT(trackTree, kinematicsForT);

    
    // 遍历链中的每个文件 / Loop through each file in the chain
    for (int i = 0; i < chain.GetNFiles(); ++i) {
        cout << "Processing file " << chain.GetFileName(i) << endl; // 输出当前处理的文件 / Output current file being processed
        clas12::clas12reader reader(chain.GetFileName(i).Data()); // 创建读取器对象 / Create reader object

        // 事件循环 / Event loop
        while (reader.next()) { // 读取下一个事件 / Read next event
            auto particles = reader.getDetParticles();

            // 遍历所有粒子 / Loop through all particles
            for (const auto& particle : particles) {
                auto [temp_pid, temp_px, temp_py, temp_pz] = temporaryParticleDeclare(particle); // 获取粒子信息 / Get particle information 
                // 存储电子、质子和光子的动量到临时变量 / Store momentum of electron, proton, and photon to temporary variables
                ParticlePushBack("Electron", temp_pid, temp_px, temp_py, temp_pz,electronDVCScut(temp_px, temp_py, temp_pz, temp_pid));
                ParticlePushBack("Proton", temp_pid, temp_px, temp_py, temp_pz,protonDVCScut(temp_px, temp_py, temp_pz, temp_pid, target_mass));
                ParticlePushBack("Photon", temp_pid, temp_px, temp_py, temp_pz,photonDVCScut(temp_px, temp_py, temp_pz, temp_pid));
            }

            if (*number_Electron_per_event == 1 && *number_Proton_per_event == 1 && *number_Photon_per_event == 1) { // 如果有一个电子 / If there is one electron
                calculateEventKinematics(kinematics, p4_beam, *Electron_LorentzVector, target_mass);
                calculateEventKinematicsForT(kinematicsForT, *Proton_LorentzVector, target_mass);
                //cout << "Q2: " << kinematics.Q2 << ", Nu: " << kinematics.Nu << ", xB: " << kinematics.xB << ", W: " << kinematics.W << endl; // 输出运动学变量 / Output kinematic variables
                trackTree->Fill(); // 填充 TTree / Fill the TTree
            }

            resetParticleMomentum("Electron"); // 重置电子动量 / Reset electron momentum
            resetParticleMomentum("Proton"); // 重置质子动量 / Reset proton momentum
            resetParticleMomentum("Photon"); // 重置光子动量 / Reset photon momentum
        }
    }

    // 写入 ROOT 文件并关闭 / Write to ROOT file and close
    rFile->Write();
    rFile->Close();

    return 0; // 返回成功 / Return success
}
