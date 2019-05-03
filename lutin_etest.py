#!/usr/bin/python
import realog.debug as debug
import lutin.tools as tools


def get_type():
	return "LIBRARY"

def get_desc():
	return "Ewol tool kit (test: test framework)"

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
	    'etest/etest.cpp',
	    'etest/debug.cpp',
	    ])
	
	my_module.add_header_file([
	    'etest/etest.hpp',
	    'etest/debug.hpp',
	    ])
	
	# build in C++ mode
	my_module.compile_version("c++", 2017)
	# add dependency of the generic C++ library:
	my_module.add_depend([
	    'etk-core',
	    'echrono',
	    'elog',
	    'cxx'
	    ])
	
	my_module.add_path(".")
	return True


