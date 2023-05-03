###############################################################################
# 
# Author:      Jesus R. Rijo Candelario (Mercer University)
# Date:        05/02/2023
# Course:      CSC 415: Graphics visualization and simulation.
# Instructor:  Dr. A. Pounds.
#
# Description: Python script to perform breadth-first search BFS.
#
# Note:        This implementation is heavily based on the implementation 
#              provided by GeeksforGeeks on the web.
#
###############################################################################

import os            # Module to interface with the OS.
import sys           # Module for system-specific paramenters
import pygame as pg  # PyGame for 2D graphics programming.
import random        # Pseudo-random number generation.

###############################################################################
#
# Function #1:
#
# Pre: Both grid and validated should
#
# Pos: Checks if the neighbor is valid.
#
###############################################################################

def validate_neighbor( visited, I, J ):
  
    # Bound checks.
    if( I < 0 or J < 0 or I >= 10 or J >= 10 ):
        return False

    # Already visited check.
    if( visited[I][J] == 1 ):
        return False

    return True

###############################################################################
#
# Function #2:
#
# Pre: Both grid and validated should be initialized.
#
# Pos: Performs BFS, starting with grid[I][J].
#
###############################################################################

def bfs( grid, visited, I, J ):

    sol = []
    print( "BFS for =>", I, J )

    # Arrays to specify directions.
    dRow = [-1,0,1,0]
    dCol = [0,1,0,-1]

    # Setting up things for BFS.
    q = []
    q.append( [I,J] )
    visited[I][J] = 1

    while( len(q) > 0 ):
        cell = q[0]
        x = cell[0]
        y = cell[1]

        # Printing neighors.
        print( '\t', x, y )
        sol.append( [x,y] )
        q.pop(0)

        # Checking adjacent nodes.
        for i in range(4):
            adjx = x + dRow[i]
            adjy = y + dCol[i]

            if( validate_neighbor( visited, adjx, adjy ) ):
                if( grid[adjx][adjy] == 1 ):
                    q.insert( 0, [ adjx, adjy ] )
                    visited[adjx][adjy] = 1

    # Returning list found with BFS.
    print('Finished BFS')
    return sol
