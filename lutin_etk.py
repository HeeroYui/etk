#!/usr/bin/python
import lutin.debug as debug
import lutin.tools as tools


def get_type():
	return "LIBRARY"

def get_desc():
	return "Ewol tool kit"

def get_licence():
	return "MPL-2"

def get_compagny_type():
	return "com"

def get_compagny_name():
	return "atria-soft"

def get_maintainer():
	return "authors.txt"

def get_version():
	return "version.txt"

def configure(target, my_module):
	my_module.add_extra_flags()
	# add the file to compile:
	my_module.add_src_file([
	    'etk/debug.cpp',
	    'etk/etk.cpp',
	    'etk/stdTools.cpp',
	    'etk/tool.cpp',
	    'etk/Noise.cpp',
	    'etk/Color.cpp',
	    'etk/RegExp.cpp',
	    'etk/math/Matrix2.cpp',
	    'etk/math/Matrix4.cpp',
	    'etk/math/Vector2D.cpp',
	    'etk/math/Vector3D.cpp',
	    'etk/math/Vector4D.cpp',
	    'etk/os/FSNode.cpp',
	    'etk/os/FSNodeRight.cpp',
	    'etk/archive/Archive.cpp',
	    'etk/archive/Zip.cpp'])
	
	my_module.add_header_file([
	    'etk/etk.hpp',
	    'etk/debug.hpp',
	    'etk/types.hpp',
	    'etk/stdTools.hpp',
	    'etk/tool.hpp',
	    'etk/Noise.hpp',
	    'etk/Color.hpp',
	    'etk/RegExp.hpp',
	    'etk/Buffer.hpp',
	    'etk/Hash.hpp',
	    'etk/math/Matrix2.hpp',
	    'etk/math/Matrix4.hpp',
	    'etk/math/Vector2D.hpp',
	    'etk/math/Vector3D.hpp',
	    'etk/math/Vector4D.hpp',
	    'etk/os/Fifo.hpp',
	    'etk/os/FSNode.hpp',
	    'etk/os/FSNodeRight.hpp',
	    'etk/archive/Archive.hpp',
	    'etk/archive/Zip.hpp'])
	
	# build in C++ mode
	my_module.compile_version("c++", 2011)
	# add dependency of the generic C++ library:
	my_module.add_depend([
	    'cxx',
	    'm',
	    'elog',
	    'ememory'
	    ])
	# add some optionnal libraries
	my_module.add_optionnal_depend('minizip', ["c++", "-DETK_BUILD_MINIZIP"])
	my_module.add_optionnal_depend('linearmath', ["c", "-DETK_BUILD_LINEARMATH"], export=True)
	
	if "Android" in target.get_type():
		my_module.add_depend("SDK")
	
	my_module.add_path(".")
	return True


