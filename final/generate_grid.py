import os           # A
import sys          # A
import pygame as pg # PyGame for 2D graphics programming.
import random       # Random number generation.

###############################################################################
#
# Function #1:
#
# Pre: Grid should be initialized.
#
# Pos: Returns a random (possibly useless) grid.
#
###############################################################################

def random_grid( grid ):
    for i in range(10):
        for j in range(10):
            if( random.randint(1,100) > 50 ):
                grid[i][j] = 1
    return grid

###############################################################################
#
# Function #2:
#
# Pre:  Grid should be initialized.
#
# Pos:  Returns a random grid created with the recursive division algorithm.
#
# Note: This implementation is an adaption of Jamis Buck's Mazes book 
#       ( weblog.jamisbuck.ong/2011/1/12/maze-generation-recursive-division
#       -algorithm.html )
#
###############################################################################

def divide( grid, x, y, w, h, orientation )
    if( w < 2 or h < 2 )
        return

    # Initializations.
    wx, wy, px, py, dx, dy, length = 0, 0, 0, 0, 0, 0, 0

    # Range of the wall.
    if( horizontal ):
        wx = x + 0
        wy = y + random.randint(h-2)
    else:
        wx = x + random.randint(w-2)
        wy = y
    
    # Gap in the wall.
    if( horizontal ):
        px = wx + random.randint(w)
        py = wy + 0
    else:
        px = wx + 0
        py = wy + random.randint(h)

    # Direction of wall.
    if( horizontal ):
        dx = 1
        dy = 0
    else:
        dx = 0
        dy = 1

    # Length and orthogonality of wall.
    if( horizontal ):
        length = width
        dy = 0
    else:
        length = height
        dy = 1




    #wx = x +



