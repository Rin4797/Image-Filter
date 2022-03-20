cmake_minimum_required(VERSION 3.17)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(image_processor
        image_processor.cpp
        Image.cpp
        filters/Crop.cpp
        filters/Filter.cpp
        filters/FilterFactory.cpp
        filters/MatrixFilter.cpp
        filters/Sharpening.cpp
        filters/Edge_Detection.cpp
        filters/Grayscale.cpp
        filters/Negative.cpp
        filters/GaussianBlur.cpp
        BMP.cpp
        )
