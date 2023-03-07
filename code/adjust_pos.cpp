///////////////////////////////////////////////////////////////////////////////
//
// Author:	Jesus Rafael Rijo Candelario (Mercer University)
// Date:	02/06/2023
// Course:	CSC 415: Graphics Simulation and Visualization
// Instructor:  Dr. A. Pounds
//
// Description: C/C++ program to adjust the angle of the spinning pendulum.
// 		This program DOES NOT SIMULATE a realistic pendulum.
//
///////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

// Standard C++ namespace;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                           FUNCTION PROTOTYPES                             //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

double degrees_to_radians( const double deg ); 

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                        FUNCTION IMPLEMENTATIONS                           //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// Function #1: 
//
// Inputs: rot_angle => Angle of rotation.
// 	   rot_dir   => Direction of rotation (clockwise or counterclockwise).
// 	   rot_flag  => Flag to enable/disable rotation.
//
// Pos:	   Updates the angle of rotation.
//
///////////////////////////////////////////////////////////////////////////////

void adjust_pos( double & x, double & y, double & z, const int option ) 
{
	glm::vec4 pts( x, y, z, 0.0 );
	glm::mat4 rot;
	

/*	
	pts = glm::vec3(x,y,z);

	glm::mat3 aaa = glm::rotate( glm::mat3(1.0f), 0.1f, glm::vec2(1.0f,0.0f) );

	float aaa[9] = { 1, 0, 0, 0, cos(0.1), -sin(0.1), 0, sin(0.1), cos(0.1) }
	glm::mat3
*/


	switch( option ) {
		case 1:
			rot = glm::rotate( glm::mat4(1.0f),  0.1f, glm::vec3(1.0f,0.0f,0.0f) );
			pts = rot * pts;
			x = pts[0]; y = pts[1]; z = pts[2];
			break;
		case 2:
			rot = glm::rotate( glm::mat4(1.0f), -0.1f, glm::vec3(1.0f,0.0f,0.0f) );
			pts = rot * pts;
			x = pts[0]; y = pts[1]; z = pts[2];
			break;
		case 3:
			rot = glm::rotate( glm::mat4(1.0f),  0.1f, glm::vec3(0.0f,1.0f,0.0f) );
			pts = rot * pts;
			x = pts[0]; y = pts[1]; z = pts[2];
			break;
		case 4:		
			rot = glm::rotate( glm::mat4(1.0f), -0.1f, glm::vec3(0.0f,1.0f,0.0f) );
			pts = rot * pts;
			x = pts[0]; y = pts[1]; z = pts[2];
			break;
		default:
			break;
	}

	cout << x << " " << y << " " << z << endl;
}


double degrees_to_radians( const double deg ) 
{
	return deg * ( 3.1416 / 180.0 );
}
