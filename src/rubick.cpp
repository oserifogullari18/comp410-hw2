//
//  Display a rotating cube
//

//
//  Display a rotating cube, revisited
//
#include "Angel.h"

typedef vec4 color4;
typedef vec4 point4;

const int NumVertices_cube =
    36;                  //(6 faces)(2 triangles/face)(3 vertices/triangle)
const int numCubes = 27; // nums of cube 2x2x2 rubix cube
float radius = 0.25;

int WIDTH = 800;
int HEIGHT = 600;

int shuffle[] = {rand() % 4, rand() % 4, rand() % 4, rand() % 4, rand() % 4};

double counter = 0; // for rotation animation
int shuffle_counter = sizeof(shuffle) / sizeof(shuffle[0]) -
                      1; // Shuffle count, array size of shuffle

// position enumeration
enum { PosX, PosY, PosZ, NumPos };
// Array of rotation angles (in degrees) for each coordinate axis
enum { Xaxis, Yaxis, Zaxis, NumAxes };

// camera angle
GLfloat Theta[NumAxes] = {30.0, 330.0, 0.0};

// Cube Structure
struct smallCube {
  point4 points[NumVertices_cube];
  color4 colors[NumVertices_cube];
  GLfloat theta[NumAxes];
  GLfloat pos[NumPos];
  int identity;
  int nextIdentity;
  int surface_id;
  int SurfaceColors[6];
};

struct smallCube Cubes[numCubes];

// Vertices of a unit cube centered at origin, sides aligned with axes
point4 verticesCube[8]{point4(-radius, -radius, radius, 1.0),
                       point4(-radius, radius, radius, 1.0),
                       point4(radius, radius, radius, 1.0),
                       point4(radius, -radius, radius, 1.0),
                       point4(-radius, -radius, -radius, 1.0),
                       point4(-radius, radius, -radius, 1.0),
                       point4(radius, radius, -radius, 1.0),
                       point4(radius, -radius, -radius, 1.0)};

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

// Array of cube positions for each coordinate axis
GLfloat Position[numCubes][NumPos] = {
    // cube id
    {-0.51, 0.51, -0.51},  // 0
    {0.51, 0.51, -0.51},   // 1
    {0.51, 0.51, 0.51},    // 2
    {-0.51, 0.51, 0.51},   // 3
    {-0.51, -0.51, -0.51}, // 4
    {0.51, -0.51, -0.51},  // 5
    {0.51, -0.51, 0.51},   // 6
    {-0.51, -0.51, 0.51},  // 7

    {-0.51, 0.51, 0},  // 8
    {0.51, 0.51, 0},   // 9
    {-0.51, -0.51, 0}, // 10
    {0.51, -0.51, 0},  // 11
    {0, 0, 0},         // 12

    {-0.51, 0, 0.51},  // 13
    {0.51, 0, 0.51},   // 14
    {-0.51, 0, -0.51}, // 15
    {0.51, 0, -0.51},  // 16

    {0, -0.51, 0.51},  // 17
    {0, 0.51, 0.51},   // 18
    {0, -0.51, -0.51}, // 19
    {0, 0.51, -0.51},  // 20

    {0, -0.51, 0}, // 21
    {0, 0.51, 0},  // 22
    {0, 0, -0.51}, // 23
    {0, 0, 0.51},  // 24
    {-0.51, 0, 0}, // 25
    {0.51, 0, 0},  // 26

};

// Array of cube speed for each coordinate axis
enum { SpeedX, SpeedY, SpeedZ, SpeedRotate, NumSpeed };
double Speed[NumSpeed] = {0.05, 0.05, 0.05, 2};

// Model-view and projection matrices uniform location
GLuint ModelView, Projection;

// Array for VOA and VBO IDs
GLuint VaoIDs[numCubes], VboIDs[numCubes];

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
// create singe cube
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

    Cubes[i].identity = i;
    Cubes[i].nextIdentity = i;

    Cubes[i].pos[PosX] = Position[i][PosX];
    Cubes[i].pos[PosY] = Position[i][PosY];
    Cubes[i].pos[PosZ] = Position[i][PosZ];

    Cubes[i].theta[Xaxis] = 0.0;
    Cubes[i].theta[Yaxis] = 0.0;
    Cubes[i].theta[Zaxis] = 0.0;

    createQuads(i);
  }
}

