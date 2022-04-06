cmake_minimum_required(VERSION 3.17)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(BMP
        BMP.cpp
        )

add_library(Image
        Image.cpp
        )

add_library(Parser
        Parser.cpp
        )

add_library(Filter
        filters/Crop.cpp
        filters/Filter.cpp
        filters/FilterFactory.cpp
        filters/MatrixFilter.cpp
        filters/Sharpening.cpp
        filters/Edge_Detection.cpp
        filters/Grayscale.cpp
        filters/Negative.cpp
        filters/GaussianBlur.cpp
        filters/Crystallizing.cpp
        )

add_library(Exception
        Exception.cpp
        )

add_executable(image_processor
        image_processor.cpp
        BMP.cpp
        Image.cpp
        Parser.cpp
        filters/Crop.cpp
        filters/Filter.cpp
        filters/FilterFactory.cpp
        filters/MatrixFilter.cpp
        filters/Sharpening.cpp
        filters/Edge_Detection.cpp
        filters/Grayscale.cpp
        filters/Negative.cpp
        filters/GaussianBlur.cpp
        filters/Crystallizing.cpp
        Exception.cpp
        )

add_executable(test
        test.cpp
        )
target_link_libraries(
        test
        gtest_main
        BMP
        Image
        Parser
        Filter
        Exception
)

