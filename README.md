# **CLAS12 Particle Analysis Tool**

## **Project Overview**
This project is a tool for analyzing CLAS12 experimental data, leveraging ROOT and HIPO libraries to process particle physics data. The main functionalities include:
- Reading HIPO files and adding them to an analysis chain.
- Calculating kinematic variables of particles (e.g., momentum, energy, angles, etc.).
- Applying particle selection cuts.
- Storing analysis results in a ROOT file for further visualization and analysis.

---

## **Project Structure**
```
.
├── main_macro/
│   └── example001.cpp        # Main program to execute the data analysis workflow
├── source/
│   ├── Files2Chain/
│   │   ├── Files2Chain.h     # Declaration of functions to add HIPO files to the chain
│   │   └── Files2Chain.cxx   # Implementation of functions to add HIPO files to the chain
│   ├── ParticleMath/
│   │   ├── MathKinematicVariable.h   # Declaration of kinematic variable calculation functions
│   │   ├── MathKinematicVariable.cxx # Implementation of kinematic variable calculation functions
│   │   ├── ParticleMassTable.h       # Declaration of particle mass table query functions
│   │   ├── ParticleMassTable.cxx     # Implementation of particle mass table query functions
│   │   ├── ParticleMomentDeclare.h   # Declaration of particle momentum-related functions
│   │   ├── ParticleMomentDeclare.cxx # Implementation of particle momentum-related functions
│   │   ├── ParticleMomentumSave.h    # Declaration of particle momentum storage functions
│   │   ├── ParticleMomentumSave.cxx  # Implementation of particle momentum storage functions
│   │   ├── EventKinematicDeclare.h   # Declaration of event kinematic variable-related functions
│   │   └── EventKinematicDeclare.cxx # Implementation of event kinematic variable-related functions
│   ├── Cuts/
│   │   ├── ParticleCut.h             # Declaration of particle selection cut functions
│   │   └── ParticleCut.cxx           # Implementation of particle selection cut functions
├── CMakeLists.txt             # CMake build configuration file
└── README.md                  # Project documentation
```

---

## **Dependencies**
- **ROOT**: For data analysis and visualization.
- **HIPO**: For reading CLAS12 HIPO files.
- **C++17**: The project uses the C++17 standard.

---

## **Build and Run**
### **1. Configure Environment**
Ensure the following environment variables are correctly set:
- `HIPO`: Path to the HIPO library.
- `CLAS12ROOT`: Path to the CLAS12 ROOT library.

### **2. Build the Project**
```bash
mkdir build
cd build
cmake ..
make
```

### **3. Run the Program**
```bash
./example001 <beam_energy> <hipo_file_directory_path>
```
Example:
```bash
./example001 6.535 /path/to/hipo/files
```

---

## **Functionality**

### **Main Program**
- **`example001.cpp`**:
  - The main program responsible for reading HIPO files, calculating kinematic variables, applying selection cuts, and storing results in a ROOT file.

---

### **Module Descriptions**

#### **1. Files2Chain**
- **`Files2Chain.h` and `Files2Chain.cxx`**:
  - Provides the `addFilesToChain` function to recursively traverse a directory and add all `.hipo` files to a `clas12root::HipoChain`.
  - **Function**:
    ```cpp
    int addFilesToChain(clas12root::HipoChain& chain, const std::string& directory);
    ```

---

#### **2. ParticleMath**
- **`MathKinematicVariable.h` and `MathKinematicVariable.cxx`**:
  - Provides functions to calculate kinematic variables such as \( Q^2 \), \( \nu \), \( x_B \), \( W \), \( s \), \( y \), \( t \).
  - **Key Functions**:
    ```cpp
    double math_Q2(const TLorentzVector& p4_beam, const TLorentzVector& p4_electron);
    double math_Nu(const TLorentzVector& p4_beam, const TLorentzVector& p4_electron);
    double math_xB(const TLorentzVector& p4_beam, const TLorentzVector& p4_electron, const double target_mass);
    double math_W(const TLorentzVector& p4_beam, const TLorentzVector& p4_electron, const double target_mass);
    double math_s(const TLorentzVector& p4_beam, const double target_mass);
    double math_y(const TLorentzVector& p4_beam, const TLorentzVector& p4_electron, const double target_mass);
    double math_t(const TLorentzVector& p4_recoil, const double target_mass);
    ```

- **`ParticleMassTable.h` and `ParticleMassTable.cxx`**:
  - Provides the `getParticleMass` function to query the rest mass of particles.
  - **Key Function**:
    ```cpp
    double getParticleMass(int pid);
    ```

- **`ParticleMomentDeclare.h` and `ParticleMomentDeclare.cxx`**:
  - Provides functions for declaring, initializing, and resetting particle momentum.
  - **Key Functions**:
    ```cpp
    ParticleMomentum declareParticleMomentum(const std::string& particleName);
    void resetParticleMomentum(const std::string& particleName);
    std::tuple<int, float, float, float> temporaryParticleDeclare(const clas12::region_particle* particle);
    void SetMomentumInTree(TTree* tree, const std::string& particleName);
    ```

- **`ParticleMomentumSave.h` and `ParticleMomentumSave.cxx`**:
  - Provides the `ParticlePushBack` function to store particle momentum, energy, and angle information.
  - **Key Function**:
    ```cpp
    void ParticlePushBack(const std::string& particleName, int pid, float px, float py, float pz, bool cut);
    ```

- **`EventKinematicDeclare.h` and `EventKinematicDeclare.cxx`**:
  - Provides functions for initializing, calculating, and storing event kinematic variables.
  - **Key Functions**:
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
- **`ParticleCut.h` and `ParticleCut.cxx`**:
  - Provides particle selection cut functions to filter particles meeting DVCS conditions.
  - **Key Functions**:
    ```cpp
    bool electronDVCScut(double px, double py, double pz, int pid);
    bool protonDVCScut(double px, double py, double pz, int pid, double target_mass);
    bool photonDVCScut(double px, double py, double pz, int pid);
    ```

---

## **Output**
- **ROOT File**:
  - The analysis results are stored in `output.root`, containing the following branches:
    - Particle momentum components (`Px`, `Py`, `Pz`).
    - Particle energy (`E`).
    - Particle angles (`Theta`).
    - Particle momentum magnitude (`P`).
    - Event kinematic variables (`Q2`, `Nu`, `xB`, `W`, `s`, `y`, `t`).

---

## **Example Output**
After running the program, you can use the ROOT browser to inspect the results:
```bash
root -l output.root
```
