//
//  Display a rotating cube
//

#include "Angel.h"

typedef vec4  color4;
typedef vec4  point4;

const int NumVertices = 324; //(6 faces)(2 triangles/face)(3 vertices/triangle)

point4 points[NumVertices];
color4 colors[NumVertices];



// Vertices of a unit cube centered at origin, sides aligned with axes
point4 vertices[] = {
    point4( -0.6, -0.6, -0.3, 1.0 ),
    point4( -0.6, -0.3, -0.3, 1.0 ),
    point4( -0.3, -0.3, -0.3, 1.0 ),
    point4( -0.3, -0.6, -0.3, 1.0 ),
    point4( -0.6, -0.6, -0.6, 1.0 ),
    point4( -0.6, -0.3, -0.6, 1.0 ),
    point4( -0.3, -0.3, -0.6, 1.0 ),
    point4( -0.3, -0.6, -0.6, 1.0 ),
    point4(  0.0, -0.3, -0.6, 1.0 ),
    point4(  0.0, -0.6, -0.6, 1.0 ),
    point4(  0.0, -0.3, -0.3, 1.0 ),
    point4(  0.0, -0.6, -0.3, 1.0 ),
    point4(  0.3, -0.3, -0.6, 1.0 ),
    point4(  0.3, -0.6, -0.6, 1.0 ),
    point4(  0.3, -0.3, -0.3, 1.0 ),
    point4(  0.3, -0.6, -0.3, 1.0 ),
    
    point4( -0.6, 0.0, -0.3, 1.0 ),
    point4( -0.6, 0.0, -0.6, 1.0 ),
    point4( -0.3, 0.0, -0.6, 1.0 ),
    point4( -0.3, 0.0, -0.3, 1.0 ),
    point4(  0.0, 0.0, -0.3, 1.0 ),
    point4(  0.0, 0.0, -0.6, 1.0 ),
    point4(  0.3, 0.0, -0.6, 1.0 ),
    point4(  0.3, 0.0, -0.3, 1.0 ),
    
    point4( -0.6, 0.3, -0.3, 1.0 ),
    point4( -0.6, 0.3, -0.6, 1.0 ),
    point4( -0.3, 0.3, -0.6, 1.0 ),
    point4( -0.3, 0.3, -0.3, 1.0 ),
    point4(  0.0, 0.3, -0.3, 1.0 ),
    point4(  0.0, 0.3, -0.6, 1.0 ),
    point4(  0.3, 0.3, -0.6, 1.0 ),
    point4(  0.3, 0.3, -0.3, 1.0 ),
};



// RGBA olors
color4 vertex_colors[8] = {
    color4( 0.0, 0.0, 0.0, 1.0 ),  // black
    color4( 1.0, 0.0, 0.0, 1.0 ),  // red
    color4( 1.0, 1.0, 0.0, 1.0 ),  // yellow
    color4( 0.0, 1.0, 0.0, 1.0 ),  // green
    color4( 0.0, 0.0, 1.0, 1.0 ),  // blue
    color4( 1.0, 0.0, 1.0, 1.0 ),  // magenta
    color4( 0.0, 1.0, 1.0, 1.0 ),  // cyan
    color4( 1.0, 1.0, 1.0, 1.0 )  // white
};

// Array of rotation angles (in degrees) for each coordinate axis
enum { Xaxis = 0, Yaxis = 1, Zaxis = 2, NumAxes = 3 };
int      Axis = Xaxis;
GLfloat  Theta[NumAxes] = { 5, 10, 0 };

// Model-view and projection matrices uniform location
GLuint  ModelView, Projection;

//----------------------------------------------------------------------------

// quad generates two triangles for each face and assigns colors to the vertices
int Index = 0;

void quad( int a, int b, int c, int d, int color )
{
    colors[Index] = vertex_colors[color]; points[Index] = vertices[a]; Index++;
    colors[Index] = vertex_colors[color]; points[Index] = vertices[b]; Index++;
    colors[Index] = vertex_colors[color]; points[Index] = vertices[c]; Index++;
    colors[Index] = vertex_colors[color]; points[Index] = vertices[a]; Index++;
    colors[Index] = vertex_colors[color]; points[Index] = vertices[c]; Index++;
    colors[Index] = vertex_colors[color]; points[Index] = vertices[d]; Index++;

}

//----------------------------------------------------------------------------

// generate 12 triangles: 36 vertices and 36 colors

