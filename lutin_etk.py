#!/usr/bin/python
import lutin.module as module
import lutin.tools as tools

def get_desc():
	return "e-tk : Ewol tool kit"


def create(target):
	myModule = module.Module(__file__, 'etk', 'LIBRARY')
	myModule.add_extra_compile_flags()
	myModule.add_src_file([
		'etk/etk.cpp'
		])
	myModule.add_module_depend([
		'etk-archive',
		'etk-base',
		'etk-color',
		'etk-file',
		'etk-log',
		'etk-math',
		'etk-time'])
	myModule.add_export_path(tools.get_current_path(__file__))
	return myModule


