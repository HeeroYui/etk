#!/usr/bin/python
import lutin.module as module
import lutin.tools as tools
import lutin.debug as debug

def get_desc():
	return "basic debug log for test"


def create(target):
	my_module = module.Module(__file__, 'test-debug', 'LIBRARY')
	my_module.add_src_file([
		'test-debug/debug.cpp'
		])
	my_module.add_module_depend('etk')
	my_module.add_export_path(tools.get_current_path(__file__))
	return my_module


