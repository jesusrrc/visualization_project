///////////////////////////////////////////////////////////////////////////////
//
// Author:	Jesus Rafael Rijo Candelario (Mercer University)
// Date:	01/29/2023
// Course:	CSC 415: Graphics Simulation and Visualization (Spring 2023)
// Instructor:  Dr. A. Pounds
//
// Description: C/C++ program for the Window Manager Conversion Projection.
//
///////////////////////////////////////////////////////////////////////////////

#include "stdio.h"

// C++ libraries.
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

// Graphics libraries.
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

// Custom programs/libraries.
#include "Utils.h"
#include "process_stl.cpp"
#include "adjust_angle.cpp"
#include "get_grid.cpp"

#define numVAOs 1
#define numVBOs 2

// Namespace used by this program to cleanly used global variables.
namespace main_ns {
	double rot_angle  = 0.0;  // Angle of rotation.
	double rot_factor = 0.05; // Step-size factor.
	int rot_dir 	  = 1;    // Direction of rotation.
	int rot_flag 	  = 1;	  // Flag to specify if the pendulum must rotate.

	float fov	  = 1.7;  // FOV for glm::perspective.

	double x 	  = 10.0; // Positions of the camera
	double y 	  = 10.0; // (deprecated).
	double z 	  = 0.0;

	double alpha	  = 0.0;  // Angles of the camera.
	double theta 	  = 0.0;
}

// Standard C++ namespace and custom namespace.
using namespace std;
using namespace main_ns;

///////////////////////////////////////////////////////////////////////////////
//								 	     //
//			       GLOBAL VARIABLES			             //
//									     //
///////////////////////////////////////////////////////////////////////////////

Utils util = Utils();
float cameraX, cameraY, cameraZ;
float cubeLocX, cubeLocY, cubeLocZ;
GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

// Variable allocation for display
GLuint mvLoc, projLoc, lookAtLoc;
int width, height;
float aspect;

// NOTE: The program will move the camera by modifying lookAtMat and vMat.
glm::mat4 pMat, mMat, mvMat;
glm::mat4 lookAtMat = glm::lookAt( glm::vec3(10.0f, 10.0f, 0.0f), 
		                   glm::vec3(0.0f,   0.0f, 0.0f),
                                   glm::vec3(0.0f,   1.0f, 0.0f)  );
glm::mat4 vMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
int num_vertices = 0;
int num_pts = 0;

///////////////////////////////////////////////////////////////////////////////
//									     //
//			     FUNCTION PROTOTYPES		             //
//									     //
///////////////////////////////////////////////////////////////////////////////

string getFileName( int option );
void setupVertices( int option ); 
void init(GLFWwindow* window);
void display(GLFWwindow* window, double currentTime); 
void keyboard_button_callback( GLFWwindow* window, int key, int scancode, 
int action, int mods );

///////////////////////////////////////////////////////////////////////////////
//									     //
//			   FUNCTION IMPLEMENTATIONS 	                     //
//									     //
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// Function #1: 
//
// Inputs: option => Int denoting the path to the STL file.
//
// Pos:	   Returns the path for the right path.
//
///////////////////////////////////////////////////////////////////////////////

string getFileName( int option ) 
{
	switch( option ) {
    		case 1:
      			return "./stls/pendulum_part1.stl";   
    		case 2:
	      		return "./stls/pendulum_part2.stl";   
	    	case 3:
	      		return "./stls/pendulum_part3.stl";   
	    	case 4:
	      		return "./stls/pendulum_part4.stl";   
	    	default:
	      		return "./stls/pendulum_part4.stl";   
  	}
}

///////////////////////////////////////////////////////////////////////////////
//
// Function #2: 
//
// Inputs: option => Int denoting the path to the STL file.
//
// Pos:	   Builds the VBO/VAO logic to load the vertices/colors of a STL
//         file into memory.
//
///////////////////////////////////////////////////////////////////////////////

void setupVertices( int option ) 
{
	// Vectors to dynamically read information from the STL file.
	vector<float> vertexPositions_vec;
	vector<float> vertexColors_vec;

  	// Use ONE vao as before	
  	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);

    	// Use TWO virtual buffer objects, vbo[0] is for the vertexPositions
	glGenBuffers( 2, vbo );

	// IMPORTANT: Reading vertices from the file.
  	num_pts = 0;
