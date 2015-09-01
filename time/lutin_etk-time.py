#!/usr/bin/python
import lutin.module as module
import lutin.tools as tools

def get_desc():
	return "etk time interface"

def get_license():
	return "APACHE v2.0"

def create(target):
	myModule = module.Module(__file__, 'etk-time', 'LIBRARY')
	myModule.add_extra_compile_flags()
	"""
	myModule.add_src_file([
		"etk-log/log.cpp"
		])
	"""
	myModule.add_module_depend(["etk-base"])
	myModule.add_export_path(tools.get_current_path(__file__))
	return myModule
