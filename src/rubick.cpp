//
//  Display a rotating cube
//

//
//  Display a rotating cube, revisited
//
#include "Angel.h"

typedef vec4 color4;
typedef vec4 point4;

// number of vertices in each cube
const int NumVertices_cube =
    36; //(6 faces)(2 triangles/face)(3 vertices/triangle)
float radius = 0.25;

// window widht and height
int WIDTH = 800;
int HEIGHT = 600;

// position enumeration
enum { PosX, PosY, PosZ, NumPos };
// Array of rotation angles (in degrees) for each coordinate axis
enum { Xaxis, Yaxis, Zaxis, NumAxes };
// current rotating situation
bool rotating;

// camera angle
GLfloat Theta[NumAxes] = {30.0, 330.0, 0.0};

// Small Cube Structure for Rubik
struct smallCube {
  point4 points[NumVertices_cube];
  color4 colors[NumVertices_cube];
  GLfloat theta[NumAxes];
  GLfloat pos[NumPos];
  int CurrentLocID;
  int TempLocID;
  int InitialLocID;
  int surface_id;
  int SurfaceColors[6];
  mat4 model_view;
};

// Vertices of a small cube centered at origin, sides aligned with axes
point4 verticesCube[8]{point4(-radius, -radius, radius, 1.0),
                       point4(-radius, radius, radius, 1.0),
                       point4(radius, radius, radius, 1.0),
                       point4(radius, -radius, radius, 1.0),
                       point4(-radius, -radius, -radius, 1.0),
                       point4(-radius, radius, -radius, 1.0),
                       point4(radius, radius, -radius, 1.0),
                       point4(radius, -radius, -radius, 1.0)};
// Vertices of the big surface ID cube centered at origin, sides aligned with
// axes
point4 verticesCubeSurfaceID[8]{
    point4(-radius * 3, -radius * 3, radius * 3, 1.0),
    point4(-radius * 3, radius * 3, radius * 3, 1.0),
    point4(radius * 3, radius * 3, radius * 3, 1.0),
    point4(radius * 3, -radius * 3, radius * 3, 1.0),
    point4(-radius * 3, -radius * 3, -radius * 3, 1.0),
    point4(-radius * 3, radius * 3, -radius * 3, 1.0),
    point4(radius * 3, radius * 3, -radius * 3, 1.0),
    point4(radius * 3, -radius * 3, -radius * 3, 1.0)};

// 1    3      4     5        5          6
// red, yellow, green, blue, white and orange
color4 vertexColors[6] = {
    color4(1.0, 0.0, 0.0, 1.0), // red
    color4(1.0, 1.0, 0.0, 1.0), // yellow
    color4(0.0, 1.0, 0.0, 1.0), // green
    color4(0.0, 0.0, 1.0, 1.0), // blue
    color4(1.0, 1.0, 1.0, 1.0), // white
    color4(1, 0.647, 0, 1.0),   // orange
};

/////////// Create Big Surface Id Cube ///////////////
point4 pointsSurfaceIDCube[NumVertices_cube];
color4 colorsSurfaceIDCube[NumVertices_cube];
int IndexB = 0;
void quadBig(int a, int b, int c, int d, int color) {
  colorsSurfaceIDCube[IndexB] = vertexColors[color];
  pointsSurfaceIDCube[IndexB] = verticesCubeSurfaceID[a];
  IndexB++;
  colorsSurfaceIDCube[IndexB] = vertexColors[color];
  pointsSurfaceIDCube[IndexB] = verticesCubeSurfaceID[b];
  IndexB++;
  colorsSurfaceIDCube[IndexB] = vertexColors[color];
  pointsSurfaceIDCube[IndexB] = verticesCubeSurfaceID[c];
  IndexB++;
  colorsSurfaceIDCube[IndexB] = vertexColors[color];
  pointsSurfaceIDCube[IndexB] = verticesCubeSurfaceID[a];
  IndexB++;
  colorsSurfaceIDCube[IndexB] = vertexColors[color];
  pointsSurfaceIDCube[IndexB] = verticesCubeSurfaceID[c];
  IndexB++;
  colorsSurfaceIDCube[IndexB] = vertexColors[color];
  pointsSurfaceIDCube[IndexB] = verticesCubeSurfaceID[d];
  IndexB++;
}

// create big cube
void createQuadsBigCube() {
  IndexB = 0;
  quadBig(1, 0, 3, 2, 0);
  quadBig(2, 3, 7, 6, 1);
  quadBig(3, 0, 4, 7, 2);
  quadBig(6, 5, 1, 2, 3);
  quadBig(4, 5, 6, 7, 4);
  quadBig(5, 4, 0, 1, 5);
}

/////////// Create Small sub-cubes ///////////////
const int numCubes = 27; // nums of cube 2x2x2 rubix cube
struct smallCube Cubes[numCubes];
// Array of cube positions for each coordinate axis
GLfloat Position[numCubes][NumPos] = {
    // cube id
    // z(1)
    {-0.51, 0.51, 0.51},  // 0
    {0, 0.51, 0.51},      // 1
    {0.51, 0.51, 0.51},   // 2
    {-0.51, 0, 0.51},     // 3
    {0, 0, 0.51},         // 4
    {0.51, 0, 0.51},      // 5
    {-0.51, -0.51, 0.51}, // 6
    {0, -0.51, 0.51},     // 7
    {0.51, -0.51, 0.51},  // 8

    // z(0)
    {-0.51, 0.51, 0},  // 9
    {0, 0.51, 0},      // 10
    {0.51, 0.51, 0},   // 11
    {-0.51, 0, 0},     // 12
    {0, 0, 0},         // 13
    {0.51, 0, 0},      // 14
    {-0.51, -0.51, 0}, // 15
    {0, -0.51, 0},     // 16
    {0.51, -0.51, 0},  // 17

    // z(-1)
    {-0.51, 0.51, -0.51},  // 18
    {0, 0.51, -0.51},      // 19
    {0.51, 0.51, -0.51},   // 20
    {-0.51, 0, -0.51},     // 21
    {0, 0, -0.51},         // 22
    {0.51, 0, -0.51},      // 23
    {-0.51, -0.51, -0.51}, // 24
    {0, -0.51, -0.51},     // 25
    {0.51, -0.51, -0.51}   // 26

};

