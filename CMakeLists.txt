cmake_minimum_required(VERSION 3.1)
project(tinyspider)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES include/findlink.hpp src/findlink.cpp src/main.cpp include/client_http.hpp include/linkbufformultithread.h src/linkbufformultithread.cpp)
add_executable(tinyspider ${SOURCE_FILES})

target_link_libraries(tinyspider pthread)
target_link_libraries(tinyspider boost_system)
target_link_libraries(tinyspider boost_thread)
target_link_libraries(tinyspider boost_filesystem)
target_link_libraries(tinyspider boost_date_time)
target_link_libraries(tinyspider boost_regex)