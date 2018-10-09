/** @file
 * @author Edouard DUPIN
 * @copyright 2017, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once
#include <etk/types.hpp>

// it is define bu generic "include <new>" ==> no double define of placement new
#ifndef _NEW
	// Default placement versions of operator new (use char* instead of void* to permit no multiple definition).
	inline void* operator new(size_t, char* _p) throw() {
		return _p;
	}
	inline void operator delete (void*, char*) throw() {
		
	}
#endif

//#define ETK_MEMORY_CHECKER 2

#ifndef ETK_MEMORY_CHECKER
	#define ETK_MEMORY_CHECKER 0
#endif

#if ETK_MEMORY_CHECKER > 0
	namespace etk {
		namespace memory {
			/**
			 * @brief Create an allocation memory and set start and stop header. Log in the curent structure.
			 * If no more free element in the basic structure, the system allocate without saving information and header start and stop
			 * @param[in] _num number of alament needed to allocate
			 * @param[in] _size Size of one element to allocate
			 * @param[in] _variableName Variable name to allocate (must be a real static cont never removed)
			 * @param[in] _functionName Fonction Name where allocation is done (must be a real static cont never removed)
			 * @param[in] _line Line where allocation is done.
			 * @param[in] _fileName File where allocation is done. (must be a real static cont never removed)
			 * @return pointer on the current memory allocation. (or NULL if an error occured)
			 */
			void* allocate(size_t _num, size_t _size, const char* _variableName, const char* _functionName, int32_t _line, const char* _fileName);
			/**
			 * @brief Free Memory with the dedicate pointer
			 * If the memory is not saved the current pointer is free, else we get the real pointer and free it
			 * @param[in,out] _pointerData User pointer Data.
			 * @param[in] _variableName Variable name where free is done. (must be a real static cont never removed)
			 * @param[in] _functionName Fonction name where free is done. (must be a real static cont never removed)
			 * @param[in] _line line where free is done.
			 * @param[in] _fileName file where free is done. (must be a real static cont never removed)
			 */
			void remove(void* _pointerData, const char* _variableName, const char* _functionName, int32_t _line, const char* _fileName);
			/**
			 * @brief Display all memory not free by this system.
			 * @param[in] _statusOnly Display only the memory allocation status.
			 */
			void display(bool _statusOnly=true);
			/**
			 * @brief Check if memory have not write out of the range.
			 */
			bool check();
			/**
			 * @brief Check if the pointer is already register in the allocator (can not predist the size, but permti to know where the error came from in debug mode
			 * @param[in] _pointerPointer on the data to check
			 * @return true the pointer is set
			 * @return false the pointer is not set
			 */
			bool checkPointer(void* _pointer);
			/**
			 * @brief Create a snapshoot of the memory
			 * @return handle on the snapshoot
			 */
			uint64_t* createSnapshoot();
			/**
			 * @brief Check if a snapshoot is correct (no change)
			 * @param[in] _handle Handle on the snapshoot
			 * @return true the memory is identical
			 */
			bool checkSnapshoot(uint64_t* _handle);
			/**
			 * @brief Free the snapshoot handle
			 * @param[in] _handle Handle on the snapshoot
			 */
			void clearSnapshoot(uint64_t* _handle);
			/**
			 * @brief When reallocate data and permit to the allocator to not warning when check the the snapshoot
			 */
			void flipID(void* _pointer1, void* _pointer2);
			
			template<class ETK_TYPE,
			         class... ETK_MEMORY_ARGS>
			ETK_TYPE* allocatorNew(ETK_MEMORY_ARGS&& ... _args) {
				char* tmp = (char*)etk::memory::allocate(1, sizeof(ETK_TYPE), "new", __func__, __LINE__, __FILE__);
				return new (tmp) ETK_TYPE(etk::forward<ETK_MEMORY_ARGS>(_args)...);
			}
			template<class ETK_TYPE,
			         class... ETK_MEMORY_ARGS>
			ETK_TYPE* allocatorNewSize(size_t _size, ETK_MEMORY_ARGS&& ... _args) {
				char* tmp = (char*)etk::memory::allocate(_size, sizeof(ETK_TYPE), "new", __func__, __LINE__, __FILE__);
				return new (tmp) ETK_TYPE(etk::forward<ETK_MEMORY_ARGS>(_args)...);
			}
			template<class ETK_TYPE,
			         class... ETK_MEMORY_ARGS>
			ETK_TYPE* allocatorNewFull(const char* _variableName,
			                           const char* _functionName,
			                           int32_t _line,
			                           const char* _fileName,
			                           ETK_MEMORY_ARGS&& ... _args) {
				char* tmp = (char*)etk::memory::allocate(1, sizeof(ETK_TYPE), _variableName, _functionName, _line, _fileName);
				return new (tmp) ETK_TYPE(etk::forward<ETK_MEMORY_ARGS>(_args)...);
			}
			template<class ETK_TYPE>
			void allocatorDelete(ETK_TYPE* _element,
			                     const char* _variableName = "",
			                     const char* _functionName = "",
			                     int32_t _line = __LINE__,
			                     const char* _fileName = __FILE__) {
				if (_element == null) {
					return;
				}
				_element->~ETK_TYPE();
				etk::memory::remove((void*)_element, _variableName, _functionName, _line, _fileName);
				_element = null;
			}
		}
	}
	
	#define ETK_NEW(type, ...) \
		new ((char*)etk::memory::allocate(1, sizeof(type), #type, __func__, __LINE__, __FILE__)) type(__VA_ARGS__)
	
	#define ETK_DELETE(type, pointerData) \
		etk::memory::allocatorDelete((type*)(pointerData), #type, __func__, __LINE__, __FILE__)
	
	#define ETK_MALLOC(type, nbElements) \
		((type *)etk::memory::allocate( (nbElements), sizeof(type), #type, __func__, __LINE__, __FILE__))
	
	#define ETK_FREE(type, pointerData) \
		etk::memory::remove( (pointerData), #type, __func__, __LINE__, __FILE__)
	
	#define ETK_MEM_SHOW_LOG(...) \
		etk::memory::display(__VA_ARGS__)
	
	#define ETK_MEM_CHECK() \
		etk::memory::check()
	
	#define ETK_MEM_CHECK_POINTER(pointer) \
		etk::memory::checkPointer(pointer)
	
	#define ETK_MEM_FLIP_ID(pointer1, pointer2) \
		etk::memory::flipID((void*)pointer1, (void*)pointer2)
#else
	namespace etk {
		namespace memory {
			template<class ETK_TYPE,
			         class... ETK_MEMORY_ARGS>
			ETK_TYPE* allocatorNew(ETK_MEMORY_ARGS&& ... _args) {
				return new ETK_TYPE(etk::forward<ETK_MEMORY_ARGS>(_args)...);
			}
			template<class ETK_TYPE,
			         class... ETK_MEMORY_ARGS>
			ETK_TYPE* allocatorNewFull(const char* _variableName,
			                           const char* _functionName,
			                           int32_t _line,
			                           const char* _fileName,
			                           ETK_MEMORY_ARGS&& ... _args) {
				return new ETK_TYPE(etk::forward<ETK_MEMORY_ARGS>(_args)...);
			}
			template<class ETK_TYPE>
			void allocatorDelete(ETK_TYPE* _element,
			                     const char* _variableName = "",
			                     const char* _functionName = "",
			                     int32_t _line = __LINE__,
			                     const char* _fileName = __FILE__) {
				delete _element;
			}
		}
	}
	
	#define ETK_NEW(type, ...) \
		new type(__VA_ARGS__)
	
	#define ETK_DELETE(type, pointerData) \
		delete ((type*)(pointerData))
	
	#define ETK_MALLOC(dataType, nbElements) \
		(dataType *)new dataType[nbElements]
	
	#define ETK_FREE(type, pointerData) \
		delete[] (type*)pointerData
	
	#define ETK_MEM_SHOW_LOG(...) \
		do { } while(false)
	
	#define ETK_MEM_CHECK() \
		do {} while(false)
	
	#define ETK_MEM_CHECK_POINTER(pointer) \
		do {} while(false)
	
	#define ETK_MEM_FLIP_ID(pointer1, pointer2) \
		do {} while(false)

#endif
