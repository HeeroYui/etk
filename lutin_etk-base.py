#!/usr/bin/python
import lutin.debug as debug
import lutin.tools as tools


def get_type():
	return "LIBRARY"

def get_desc():
	return "Ewol tool kit (base: container)"

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
	    'etk/String.cpp',
	    'etk/UString.cpp',
	    'etk/utf8.cpp',
	    'etk/stdTools.cpp',
	    'etk/Stream.cpp',
	    'etk/Function.cpp',
	    'etk/Allocator.cpp',
	    'etk/typeInfo.cpp',
	    ])
	
	my_module.add_header_file([
	    'etk/types.hpp',
	    'etk/stdTools.hpp',
	    'etk/Buffer.hpp',
	    'etk/String.hpp',
	    'etk/UString.hpp',
	    'etk/utf8.hpp',
	    'etk/Vector.hpp',
	    'etk/Stream.hpp',
	    'etk/Pair.hpp',
	    'etk/Map.hpp',
	    'etk/move.hpp',
	    'etk/typeTrait.hpp',
	    'etk/Function.hpp',
	    'etk/NullPtr.hpp',
	    'etk/typeInfo.hpp',
	    ])
	
	# build in C++ mode
	my_module.compile_version("c++", 2011)
	# add dependency of the generic C++ library:
	my_module.add_depend([
	    'c',
	    'm',
	    "pthread",
	    ])
	
	if "Android" in target.get_type():
		my_module.add_depend("SDK")
	
	my_module.add_path(".")
	return True


