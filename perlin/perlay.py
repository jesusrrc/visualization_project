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

# General visualization.
import matplotlib.pyplot as plt
# Perlin computations.
import perlin_noise

# Instatiating object to retrieve Perlin noise computations.
noise = perlin_noise.PerlinNoise( octaves=10, seed=1 )
size_x = size_y = 100

"""
for i in range(size_y):
    for j in range(size_x):
            print( noise( [i/size_x,j/size_y] ) )
"""

# Computing 3D coordinates with noisy heights.
pic = [ [noise([i/size_x,j/size_y]) for j in range(size_x)] for i in range(size_y) ]

# Printing x, y, and color.
for i in range(100):
    for j in range(100):
        print( i, j, pic[i][j] ) 

# Mathplotlib calls to display the region as a grayscale.
# In this project, we will interpret the colors as different
# heights, on the normalized range [-1/2,1/2].
plt.imshow( pic, cmap='gray' )
plt.colorbar()
plt.show()

