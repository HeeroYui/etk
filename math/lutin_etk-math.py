#!/usr/bin/python
import lutin.module as module
import lutin.tools as tools

def get_desc():
	return "e-tk : Ewol tool kit"

def get_license():
	return "APACHE v2.0"

def create(target):
	myModule = module.Module(__file__, 'etk-math', 'LIBRARY')
	myModule.add_extra_compile_flags()
	myModule.add_src_file([
		'etk-math/Matrix4.cpp',
		'etk-math/Vector2D.cpp',
		'etk-math/Vector3D.cpp',
		'etk-math/Vector4D.cpp'
		])
	myModule.add_module_depend(["etk-base"])
	# atomaticly wrap on the bullet lib interface (simplify interface)
	myModule.add_optionnal_module_depend('linearmath', ["c", "-DETK_BUILD_LINEARMATH"], export=True)
	myModule.add_export_path(tools.get_current_path(__file__))
	return myModule