//	process_stl( num_pts, vertexPositions_vec, vertexColors_vec, option, getFileName( option ) );	
	
	get_grid_pts( num_pts, vertexPositions_vec, vertexColors_vec );
	cout << num_pts << endl;	


	// Converting float vectors into static float arrays. NOTE: Using
	// non-static ints to specify array size WILL NOT work in older C++
	// compilers.
	float vertexPositions[vertexPositions_vec.size()];
	float vertexColors[vertexColors_vec.size()];

	// Copying the data of the vectors into the arrays.
	copy(vertexPositions_vec.begin(), vertexPositions_vec.end(), vertexPositions );
	copy(vertexColors_vec.begin(), vertexColors_vec.end(), vertexColors );

  	// vbo[0] is for the vertexPositions and vbo[1] is for the vertexColors. NOTE:
	// sizeof() should work as in the previous example, as the arrays are static.
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
  	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
  	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColors), vertexColors, GL_STATIC_DRAW);
}

///////////////////////////////////////////////////////////////////////////////
//
// Function #3: 
//
// Inputs: window => Pointer to window used by GLFW.
//
// Pos:	   Specifies the rendering program and the coordinates of the camera 
// 	   and pendulum.
//
///////////////////////////////////////////////////////////////////////////////

void init(GLFWwindow* window) 
{
	renderingProgram = Utils::createShaderProgram("vertShader.glsl", "fragShader.glsl");

    	// These are the camera positions and cube locations.  We will need them to
    	// set up the modelview and perspective matrices.  Note the scope of the variables.
	cameraX = 0.0f; cameraY = 0.0f; cameraZ = 8.0f;
	cubeLocX = 0.0f; cubeLocY = -2.0f; cubeLocZ = 0.0f;
}

///////////////////////////////////////////////////////////////////////////////
//
// Function #4: 
//
// Inputs: window      => Pointer to window used by GLFW.
// 	   currentTime => Current time at runtime.
//
// Pos:	   Defines the display function used by GLFW.
//
///////////////////////////////////////////////////////////////////////////////

void display(GLFWwindow* window, double currentTime) 
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glUseProgram(renderingProgram);

	// Setting up vertices.
	setupVertices(0);
		
	// These are getting the memory locations of the modelview and projection
	// matrices from the renderer.
	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
	lookAtLoc = glGetUniformLocation(renderingProgram, "lookAt_matrix");

	// Now we set the perspective based on the window size and the aspect ratio.
	// The glm::perspective function rerturn the projection matrix.
	glfwGetFramebufferSize(window, &width, &height);
	aspect = (float)width / (float)height;
	pMat = glm::perspective(main_ns::fov, aspect, 0.1f, 1000.0f);

	// Now we are going to move the camera and cube to set up the modelview matrix.
	//  -- NOTE -- now using lookAt to specify camera position, so set the vmat to
	//  the identity matrix using glm:translate
	//vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	// Now let's also leave the cube at the center of the scene
	//mMat = glm::translate(glm::mat4(1.0f), glm::vec3(cubeLocX, cubeLocY, cubeLocZ));
	mMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,0.0f));

	

	// OpenGL undestands that the following line is actually MATRIX MULTIPLICATION and 
	// produces the modelview matrix from vMat and mMat.
	mvMat = vMat * mMat;

	// Specifying lookat matrix with the angle adjustements.
	lookAtMat = glm::lookAt( glm::vec3( 15 * cos(main_ns::theta) * sin(main_ns::alpha),
					    15 * sin(main_ns::theta),
					    15 * cos(main_ns::theta) * cos(main_ns::alpha) ),
	                         glm::vec3( sin(main_ns::alpha) - 3.14f/2.0f, 
				    	    0.0f, 
				            cos(main_ns::theta) - 3.14f/2.0f ) ,
					    glm::vec3(0.0f, 1.0f, 0.0f)  );

	// Now place the modelview and projection matrices in the memory locations
	// we recovered earlier from the renderer.
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
	glUniformMatrix4fv(lookAtLoc, 1, GL_FALSE, glm::value_ptr(lookAtMat));

	// Now we are going to bind the vertex attribute array buffer and then 
	// tell GL what type of data is in the vbo.  They are
	// floating point vertices arranged as 4 component vectors.
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, 0);
	// And now we tell GL that this is the array we want to draw with glDrawArrays
	glEnableVertexAttribArray(0);

	// And now the colors
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, 0);
	// And now we tell GL that this is the array we want to draw with glDrawArrays
	glEnableVertexAttribArray(1);

	// Turn on the Z-Buffer depth test.
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Drawing the vertices.
	int final_size = (int) ( num_pts / 4 );	
	glDrawArrays(GL_TRIANGLES, 0, final_size );
}


