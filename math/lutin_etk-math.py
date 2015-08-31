#!/usr/bin/python
import lutin.module as module
import lutin.tools as tools

def get_desc():
	return "e-tk : Ewol tool kit"


def create(target):
	# module name is 'edn' and type binary.
	myModule = module.Module(__file__, 'etk-math', 'LIBRARY')
	# add extra compilation flags :
	myModule.add_extra_compile_flags()
	# add the file to compile:
	myModule.add_src_file([
		'etk-math/Matrix4.cpp',
		'etk-math/Vector2D.cpp',
		'etk-math/Vector3D.cpp',
		'etk-math/Vector4D.cpp'
		])
	myModule.add_export_path(tools.get_current_path(__file__))
	
	# add the currrent module at the 
	return myModule


