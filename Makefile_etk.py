#!/usr/bin/python
import module
import buildTools

# prevent erro integration
#del myModule

# module name is 'edn' and type binary.
myModule = module.module(__file__, 'etk', 'LIBRARY')
# add the file to compile:


myModule.AddSrcFile([
	'etk/Debug.cpp',
	'etk/DebugInternal.cpp',
	'etk/unicode.cpp',
	'etk/unicodeTable.cpp',
	'etk/Char.cpp',
	'etk/UString.cpp',
	'etk/Stream.cpp',
	'etk/RegExp.cpp',
	'etk/tool.cpp',
	'etk/Noise.cpp'])


myModule.AddSrcFile([
	'etk/math/Matrix4.cpp',
	'etk/math/Vector2D.cpp',
	'etk/math/Vector3D.cpp'])


myModule.AddSrcFile([
	'etk/os/FSNode.cpp',
	'etk/os/FSNodeRight.cpp',
	'etk/os/Memory.cpp'])

# game mode area :
myModule.AddSrcFile([
	'ewol/widget/Scene.cpp',
	'ewol/game/Camera.cpp'])


#ifeq ("$(TARGET_OS)","Windows")
#	myModule.AddSrcFile('etk/os/Mutex.Windows.cpp')
#	myModule.AddSrcFile('etk/os/Semaphore.Windows.cpp')
#else
myModule.AddSrcFile('etk/os/Mutex.Generic.cpp')
myModule.AddSrcFile('etk/os/Semaphore.Generic.cpp')
#endif


# name of the dependency
#ifeq ("$(PLATFORM)","Android")
myModule.AddModuleDepend(['linearmath', 'libzip'])

myModule.CompileFlags_CC([
	'-Wno-write-strings',
	'-Wall'])
# TODO : The other way is to remove this ...
# TODO : Fore release mode : the etk folder are absolutly not at the same position in the tree ...
#,'-DMODE_RELEASE'])


myModule.AddExportPath(buildTools.GetCurrentPath(__file__))


# add the currrent module at the 
module.AddModule(myModule)