// Model-view and projection matrices uniform location
GLuint ModelView, Projection;

// Array for VOA and VBO IDs
GLuint VaoIDs[numCubes], VboIDs[numCubes];
GLuint VaoIDSurfaceIDCube, VboIDSurfaceIDCube;

//----------------------------------------------------------------------------

// quad generates two triangles for each face and assigns colors
//    to the vertices
int Index = 0;
void quad(int a, int b, int c, int d, int color, int cube_index) {
  // Initialize colors and points of the cube
  Cubes[cube_index].colors[Index] = vertexColors[color];
  Cubes[cube_index].points[Index] = verticesCube[a];
  Index++;

  Cubes[cube_index].colors[Index] = vertexColors[color];
  Cubes[cube_index].points[Index] = verticesCube[b];
  Index++;

  Cubes[cube_index].colors[Index] = vertexColors[color];
  Cubes[cube_index].points[Index] = verticesCube[c];
  Index++;

  Cubes[cube_index].colors[Index] = vertexColors[color];
  Cubes[cube_index].points[Index] = verticesCube[a];
  Index++;

  Cubes[cube_index].colors[Index] = vertexColors[color];
  Cubes[cube_index].points[Index] = verticesCube[c];
  Index++;

  Cubes[cube_index].colors[Index] = vertexColors[color];
  Cubes[cube_index].points[Index] = verticesCube[d];
  Index++;
}
// create small cube
void createQuads(int cube_index) {
  Index = 0;
  quad(1, 0, 3, 2, Cubes[cube_index].SurfaceColors[0], cube_index);
  quad(2, 3, 7, 6, Cubes[cube_index].SurfaceColors[1], cube_index);
  quad(3, 0, 4, 7, Cubes[cube_index].SurfaceColors[2], cube_index);
  quad(6, 5, 1, 2, Cubes[cube_index].SurfaceColors[3], cube_index);
  quad(4, 5, 6, 7, Cubes[cube_index].SurfaceColors[4], cube_index);
  quad(5, 4, 0, 1, Cubes[cube_index].SurfaceColors[5], cube_index);
}

// create rubiks cube
void rubiksCube() {
  for (int i = 0; i < numCubes; i++) {
    Cubes[i].SurfaceColors[0] = 0;
    Cubes[i].SurfaceColors[1] = 1;
    Cubes[i].SurfaceColors[2] = 2;
    Cubes[i].SurfaceColors[3] = 3;
    Cubes[i].SurfaceColors[4] = 4;
    Cubes[i].SurfaceColors[5] = 5;

    Cubes[i].CurrentLocID = i;
    Cubes[i].InitialLocID = i;
    Cubes[i].TempLocID = i;

    Cubes[i].pos[PosX] = Position[i][PosX];
    Cubes[i].pos[PosY] = Position[i][PosY];
    Cubes[i].pos[PosZ] = Position[i][PosZ];

    Cubes[i].theta[Xaxis] = 0.0;
    Cubes[i].theta[Yaxis] = 0.0;
    Cubes[i].theta[Zaxis] = 0.0;
    Cubes[i].model_view =
        mat4(Translate(vec3(0.0, 0.0, 0.0)) *
             Translate(vec3(Cubes[i].pos[PosX], Cubes[i].pos[PosY],
                            Cubes[i].pos[PosZ])) *
             Scale(1.0, 1.0, 1.0));
    createQuads(i);
  }
}

// update location function after rotating
void UpdateLocations() {
  for (int i = 0; i < numCubes; i++) {
    // std::cout << Cubes[i].CurrentLocID << std::endl;
    Cubes[i].CurrentLocID = Cubes[i].TempLocID;
  }
}

// Animating rotate with 5 degree speed
void timer_update() {
  for (int i = 0; i < numCubes; i++) {
    // Check X Axis
    if (Cubes[i].theta[Xaxis] != 0) {
      if (Cubes[i].theta[Xaxis] < 0) {
        Cubes[i].theta[Xaxis] += 5;
        Cubes[i].model_view = RotateX(-5) * Cubes[i].model_view;
      } else if (Cubes[i].theta[Xaxis] > 0) {
        Cubes[i].theta[Xaxis] -= 5;
        Cubes[i].model_view = RotateX(+5) * Cubes[i].model_view;
      }
    }

    // Check Y Axis
    if (Cubes[i].theta[Yaxis] != 0) {
      if (Cubes[i].theta[Yaxis] < 0) {
        Cubes[i].theta[Yaxis] += 5;
        Cubes[i].model_view = RotateY(-5) * Cubes[i].model_view;
      } else if (Cubes[i].theta[Yaxis] > 0) {
        Cubes[i].theta[Yaxis] -= 5;
        Cubes[i].model_view = RotateY(+5) * Cubes[i].model_view;
      }
    }

    // Check Z Axis
    if (Cubes[i].theta[Zaxis] != 0) {
      if (Cubes[i].theta[Zaxis] < 0) {
        Cubes[i].theta[Zaxis] += 5;
        Cubes[i].model_view = RotateZ(-5) * Cubes[i].model_view;
      } else if (Cubes[i].theta[Zaxis] > 0) {
        Cubes[i].theta[Zaxis] -= 5;
        Cubes[i].model_view = RotateZ(+5) * Cubes[i].model_view;
      }
    }
  }
}

