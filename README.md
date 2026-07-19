# Affine Snake Game (Qt6)

A modern, continuous-movement variation of the classic Snake game built using **C++** and the **Qt6 Framework**. 

Unlike traditional grid-based Snake games locked to 90-degree turns, this application implements continuous 360-degree free-angle movement. The core physics and kinematic calculations are driven entirely by **affine transformation matrices**.

## 🎮 Features
* **Free-Angle Steering:** The snake can move at any arbitrary angle across a 700x700 pixel environment.
* **Matrix Kinematics:** Position updates are calculated using translation matrices via Qt's `QTransform` class.
* **Dynamic Speed Control:** The player can accelerate or brake in real-time.
* **Continuous Collision Detection:** Custom hit-box logic for wall bounds, apple consumption, and self-intersection.
* **Asset Scaling:** Automatic algorithmic scaling of raw `.png` image assets to uniform target dimensions.

## ⚙️ Prerequisites
To build and run this project, you will need:
* **C++17** or higher
* **CMake** (Version 3.10+)
* **Qt6 Framework** (Core, Gui, Widgets modules)
* Target Compiler (e.g., MinGW/GCC via MSYS2 UCRT64 environment)

## 🚀 Build Instructions
This project utilizes CMake for cross-platform building.

1. Clone the repository or extract the project files to a local directory.
2. Ensure your graphical assets (`head.png`, `dot.png`, `apple.png`) are located in the build execution directory.
3. Open your terminal and run the following CMake commands:

```bash
mkdir build
cd build
cmake ..
cmake --build .
