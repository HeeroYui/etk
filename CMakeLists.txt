cmake_minimum_required(VERSION 2.8)

# Declare the project
project(etk CXX)

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


#Create src file list
set(src_files
	etk/debugGeneric.cpp
	etk/debugGeneric.h
	etk/debug.cpp
	etk/debug.h
	etk/stdTools.cpp
	etk/stdTools.h
	etk/Stream.cpp
	etk/Stream.h
	etk/tool.cpp
	etk/tool.h
	etk/Noise.cpp
	etk/Noise.h
	etk/Color.cpp
	etk/Color.h
	etk/math/Matrix4.cpp
	etk/math/Matrix4.h
	etk/math/Vector2D.cpp
	etk/math/Vector2D.h
	etk/math/Vector3D.cpp
	etk/math/Vector3D.h
	etk/math/Vector4D.cpp
	etk/math/Vector4D.h
	etk/os/FSNode.cpp
	etk/os/FSNode.h
	etk/os/FSNodeRight.cpp
	etk/os/FSNodeRight.h
	etk/archive/Archive.cpp
	etk/archive/Archive.h
	etk/archive/Zip.cpp
	etk/archive/Zip.h
	etk/os/Mutex.Generic.cpp
	etk/os/Mutex.h
	etk/os/Semaphore.Generic.cpp
	etk/os/Semaphore.h
)

add_definitions( -DDEBUG_LEVEL=3 )
add_definitions( -DDEBUG=1 )
if (APPLE)
	add_definitions( -D__TARGET_OS__MacOs )
elseif (UNIX)
	add_definitions( -D__TARGET_OS__Linux )
elseif (WIN32)
	add_definitions( -D__TARGET_OS__Windows )
endif ()


#Create a static Lib:
add_library(etk STATIC ${src_files} )

include_directories(${zlib_SOURCE_DIR}/contrib/)
include_directories(${linearmath_SOURCE_DIR}/bullet/src/)

target_link_libraries(etk linearmath zlib)

#myModule.add_export_flag_LD("-lpthread")


# display all variable ...
#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()
