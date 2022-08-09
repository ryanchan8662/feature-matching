# feature-matching

## Overview

Provides a general feature recognition library based on a simple convolutional filter-based edge finder. Built for use in embedded devices such as computer vision modules or robotic applications, where the use of libraries and/or dedicated processing accelerators are restricted or unfeasible.

### TODO:
- Apply Sobel operator to isolate edges and gradients within RGB image
- Implement a Harris Corner Detection algorithm to detect features based on edge direction
- Recognise common features or elements between two stereoscopic perspectives with a weighted property system
- Derive a 3D representation of an environment given 2 stereoscopic feature-rich input maps

### Finished:
- Set up data structure to represent and retrieve 2D image data within memory
- Import and export BMP images for testing and development
- Implement conversion system between 1st and 2nd dimensional vectors for memory
- Add point draw system to visually identify features
