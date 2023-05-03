###############################################################################
# 
# Author:      Jesus R. Rijo Candelario (Mercer University)
# Date:        05/02/2023
# Course:      CSC 415: Graphics visualization and simulation.
# Instructor:  Dr. A. Pounds.
#
# Description: Pygame script to generate a 10x10 puzzle. Note that not all 
#              valid nodes are necessarily reachable.
#
###############################################################################

import os            # Module to interface with the OS.
import sys           # Module for system-specific paramenters
import pygame as pg  # PyGame for 2D graphics programming.
import random        # Pseudo-random number generation.
import generate_grid # Helper function to build grid.

###############################################################################
#
# Function #1:
#
# Pre: The screen and grid objects should be initializes.
#
# Pos: Draws 100*100 squares on the screen to form a grid.
#
###############################################################################

def draw_grid( SCREEN, grid, W, H ):
    local_color = (50,100,50)

    # For each square, we will draw a square with its right color.
    for i in range(10):
        for j in range(10):
            # Choosing the color of the ith square.
            if( grid[i][j] == 0 ):
                local_color = (150,75,75)  # Red hue.
            else:
                local_color = (50,100,50)  # Green hue.

            # Drawing the square.
            pg.draw.rect( SCREEN, local_color, 
                          pg.Rect( W * i / 10.0, H * j / 10.0, W / 10.5, H / 10.5 ) )

def draw_icon( SCREEN, W, H, x, y ):
    local_color = (75, 100, 200)
    pg.draw.rect( SCREEN, local_color, 
                          pg.Rect( W * x / 10.0, H * y / 10.0, W / 20.5, H / 20.5 ) )

###############################################################################
# 
# Main function:
#
###############################################################################

# Specifying globals
C_BLACK = (0,0,0)           # Colors.
C_WHITE = (200,200,200)
H = 700                     # Heights.
W = 700

# Initialization calls.
pg.init()
SCREEN = pg.display.set_mode( (W,H) )
CLOCK  = pg.time.Clock()
SCREEN.fill(C_WHITE)
pg.display.set_caption("CSC 415 -- Visualization Project (A Simple Puzzle Solver)")

# Initializing grid.
grid = [[1 for x in range(10)] for y in range(10)]

# Retrieving grid from auxiliary script.
division_count = 0
orientation = 1
generate_grid.divide( grid, division_count, orientation )

# Computing two grid to test for connectedness.
x1, y1, x2, y2 = 0,0,0,0

# Computing first random cell.
while( 1 ):
    x1 = random.randint(0,9)
    y1 = random.randint(0,9)
    if( grid[x1][y1] == 1 ):
        break

# Computing second random cell.
while( 1 ):
    x2 = random.randint(0,9)
    y2 = random.randint(0,9)
    if( grid[x2][y2] == 1 and x1 != x2 and y1 != y2 ):
        break

print('Printing values for two cells to check')
print( x1, y1 )
print( x2, y2 )

# Specifying display calls:
while( 1 ):
    for event in pg.event.get():
        if( event.type == pg.QUIT ):
            pg.quit()
            sys.exit()

    # Drawing grid with right colors.
    draw_grid( SCREEN, grid, W, H )
    draw_icon( SCREEN, W, H, x1, y1 )
    draw_icon( SCREEN, W, H, x2, y2 )

    pg.display.flip()

    # Refreshing window.
    pg.display.update()
