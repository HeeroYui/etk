#!/usr/bin/python
import lutin.module as module
import lutin.tools as tools
import datetime

def get_desc():
	return "e-tk test software"


def create(target):
	# module name is 'edn' and type binary.
	my_module = module.Module(__file__, 'etk-test', 'BINARY')
	
	# add the file to compile:
	my_module.add_src_file([
		'test/main.cpp'])
	
	my_module.add_module_depend(['etk', 'gtest'])
	
	#my_module.compile_flags_XX(["-nostdinc++"]);
	
	# add the currrent module at the system
	return my_module

