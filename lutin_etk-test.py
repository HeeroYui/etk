#!/usr/bin/python
import lutin.module as module
import lutin.tools as tools
import datetime

def get_desc():
	return "e-tk test software"

def get_license():
	return "APACHE v2.0"

def create(target):
	myModule = module.Module(__file__, 'etk-test', 'BINARY')
	myModule.add_src_file([
		'test/main.cpp'])
	myModule.add_module_depend(['etk', 'gtest'])
	return myModule

