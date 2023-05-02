import os            # A
import sys           # A
import pygame as pg  # PyGame for 2D graphics programming.
import generate_grid

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

# Retrieving grid from auxiliary script.
grid = [[0 for x in range(10)] for y in range(10)]
grid = generate_grid.random_grid( grid )

# Specifying display calls:
while True:
    for event in pg.event.get():
        if( event.type == pg.QUIT ):
            pg.quit()
            sys.exit()

    # Drawing grid with right colors.
    draw_grid( SCREEN, grid, W, H )
    pg.display.flip()

    # Refreshing window.
    pg.display.update()





"""
for i in range(size_y):
    for j in range(size_x):
            print( noise( [i/size_x,j/size_y] ) )
"""

