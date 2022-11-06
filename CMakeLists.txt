cmake_minimum_required(VERSION 3.23)
project(bector
        VERSION 0.1.0
        DESCRIPTION "Bit vector for C++")

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

set(SOURCE_FILES
        include/constructors/constructors.cpp
        include/operators/assignment.cpp
        include/functions/element_access.cpp
        include/functions/capacity.cpp
        include/functions/modifiers.cpp
        include/functions/conversion.cpp
        include/operators/unary.cpp
        include/operators/binary.cpp
        include/operators/comparison.cpp)

add_library(bector SHARED ${SOURCE_FILES})

set_target_properties(bector PROPERTIES PUBLIC_HEADER include/bector.hpp)

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
