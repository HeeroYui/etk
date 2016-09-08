#!/usr/bin/python
import os
import doxy.module as module
import doxy.debug as debug
import doxy.tools as tools

def create(target, module_name):
	my_module = module.Module(__file__, module_name)
	my_module.set_version([0,9,"dev"])
	my_module.set_title("Etk: Ewol Tool Kit")
	my_module.set_website("http://atria-soft.github.io/" + module_name)
	my_module.set_website_sources("http://github.com/atria-soft/" + module_name)
	my_module.add_path([
	    module_name,
	    "doc",
	    ])
	my_module.add_data_path([
	    "data/dox",
	    ])
	my_module.add_depend([
	    'elog',
	    ])
	my_module.add_module_define([
	    "ETK_BUILD_MINIZIP",
	    ])
	my_module.add_exclude_symbols([
	    '*operator<<*',
	    '*string_to_*',
	    '*compare_no_case*',
	    '*end_with*',
	    '*extract_line*',
	    '*isIn*',
	    '*matRotate2*',
	    '*replace*',
	    '*sort*',
	    '*split*',
	    '*start_with*',
	    'tolower',
	    'toupper',
	    ])
	my_module.add_exclude_file([
	    'debug.h',
	    ])
	my_module.add_file_patterns([
	    '*.h',
	    '*.md',
	    ])
	
	
	return my_module
