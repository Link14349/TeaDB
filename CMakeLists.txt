cmake_minimum_required(VERSION 3.9)
project(TeaDB)

set(CMAKE_CXX_STANDARD 11)

add_executable(TeaDB main.cpp src/reader.cpp include/reader.h base64-master/base64.h src/db.cpp include/db.h src/table.cpp include/table.h include/stringValue.cpp include/stringValue.h include/high_precision.cpp include/high_precision.h)