cmake_minimum_required(VERSION 2.8.9)
project (TestLibrary)

#For the shared library:
set ( PROJECT_LINK_LIBS libtestStudent.dylib )
link_directories( /Users/vincent/Documents/projects/show-me-cpp-code/CMake/03_CMake_sharedlib/build )

#For the static library:
#set ( PROJECT_LINK_LIBS libtestStudent.a )
#link_directories( /Users/vincent/Documents/projects/show-me-cpp-code/CMake/04_Cmake_staticlib/build )

include_directories(/Users/vincent/Documents/projects/show-me-cpp-code/CMake/03_CMake_sharedlib/include)

add_executable(libtest libtest.cpp)
target_link_libraries(libtest ${PROJECT_LINK_LIBS} )