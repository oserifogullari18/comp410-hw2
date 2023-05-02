# OS
WSL2 with Ubuntu 20.04.6 LTS
# Installation

```sh
g++ src/main.cpp src/InitShader.cpp -o rubik -lGL -lglfw -lGLEW -I include/
```
# Usage

```sh
./rubik
```

Press H to get help  
Left-Click on Surface -> Rotate Clockwise Direction  
Right-Click on Surface -> Rotate Anti-clockwise Direction  
Press Space -> Shuffle Rubik  
Press W, A, S, D -> Change View Angle  
Press ESC or Q -> Exit Game  
