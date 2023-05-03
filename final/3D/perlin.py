###################################################################################################
#
# Author:      Jesus R. Rijo Candelario (Mercer University)
# Date:        04/2023
# Courses:     CSC 415: Graphics Visualization and Simulation (Spring 2023)
# Instructor:  Dr. A. Pounds
#
# Description: Python 3 script to output the 3D coordinates of a region for our project using
#              Perlin noise for randomness.
#
# Note:        This script is heavily based on the script provided in the PIP page for the
#              perlin_noise module.
#
###################################################################################################

import matplotlib.pyplot as plt # General visualization.
import perlin_noise             # Perlin noise.
import sys                      # Command line arguments.

# Instatiating object to retrieve Perlin noise computations.
noise = perlin_noise.PerlinNoise( octaves=10, seed=1 )
size_x = size_y = 100

# Computing 3D coordinates with noisy heights.
pic = [ [noise([i/size_x,j/size_y]) for j in range(size_x)] for i in range(size_y) ]

# Retrieving height offset.
height_offset = 1.0
if( len(sys.argv) > 1 ):
    height_offset = float(sys.argv[1])

# Printing x, y, and offset-adjusted height.
for i in range(100):
    for j in range(100):
        print( i, j, height_offset * pic[i][j] ) 

# Mathplotlib calls to display the region as a grayscale.
# In this project, we will interpret the colors as different
# heights, on the normalized range [-1/2,1/2].
plt.imshow( pic, cmap='gray' )
plt.colorbar()
plt.show()
