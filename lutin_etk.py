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
	    'etk/tool.cpp',
	    'etk/Noise.cpp',
	    'etk/Color.cpp',
	    'etk/RegEx.cpp',
	    'etk/fileSystem/fileSystem.cpp',
	    'etk/fileSystem/Path.cpp',
	    'etk/fileSystem/Permissions.cpp',
	    'etk/fileSystem/Type.cpp',
	    'etk/theme/theme.cpp',
	    'etk/math/Matrix2x2.cpp',
	    'etk/math/Matrix2x3.cpp',
	    'etk/math/Matrix3x3.cpp',
	    'etk/math/Matrix4x4.cpp',
	    'etk/math/Vector2D.cpp',
	    'etk/math/Vector3D.cpp',
	    'etk/math/Vector4D.cpp',
	    'etk/math/Quaternion.cpp',
	    'etk/math/Transform3D.cpp',
	    'etk/os/FSNode.cpp',
	    'etk/os/FSNodeRight.cpp',
	    'etk/archive/Archive.cpp',
	    'etk/archive/Zip.cpp',
	    ])
	
	my_module.add_header_file([
	    'etk/etk.hpp',
	    'etk/debug.hpp',
	    'etk/stdTools.hpp',
	    'etk/tool.hpp',
	    'etk/Noise.hpp',
	    'etk/Color.hpp',
	    'etk/RegEx.hpp',
	    'etk/fileSystem/fileSystem.hpp',
	    'etk/fileSystem/Path.hpp',
	    'etk/fileSystem/Permissions.hpp',
	    'etk/fileSystem/Type.hpp',
	    'etk/theme/theme.hpp',
	    'etk/math/Matrix2x2.hpp',
	    'etk/math/Matrix2x3.hpp',
	    'etk/math/Matrix3x3.hpp',
	    'etk/math/Matrix4x4.hpp',
	    'etk/math/Vector2D.hpp',
	    'etk/math/Vector3D.hpp',
	    'etk/math/Vector4D.hpp',
	    'etk/math/Quaternion.hpp',
	    'etk/math/Transform3D.hpp',
	    'etk/os/Fifo.hpp',
	    'etk/os/FSNode.hpp',
	    'etk/os/FSNodeRight.hpp',
	    'etk/archive/Archive.hpp',
	    'etk/archive/Zip.hpp',
	    'etk/TreeNode.hpp',
	    'etk/FlatTree.hpp',
	    ])
	
	# build in C++ mode
	my_module.compile_version("c++", 2017)
	# add dependency of the generic C++ library:
	my_module.add_depend([
	    'c',
	    'm',
	    'elog',
	    'ememory',
	    'etk-base',
	    ])
	# TODO: Remove this ==> when ready to remove dependency with stl:
	my_module.add_depend(['cxx'])
	
	# add some optionnal libraries
	my_module.add_optionnal_depend('minizip', ["c++", "-DETK_BUILD_MINIZIP"])
	my_module.add_optionnal_depend('linearmath', ["c", "-DETK_BUILD_LINEARMATH"], export=True)
	
	if "Android" in target.get_type():
		my_module.add_depend("SDK")
	
	my_module.add_path(".")
	return True


