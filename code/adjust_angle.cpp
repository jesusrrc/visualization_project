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

// Standard C++ namespace;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                           FUNCTION PROTOTYPES                             //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

void adjust_angle( double & rot_angle, const double rot_factor, int & rot_dir, const int rot_flag );

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

void adjust_angle( double & rot_angle, const double rot_factor, int & rot_dir, const int rot_flag ) 
{
	// Check in case the program cannot rotate.
	if( !rot_flag ) {
		return;
	}

	// Spinning counterclockwise. 
	if( rot_dir == 1 && rot_angle < 3.1416/2.0 ) {
		rot_angle += rot_factor;
	}	
	else if( rot_angle > 3.1416/2.0 ) {
		rot_dir = -1;
	}

	// Spinning clockwise.
	if( rot_dir == -1 && rot_angle > -3.1416/2.0 ) {
		rot_angle -= rot_factor;
	}	
	else if( rot_angle < -3.1416/2.0 ) {
		rot_dir = 1;
	}
}