// rotate function
void rotate(int RoteteNumber, int RotateDirection) {

  switch (RoteteNumber) {
  // rotate red surface
  case 1:
    if (RotateDirection == 1) {
      for (int i = 0; i < numCubes; i++) {
        if (Cubes[i].CurrentLocID == 0) {
          Cubes[i].theta[Zaxis] += 90.0;
          Cubes[i].TempLocID = 6;
        } else if (Cubes[i].CurrentLocID == 1) {
          Cubes[i].theta[Zaxis] += 90.0;
          Cubes[i].TempLocID = 3;
        } else if (Cubes[i].CurrentLocID == 2) {
          Cubes[i].theta[Zaxis] += 90.0;
          Cubes[i].TempLocID = 0;
        } else if (Cubes[i].CurrentLocID == 3) {
          Cubes[i].theta[Zaxis] += 90.0;
          Cubes[i].TempLocID = 7;
        } else if (Cubes[i].CurrentLocID == 4) {
          Cubes[i].theta[Zaxis] += 90.0;
          Cubes[i].TempLocID = 4;
        } else if (Cubes[i].CurrentLocID == 5) {
          Cubes[i].theta[Zaxis] += 90.0;
          Cubes[i].TempLocID = 1;
        } else if (Cubes[i].CurrentLocID == 6) {
          Cubes[i].theta[Zaxis] += 90.0;
          Cubes[i].TempLocID = 8;
        } else if (Cubes[i].CurrentLocID == 7) {
          Cubes[i].theta[Zaxis] += 90.0;
          Cubes[i].TempLocID = 5;
        } else if (Cubes[i].CurrentLocID == 8) {
          Cubes[i].theta[Zaxis] += 90.0;
          Cubes[i].TempLocID = 2;
        }
      }
    } else {
      for (int i = 0; i < numCubes; i++) {

        if (Cubes[i].CurrentLocID == 0) {
          Cubes[i].theta[Zaxis] -= 90.0;
          Cubes[i].TempLocID = 2;
        } else if (Cubes[i].CurrentLocID == 1) {
          Cubes[i].theta[Zaxis] -= 90.0;
          Cubes[i].TempLocID = 5;
        } else if (Cubes[i].CurrentLocID == 2) {
          Cubes[i].theta[Zaxis] -= 90.0;
          Cubes[i].TempLocID = 8;
        } else if (Cubes[i].CurrentLocID == 3) {
          Cubes[i].theta[Zaxis] -= 90.0;
          Cubes[i].TempLocID = 1;
        } else if (Cubes[i].CurrentLocID == 4) {
          Cubes[i].theta[Zaxis] -= 90.0;
          Cubes[i].TempLocID = 4;
        } else if (Cubes[i].CurrentLocID == 5) {
          Cubes[i].theta[Zaxis] -= 90.0;
          Cubes[i].TempLocID = 7;
        } else if (Cubes[i].CurrentLocID == 6) {
          Cubes[i].theta[Zaxis] -= 90.0;
          Cubes[i].TempLocID = 0;
        } else if (Cubes[i].CurrentLocID == 7) {
          Cubes[i].theta[Zaxis] -= 90.0;
          Cubes[i].TempLocID = 3;
        } else if (Cubes[i].CurrentLocID == 8) {
          Cubes[i].theta[Zaxis] -= 90.0;
          Cubes[i].TempLocID = 6;
        }
      }
    }
    UpdateLocations();
    break;
    // rotate yellow surface
  case 2:
    if (RotateDirection == 0) {
      for (int i = 0; i < numCubes; i++) {
        if (Cubes[i].CurrentLocID == 2) {
          Cubes[i].theta[Xaxis] -= 90.0;
          Cubes[i].TempLocID = 20;
        } else if (Cubes[i].CurrentLocID == 11) {
          Cubes[i].theta[Xaxis] -= 90.0;
          Cubes[i].TempLocID = 23;
        } else if (Cubes[i].CurrentLocID == 20) {
          Cubes[i].theta[Xaxis] -= 90.0;
          Cubes[i].TempLocID = 26;
        } else if (Cubes[i].CurrentLocID == 5) {
          Cubes[i].theta[Xaxis] -= 90.0;
          Cubes[i].TempLocID = 11;
        } else if (Cubes[i].CurrentLocID == 14) {
          Cubes[i].theta[Xaxis] -= 90.0;
          Cubes[i].TempLocID = 14;
        } else if (Cubes[i].CurrentLocID == 23) {
          Cubes[i].theta[Xaxis] -= 90.0;
          Cubes[i].TempLocID = 17;
        } else if (Cubes[i].CurrentLocID == 8) {
          Cubes[i].theta[Xaxis] -= 90.0;
          Cubes[i].TempLocID = 2;
        } else if (Cubes[i].CurrentLocID == 17) {
          Cubes[i].theta[Xaxis] -= 90.0;
          Cubes[i].TempLocID = 5;
        } else if (Cubes[i].CurrentLocID == 26) {
          Cubes[i].theta[Xaxis] -= 90.0;
          Cubes[i].TempLocID = 8;
        }
      }
    } else {
      for (int i = 0; i < numCubes; i++) {
        if (Cubes[i].CurrentLocID == 2) {
          Cubes[i].theta[Xaxis] += 90.0;
          Cubes[i].TempLocID = 8;
        } else if (Cubes[i].CurrentLocID == 11) {
          Cubes[i].theta[Xaxis] += 90.0;
          Cubes[i].TempLocID = 5;
        } else if (Cubes[i].CurrentLocID == 20) {
          Cubes[i].theta[Xaxis] += 90.0;
          Cubes[i].TempLocID = 2;
        } else if (Cubes[i].CurrentLocID == 5) {
          Cubes[i].theta[Xaxis] += 90.0;
          Cubes[i].TempLocID = 17;
        } else if (Cubes[i].CurrentLocID == 14) {
          Cubes[i].theta[Xaxis] += 90.0;
          Cubes[i].TempLocID = 14;
        } else if (Cubes[i].CurrentLocID == 23) {
          Cubes[i].theta[Xaxis] += 90.0;
          Cubes[i].TempLocID = 11;
        } else if (Cubes[i].CurrentLocID == 8) {
          Cubes[i].theta[Xaxis] += 90.0;
          Cubes[i].TempLocID = 26;
        } else if (Cubes[i].CurrentLocID == 17) {
          Cubes[i].theta[Xaxis] += 90.0;
          Cubes[i].TempLocID = 23;
        } else if (Cubes[i].CurrentLocID == 26) {
          Cubes[i].theta[Xaxis] += 90.0;
          Cubes[i].TempLocID = 20;
        }
      }
    }
    UpdateLocations();
    break;

    // rotate blue surface
  case 3:
    if (RotateDirection == 0) {
      for (int i = 0; i < numCubes; i++) {
        if (Cubes[i].CurrentLocID == 0) {
          Cubes[i].theta[Yaxis] -= 90.0;
          Cubes[i].TempLocID = 18;
        } else if (Cubes[i].CurrentLocID == 1) {
          Cubes[i].theta[Yaxis] -= 90.0;
          Cubes[i].TempLocID = 9;
        } else if (Cubes[i].CurrentLocID == 2) {
          Cubes[i].theta[Yaxis] -= 90.0;
          Cubes[i].TempLocID = 0;
        } else if (Cubes[i].CurrentLocID == 9) {
          Cubes[i].theta[Yaxis] -= 90.0;
          Cubes[i].TempLocID = 19;
        } else if (Cubes[i].CurrentLocID == 10) {
          Cubes[i].theta[Yaxis] -= 90.0;
          Cubes[i].TempLocID = 10;
        } else if (Cubes[i].CurrentLocID == 11) {
          Cubes[i].theta[Yaxis] -= 90.0;
          Cubes[i].TempLocID = 1;
        } else if (Cubes[i].CurrentLocID == 18) {
          Cubes[i].theta[Yaxis] -= 90.0;
          Cubes[i].TempLocID = 20;
        } else if (Cubes[i].CurrentLocID == 19) {
          Cubes[i].theta[Yaxis] -= 90.0;
          Cubes[i].TempLocID = 11;
        } else if (Cubes[i].CurrentLocID == 20) {
          Cubes[i].theta[Yaxis] -= 90.0;
          Cubes[i].TempLocID = 2;
        }
      }
    } else {
      for (int i = 0; i < numCubes; i++) {

        if (Cubes[i].CurrentLocID == 0) {
          Cubes[i].theta[Yaxis] += 90.0;
          Cubes[i].TempLocID = 2;
        } else if (Cubes[i].CurrentLocID == 1) {
          Cubes[i].theta[Yaxis] += 90.0;
          Cubes[i].TempLocID = 11;
        } else if (Cubes[i].CurrentLocID == 2) {
          Cubes[i].theta[Yaxis] += 90.0;
          Cubes[i].TempLocID = 20;
        } else if (Cubes[i].CurrentLocID == 9) {
          Cubes[i].theta[Yaxis] += 90.0;
          Cubes[i].TempLocID = 1;
        } else if (Cubes[i].CurrentLocID == 10) {
          Cubes[i].theta[Yaxis] += 90.0;
          Cubes[i].TempLocID = 10;
        } else if (Cubes[i].CurrentLocID == 11) {
          Cubes[i].theta[Yaxis] += 90.0;
          Cubes[i].TempLocID = 19;
        } else if (Cubes[i].CurrentLocID == 18) {
          Cubes[i].theta[Yaxis] += 90.0;
          Cubes[i].TempLocID = 0;
        } else if (Cubes[i].CurrentLocID == 19) {
          Cubes[i].theta[Yaxis] += 90.0;
          Cubes[i].TempLocID = 9;
        } else if (Cubes[i].CurrentLocID == 20) {
          Cubes[i].theta[Yaxis] += 90.0;
          Cubes[i].TempLocID = 18;
        }
      }
    }
    UpdateLocations();
    break;
  // rotate green surface
  case 4:
    if (RotateDirection == 1) {
      for (int i = 0; i < numCubes; i++) {
        if (Cubes[i].CurrentLocID == 6) {
          Cubes[i].theta[Yaxis] -= 90.0;
          Cubes[i].TempLocID = 24;
        } else if (Cubes[i].CurrentLocID == 7) {
          Cubes[i].theta[Yaxis] -= 90.0;
          Cubes[i].TempLocID = 15;
        } else if (Cubes[i].CurrentLocID == 8) {
          Cubes[i].theta[Yaxis] -= 90.0;
          Cubes[i].TempLocID = 6;
        } else if (Cubes[i].CurrentLocID == 15) {
          Cubes[i].theta[Yaxis] -= 90.0;
          Cubes[i].TempLocID = 25;
        } else if (Cubes[i].CurrentLocID == 16) {
          Cubes[i].theta[Yaxis] -= 90.0;
          Cubes[i].TempLocID = 16;
        } else if (Cubes[i].CurrentLocID == 17) {
          Cubes[i].theta[Yaxis] -= 90.0;
          Cubes[i].TempLocID = 7;
        } else if (Cubes[i].CurrentLocID == 24) {
          Cubes[i].theta[Yaxis] -= 90.0;
          Cubes[i].TempLocID = 26;
        } else if (Cubes[i].CurrentLocID == 25) {
          Cubes[i].theta[Yaxis] -= 90.0;
          Cubes[i].TempLocID = 17;
        } else if (Cubes[i].CurrentLocID == 26) {
          Cubes[i].theta[Yaxis] -= 90.0;
          Cubes[i].TempLocID = 8;
        }
      }
    } else {
      for (int i = 0; i < numCubes; i++) {

        if (Cubes[i].CurrentLocID == 6) {
          Cubes[i].theta[Yaxis] += 90.0;
          Cubes[i].TempLocID = 8;
        } else if (Cubes[i].CurrentLocID == 7) {
          Cubes[i].theta[Yaxis] += 90.0;
          Cubes[i].TempLocID = 17;
        } else if (Cubes[i].CurrentLocID == 8) {
          Cubes[i].theta[Yaxis] += 90.0;
          Cubes[i].TempLocID = 26;
        } else if (Cubes[i].CurrentLocID == 15) {
          Cubes[i].theta[Yaxis] += 90.0;
          Cubes[i].TempLocID = 7;
        } else if (Cubes[i].CurrentLocID == 16) {
          Cubes[i].theta[Yaxis] += 90.0;
          Cubes[i].TempLocID = 16;
        } else if (Cubes[i].CurrentLocID == 17) {
          Cubes[i].theta[Yaxis] += 90.0;
          Cubes[i].TempLocID = 25;
        } else if (Cubes[i].CurrentLocID == 24) {
          Cubes[i].theta[Yaxis] += 90.0;
          Cubes[i].TempLocID = 6;
        } else if (Cubes[i].CurrentLocID == 25) {
          Cubes[i].theta[Yaxis] += 90.0;
          Cubes[i].TempLocID = 15;
        } else if (Cubes[i].CurrentLocID == 26) {
          Cubes[i].theta[Yaxis] += 90.0;
          Cubes[i].TempLocID = 24;
        }
      }
    }
    UpdateLocations();
    break;
    // rotate orange surface
  case 5:
    if (RotateDirection == 1) {
      for (int i = 0; i < numCubes; i++) {
        if (Cubes[i].CurrentLocID == 0) {
          Cubes[i].theta[Xaxis] -= 90.0;
          Cubes[i].TempLocID = 18;
        } else if (Cubes[i].CurrentLocID == 3) {
          Cubes[i].theta[Xaxis] -= 90.0;
          Cubes[i].TempLocID = 9;
        } else if (Cubes[i].CurrentLocID == 6) {
          Cubes[i].theta[Xaxis] -= 90.0;
          Cubes[i].TempLocID = 0;
        } else if (Cubes[i].CurrentLocID == 9) {
          Cubes[i].theta[Xaxis] -= 90.0;
          Cubes[i].TempLocID = 21;
        } else if (Cubes[i].CurrentLocID == 12) {
          Cubes[i].theta[Xaxis] -= 90.0;
          Cubes[i].TempLocID = 12;
        } else if (Cubes[i].CurrentLocID == 15) {
          Cubes[i].theta[Xaxis] -= 90.0;
          Cubes[i].TempLocID = 3;
        } else if (Cubes[i].CurrentLocID == 18) {
          Cubes[i].theta[Xaxis] -= 90.0;
          Cubes[i].TempLocID = 24;
        } else if (Cubes[i].CurrentLocID == 21) {
          Cubes[i].theta[Xaxis] -= 90.0;
          Cubes[i].TempLocID = 15;
        } else if (Cubes[i].CurrentLocID == 24) {
          Cubes[i].theta[Xaxis] -= 90.0;
          Cubes[i].TempLocID = 6;
        }
      }
    } else {
      for (int i = 0; i < numCubes; i++) {

        if (Cubes[i].CurrentLocID == 0) {
          Cubes[i].theta[Xaxis] += 90.0;
          Cubes[i].TempLocID = 6;
        } else if (Cubes[i].CurrentLocID == 3) {
          Cubes[i].theta[Xaxis] += 90.0;
          Cubes[i].TempLocID = 15;
        } else if (Cubes[i].CurrentLocID == 6) {
          Cubes[i].theta[Xaxis] += 90.0;
          Cubes[i].TempLocID = 24;
        } else if (Cubes[i].CurrentLocID == 9) {
          Cubes[i].theta[Xaxis] += 90.0;
          Cubes[i].TempLocID = 3;
        } else if (Cubes[i].CurrentLocID == 12) {
          Cubes[i].theta[Xaxis] += 90.0;
          Cubes[i].TempLocID = 12;
        } else if (Cubes[i].CurrentLocID == 15) {
          Cubes[i].theta[Xaxis] += 90.0;
          Cubes[i].TempLocID = 21;
        } else if (Cubes[i].CurrentLocID == 18) {
          Cubes[i].theta[Xaxis] += 90.0;
          Cubes[i].TempLocID = 0;
        } else if (Cubes[i].CurrentLocID == 21) {
          Cubes[i].theta[Xaxis] += 90.0;
          Cubes[i].TempLocID = 9;
        } else if (Cubes[i].CurrentLocID == 24) {
          Cubes[i].theta[Xaxis] += 90.0;
          Cubes[i].TempLocID = 18;
        }
      }
    }
    UpdateLocations();
    break;

    // rotate white surface
  case 6:
    if (RotateDirection == 0) {
      for (int i = 0; i < numCubes; i++) {
        if (Cubes[i].CurrentLocID == 18) {
          Cubes[i].theta[Zaxis] += 90.0;
          Cubes[i].TempLocID = 24;
        } else if (Cubes[i].CurrentLocID == 19) {
          Cubes[i].theta[Zaxis] += 90.0;
          Cubes[i].TempLocID = 21;
        } else if (Cubes[i].CurrentLocID == 20) {
          Cubes[i].theta[Zaxis] += 90.0;
          Cubes[i].TempLocID = 18;
        } else if (Cubes[i].CurrentLocID == 21) {
          Cubes[i].theta[Zaxis] += 90.0;
          Cubes[i].TempLocID = 25;
        } else if (Cubes[i].CurrentLocID == 22) {
          Cubes[i].theta[Zaxis] += 90.0;
          Cubes[i].TempLocID = 22;
        } else if (Cubes[i].CurrentLocID == 23) {
          Cubes[i].theta[Zaxis] += 90.0;
          Cubes[i].TempLocID = 19;
        } else if (Cubes[i].CurrentLocID == 24) {
          Cubes[i].theta[Zaxis] += 90.0;
          Cubes[i].TempLocID = 26;
        } else if (Cubes[i].CurrentLocID == 25) {
          Cubes[i].theta[Zaxis] += 90.0;
          Cubes[i].TempLocID = 23;
        } else if (Cubes[i].CurrentLocID == 26) {
          Cubes[i].theta[Zaxis] += 90.0;
          Cubes[i].TempLocID = 20;
        }
      }
    } else {
      for (int i = 0; i < numCubes; i++) {

        if (Cubes[i].CurrentLocID == 18) {
          Cubes[i].theta[Zaxis] -= 90.0;
          Cubes[i].TempLocID = 20;
        } else if (Cubes[i].CurrentLocID == 19) {
          Cubes[i].theta[Zaxis] -= 90.0;
          Cubes[i].TempLocID = 23;
        } else if (Cubes[i].CurrentLocID == 20) {
          Cubes[i].theta[Zaxis] -= 90.0;
          Cubes[i].TempLocID = 26;
        } else if (Cubes[i].CurrentLocID == 21) {
          Cubes[i].theta[Zaxis] -= 90.0;
          Cubes[i].TempLocID = 19;
        } else if (Cubes[i].CurrentLocID == 22) {
          Cubes[i].theta[Zaxis] -= 90.0;
          Cubes[i].TempLocID = 22;
        } else if (Cubes[i].CurrentLocID == 23) {
          Cubes[i].theta[Zaxis] -= 90.0;
          Cubes[i].TempLocID = 25;
        } else if (Cubes[i].CurrentLocID == 24) {
          Cubes[i].theta[Zaxis] -= 90.0;
          Cubes[i].TempLocID = 18;
        } else if (Cubes[i].CurrentLocID == 25) {
          Cubes[i].theta[Zaxis] -= 90.0;
          Cubes[i].TempLocID = 21;
        } else if (Cubes[i].CurrentLocID == 26) {
          Cubes[i].theta[Zaxis] -= 90.0;
          Cubes[i].TempLocID = 24;
        }
      }
    }
    UpdateLocations();
    break;
  }
}

