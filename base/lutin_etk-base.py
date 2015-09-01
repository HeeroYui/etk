#!/usr/bin/python
import lutin.module as module
import lutin.tools as tools

def get_desc():
	return "etk basis"

def get_license():
	return "APACHE v2.0"


def create(target):
	myModule = module.Module(__file__, 'etk-base', 'LIBRARY')
	myModule.add_extra_compile_flags()
	myModule.add_src_file([
		'etk/debug.cpp',
		'etk/stdTools.cpp',
		'etk/tool.cpp',
		'etk/Noise.cpp',
		'etk/thread/tools.cpp'
		])
	
	myModule.add_module_depend(["etk-log"])
	
	if target.config["mode"] == "release":
		myModule.compile_flags('c', "-DMODE_RELEASE")
	else:
		myModule.add_export_flag('c', "-DDEBUG_LEVEL=3")
		myModule.add_export_flag('c', "-DDEBUG=1")
		# Bor backtrace display :
		if target.name != "Windows":
			myModule.add_export_flag('link', "-ldl -rdynamic")
	
	# for ald C++ compatibility (old GCC) just link with boost ...
	if     target.config["compilator"] == "gcc" \
	   and target.xx_version < 4007000:
		# note : this framework depend on C++ 11, but a simple port of Boost for old compatibility has been done ...
		myModule.compile_version_XX(1999)
		myModule.add_optionnal_module_depend('boost', ["c++", "-DETK_BUILD_BOOST"], export=True)
		myModule.add_export_path(tools.get_current_path(__file__) + "/binding_boost")
	else:
		myModule.compile_version_XX(2011)
		# name of the dependency
		myModule.add_export_path(tools.get_current_path(__file__) + "/binding_X11")
	
	if target.name=="Windows":
		pass
	elif target.name=="Android":
		pass
	else:
		myModule.add_export_flag('link', "-lpthread")
	
	myModule.add_export_path(tools.get_current_path(__file__))
	return myModule


