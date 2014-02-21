cmake_minimum_required(VERSION 2.6)

# Declare the project
project(libetk CXX)

##
## Include C++ X11 dependency ... (check correct flags)
##
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
	CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
	if(COMPILER_SUPPORTS_CXX0X)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
	else()
		message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
	endif()
endif()




# set output path:
set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})

include_directories(.)

#include_directories(${bulletlib_INCLUDE_DIRS})
include_directories(${linearmath_INCLUDE_DIRS})

#Create src file list
set(src_files
	etk/debugGeneric.cpp
	etk/debug.cpp
	etk/stdTools.cpp
	etk/Stream.cpp
	etk/RegExp.cpp
	etk/tool.cpp
	etk/Noise.cpp
	etk/Color.cpp
	etk/math/Matrix4.cpp
	etk/math/Vector2D.cpp
	etk/math/Vector3D.cpp
	etk/math/Vector4D.cpp
	etk/os/FSNode.cpp
	etk/os/FSNodeRight.cpp
	etk/archive/Archive.cpp
	etk/archive/Zip.cpp
	etk/os/Mutex.Generic.cpp
	etk/os/Semaphore.Generic.cpp
)

#add_definitions( -DMODE_RELEASE )

#add_definitions( -DDEBUG_LEVEL=3 )
#add_definitions( -DDEBUG=1 )


#Create a static Lib:
add_library(etk STATIC ${src_files} )

target_link_libraries(etk bulletlib)

#myModule.add_module_depend('linearmath')
#myModule.add_module_depend('minizip')


#myModule.add_export_flag_LD("-lpthread")