// random integer generator for shuffle
int random(int min, int max) {
  return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}
int RandomShuffleRotateSurfaces[10];
int RandomShuffleRotateDir[10];
bool RandomShuffle = false;

// OpenGL initialization
void init() {
  // init rubiks
  rubiksCube();

  // create big cube for surface id
  createQuadsBigCube();

  // Init shaders
  GLuint program = InitShader("src/vshader.glsl", "src/fshader.glsl");
  // Retrieve tshader variables for collors and positions
  GLuint vColor = glGetAttribLocation(program, "vColor");
  GLuint vPosition = glGetAttribLocation(program, "vPosition");
  // initialize program
  glUseProgram(program);

  // create the Vertex Array Objects for small cubes in rubik
  glGenVertexArrays(numCubes, VaoIDs);
  // generating Vertex Buffer Objects (VBO) for small cubes in rubik
  glGenBuffers(numCubes, VboIDs);

  // Create and bind a vertex array object for the big surface ID cube
  glGenVertexArrays(1, &VaoIDSurfaceIDCube);
  glBindVertexArray(VaoIDSurfaceIDCube);

  // Create and bind a vertex array buffer for the big surface ID cube
  glGenBuffers(1, &VboIDSurfaceIDCube);
  glBindBuffer(GL_ARRAY_BUFFER, VboIDSurfaceIDCube);

  // Put points and collors for the the big surface ID cube into buffer
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(pointsSurfaceIDCube) + sizeof(colorsSurfaceIDCube), NULL,
               GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pointsSurfaceIDCube),
                  pointsSurfaceIDCube);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(pointsSurfaceIDCube),
                  sizeof(colorsSurfaceIDCube), colorsSurfaceIDCube);

  glEnableVertexAttribArray(vPosition);
  glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
  glEnableVertexAttribArray(vColor);
  glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0,
                        BUFFER_OFFSET(sizeof(pointsSurfaceIDCube)));

  // Bind buffers and put points and collors into the buffers for each small
  // cube in the rubick
  for (int i = 0; i < numCubes; i++) {
    glBindVertexArray(VaoIDs[i]);

    glBindBuffer(GL_ARRAY_BUFFER, VboIDs[i]);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Cubes[i].points) + sizeof(Cubes[i].colors), NULL,
                 GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Cubes[i].points),
                    Cubes[i].points);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(Cubes[i].points),
                    sizeof(Cubes[i].colors), Cubes[i].colors);

    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0,
                          BUFFER_OFFSET(0));
    glEnableVertexAttribArray(vColor);
    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0,
                          BUFFER_OFFSET(sizeof(Cubes[i].points)));
  }

  // Retrieve transformation uniform variable locations
  ModelView = glGetUniformLocation(program, "ModelView");
  Projection = glGetUniformLocation(program, "Projection");

  mat4 projection;
  projection = (Perspective(45.0, (GLfloat)WIDTH / (GLfloat)HEIGHT, 5, 20.0) *
                Translate(vec3(0.0, 0.0, -10.0)));
  glUniformMatrix4fv(Projection, 1, GL_TRUE, projection);

  // Enable hiddden surface removal
  glEnable(GL_DEPTH_TEST);
  // Set state variable "clear color" to clear buffer with.
  glClearColor(0.3, 0.3, 0.3, 0.3);
}

