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
	    'etk/path/fileSystem.cpp',
	    'etk/path/Path.cpp',
	    'etk/path/Permissions.cpp',
	    'etk/io/OpenMode.cpp',
	    'etk/io/SeekMode.cpp',
	    'etk/io/Interface.cpp',
	    'etk/io/File.cpp',
	    'etk/io/ZipFile.cpp',
	    'etk/theme/theme.cpp',
	    'etk/theme/ProviderTheme.cpp',
	    'etk/math/Matrix2x2.cpp',
	    'etk/math/Matrix2x3.cpp',
	    'etk/math/Matrix3x3.cpp',
	    'etk/math/Matrix4x4.cpp',
	    'etk/math/Vector2D.cpp',
	    'etk/math/Vector3D.cpp',
	    'etk/math/Vector4D.cpp',
	    'etk/math/Quaternion.cpp',
	    'etk/math/Transform3D.cpp',
	    'etk/archive/Archive.cpp',
	    'etk/archive/Zip.cpp',
	    'etk/uri/Uri.cpp',
	    'etk/uri/uri.cpp',
	    'etk/uri/Query.cpp',
	    'etk/uri/provider/provider.cpp',
	    'etk/uri/provider/ProviderFile.cpp',
	    'etk/uri/provider/ProviderFileZip.cpp',
	    ])
	
	my_module.add_header_file([
	    'etk/etk.hpp',
	    'etk/debug.hpp',
	    'etk/Buffer.hpp',
	    'etk/tool.hpp',
	    'etk/Noise.hpp',
	    'etk/Color.hpp',
	    'etk/RegEx.hpp',
	    'etk/path/fileSystem.hpp',
	    'etk/path/Path.hpp',
	    'etk/path/Permissions.hpp',
	    'etk/io/OpenMode.hpp',
	    'etk/io/SeekMode.hpp',
	    'etk/io/Interface.hpp',
	    'etk/io/File.hpp',
	    'etk/io/ZipFile.hpp',
	    'etk/theme/theme.hpp',
	    'etk/theme/ProviderTheme.hpp',
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
	    'etk/archive/Archive.hpp',
	    'etk/archive/Zip.hpp',
	    'etk/TreeNode.hpp',
	    'etk/FlatTree.hpp',
	    'etk/uri/Uri.hpp',
	    'etk/uri/uri.hpp',
	    'etk/uri/Query.hpp',
	    'etk/uri/provider/provider.hpp',
	    'etk/uri/provider/Interface.hpp',
	    'etk/uri/provider/ProviderFile.hpp',
	    'etk/uri/provider/ProviderFileZip.hpp',
	    ])
	
	# build in C++ mode
	my_module.compile_version("c++", 2017)
	# add dependency of the generic C++ library:
	my_module.add_depend([
	    'c',
	    'm',
	    'elog',
	    'ememory',
	    'etk-core',
	    ])
	# TODO: Remove this ==> when ready to remove dependency with stl:
	my_module.add_depend(['cxx'])
	
	# add some optionnal libraries
	my_module.add_optionnal_depend('minizip', ["c++", "-DETK_BUILD_MINIZIP"], export=True)
	my_module.add_optionnal_depend('linearmath', ["c", "-DETK_BUILD_LINEARMATH"], export=True)
	
	if "Android" in target.get_type():
		my_module.add_depend("SDK")
	
	my_module.add_path(".")
	return True


