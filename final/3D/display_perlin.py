###################################################################################################
#
# Author:      Jesus R. Rijo Candelario (Mercer University)
# Date:        04/2023
# Courses:     CSC 415: Graphics Visualization and Simulation (Spring 2023)
# Instructor:  Dr. A. Pounds
#
# Description: Python 3 script to display the 3D coordinates of a region for our project using
#              Perlin noise for randomness.
#
# Note:        This script is heavily based on the script provided in the PIP page for the
#              perlin_noise module.
#
###################################################################################################

import matplotlib.pyplot as plt # General visualization.
import perlin_noise             # Perlin noise.
import sys                      # Command line arguments.

x = []
y = []
z = []

# Getting triplets from the file.
with open('output', 'r') as fp:
    for triplet in fp:
        triplet = triplet.split()
        x.append( float( triplet[0] ) )
        y.append( float( triplet[1] ) )
        z.append( float( triplet[2] ) )

# Mathplotlib calls.
ax = plt.axes(projection='3d')
ax.scatter3D(x,y,z,c=z, cmap='Greens')
ax.set_title("Display of 3D Data")
plt.show()
