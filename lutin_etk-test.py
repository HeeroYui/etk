#!/usr/bin/python
import lutin.debug as debug
import lutin.tools as tools


def get_type():
	return "BINARY"

def get_sub_type():
	return "TEST"

def get_desc():
	return "e-tk test software"

def get_licence():
	return "MPL-2"

def get_compagny_type():
	return "com"

def get_compagny_name():
	return "atria-soft"

def get_maintainer():
	return "authors.txt"

def configure(target, my_module):
	my_module.add_src_file([
	    'test/main.cpp',
	    'test/testColor.cpp',
	    'test/testHash.cpp',
	    'test/testMatrix3x3.cpp',
	    'test/testRegExp.cpp',
	    'test/testTransform.cpp',
	    'test/testVector3_f.cpp',
	    'test/testArchive.cpp',
	    'test/testFSNode.cpp',
	    'test/testMatrix2x2.cpp',
	    'test/testQuaternion.cpp',
	    'test/testStdShared.cpp',
	    'test/testVector2_f.cpp',
	    'test/testString.cpp',
	    ])
	my_module.add_depend([
	    'etk',
	    'gtest',
	    'test-debug'
	    ])
	return True

