cmake_minimum_required(VERSION 3.9)
project(compare_demo)
 
 

# set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE "Debug")
 

set(SOURCE_FILES src/compare.cpp)
# aux_source_directory(${CMAKE_SOURCE_DIR}/libtfhe DIR)  


#add_executable(hello_world ${DIR})

include_directories(${CMAKE_SOURCE_DIR}/src/libs/ubuntu/include)
include_directories(${CMAKE_SOURCE_DIR}/src/libs/ubuntu/include/hesea)
include_directories(${CMAKE_SOURCE_DIR}/src/libs/ubuntu/include/hesea/pke)
include_directories(${CMAKE_SOURCE_DIR}/src/libs/ubuntu/include/hesea/core)
include_directories(${CMAKE_SOURCE_DIR}/src/libs/ubuntu/include/hesea/binfhe)
include_directories(${CMAKE_SOURCE_DIR}/src/libs/ubuntu/include/hesea/cereal)


add_executable(compare_demo  ${SOURCE_FILES})

 
target_link_libraries(compare_demo  
${CMAKE_SOURCE_DIR}/src/libs/ubuntu/lib/libHESEApke.so
${CMAKE_SOURCE_DIR}/src/libs/ubuntu/lib/libHESEAcore.so
${CMAKE_SOURCE_DIR}/src/libs/ubuntu/lib/libHESEAbinfhe.so)
 