// OpenGL initialization
void init() {
  // init cube
  rubiksCube();

  GLuint program = InitShader("src/vshader.glsl", "src/fshader.glsl");
  GLuint vColor = glGetAttribLocation(program, "vColor");
  GLuint vPosition = glGetAttribLocation(program, "vPosition");
  glUseProgram(program);
  // create the Vertex Array Objects
  glGenVertexArrays(numCubes, VaoIDs);

  // generating Vertex Buffer Objects (VBO)
  glGenBuffers(numCubes, VboIDs);

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

void shuffleCube() {
  for (int i = 0; i < sizeof(shuffle) / sizeof(shuffle[0]); i++)
    shuffle[i] = rand() % 4;
  shuffle_counter = sizeof(shuffle) / sizeof(shuffle[0]) - 1;
}

//----------------------------------------------------------------------------

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  vec3 displacement;
  mat4 model_view;

  // camera
  mat4 projection;
  projection = (Perspective(45.0, (GLfloat)WIDTH / (GLfloat)HEIGHT, 2, 20.0) *
                Translate(vec3(0.0, 0.0, -5.0)) * RotateX(Theta[Xaxis]) *
                RotateY(Theta[Yaxis]) * RotateZ(Theta[Zaxis]) *
                Translate(vec3(0.0, 0.0, 0.0)));
  glUniformMatrix4fv(Projection, 1, GL_TRUE, projection);

  for (int i = 0; i < numCubes; i++) {
    model_view =
        mat4(Translate(vec3(0.0, 0.0, 0.0)) * RotateX(Cubes[i].theta[Xaxis]) *
             RotateY(Cubes[i].theta[Yaxis]) * RotateZ(Cubes[i].theta[Zaxis]) *
             Translate(vec3(Cubes[i].pos[PosX], Cubes[i].pos[PosY],
                            Cubes[i].pos[PosZ])) *
             Scale(1.0, 1.0, 1.0));
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
    case GLFW_KEY_ESCAPE:
      exit(EXIT_SUCCESS);
      break;
    case GLFW_KEY_Q:
      exit(EXIT_SUCCESS);
      break;
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

    case GLFW_KEY_SPACE:
      shuffleCube();
      printf("\n*** Shuffling cube ***\n");

    case GLFW_KEY_H:
      printf("Press h to get help \n");
      printf("Press i to initialize the pose \n");
      printf("Press c to change color \n");
      printf("Press q to quit \n");
      printf("Mouse Right Click to change the object shape type \n");
      printf("Mouse Left Click to change the draw mode \n");
      break;
    }
  }
}

void mouse_button_callback(GLFWwindow *window, int button, int action,
                           int mods) {
  if (action == GLFW_PRESS) {
    switch (button) {
    // change the object shape type
    case GLFW_MOUSE_BUTTON_RIGHT:
      break;
    case GLFW_MOUSE_BUTTON_MIDDLE:
      break;
    // change draw mode
    case GLFW_MOUSE_BUTTON_LEFT:
      double x, y;
      glfwGetCursorPos(window, &x, &y);

      int current_width, current_height;
      glfwGetWindowSize(window, &current_width, &current_height);
      y = current_height - y;

      unsigned char pixel[4];
      glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
      int R = (int)pixel[0], G = (int)pixel[1], B = (int)pixel[2];
      std::cout << R << std::endl;
      std::cout << G << std::endl;
      std::cout << B << std::endl;

      break;
      // set how the triangles are drawn;
      // wireframe (i.e., as lines)s olid mode break;
    }
  }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(
      0, 0, width,
      height); // may not need this since the default is usually the window size

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

  double frameRate = 120, currentTime, previousTime = 0.0;
  while (!glfwWindowShouldClose(window)) {
    // rotate in 120 fps
    currentTime = glfwGetTime();
    if (currentTime - previousTime >= 1 / frameRate) {
      previousTime = currentTime;
    }
    // update screen
    display();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
