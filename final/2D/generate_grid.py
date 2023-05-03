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

    print('\tUsing Randomized Generation')

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
# Note: This implementation is a VERY NAIVE adaptation of Jamis Buck's Mazes book 
#       ( weblog.jamisbuck.ong/2011/1/12/maze-generation-recursive-division
#       -algorithm.html ).
#
###############################################################################

def divide( grid, division_count, orientation ):

    print('\tUsing Naive Recursive Division Generation')

    wall_choices = []   # Variables to store previous wall places.
    wall_place   = -1
    gap          = -1

    for j in range(5):
        
        # Choosing an unique row/column for the wall.
        while( 1 ):
            wall_place = random.randint(0,10-1)
            if( wall_place not in wall_choices ):
                break
        wall_choices.append( wall_place )

        # Choosing wall and its gap.
        if( orientation == 1 ):
            for i in range(10):
                grid[wall_place][i] = 0
            
            # Choosing gap.
            while( 1 ):
                gap = random.randint(0,10-1)
                if( gap not in wall_choices ):
                    break
            wall_choices.append( gap )

            # Specifying gap and flipping orientation.
            grid[wall_place][gap] = 1
            orientation = 0
        else:
            for i in range(10):
                grid[i][wall_place] = 0
            gap = random.randint(0,10-1)

            # Choosing gap.
            while( 1 ):
                gap = random.randint(0,10-1)
                if( gap not in wall_choices ):
                    break
            wall_choices.append( gap )

            # Specifying gap and flipping orientation.
            grid[gap][wall_place] = 1
            orientation = 1
