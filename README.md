# CSE 426 — Computer Graphics Lab Assignment (Spring 2025) 

**By:** Nishat Tasnim (`NishatTasnim01`) — Student ID: `21201149`

## Tasks 

**Task #01 You are required to implement Bresenham's Line Drawing Algorithm with the following variations and constraints.**
a. Standard Line Drawing: Implement the classic Bresenham's Line Drawing Algorithm to draw a line between two points P1(x1,y1) and P2(x2,y2). Make sure your implementation can handle all line orientations (positive and negative slopes, vertical, and horizontal lines).

**Task #01 (a) — Solution link:** [https://github.com/NishatTasnim01/Computer_Graphics_Assignment/blob/main/21201149_1A.cpp](https://github.com/NishatTasnim01/Computer_Graphics_Assignment/blob/main/21201149_1A.cpp)

b. Handling Thick Lines: Implement an extension of Bresenham’s algorithm that can draw lines with a thickness. Given a line width W, you need to calculate and fill the region around the line in such a way that the line appears with a specified thickness. You will need to modify the line drawing to use 4-way or 8-way symmetry to achieve this.

**Task #01 (b) — Solution link:** [https://github.com/NishatTasnim01/Computer_Graphics_Assignment/blob/main/21201149_1B.cpp](https://github.com/NishatTasnim01/Computer_Graphics_Assignment/blob/main/21201149_1B.cpp)

**Task #02 Using a circle drawing algorithm, draw multiple concentric circles with increasing radius and thickness. Implement a color gradient that changes gradually with each circle’s radius, creating a smooth transition of colors from the innermost to the outermost circle.**

**Task #02 — Solution link:** [https://github.com/NishatTasnim01/Computer_Graphics_Assignment/blob/main/21201149_2.cpp](https://github.com/NishatTasnim01/Computer_Graphics_Assignment/blob/main/21201149_2.cpp)

**Task #03 Implement the Liang-Barsky Line Clipping Algorithm to clip lines against a rectangular clipping window defined by (xmin,ymin) and (xmax,ymax). Your program should:**
● Take as input multiple line segments (each defined by endpoints).
● Clip each line segment to the clipping window using the Liang-Barsky algorithm.
● Display the original lines in one color and the clipped portions in another.
● Handle all cases including lines fully inside, fully outside, and partially intersecting the clipping window.

**Task #03 — Solution link:** [https://github.com/NishatTasnim01/Computer_Graphics_Assignment/blob/main/21201149_3.cpp](https://github.com/NishatTasnim01/Computer_Graphics_Assignment/blob/main/21201149_3.cpp)

## Built With

* C++ (C++11 / C++17 compatible)
* OpenGL (legacy immediate-mode; `glBegin`/`glEnd`)
* GLUT / freeglut (for windowing & input)
* Standard C++ libraries (cmath, vector, iostream, etc.)

## Requirements / Dependencies

* A C++ compiler: `g++` (Linux/macOS) or MinGW (Windows / Code::Blocks)
* OpenGL dev libraries:

  * **Linux:** `libgl1-mesa-dev`, `libglu1-mesa-dev`, `freeglut3-dev` (or equivalent)
  * **Windows:** freeglut binaries or `freeglut` dev files; link with `-lfreeglut -lopengl32 -lglu32 -lwinmm`
  * **macOS:** OpenGL + GLUT frameworks (may require installing Xcode command line tools)

## Build & Run

### Linux (g++)

Install dependencies (Ubuntu/Debian example):

```sh
sudo apt update
sudo apt install build-essential freeglut3 freeglut3-dev libglu1-mesa-dev mesa-common-dev
```

Compile:

```sh
g++ -std=c++17 21201149_1A.cpp -o task1a -lGL -lGLU -lglut
g++ -std=c++17 21201149_1B.cpp -o task1b -lGL -lGLU -lglut
g++ -std=c++17 21201149_2.cpp -o task2  -lGL -lGLU -lglut
g++ -std=c++17 21201149_3.cpp -o task3  -lGL -lGLU -lglut
```

Run:

```sh
./task1a
./task1b
./task2
./task3
```

### macOS

Compile:

```sh
g++ -std=c++17 21201149_1A.cpp -o task1a -framework OpenGL -framework GLUT
# repeat similarly for other files
```

Run:

```sh
./task1a
```

### Windows (MinGW CLI)

Ensure freeglut headers/libs are installed and `freeglut.dll` is available at runtime.

Compile:

```sh
g++ -std=c++17 21201149_1A.cpp -o task1a.exe -lfreeglut -lopengl32 -lglu32 -lwinmm
# repeat for other files
```

Run:

```sh
task1a.exe
```

### Code::Blocks (Windows)

1. Create a new Console (or Empty) C++ project.
2. Add the `.cpp` file to the project.
3. Project → Build options → Linker settings:

   * Add `freeglut`, `opengl32`, `glu32`, `winmm`
4. Ensure `freeglut.dll` is placed next to the generated `.exe` or in `C:\Windows\System32`.
5. Build & Run inside Code::Blocks.


## Contact

Solved By: **Nishat Tasnim**
GitHub: [https://github.com/NishatTasnim01](https://github.com/NishatTasnim01)
Student Tag: `21201149`

## Acknowledgements

* Course: CSE 426 — Computer Graphics, University of Asia Pacific
* Instructor: Md Rasheduzzaman (Lecturer, CSE, UAP)

---