void colorcube()
{
    quad( 1, 0, 3, 2, 1 );
    quad( 2, 3, 7, 6, 2 );
    quad( 3, 0, 4, 7, 3 );
    quad( 6, 5, 1, 2, 6 );
    quad( 4, 5, 6, 7, 4 );
    quad( 5, 4, 0, 1, 5 );
    quad( 2, 3, 11, 10, 1 );
    quad( 10, 11, 9, 8, 2 );
    quad( 11, 3, 7, 9, 3 );
    quad( 8, 6, 2, 10, 6 );
    quad( 7, 6, 8, 9, 4 );
    quad( 6, 7, 3, 2, 5 );
    quad( 10, 11, 15, 14, 1 );
    quad( 14, 15, 13, 12, 2 );
    quad( 15, 11, 9, 13, 3 );
    quad( 12, 8, 10, 14, 6 );
    quad( 9, 8, 12, 13, 4 );
    quad( 8, 9, 11, 10, 5 );

    quad( 16, 1, 2, 19, 1 );
    quad( 19, 2, 6, 18, 2 );
    quad( 4, 1, 5, 6, 3 );
    quad( 18, 17, 16, 19, 6 );
    quad( 5, 17, 18, 6, 4 );
    quad( 17, 5, 1, 16, 5 );
    quad( 19, 2, 10, 20, 1 );
    quad( 20, 10, 8, 21, 2 );
    quad( 10, 2, 6, 8, 3 );
    quad( 21, 18, 19, 20, 6 );
    quad( 6, 18, 21, 8, 4 );
    quad( 18, 6, 2, 19, 5 );
    quad( 20, 10, 14, 23, 1 );
    quad( 23, 14, 12, 22, 2 );
    quad( 14, 10, 8, 12, 3 );
    quad( 22, 21, 20, 23, 6 );
    quad( 8, 21, 22, 12, 4 );
    quad( 21, 8, 10, 20, 5 );
    
    quad( 24, 16, 19, 27, 1 );
    quad( 27, 19, 18, 26, 2 );
    quad( 5, 16, 17, 18, 3 );
    quad( 26, 25, 24, 27, 6 );
    quad( 17, 25, 26, 18, 4 );
    quad( 25, 17, 16, 24, 5 );
    quad( 27, 19, 20, 28, 1 );
    quad( 28, 20, 21, 29, 2 );
    quad( 20, 19, 18, 21, 3 );
    quad( 29, 26, 27, 28, 6 );
    quad( 18, 26, 29, 21, 4 );
    quad( 26, 18, 19, 27, 5 );
    quad( 28, 20, 23, 31, 1 );
    quad( 31, 23, 22, 30, 2 );
    quad( 23, 20, 21, 22, 3 );
    quad( 30, 29, 28, 31, 6 );
    quad( 21, 29, 30, 22, 4 );
    quad( 29, 21, 20, 28, 5 );
}



//---------------------------------------------------------------------
//
// init
//

void init()
{
    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "/Users/ozlemserifogullari/Documents/comp410/hw0/HW0/HW0/vshader.glsl", "/Users/ozlemserifogullari/Documents/comp410/hw0/HW0/HW0/fshader.glsl" );
    glUseProgram( program );
    
    colorcube(); // create the cube in terms of 6 faces each of which is made of two triangles

    // Create a vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );
    
    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(points), points );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors );
    


    // set up vertex arrays
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
   
    GLuint vColor = glGetAttribLocation( program, "vColor" );
    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points)) );
   
    
    
    // Retrieve transformation uniform variable locations
    ModelView = glGetUniformLocation( program, "ModelView" );
    Projection = glGetUniformLocation( program, "Projection" );
    
    
    // Set projection matrix
    mat4  projection;
    projection = Ortho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // Ortho(): user-defined function in mat.h
    glUniformMatrix4fv( Projection, 1, GL_TRUE, projection );
    
    glEnable( GL_DEPTH_TEST );
    glClearColor( 1.0, 1.0, 1.0, 1.0 );
}

//---------------------------------------------------------------------
//
// display
//

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    const vec3 displacement( 0.0 , 0.0 , 0.0);
    mat4  model_view = (  Translate( displacement ) * Scale(1.0, 1.0, 1.0)
                            *
                            RotateX( Theta[Xaxis] ) *
                            RotateY( Theta[Yaxis] ) *
                            RotateZ( Theta[Zaxis] )
                            );  // Scale(), Translate(), RotateX(), RotateY(), RotateZ(): user-defined functions in mat.h
    glUniformMatrix4fv( ModelView, 1, GL_TRUE, model_view );
    glDrawArrays( GL_TRIANGLES, 0, NumVertices );
    glFlush();

            

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    switch( key ) {
        case GLFW_KEY_ESCAPE: case GLFW_KEY_Q:
            exit( EXIT_SUCCESS );
            break;
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if ( action == GLFW_PRESS ) {
        switch( button ) {
            case GLFW_MOUSE_BUTTON_RIGHT:    Axis = Xaxis;  break;
            case GLFW_MOUSE_BUTTON_MIDDLE:  Axis = Yaxis;  break;
            case GLFW_MOUSE_BUTTON_LEFT:   Axis = Zaxis;  break;
        }
    }
}

void update( void )
{
    Theta[Axis] += 4.0;

    if ( Theta[Axis] > 360.0 ) {
        Theta[Axis] -= 360.0;
    }
}

void translateVertices(GLfloat* vertices, GLfloat* newVertices, float xAmount, float yAmount, float zAmount, int vertexAttributeNumber, int iterationNumber)
{
    for (int i = 0; i < iterationNumber; i++) {
        newVertices[i] = vertices[i];

        if(xAmount != 0 && i%vertexAttributeNumber % 9 == 0) {
            newVertices[i] += xAmount;
        }

        if(yAmount != 0 && i%vertexAttributeNumber % 9 == 1) {
            newVertices[i] += yAmount;
        }

        if(zAmount != 0 && i%vertexAttributeNumber % 9 == 2) {
            newVertices[i] += zAmount;
        }
    }
};

//---------------------------------------------------------------------
//
// main
//

int main()
{
    if (!glfwInit())
            exit(EXIT_FAILURE);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    
    GLFWwindow* window = glfwCreateWindow(512, 512, "Spin Cube", NULL, NULL);
    glfwMakeContextCurrent(window);
    
    if (!window)
        {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    
    init();

    double frameRate = 120, currentTime, previousTime = 0.0;
    while (!glfwWindowShouldClose(window))
    {
        currentTime = glfwGetTime();
        if (currentTime - previousTime >= 1/frameRate){
            previousTime = currentTime;
//            update();
        }
        
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}








