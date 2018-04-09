cmake_minimum_required(VERSION 3.10)
project(vcnc_main)

set(CMAKE_CXX_STANDARD 17)

add_executable(vcnc_main main.cpp src/ringbuffer.h src/movingaverage.h src/parameters.h src/vec.h src/interpolator.h src/vcnc_types.h)