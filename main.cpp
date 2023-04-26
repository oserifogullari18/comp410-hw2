//
//  Display a rotating cube
//

#include "Angel.h"

typedef vec4  color4;
typedef vec4  point4;

const int NumVertices = 972; //(6 faces)(2 triangles/face)(3 vertices/triangle)(27 cube)

point4 points[NumVertices];
color4 colors[NumVertices];



// Vertices of a unit cube centered at origin, sides aligned with axes
point4 vertices[] = {
    point4( -0.6, -0.6, 0.3, 1.0 ),
    point4( -0.6, -0.3, 0.3, 1.0 ),
    point4( -0.3, -0.3, 0.3, 1.0 ),
    point4( -0.3, -0.6, 0.3, 1.0 ),
    point4( -0.6, -0.6, 0.0, 1.0 ),
    point4( -0.6, -0.3, 0.0, 1.0 ),
    point4( -0.3, -0.3, 0.0, 1.0 ),
    point4( -0.3, -0.6, 0.0, 1.0 ),
    
    point4( -0.25, -0.6, 0.3, 1.0 ),
    point4( -0.25, -0.3, 0.3, 1.0 ),
    point4( 0.05, -0.3, 0.3, 1.0 ),
    point4( 0.05, -0.6, 0.3, 1.0 ),
    point4( -0.25, -0.6, 0.0, 1.0 ),
    point4( -0.25, -0.3, 0.0, 1.0 ),
    point4( 0.05, -0.3, 0.0, 1.0 ),
    point4( 0.05, -0.6, 0.0, 1.0 ),
    
    point4( 0.1, -0.6, 0.3, 1.0 ),
    point4( 0.1, -0.3, 0.3, 1.0 ),
    point4( 0.4, -0.3, 0.3, 1.0 ),
    point4( 0.4, -0.6, 0.3, 1.0 ),
    point4( 0.1, -0.6, 0.0, 1.0 ),
    point4( 0.1, -0.3, 0.0, 1.0 ),
    point4( 0.4, -0.3, 0.0, 1.0 ),
    point4( 0.4, -0.6, 0.0, 1.0 ),
    
    point4( -0.6, -0.25, 0.3, 1.0 ),
    point4( -0.6, 0.05, 0.3, 1.0 ),
    point4( -0.3, 0.05, 0.3, 1.0 ),
    point4( -0.3, -0.25, 0.3, 1.0 ),
    point4( -0.6, -0.25, 0.0, 1.0 ),
    point4( -0.6, 0.05, 0.0, 1.0 ),
    point4( -0.3, 0.05, 0.0, 1.0 ),
    point4( -0.3, -0.25, 0.0, 1.0 ),
    
    point4( -0.25, -0.25, 0.3, 1.0 ),
    point4( -0.25, 0.05, 0.3, 1.0 ),
    point4( 0.05, 0.05, 0.3, 1.0 ),
    point4( 0.05, -0.25, 0.3, 1.0 ),
    point4( -0.25, -0.25, 0.0, 1.0 ),
    point4( -0.25, 0.05, 0.0, 1.0 ),
    point4( 0.05, 0.05, 0.0, 1.0 ),
    point4( 0.05, -0.25, 0.0, 1.0 ),
    
    point4( 0.1, -0.25, 0.3, 1.0 ),
    point4( 0.1, 0.05, 0.3, 1.0 ),
    point4( 0.4, 0.05, 0.3, 1.0 ),
    point4( 0.4, -0.25, 0.3, 1.0 ),
    point4( 0.1, -0.25, 0.0, 1.0 ),
    point4( 0.1, 0.05, 0.0, 1.0 ),
    point4( 0.4, 0.05, 0.0, 1.0 ),
    point4( 0.4, -0.25, 0.0, 1.0 ),
    
    point4( -0.6, 0.1, 0.3, 1.0 ),
    point4( -0.6, 0.4, 0.3, 1.0 ),
    point4( -0.3, 0.4, 0.3, 1.0 ),
    point4( -0.3, 0.1, 0.3, 1.0 ),
    point4( -0.6, 0.1, 0.0, 1.0 ),
    point4( -0.6, 0.4, 0.0, 1.0 ),
    point4( -0.3, 0.4, 0.0, 1.0 ),
    point4( -0.3, 0.1, 0.0, 1.0 ),
    
    point4( -0.25, 0.1, 0.3, 1.0 ),
    point4( -0.25, 0.4, 0.3, 1.0 ),
    point4( 0.05, 0.4, 0.3, 1.0 ),
    point4( 0.05, 0.1, 0.3, 1.0 ),
    point4( -0.25, 0.1, 0.0, 1.0 ),
    point4( -0.25, 0.4, 0.0, 1.0 ),
    point4( 0.05, 0.4, 0.0, 1.0 ),
    point4( 0.05, 0.1, 0.0, 1.0 ),
    
    point4( 0.1, 0.1, 0.3, 1.0 ),
    point4( 0.1, 0.4, 0.3, 1.0 ),
    point4( 0.4, 0.4, 0.3, 1.0 ),
    point4( 0.4, 0.1, 0.3, 1.0 ),
    point4( 0.1, 0.1, 0.0, 1.0 ),
    point4( 0.1, 0.4, 0.0, 1.0 ),
    point4( 0.4, 0.4, 0.0, 1.0 ),
    point4( 0.4, 0.1, 0.0, 1.0 ),

    // second part
    point4( -0.6, -0.6, -0.05, 1.0 ),
    point4( -0.6, -0.3, -0.05, 1.0 ),
    point4( -0.3, -0.3, -0.05, 1.0 ),
    point4( -0.3, -0.6, -0.05, 1.0 ),
    point4( -0.6, -0.6, -0.35, 1.0 ),
    point4( -0.6, -0.3, -0.35, 1.0 ),
    point4( -0.3, -0.3, -0.35, 1.0 ),
    point4( -0.3, -0.6, -0.35, 1.0 ),
    
    point4( -0.25, -0.6, -0.05, 1.0 ),
    point4( -0.25, -0.3, -0.05, 1.0 ),
    point4( 0.05, -0.3, -0.05, 1.0 ),
    point4( 0.05, -0.6, -0.05, 1.0 ),
    point4( -0.25, -0.6, -0.35, 1.0 ),
    point4( -0.25, -0.3, -0.35, 1.0 ),
    point4( 0.05, -0.3, -0.35, 1.0 ),
    point4( 0.05, -0.6, -0.35, 1.0 ),
    
    point4( 0.1, -0.6, -0.05, 1.0 ),
    point4( 0.1, -0.3, -0.05, 1.0 ),
    point4( 0.4, -0.3, -0.05, 1.0 ),
    point4( 0.4, -0.6, -0.05, 1.0 ),
    point4( 0.1, -0.6, -0.35, 1.0 ),
    point4( 0.1, -0.3, -0.35, 1.0 ),
    point4( 0.4, -0.3, -0.35, 1.0 ),
    point4( 0.4, -0.6, -0.35, 1.0 ),
    
    point4( -0.6, -0.25, -0.05, 1.0 ),
    point4( -0.6, 0.05, -0.05, 1.0 ),
    point4( -0.3, 0.05, -0.05, 1.0 ),
    point4( -0.3, -0.25, -0.05, 1.0 ),
    point4( -0.6, -0.25, -0.35, 1.0 ),
    point4( -0.6, 0.05, -0.35, 1.0 ),
    point4( -0.3, 0.05, -0.35, 1.0 ),
    point4( -0.3, -0.25, -0.35, 1.0 ),
    
    point4( -0.25, -0.25, -0.05, 1.0 ),
    point4( -0.25, 0.05, -0.05, 1.0 ),
    point4( 0.05, 0.05, -0.05, 1.0 ),
    point4( 0.05, -0.25, -0.05, 1.0 ),
    point4( -0.25, -0.25, -0.35, 1.0 ),
    point4( -0.25, 0.05, -0.35, 1.0 ),
    point4( 0.05, 0.05, -0.35, 1.0 ),
    point4( 0.05, -0.25, -0.35, 1.0 ),
    
    point4( 0.1, -0.25, -0.05, 1.0 ),
    point4( 0.1, 0.05, -0.05, 1.0 ),
    point4( 0.4, 0.05, -0.05, 1.0 ),
    point4( 0.4, -0.25, -0.05, 1.0 ),
    point4( 0.1, -0.25, -0.35, 1.0 ),
    point4( 0.1, 0.05, -0.35, 1.0 ),
    point4( 0.4, 0.05, -0.35, 1.0 ),
    point4( 0.4, -0.25, -0.35, 1.0 ),
    
    point4( -0.6, 0.1, -0.05, 1.0 ),
    point4( -0.6, 0.4, -0.05, 1.0 ),
    point4( -0.3, 0.4, -0.05, 1.0 ),
    point4( -0.3, 0.1, -0.05, 1.0 ),
    point4( -0.6, 0.1, -0.35, 1.0 ),
    point4( -0.6, 0.4, -0.35, 1.0 ),
    point4( -0.3, 0.4, -0.35, 1.0 ),
    point4( -0.3, 0.1, -0.35, 1.0 ),
    
    point4( -0.25, 0.1, -0.05, 1.0 ),
    point4( -0.25, 0.4, -0.05, 1.0 ),
    point4( 0.05, 0.4, -0.05, 1.0 ),
    point4( 0.05, 0.1, -0.05, 1.0 ),
    point4( -0.25, 0.1, -0.35, 1.0 ),
    point4( -0.25, 0.4, -0.35, 1.0 ),
    point4( 0.05, 0.4, -0.35, 1.0 ),
    point4( 0.05, 0.1, -0.35, 1.0 ),
    
    point4( 0.1, 0.1, -0.05, 1.0 ),
    point4( 0.1, 0.4, -0.05, 1.0 ),
    point4( 0.4, 0.4, -0.05, 1.0 ),
    point4( 0.4, 0.1, -0.05, 1.0 ),
    point4( 0.1, 0.1, -0.35, 1.0 ),
    point4( 0.1, 0.4, -0.35, 1.0 ),
    point4( 0.4, 0.4, -0.35, 1.0 ),
    point4( 0.4, 0.1, -0.35, 1.0 ),
    
    // third part
    point4( -0.6, -0.6, -0.4, 1.0 ),
    point4( -0.6, -0.3, -0.4, 1.0 ),
    point4( -0.3, -0.3, -0.4, 1.0 ),
    point4( -0.3, -0.6, -0.4, 1.0 ),
    point4( -0.6, -0.6, -0.7, 1.0 ),
    point4( -0.6, -0.3, -0.7, 1.0 ),
    point4( -0.3, -0.3, -0.7, 1.0 ),
    point4( -0.3, -0.6, -0.7, 1.0 ),
    
    point4( -0.25, -0.6, -0.4, 1.0 ),
    point4( -0.25, -0.3, -0.4, 1.0 ),
    point4( 0.05, -0.3, -0.4, 1.0 ),
    point4( 0.05, -0.6, -0.4, 1.0 ),
    point4( -0.25, -0.6, -0.7, 1.0 ),
    point4( -0.25, -0.3, -0.7, 1.0 ),
    point4( 0.05, -0.3, -0.7, 1.0 ),
    point4( 0.05, -0.6, -0.7, 1.0 ),
    
    point4( 0.1, -0.6, -0.4, 1.0 ),
    point4( 0.1, -0.3, -0.4, 1.0 ),
    point4( 0.4, -0.3, -0.4, 1.0 ),
    point4( 0.4, -0.6, -0.4, 1.0 ),
    point4( 0.1, -0.6, -0.7, 1.0 ),
    point4( 0.1, -0.3, -0.7, 1.0 ),
    point4( 0.4, -0.3, -0.7, 1.0 ),
    point4( 0.4, -0.6, -0.7, 1.0 ),
    
    point4( -0.6, -0.25, -0.4, 1.0 ),
    point4( -0.6, 0.05, -0.4, 1.0 ),
    point4( -0.3, 0.05, -0.4, 1.0 ),
    point4( -0.3, -0.25, -0.4, 1.0 ),
    point4( -0.6, -0.25, -0.7, 1.0 ),
    point4( -0.6, 0.05, -0.7, 1.0 ),
    point4( -0.3, 0.05, -0.7, 1.0 ),
    point4( -0.3, -0.25, -0.7, 1.0 ),
    
    point4( -0.25, -0.25, -0.4, 1.0 ),
    point4( -0.25, 0.05, -0.4, 1.0 ),
    point4( 0.05, 0.05, -0.4, 1.0 ),
    point4( 0.05, -0.25, -0.4, 1.0 ),
    point4( -0.25, -0.25, -0.7, 1.0 ),
    point4( -0.25, 0.05, -0.7, 1.0 ),
    point4( 0.05, 0.05, -0.7, 1.0 ),
    point4( 0.05, -0.25, -0.7, 1.0 ),
    
    point4( 0.1, -0.25, -0.4, 1.0 ),
    point4( 0.1, 0.05, -0.4, 1.0 ),
    point4( 0.4, 0.05, -0.4, 1.0 ),
    point4( 0.4, -0.25, -0.4, 1.0 ),
    point4( 0.1, -0.25, -0.7, 1.0 ),
    point4( 0.1, 0.05, -0.7, 1.0 ),
    point4( 0.4, 0.05, -0.7, 1.0 ),
    point4( 0.4, -0.25, -0.7, 1.0 ),
    
    point4( -0.6, 0.1, -0.4, 1.0 ),
    point4( -0.6, 0.4, -0.4, 1.0 ),
    point4( -0.3, 0.4, -0.4, 1.0 ),
    point4( -0.3, 0.1, -0.4, 1.0 ),
    point4( -0.6, 0.1, -0.7, 1.0 ),
    point4( -0.6, 0.4, -0.7, 1.0 ),
    point4( -0.3, 0.4, -0.7, 1.0 ),
    point4( -0.3, 0.1, -0.7, 1.0 ),
    
    point4( -0.25, 0.1, -0.4, 1.0 ),
    point4( -0.25, 0.4, -0.4, 1.0 ),
    point4( 0.05, 0.4, -0.4, 1.0 ),
    point4( 0.05, 0.1, -0.4, 1.0 ),
    point4( -0.25, 0.1, -0.7, 1.0 ),
    point4( -0.25, 0.4, -0.7, 1.0 ),
    point4( 0.05, 0.4, -0.7, 1.0 ),
    point4( 0.05, 0.1, -0.7, 1.0 ),
    
    point4( 0.1, 0.1, -0.4, 1.0 ),
    point4( 0.1, 0.4, -0.4, 1.0 ),
    point4( 0.4, 0.4, -0.4, 1.0 ),
    point4( 0.4, 0.1, -0.4, 1.0 ),
    point4( 0.1, 0.1, -0.7, 1.0 ),
    point4( 0.1, 0.4, -0.7, 1.0 ),
    point4( 0.4, 0.4, -0.7, 1.0 ),
    point4( 0.4, 0.1, -0.7, 1.0 ),
 

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
GLfloat  Theta[NumAxes] = { 0, 0, 0 };

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
    // first part with 9 cube
    quad( 1, 0, 3, 2, 1 );
    quad( 2, 3, 7, 6, 0 );
    quad( 3, 0, 4, 7, 3 );
    quad( 6, 5, 1, 2, 0 );
    quad( 4, 5, 6, 7, 0 );
    quad( 5, 4, 0, 1, 5 );
    
    quad( 9, 8, 11, 10, 1 );
    quad( 10, 11, 15, 14, 0 );
    quad( 11, 8, 12, 15, 3 );
    quad( 14, 13, 9, 10, 0 );
    quad( 12, 13, 14, 15, 0 );
    quad( 13, 12, 8, 9, 0 );

    quad( 17, 16, 19, 18, 1 );
    quad( 18, 19, 23, 22, 2 );
    quad( 19, 16, 20, 23, 3 );
    quad( 22, 21, 17, 18, 0 );
    quad( 20, 21, 22, 23, 0 );
    quad( 21, 20, 16, 17, 0 );
    
    quad( 25, 24, 27, 26, 1 );
    quad( 26, 27, 31, 30, 0 );
    quad( 27, 24, 28, 31, 0 );
    quad( 30, 29, 25, 26, 0 );
    quad( 28, 29, 30, 31, 0 );
    quad( 29, 28, 24, 25, 5 );
    
    quad( 33, 32, 35, 34, 1 );
    quad( 34, 35, 39, 38, 0 );
    quad( 35, 32, 36, 39, 0 );
    quad( 38, 37, 33, 34, 0 );
    quad( 36, 37, 38, 39, 0 );
    quad( 37, 36, 32, 33, 0 );
    
    quad( 41, 40, 43, 42, 1 );
    quad( 42, 43, 47, 46, 2 );
    quad( 43, 40, 44, 47, 0 );
    quad( 46, 45, 41, 42, 0 );
    quad( 44, 45, 46, 47, 0 );
    quad( 45, 44, 40, 41, 0 );
    
    quad( 49, 48, 51, 50, 1 );
    quad( 50, 51, 55, 54, 0 );
    quad( 51, 48, 52, 55, 0 );
    quad( 54, 53, 49, 50, 4 );
    quad( 52, 53, 54, 55, 0 );
    quad( 53, 52, 48, 49, 5 );
    
    quad( 57, 56, 59, 58, 1 );
    quad( 58, 59, 63, 62, 0 );
    quad( 59, 56, 60, 63, 0 );
    quad( 62, 61, 57, 58, 4 );
    quad( 60, 61, 62, 63, 0 );
    quad( 61, 60, 56, 57, 0 );
    
    quad( 65, 64, 67, 66, 1 );
    quad( 66, 67, 71, 70, 2 );
    quad( 67, 64, 68, 71, 0 );
    quad( 70, 69, 65, 66, 4 );
    quad( 68, 69, 70, 71, 0 );
    quad( 69, 68, 64, 65, 0 );
    
    // second part
    
    quad( 73, 72, 75, 74, 0 );
    quad( 74, 75, 79, 78, 0 );
    quad( 75, 72, 76, 79, 3 );
    quad( 78, 77, 73, 74, 0 );
    quad( 76, 77, 78, 79, 0 );
    quad( 77, 76, 72, 73, 5 );
    
    quad( 81, 80, 83, 82, 0 );
    quad( 82, 83, 87, 86, 0 );
    quad( 83, 80, 84, 87, 3 );
    quad( 86, 85, 81, 82, 0 );
    quad( 84, 85, 86, 87, 0 );
    quad( 85, 84, 80, 81, 0 );
    
    quad( 89, 88, 91, 90, 0 );
    quad( 90, 91, 95, 94, 2 );
    quad( 91, 88, 92, 95, 3 );
    quad( 94, 93, 89, 90, 0 );
    quad( 92, 93, 94, 95, 0 );
    quad( 93, 92, 88, 89, 0 );
    
    quad( 97, 96, 99, 98, 0 );
    quad( 98, 99, 103, 102, 0 );
    quad( 99, 96, 100, 103, 0 );
    quad( 102, 101, 97, 98, 0 );
    quad( 100, 101, 102, 103, 0 );
    quad( 101, 100, 96, 97, 5 );
    
    quad( 105, 104, 107, 106, 0 );
    quad( 106, 107, 111, 110, 0 );
    quad( 107, 104, 108, 111, 0 );
    quad( 110, 109, 105, 106, 0 );
    quad( 108, 109, 110, 111, 0 );
    quad( 109, 108, 104, 105, 0 );
    
    quad( 113, 112, 115, 114, 0 );
    quad( 114, 115, 119, 118, 2 );
    quad( 115, 112, 116, 119, 0 );
    quad( 118, 117, 113, 114, 0 );
    quad( 116, 117, 118, 119, 0 );
    quad( 117, 116, 112, 113, 0 );
    
    quad( 121, 120, 123, 122, 0 );
    quad( 122, 123, 127, 126, 0 );
    quad( 123, 120, 124, 127, 0 );
    quad( 126, 125, 121, 122, 4 );
    quad( 124, 125, 126, 127, 0 );
    quad( 125, 124, 120, 121, 5 );
    
    quad( 129, 128, 131, 130, 0 );
    quad( 130, 131, 135, 134, 0 );
    quad( 131, 128, 132, 135, 0 );
    quad( 134, 133, 129, 130, 4 );
    quad( 132, 133, 134, 135, 0 );
    quad( 133, 132, 128, 129, 0 );
    
    quad( 137, 136, 139, 138, 0 );
    quad( 138, 139, 143, 142, 2 );
    quad( 139, 136, 140, 143, 0 );
    quad( 142, 141, 137, 138, 4 );
    quad( 140, 141, 142, 143, 0 );
    quad( 141, 140, 136, 137, 0 );
    
    // third part
    
    quad( 145, 144, 147, 146, 0 );
    quad( 146, 147, 151, 150, 0 );
    quad( 147, 144, 148, 151, 3 );
    quad( 150, 149, 145, 146, 0 );
    quad( 148, 149, 150, 151, 6 );
    quad( 149, 148, 144, 145, 5 );
    
    quad( 153, 152, 155, 154, 0 );
    quad( 154, 155, 159, 158, 0 );
    quad( 155, 152, 156, 159, 3 );
    quad( 158, 157, 153, 154, 0 );
    quad( 156, 157, 158, 159, 6 );
    quad( 157, 156, 152, 153, 0 );
    
    quad( 161, 160, 163, 162, 0 );
    quad( 162, 163, 167, 166, 2 );
    quad( 163, 160, 164, 167, 3 );
    quad( 166, 165, 161, 162, 0 );
    quad( 164, 165, 166, 167, 6 );
    quad( 165, 164, 160, 161, 0 );
    
    quad( 169, 168, 171, 170, 0 );
    quad( 170, 171, 175, 174, 0 );
    quad( 171, 168, 172, 175, 0 );
    quad( 174, 173, 169, 170, 0 );
    quad( 172, 173, 174, 175, 6 );
    quad( 173, 172, 168, 169, 5 );
    
    quad( 177, 176, 179, 178, 0 );
    quad( 178, 179, 183, 182, 0 );
    quad( 179, 176, 180, 183, 0 );
    quad( 182, 181, 177, 178, 0 );
    quad( 180, 181, 182, 183, 6 );
    quad( 181, 180, 176, 177, 0 );
    
    quad( 185, 184, 187, 186, 0 );
    quad( 186, 187, 191, 190, 2 );
    quad( 187, 184, 188, 191, 0 );
    quad( 190, 189, 185, 186, 0 );
    quad( 188, 189, 190, 191, 6 );
    quad( 189, 188, 184, 185, 0 );
    
    quad( 193, 192, 195, 194, 0 );
    quad( 194, 195, 199, 198, 0 );
    quad( 195, 192, 196, 199, 0 );
    quad( 198, 197, 193, 194, 4 );
    quad( 196, 197, 198, 199, 6 );
    quad( 197, 196, 192, 193, 5 );
    
    quad( 201, 200, 203, 202, 0 );
    quad( 202, 203, 207, 206, 0 );
    quad( 203, 200, 204, 207, 0 );
    quad( 206, 205, 201, 202, 4 );
    quad( 204, 205, 206, 207, 6 );
    quad( 205, 204, 200, 201, 0 );
    
    quad( 209, 208, 211, 210, 0 );
    quad( 210, 211, 215, 214, 2 );
    quad( 211, 208, 212, 215, 0 );
    quad( 214, 213, 209, 210, 4 );
    quad( 212, 213, 214, 215, 6 );
    quad( 213, 212, 208, 209a, 0 );
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
    projection = Perspective(45.0f, 1.0, 0.1, 100.0); // Ortho(): user-defined function in mat.h
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
    const vec3 displacement( 0.0 , 0.0 , -3.0);
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
            update();
        }
        
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}



