#!/usr/bin/python
import lutin.module as module
import lutin.tools as tools

def get_desc():
	return "Zip file access"

def get_license():
	return "APACHE v2.0"


def create(target):
	# module name is 'edn' and type binary.
	myModule = module.Module(__file__, 'etk-archive', 'LIBRARY')
	# add extra compilation flags :
	myModule.add_extra_compile_flags()
	# add the file to compile:
	myModule.add_src_file([
		'etk-archive/Archive.cpp',
		'etk-archive/Zip.cpp'
		])
	myModule.add_module_depend(["etk-base"])
	myModule.add_optionnal_module_depend('minizip', ["c++", "-DETK_BUILD_MINIZIP"])
	myModule.add_export_path(tools.get_current_path(__file__))
	return myModule