///////////////////////////////////////////////////////////////////////////////
//
// Function #5: 
//
// Inputs: window => Pointer to window used by GLFW.
// 	   button => Keyboard key pressed.
// 	   action => Type of action of key.
// 	   mods   => Modifier keys. 
//
// Pos:	   Handles mouse inputs.
//
///////////////////////////////////////////////////////////////////////////////

void mouse_button_callback( GLFWwindow* window, int button, int action, int mods ) 
{
	// Right mouse button: Increases rotation factor.
	if( button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS ) {
		if( main_ns::rot_factor <= 3.1416 / 2.0 ) {
			main_ns::rot_factor += 0.05; 
		}
	}
	// Left mouse button: Decreases rotation factor (Beware of floating-
	// point arithmetic).
	if( button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS ) {
		if( main_ns::rot_factor > 1e-5 ) {
			main_ns::rot_factor -= 0.05; 
		}
	}
	// Middle mouse button: Resets both the rotation angle and 
	// rotation factor.
	if( button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS ) {
		main_ns::rot_angle  = 0.0; 
		main_ns::rot_factor = 0.05; 
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// Function #6: 
//
// Inputs: window   => Pointer to window used by GLFW.
// 	   button   => Keyboard key pressed.
// 	   scancode => System-specific scancode of the key
// 	   action   => Type of action of key.
// 	   mods     => Modifier keys. 
//
// Pos:	   Handles keyboard inputs.
//
///////////////////////////////////////////////////////////////////////////////

void keyboard_button_callback( GLFWwindow* window, int key, int scancode, 
int action, int mods ) 
{
	double x,y,z;
	glm::mat4 rot;

	// Up camera move.
	if( key == GLFW_KEY_UP && action == GLFW_PRESS ) {
		main_ns::theta += 0.05;
	}
	// Down camera move.
	if( key == GLFW_KEY_DOWN && action == GLFW_PRESS ) {
		main_ns::theta -= 0.05;
	}
	// Right camera move.
	if( key == GLFW_KEY_RIGHT && action == GLFW_PRESS ) {
		main_ns::alpha += 0.05;
	}
	// Left camera move.
	if( key == GLFW_KEY_LEFT && action == GLFW_PRESS ) {
		main_ns::alpha -= 0.05;
	}
	// Page up (zooms in).
	if( key == GLFW_KEY_PAGE_UP && action == GLFW_REPEAT && main_ns::fov > 0.02 ) {
		main_ns::fov -= 0.05;
	}
	// Page down (zooms out).
	if( key == GLFW_KEY_PAGE_DOWN && action == GLFW_REPEAT && main_ns::fov < 3.05 ) {
		main_ns::fov += 0.01;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// Main function:
//
///////////////////////////////////////////////////////////////////////////////

int main(void) 
{
	if (!glfwInit()) { 
		exit(EXIT_FAILURE); 
	}

	// Building window.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(600, 600, "CSC 415 -- Visualization/Simulation Project", NULL, NULL);
	glfwMakeContextCurrent(window);

    	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) { 
		exit(EXIT_FAILURE); 
	}
	glfwSwapInterval(1);

	// Initializing window and setting clicks/keys functions.
	init(window);
	glfwSetMouseButtonCallback( window, mouse_button_callback );
	glfwSetKeyCallback( window, keyboard_button_callback );

	// Handles display while the user does NOT close the window.
	while (!glfwWindowShouldClose(window)) {
		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Calls for termination.
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
