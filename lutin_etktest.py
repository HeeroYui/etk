#!/usr/bin/python
import lutinModule
import lutinTools
import datetime

def Create(target):
	# module name is 'edn' and type binary.
	myModule = lutinModule.module(__file__, 'etktest', 'BINARY')
	
	# add the file to compile:
	myModule.AddSrcFile([
		'test/main.cpp'])
	
	myModule.AddModuleDepend(['etk'])
	
	# add the currrent module at the system
	return myModule