//----------------------------------------------------------------------------
// Display function
void display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  vec3 displacement;
  mat4 model_view;

  // projection matrix for camera setting camera
  mat4 projection;
  projection = (Perspective(45.0, (GLfloat)WIDTH / (GLfloat)HEIGHT, 2, 20.0) *
                Translate(vec3(0.0, 0.0, -5.0)) * RotateX(Theta[Xaxis]) *
                RotateY(Theta[Yaxis]) * RotateZ(Theta[Zaxis]) *
                Translate(vec3(0.0, 0.0, 0.0)));
  glUniformMatrix4fv(Projection, 1, GL_TRUE, projection);

  // draw each small cube in rubicks using their current model view matrix
  for (int i = 0; i < numCubes; i++) {
    model_view = Cubes[i].model_view;
    // send the current model matrix to the vertex shader
    glUniformMatrix4fv(ModelView, 1, GL_TRUE, model_view);
    glBindVertexArray(VaoIDs[i]);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices_cube);
  }

  glFlush();
}

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods) {
  if (action == GLFW_PRESS || action == GLFW_REPEAT) {
    switch (key) {
    // Exit program with ESC and Q
    case GLFW_KEY_ESCAPE:
      exit(EXIT_SUCCESS);
      break;
    case GLFW_KEY_Q:
      exit(EXIT_SUCCESS);
      break;
    // Change camera angles
    case GLFW_KEY_S:
      Theta[Xaxis] += 10.0;

      if (Theta[Xaxis] > 360.0) {
        Theta[Xaxis] -= 360.0;
      }
      break;

    case GLFW_KEY_W:
      Theta[Xaxis] -= 10.0;

      if (Theta[Xaxis] > 360.0) {
        Theta[Xaxis] -= 360.0;
      }
      break;
    case GLFW_KEY_A:
      Theta[Yaxis] += 10.0;

      if (Theta[Yaxis] > 360.0) {
        Theta[Yaxis] -= 360.0;
      }
      break;

    case GLFW_KEY_D:
      Theta[Yaxis] -= 10.0;

      if (Theta[Yaxis] > 360.0) {
        Theta[Yaxis] -= 360.0;
      }
      break;
    // Shuffle Rubik
    case GLFW_KEY_SPACE:
      printf("\n*** Shuffling Rubik ***\n");
      RandomShuffle = true;
      int dir;
      int surface;
      for (int i = 0; i < 10; i++) {
        surface = random(1, 6);
        dir = random(0, 1);
        RandomShuffleRotateSurfaces[i] = surface;
        RandomShuffleRotateDir[i] = dir;
      }
      break;
    // Usage Help
    case GLFW_KEY_H:
      printf("Press H to get help \n");
      printf("Left-Click on Surface -> Rotate Clockwise Direction \n");
      printf("Right-Click on Surface -> Rotate Anti-clockwise Direction \n");
      printf("Space -> Shuffle Rubik \n");
      printf("W, A, S, D -> Change View Angle \n");
      printf("ESC or Q -> Exit Game \n");
      break;
    }
  }
}

