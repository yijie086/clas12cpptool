# **CLAS12 Particle Analysis Tool**

## **项目简介**
该项目是一个基于 CLAS12 数据分析的工具，使用 ROOT 和 HIPO 库处理粒子物理实验数据。项目的主要功能包括：
- 读取 HIPO 文件并将其添加到分析链中。
- 计算粒子的运动学变量（如动量、能量、角度等）。
- 应用粒子筛选条件（Cuts）。
- 将分析结果存储到 ROOT 文件中，便于后续可视化和分析。

---

## **项目结构**
```
.
├── main_macro/
│   └── example001.cpp        # 主程序，执行数据分析流程
├── source/
│   ├── Files2Chain/
│   │   ├── Files2Chain.h     # 声明将 HIPO 文件添加到链的函数
│   │   └── Files2Chain.cxx   # 实现将 HIPO 文件添加到链的函数
│   ├── ParticleMath/
│   │   ├── MathKinematicVariable.h   # 声明运动学变量计算函数
│   │   ├── MathKinematicVariable.cxx # 实现运动学变量计算函数
│   │   ├── ParticleMassTable.h       # 声明粒子质量表查询函数
│   │   ├── ParticleMassTable.cxx     # 实现粒子质量表查询函数
│   │   ├── ParticleMomentDeclare.h   # 声明粒子动量相关函数
│   │   ├── ParticleMomentDeclare.cxx # 实现粒子动量相关函数
│   │   ├── ParticleMomentumSave.h    # 声明粒子动量存储函数
│   │   ├── ParticleMomentumSave.cxx  # 实现粒子动量存储函数
│   │   ├── EventKinematicDeclare.h   # 声明事件运动学变量相关函数
│   │   └── EventKinematicDeclare.cxx # 实现事件运动学变量相关函数
│   ├── Cuts/
│   │   ├── ParticleCut.h             # 声明粒子筛选条件函数
│   │   └── ParticleCut.cxx           # 实现粒子筛选条件函数
├── CMakeLists.txt             # CMake 构建配置文件
└── README.md                  # 项目说明文件
```

---

## **依赖**
- **ROOT**：用于数据分析和可视化。
- **HIPO**：用于读取 CLAS12 的 HIPO 文件。
- **C++17**：项目使用 C++17 标准。

---

## **构建和运行**
### **1. 配置环境**
确保以下环境变量已正确设置：
- `HIPO`：HIPO 库的路径。
- `CLAS12ROOT`：CLAS12 ROOT 库的路径。

### **2. 构建项目**
```bash
mkdir build
cd build
cmake ..
make
```

### **3. 运行程序**
```bash
./example001 <beam_energy> <hipo_file_directory_path>
```
示例：
```bash
./example001 6.535 /path/to/hipo/files
```

---

## **功能说明**

### **主程序**
- **`example001.cpp`**：
  - 主程序，负责读取 HIPO 文件、计算运动学变量、应用筛选条件，并将结果存储到 ROOT 文件中。

---

### **模块说明**

#### **1. Files2Chain**
- **`Files2Chain.h` 和 `Files2Chain.cxx`**：
  - 提供 

`addFilesToChain`

 函数，用于递归遍历指定目录，将所有 `.hipo` 文件添加到 `clas12root::HipoChain` 中。
  - **函数**：
    ```cpp
    int addFilesToChain(clas12root::HipoChain& chain, const std::string& directory);
    ```

---

#### **2. ParticleMath**
- **`MathKinematicVariable.h` 和 `MathKinematicVariable.cxx`**：
  - 提供计算运动学变量的函数，如 \( Q^2 \)、\( \nu \)、\( x_B \)、\( W \)、\( s \)、\( y \)、\( t \)。
  - **主要函数**：
    ```cpp
    double math_Q2(const TLorentzVector& p4_beam, const TLorentzVector& p4_electron);
    double math_Nu(const TLorentzVector& p4_beam, const TLorentzVector& p4_electron);
    double math_xB(const TLorentzVector& p4_beam, const TLorentzVector& p4_electron, const double target_mass);
    double math_W(const TLorentzVector& p4_beam, const TLorentzVector& p4_electron, const double target_mass);
    double math_s(const TLorentzVector& p4_beam, const double target_mass);
    double math_y(const TLorentzVector& p4_beam, const TLorentzVector& p4_electron, const double target_mass);
    double math_t(const TLorentzVector& p4_recoil, const double target_mass);
    ```

- **`ParticleMassTable.h` 和 `ParticleMassTable.cxx`**：
  - 提供 

`getParticleMass`

 函数，用于查询粒子的静止质量。
  - **主要函数**：
    ```cpp
    double getParticleMass(int pid);
    ```

- **`ParticleMomentDeclare.h` 和 `ParticleMomentDeclare.cxx`**：
  - 提供粒子动量的声明、初始化和重置功能。
  - **主要函数**：
    ```cpp
    ParticleMomentum declareParticleMomentum(const std::string& particleName);
    void resetParticleMomentum(const std::string& particleName);
    std::tuple<int, float, float, float> temporaryParticleDeclare(const clas12::region_particle* particle);
    void SetMomentumInTree(TTree* tree, const std::string& particleName);
    ```

- **`ParticleMomentumSave.h` 和 `ParticleMomentumSave.cxx`**：
  - 提供 

`ParticlePushBack`

 函数，用于存储粒子的动量、能量、角度等信息。
  - **主要函数**：
    ```cpp
    void ParticlePushBack(const std::string& particleName, int pid, float px, float py, float pz, bool cut);
    ```

- **`EventKinematicDeclare.h` 和 `EventKinematicDeclare.cxx`**：
  - 提供事件运动学变量的初始化、计算和存储功能。
  - **主要函数**：
    ```cpp
    EventKinematics initializeEventKinematics();
    void calculateEventKinematics(EventKinematics& kinematics, const TLorentzVector& p4_beam, const TLorentzVector& p4_electron, double target_mass);
    void SetKinematicsInTree(TTree* tree, EventKinematics& kinematics);

    EventKinematicsForT initializeEventKinematicsForT();
    void calculateEventKinematicsForT(EventKinematicsForT& kinematicsForT, const TLorentzVector& p4_recoil, double target_mass);
    void SetKinematicsInTreeForT(TTree* tree, EventKinematicsForT& kinematicsForT);
    ```

---

#### **3. Cuts**
- **`ParticleCut.h` 和 `ParticleCut.cxx`**：
  - 提供粒子筛选条件函数，用于筛选符合 DVCS 条件的粒子。
  - **主要函数**：
    ```cpp
    bool electronDVCScut(double px, double py, double pz, int pid);
    bool protonDVCScut(double px, double py, double pz, int pid, double target_mass);
    bool photonDVCScut(double px, double py, double pz, int pid);
    ```

---

## **输出**
- **ROOT 文件**：
  - 分析结果存储在 `output.root` 文件中，包含以下分支：
    - 粒子的动量分量（`Px`, `Py`, `Pz`）。
    - 粒子的能量（`E`）。
    - 粒子的角度（`Theta`）。
    - 粒子的动量模（`P`）。
    - 事件运动学变量（`Q2`, `Nu`, `xB`, `W`, `s`, `y`, `t`）。

---

## **示例输出**
运行程序后，可以使用 ROOT 浏览器查看结果：
```bash
root -l output.root
```

