#!/usr/bin/python
import lutin.module as module
import lutin.tools as tools
import lutin.debug as debug

def get_desc():
	return "basic debug log for test"


def create(target):
	myModule = module.Module(__file__, 'test-debug', 'LIBRARY')
	myModule.add_src_file([
		'test-debug/debug.cpp'
		])
	myModule.add_module_depend('etk')
	myModule.add_export_path(tools.get_current_path(__file__))
	return myModule


