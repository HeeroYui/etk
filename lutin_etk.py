#!/usr/bin/python
import lutinModule as module
import lutinTools as tools

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
		'etk/stdTools.cpp',
		'etk/log.cpp',
		'etk/tool.cpp',
		'etk/Noise.cpp',
		'etk/Color.cpp',
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
	
	
	if target.config["mode"] == "release":
		# TODO : The other way is to remove this ...
		# TODO : Fore release mode : the etk folder are absolutly not at the same position in the tree ...
		myModule.compile_flags_CC("-DMODE_RELEASE")
	else:
		myModule.add_export_flag_CC("-DDEBUG_LEVEL=3")
		myModule.add_export_flag_CC("-DDEBUG=1")
		# Bor backtrace display :
		if target.name != "Windows":
			myModule.add_export_flag_LD("-ldl -rdynamic")
	
	if     target.config["compilator"] == "gcc" \
	   and target.xx_version < 4007000:
		# note : this framework depend on C++ 11, but a simple port of Boost for old compatibility has been done ...
		myModule.compile_version_XX(1999)
		myModule.add_optionnal_module_depend('boost', "ETK_BUILD_BOOST", export=True)
		myModule.add_export_path(tools.get_current_path(__file__) + "/binding_boost")
	else:
		myModule.compile_version_XX(2011)
		# name of the dependency
		myModule.add_optionnal_module_depend('linearmath', "ETK_BUILD_LINEARMATH", export=True)
		myModule.add_optionnal_module_depend('minizip', "ETK_BUILD_MINIZIP")
		myModule.add_export_path(tools.get_current_path(__file__) + "/binding_X11")
	
	if target.name=="Windows":
		None
	elif target.name=="Android":
		None
	else:
		myModule.add_export_flag_LD("-lpthread")
	
	myModule.add_export_path(tools.get_current_path(__file__))
	
	# add the currrent module at the 
	return myModule


