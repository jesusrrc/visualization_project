///////////////////////////////////////////////////////////////////////////////
//
// Author:	Jesus Rafael Rijo Candelario (Mercer University)
// Date:	02/06/2023
// Course:	CSC 415: Graphics Simulation and Visualization
// Instructor:  Dr. A. Pounds
//
// Description: C/C++ program to parse STL file generated from Blender/Vizard.
//
///////////////////////////////////////////////////////////////////////////////

// C libraries.
#include "stdlib.h"
#include "stdio.h"

// C++ libraries.
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// Standard C++ namespace;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                           FUNCTION PROTOTYPES                             //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

void process_stl( int & size, vector<float> & vertexPositions, 
                  vector<float> & vertexColors, const int option, 
                  const string filename );
void add_color( vector<float> & vertexColors, const int option );

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                        FUNCTION IMPLEMENTATIONS                           //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// Function #1: 
//
// Inputs: size 	   => A variable to store the total number of coordinates.
// 	   vertexPositions => FLoat ector of vertex coordinates.
// 	   vertexColors    => Float vector of colors.
// 	   option          => Color for segment.
// 	   filename        => Name of STL file.
//
// Pos:	   Parses the contents of the given STL file.
//
///////////////////////////////////////////////////////////////////////////////

void process_stl( int & size, vector<float> & vertexPositions, 
vector<float> & vertexColors, const int option, const string filename )
{
	// Sstream and strings for input handling.
	string input, tmp;
	stringstream ss;

	// Indices.
	int i = 0;
	int j = 0;

	// Opening hard-coded file.
	fstream fp(filename.c_str(), ios::in );
	if( fp.fail() ) {
		cerr << "File pointer error." << endl;
		exit(0);
	}

	// Clearing file pointer and setting it to the start.
	fp.clear();
	fp.seekg(0,ios::beg);
	
	// Initializing vertices.
	while( getline( fp, input ) ) {
		// Parsing lines with vertices.
		if( input.find("vertex") != string::npos ) {
			input.erase(0,7);
			stringstream ss( input );

			// Converting c-strings to floats.
			j = 0;
			while( getline( ss, tmp, ' ' ) && j != 3 ) { 			
				vertexPositions.push_back( atof( tmp.c_str() ) );
				      i++;
			        j++;	
			}
			
			vertexPositions.push_back( 1.0f );  // Homogenous coordinates
      			add_color( vertexColors, option );  // and color.
			i++;
		}
	}
	
	// Initializing size.
	size = i;

	// Closing file pointer.
	fp.close();
}

///////////////////////////////////////////////////////////////////////////////
//
// Function #2: 
//
// Inputs: vertexColors => Float vector of colors.
// 	   option       => Color for segment.
//
// Pos:	   Adds the color to a given triangle from the parsed STL file.
//
///////////////////////////////////////////////////////////////////////////////

void add_color( vector<float> & vertexColors, const int option )
{
	switch( option ) {
		// Red.
		case 1:
			vertexColors.push_back( 1.0f );
			vertexColors.push_back( 0.0f );
			vertexColors.push_back( 0.0f );
        		break;
    		// Green.
    		case 2:
			vertexColors.push_back( 0.0f );
			vertexColors.push_back( 1.0f );
			vertexColors.push_back( 0.0f );
        		break;
    		// Blue.
    		case 3:
			vertexColors.push_back( 0.0f );
			vertexColors.push_back( 0.0f );
			vertexColors.push_back( 1.0f );
        		break;
    		// White.
    		case 4:
			vertexColors.push_back( 1.0f );
			vertexColors.push_back( 1.0f );
			vertexColors.push_back( 1.0f );
        		break;
    		// Yellow.
    		default:
			vertexColors.push_back( 1.0f );
			vertexColors.push_back( 1.0f );
			vertexColors.push_back( 0.0f );
        		break;
  	}
	vertexColors.push_back( 1.00f );  // Alpha channel.
}
