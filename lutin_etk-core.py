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
	    'etk-core/String.cpp',
	    'etk-core/UString.cpp',
	    'etk-core/utf8.cpp',
	    'etk-core/stdTools.cpp',
	    'etk-core/Stream.cpp',
	    'etk-core/Function.cpp',
	    'etk-core/Allocator.cpp',
	    'etk-core/typeInfo.cpp',
	    'etk-core/Exception.cpp',
	    ])
	
	my_module.add_header_file([
	    'etk-core/algorithm.hpp',
	    'etk-core/Allocator.hpp',
	    'etk-core/types.hpp',
	    'etk-core/stdTools.hpp',
	    'etk-core/String.hpp',
	    'etk-core/UString.hpp',
	    'etk-core/utf8.hpp',
	    'etk-core/Array.hpp',
	    'etk-core/Vector.hpp',
	    'etk-core/Stream.hpp',
	    'etk-core/Pair.hpp',
	    'etk-core/Map.hpp',
	    'etk-core/Set.hpp',
	    'etk-core/move.hpp',
	    'etk-core/typeTrait.hpp',
	    'etk-core/Function.hpp',
	    'etk-core/NullPtr.hpp',
	    'etk-core/typeInfo.hpp',
	    'etk-core/Exception.hpp'
	    ], 'etk')
	
	# build in C++ mode
	my_module.compile_version("c++", 2017)
	# add dependency of the generic C++ library:
	my_module.add_depend([
	    'c',
	    'm',
	    "pthread",
	    ])
	"""
	my_module.add_flag('c++', [
		"-DETK_MEMORY_CHECKER=2"
		], export=True)
	"""
	if "Android" in target.get_type():
		my_module.add_depend("SDK")
	if "MacOs" in target.get_type():
		my_module.add_depend("cxx")
	my_module.add_path(".")
	return True


