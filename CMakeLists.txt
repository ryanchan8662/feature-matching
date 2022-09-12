cmake_minimum_required(VERSION 3.23)
project(feature_matching)

set(CMAKE_CXX_STANDARD 14)

add_executable(feature_matching main.cpp copy.cpp draw_point.cpp fast.cpp gaussian.cpp get_array.cpp reader.cpp sobel.cpp Source.cpp writer.cpp)
