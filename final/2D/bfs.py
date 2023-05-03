###############################################################################
# 
# Author:      Jesus R. Rijo Candelario (Mercer University)
# Date:        05/02/2023
# Course:      CSC 415: Graphics visualization and simulation.
# Instructor:  Dr. A. Pounds.
#
# Description: Python script to perform BFS.
#
# Note:        This implementation is heavily based on the implementation 
#              provided by W3SChools.
#
###############################################################################

import os            # Module to interface with the OS.
import sys           # Module for system-specific paramenters
import pygame as pg  # PyGame for 2D graphics programming.
import random        # Pseudo-random number generation.

def validate_neighbor( visited, I, J ):
    if( I < 0 or J < 0 or I >= 10 or J >= 10 ):
        return False
    if( visited[I][J] == 0 ):
        return False
    return True

def bfs( grid, visited, I, J ):

    dRow = [-1,0,1,0]
    dCol = [0,1,0,-1]

    q = []
    q = q + [I,J]

    visited[I][J] = 1

    while( len(q) > 0 ):
        cell = q[0]
        x = cell[0]
        y = cell[1]

        print( grid[x][y] )
        q.pop(0)

        for i in range(4):
            adjx = x + dRow[i]
            adjy = y + dCol[i]

            if( validate_neighbor( visited, adjx, adjy ) ):
                q = q + [adjx, adjy ]
                vis[adjx][adjy] = 1