void mouse_button_callback(GLFWwindow *window, int button, int action,
                           int mods) {
  if (action == GLFW_PRESS) {

    // Draw the surface ID cube in the back buffer (not seen in the screen)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    mat4 model_view =
        mat4(Translate(vec3(0.0, 0.0, 0.0)) * Scale(1.0, 1.0, 1.0) *
             Translate(vec3(Cubes[13].pos[PosX], Cubes[13].pos[PosY],
                            Cubes[13].pos[PosZ])));
    mat4 projection;
    projection = (Perspective(45.0, (GLfloat)WIDTH / (GLfloat)HEIGHT, 2, 20.0) *
                  Translate(vec3(0.0, 0.0, -5.0)) * RotateX(Theta[Xaxis]) *
                  RotateY(Theta[Yaxis]) * RotateZ(Theta[Zaxis]) *
                  Translate(vec3(0.0, 0.0, 0.0)));
    glUniformMatrix4fv(Projection, 1, GL_TRUE, projection);
    glUniformMatrix4fv(ModelView, 1, GL_TRUE, model_view);
    glBindVertexArray(VaoIDSurfaceIDCube);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices_cube);
    glFlush(); // forces all drawing commands to be sent to the graphics card
               // and executed immediately.
    glFinish();
    // glfwSwapBuffers(window);

    // initialize variables for cursor position and current window sizes
    double cursor_x, cursor_y;
    int current_width, current_height;
    unsigned char pixel[4];
    switch (button) {
    // rotate anticlockwise direction
    case GLFW_MOUSE_BUTTON_RIGHT:
      // don't take rotate commane if there is currently a rotation
      if (rotating) {
        break;
      } else {
        rotating = true;
      }
      // take and normalize cursor position
      glfwGetCursorPos(window, &cursor_x, &cursor_y);
      glfwGetWindowSize(window, &current_width, &current_height);
      cursor_y = current_height - cursor_y;
      // read the RGB value on the cursor position
      glReadPixels(cursor_x, cursor_y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
      // rotate with regard to the surface color ID.
      if (pixel[0] == 255 && pixel[1] == 0 && pixel[2] == 0) {
        rotate(1, 1); // red surface
      } else if (pixel[0] == 255 && pixel[1] == 255 && pixel[2] == 0) {
        rotate(2, 1); // yellow surface
      } else if (pixel[0] == 0 && pixel[1] == 0 && pixel[2] == 255) {
        rotate(3, 1); // blue surface
      } else if (pixel[0] == 0 && pixel[1] == 255 && pixel[2] == 0) {
        rotate(4, 1); // green surface
      } else if (pixel[0] == 255 && pixel[1] == 165 && pixel[2] == 0) {
        rotate(5, 1); // orange surface
      } else if (pixel[0] == 255 && pixel[1] == 255 && pixel[2] == 255) {
        rotate(6, 1); // white surface
      }
      break;

    // rotate clockwise direction
    case GLFW_MOUSE_BUTTON_LEFT:
      if (rotating) {
        break;
      } else {
        rotating = true;
      }
      glfwGetCursorPos(window, &cursor_x, &cursor_y);
      glfwGetWindowSize(window, &current_width, &current_height);
      cursor_y = current_height - cursor_y;

      glReadPixels(cursor_x, cursor_y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
      if (pixel[0] == 255 && pixel[1] == 0 && pixel[2] == 0) {
        rotate(1, 0); // red surface
      } else if (pixel[0] == 255 && pixel[1] == 255 && pixel[2] == 0) {
        rotate(2, 0); // yellow surface
      } else if (pixel[0] == 0 && pixel[1] == 0 && pixel[2] == 255) {
        rotate(3, 0); // blue surface
      } else if (pixel[0] == 0 && pixel[1] == 255 && pixel[2] == 0) {
        rotate(4, 0); // green surface
      } else if (pixel[0] == 255 && pixel[1] == 165 && pixel[2] == 0) {
        rotate(5, 0); // orange surface
      } else if (pixel[0] == 255 && pixel[1] == 255 && pixel[2] == 255) {
        rotate(6, 0); // white surface
      }
      break;
    }
  }
}

//// handle window resizing.
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width,
             height); // may not need this since the default is usually the
                      // window size

  // Set projection matrix
  mat4 projection;
  if (width <= height)
    projection = Ortho(-1.0, 1.0, -1.0 * (GLfloat)height / (GLfloat)width,
                       1.0 * (GLfloat)height / (GLfloat)width, -1.0, 1.0);
  else
    projection =
        Ortho(-1.0 * (GLfloat)width / (GLfloat)height,
              1.0 * (GLfloat)width / (GLfloat)height, -1.0, 1.0, -1.0, 1.0);

  glUniformMatrix4fv(Projection, 1, GL_TRUE, projection);
}

