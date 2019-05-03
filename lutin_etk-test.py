#!/usr/bin/python
import realog.debug as debug
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
	    'test/testFileSystem.cpp',
	    'test/testPath.cpp',
	    'test/testPermissions.cpp',
	    'test/testTheme.cpp',
	    'test/testUri.cpp',
	    'test/testQuery.cpp',
	    'test/testUriProvider.cpp',
	    'test/ConstructDestruct.cpp',
	    'test/testColor.cpp',
	    'test/testFunction.cpp',
	    'test/testMapUnordered.cpp',
	    'test/testMap.cpp',
	    'test/testSet.cpp',
	    'test/testMatrix3x3.cpp',
	    'test/testRegExp.cpp',
	    'test/testTransform.cpp',
	    'test/testArray.cpp',
	    'test/testVector.cpp',
	    'test/testVector3_f.cpp',
	    'test/testMatrix2x2.cpp',
	    'test/testQuaternion.cpp',
	    'test/testVector2_f.cpp',
	    'test/testString.cpp',
	    'test/testTrait.cpp',
	    'test/testThrow.cpp',
	    'test/testUTF8.cpp',
	    ])
	my_module.add_depend([
	    'etk',
	    'etest',
	    'test-debug'
	    ])
	my_module.copy_path('data/*')
	my_module.copy_path('data/data/*', 'data')
	my_module.copy_path('data/data/dir_A/*', 'data/dir_A')
	my_module.copy_path('data/data/dir_B/*', 'data/dir_B')
	my_module.copy_path('data/data/dir_B/dir_C/*', 'data/dir_B/dir_C')
	return True

