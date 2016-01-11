#!/usr/bin/python
import lutin.module as module
import lutin.tools as tools


def get_type():
	return "LIBRARY"

def get_desc():
	return "Ewol tool kit"

def get_licence():
	return "APACHE-2"

def get_compagny_type():
	return "com"

def get_compagny_name():
	return "atria-soft"

def get_maintainer():
	return ["Mr DUPIN Edouard <yui.heero@gmail.com>"]

def get_version():
	return [0,9,"dev"]

def create(target, module_name):
	my_module = module.Module(__file__, module_name, get_type())
	my_module.add_extra_compile_flags()
	# add the file to compile:
	my_module.add_src_file([
		'etk/debug.cpp',
		'etk/etk.cpp',
		'etk/stdTools.cpp',
		'etk/log.cpp',
		'etk/tool.cpp',
		'etk/Noise.cpp',
		'etk/Color.cpp',
		'etk/thread/tools.cpp',
		'etk/math/Matrix2.cpp',
		'etk/math/Matrix4.cpp',
		'etk/math/Vector2D.cpp',
		'etk/math/Vector3D.cpp',
		'etk/math/Vector4D.cpp',
		'etk/os/FSNode.cpp',
		'etk/os/FSNodeRight.cpp',
		'etk/archive/Archive.cpp',
		'etk/archive/Zip.cpp'])
	
	if target.name=="IOs":
		my_module.add_src_file('etk/logIOs.m')
	
	my_module.add_header_file([
		'etk/etk.h',
		'etk/types.h',
		'etk/stdTools.h',
		'etk/log.h',
		'etk/tool.h',
		'etk/Noise.h',
		'etk/Color.h',
		'etk/Hash.h',
		'etk/thread/tools.h',
		'etk/math/Matrix2.h',
		'etk/math/Matrix4.h',
		'etk/math/Vector2D.h',
		'etk/math/Vector3D.h',
		'etk/math/Vector4D.h',
		'etk/os/Fifo.h',
		'etk/os/FSNode.h',
		'etk/os/FSNodeRight.h',
		'etk/archive/Archive.h',
		'etk/archive/Zip.h'])
	
	if target.config["mode"] == "release":
		# TODO : The other way is to remove this ...
		# TODO : Fore release mode : the etk folder are absolutly not at the same position in the tree ...
		my_module.compile_flags('c', "-DMODE_RELEASE")
	else:
		my_module.add_export_flag('c', "-DDEBUG_LEVEL=3")
		my_module.add_export_flag('c', "-DDEBUG=1")
		# Bor backtrace display :
		if     target.name != "Windows" \
		   and target.name != "MacOs" \
		   and target.name != "IOs":
			# TODO : check if it is really needed ...
			my_module.add_export_flag('link', [
				'-ldl',
				'-rdynamic'])
		elif target.name != "Windows":
			my_module.add_export_flag('link', [
				'-ldl'])
	# build in C++ mode
	my_module.compile_version("c++", 2011)
	# add dependency of the generic C++ library:
	my_module.add_module_depend('cxx')
	# add dependency of the generic math library:
	my_module.add_module_depend('m')
	# add some optionnal libraries
	my_module.add_optionnal_module_depend('minizip', ["c++", "-DETK_BUILD_MINIZIP"])
	my_module.add_optionnal_module_depend('linearmath', ["c", "-DETK_BUILD_LINEARMATH"], export=True)
	
	if target.name=="Windows":
		pass
	elif target.name=="Android":
		#my_module.add_module_depend("SDK")
		pass
	else:
		#TODO : Set it in a generic include system
		my_module.add_export_flag('link', "-lpthread")
	
	my_module.add_path(tools.get_current_path(__file__))
	return my_module