//---------------------------------------------------------------------
// main

int main() {
  if (!glfwInit())
    exit(EXIT_FAILURE);

  // Setup opengl versions
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  // Core Profile
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // Allow Forward Compatbility
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  // initialize GLFW window
  GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Rubick", NULL, NULL);
  glfwMakeContextCurrent(window);
  glewExperimental = GL_TRUE;
  glewInit();
  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  // make resizable
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

  // attach user input callbacks to the window
  glfwSetKeyCallback(window, key_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);
  // attach reshape callbacks to the window
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  init();
  // rotate in 120 fps
  double frameRate = 120, currentTime, previousTime = 0.0;
  while (!glfwWindowShouldClose(window)) {
    // is there random shuffling ?
    if (RandomShuffle) {

      int surface;
      int dir;
      // apply 10 random rotationg
      for (int i = 0; i < 10; i++) {
        surface = RandomShuffleRotateSurfaces[i];
        dir = RandomShuffleRotateDir[i];
        rotate(surface, dir);
        // wait for each rotation
        int theta = 90;
        while (theta > 0) {
          currentTime = glfwGetTime();
          if (currentTime - previousTime >= 1 / frameRate) {
            previousTime = currentTime;
            timer_update();
            theta -= 5;
          }
          // update screen
          display();
          glfwSwapBuffers(window);
          glfwPollEvents();
        }
      }
      RandomShuffle = false;
    } else {
      // is there any rotation command?
      if (rotating) {
        // wait for current rotation
        int theta = 90;
        while (theta > 0) {
          currentTime = glfwGetTime();
          if (currentTime - previousTime >= 1 / frameRate) {
            previousTime = currentTime;
            timer_update();
            theta -= 5;
          }
          // update screen
          display();
          glfwSwapBuffers(window);
          glfwPollEvents();
        }

        rotating = false;
      } else {
        currentTime = glfwGetTime();
        if (currentTime - previousTime >= 1 / frameRate) {
          previousTime = currentTime;
          timer_update();
        }
        // update screen
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
      }
    }
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
