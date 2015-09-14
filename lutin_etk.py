#!/usr/bin/python
import lutin.module as module
import lutin.tools as tools

def get_desc():
	return "e-tk : Ewol tool kit"


def create(target):
	# module name is 'edn' and type binary.
	myModule = module.Module(__file__, 'etk', 'LIBRARY')
	# add extra compilation flags :
	myModule.add_extra_compile_flags()
	# add the file to compile:
	myModule.add_src_file([
		'etk/debug.cpp',
		'etk/etk.cpp',
		'etk/stdTools.cpp',
		'etk/log.cpp',
		'etk/tool.cpp',
		'etk/Noise.cpp',
		'etk/Color.cpp',
		'etk/thread/tools.cpp',
		'etk/math/Matrix4.cpp',
		'etk/math/Vector2D.cpp',
		'etk/math/Vector3D.cpp',
		'etk/math/Vector4D.cpp',
		'etk/os/FSNode.cpp',
		'etk/os/FSNodeRight.cpp',
		'etk/archive/Archive.cpp',
		'etk/archive/Zip.cpp'])
	
	if target.name=="IOs":
		myModule.add_src_file('etk/logIOs.m')
	
	myModule.add_header_file([
		'etk/etk.h',
		'etk/types.h',
		'etk/stdTools.h',
		'etk/log.h',
		'etk/tool.h',
		'etk/Noise.h',
		'etk/Color.h',
		'etk/Hash.h',
		'etk/thread/tools.h',
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
		myModule.compile_flags('c', "-DMODE_RELEASE")
	else:
		myModule.add_export_flag('c', "-DDEBUG_LEVEL=3")
		myModule.add_export_flag('c', "-DDEBUG=1")
		# Bor backtrace display :
		if target.name != "Windows":
			myModule.add_export_flag('link', "-ldl -rdynamic")
	
	myModule.compile_version_XX(2011)
	# name of the dependency
	myModule.add_optionnal_module_depend('minizip', ["c++", "-DETK_BUILD_MINIZIP"])
	myModule.add_optionnal_module_depend('linearmath', ["c", "-DETK_BUILD_LINEARMATH"], export=True)
	
	if target.name=="Windows":
		pass
	elif target.name=="Android":
		pass
	else:
		myModule.add_export_flag('link', "-lpthread")
	
	myModule.add_path(tools.get_current_path(__file__))
	
	# add the currrent module at the 
	return myModule


