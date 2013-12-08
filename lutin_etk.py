#!/usr/bin/python
import lutinModule
import lutinTools

def Create(target):
	# module name is 'edn' and type binary.
	myModule = lutinModule.module(__file__, 'etk', 'LIBRARY')
	# enable doculentation :
	myModule.doc_enable()
	myModule.documentation.set_website("http://HeeroYui.github.io/etk/")
	myModule.documentation.set_path(lutinTools.GetCurrentPath(__file__) + "/etk/")
	myModule.documentation.set_external_link(['linearmath','minizip'])
	# add extra compilation flags :
	myModule.add_extra_compile_flags()
	# add the file to compile:
	myModule.AddSrcFile([
		'etk/debugGeneric.cpp',
		'etk/debug.cpp',
		'etk/unicode.cpp',
		'etk/unicodeTable.cpp',
		'etk/Char.cpp',
		'etk/UChar.cpp',
		'etk/UString.cpp',
		'etk/Stream.cpp',
		'etk/RegExp.cpp',
		'etk/tool.cpp',
		'etk/Noise.cpp',
		'etk/Color.cpp',
		'etk/math/Matrix4.cpp',
		'etk/math/Vector2D.cpp',
		'etk/math/Vector3D.cpp',
		'etk/math/Vector4D.cpp',
		'etk/os/FSNode.cpp',
		'etk/os/FSNodeRight.cpp',
		'etk/archive/Archive.cpp',
		'etk/archive/Zip.cpp'])
	
	if target.name=="Windows":
		myModule.AddSrcFile('etk/os/Mutex.Windows.cpp')
		myModule.AddSrcFile('etk/os/Semaphore.Windows.cpp')
	else:
		myModule.AddSrcFile('etk/os/Mutex.Generic.cpp')
		myModule.AddSrcFile('etk/os/Semaphore.Generic.cpp')
	
	# name of the dependency
	myModule.AddModuleDepend('linearmath')
	myModule.AddModuleDepend('minizip')
	
	if target.buildMode == "release":
		# TODO : The other way is to remove this ...
		# TODO : Fore release mode : the etk folder are absolutly not at the same position in the tree ...
		myModule.CompileFlags_CC("-DMODE_RELEASE")
	else:
		myModule.AddExportFlag_CC("-DDEBUG_LEVEL=3")
		myModule.AddExportFlag_CC("-DDEBUG=1")
		# Bor backtrace display :
		if target.name!="Windows":
			myModule.AddExportflag_LD("-ldl -rdynamic")
	
	if target.name=="Windows":
		None
	elif target.name=="Android":
		None
	else:
		myModule.AddExportflag_LD("-lpthread")
	
	myModule.AddExportPath(lutinTools.GetCurrentPath(__file__))
	
	# add the currrent module at the 
	return myModule


