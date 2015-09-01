#!/usr/bin/python
import lutin.module as module
import lutin.tools as tools

def get_desc():
	return "etk file interface"

def get_license():
	return "APACHE v2.0"


def create(target):
	myModule = module.Module(__file__, 'etk-file', 'LIBRARY')
	myModule.add_extra_compile_flags()
	myModule.add_src_file([
		"etk-file/Node.cpp",
		"etk-file/Right.cpp"
		])
	
	myModule.add_module_depend(["etk-base", "etk-archive"])
	myModule.add_export_path(tools.get_current_path(__file__))
	return myModule


