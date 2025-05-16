# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Define the project name
project(example001)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include paths for HIPO, CLAS12ROOT, and Files2Chain
include_directories(
    $ENV{HIPO}/include
    $ENV{CLAS12ROOT}/Clas12Root
    $ENV{CLAS12ROOT}/Clas12Banks
    ../source/Files2Chain
    ../source/ParticleMath
)

# Add library paths for HIPO and CLAS12ROOT
link_directories($ENV{HIPO}/lib $ENV{CLAS12ROOT}/lib)

# Find ROOT and set its compile flags
find_package(ROOT REQUIRED)
include_directories(${ROOT_INCLUDE_DIRS})
link_libraries(${ROOT_LIBRARIES})

# Add the executable
add_executable(example001
    main_macro/example001.cpp
    source/Files2Chain/Files2Chain.cxx
    source/ParticleMath/MathKinematicVariable.cxx
    source/ParticleMath/ParticleMomentDeclare.cxx
    source/ParticleMath/ParticleMassTable.cxx
    source/ParticleMath/ParticleMomentumSave.cxx
    source/ParticleMath/EventKinematicDeclare.cxx
    source/Cuts/ParticleCut.cxx
)

# Link the required libraries
target_link_libraries(example001 hipo4 Clas12Banks Clas12Root)