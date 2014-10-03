#!/usr/bin/python
import lutinModule as module
import lutinTools as tools
import datetime

def get_desc():
	return "e-tk test software"


def create(target):
	# module name is 'edn' and type binary.
	myModule = module.Module(__file__, 'etktest', 'BINARY')
	
	# add the file to compile:
	myModule.add_src_file([
		'test/main.cpp'])
	
	myModule.add_module_depend(['etk'])
	
	#myModule.compile_flags_XX(["-nostdinc++"]);
	
	# add the currrent module at the system
	return myModule

