cmake_minimum_required(VERSION 3.10)
project(OOA5)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML REQUIRED system window graphics network audio)

add_executable(OOA5 SFMLGraphVisualizer.cpp SFMLGraphVisualizer.h Node.h Node.cpp List.h Execption.cpp Execption.h DiGraph.h DiGraph.cpp main.cpp PriorityQueue.h GraphVisualizer.h FileInterface.cpp FileInterface.h)

include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(OOA5 ${SFML_LIBRARIES})