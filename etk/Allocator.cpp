/** @file
 * @author Edouard DUPIN
 * @copyright 2017, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/Allocator.hpp>
#include <stdlib.h>
/*
void* operator new (size_t size) {
	return malloc(size);
}

void* operator new[] (size_t size) {
	return malloc(size);
}


void operator delete (void* ptr) {
	free(ptr);
}

void operator delete[] (void* ptr) {
	free(ptr);
}
*/



#if ETK_MEMORY_CHECKER > 0

#include <pthread.h>



#define ETK_MEM_DEBUG_LEVEL 4

#define ETK_MEMORY_PRINT(...) \
	do { \
		printf("[PRINT] "); \
		printf(__VA_ARGS__); \
		printf("\n"); \
	} while (false)
	
#if ETK_MEM_DEBUG_LEVEL > 0
	#define ETK_MEMORY_ERROR(...) \
		do { \
			printf("[ERROR] "); \
			printf(__VA_ARGS__); \
			printf("\n"); \
		} while (false)
#else
	#define ETK_MEMORY_ERROR(...) do {} while (false)
#endif
#if ETK_MEM_DEBUG_LEVEL > 1
	#define ETK_MEMORY_WARNING(...) \
		do { \
			printf("[WARNING] "); \
			printf(__VA_ARGS__); \
			printf("\n"); \
		} while (false)
#else
	#define ETK_MEMORY_WARNING(...) do {} while (false)
#endif
#if ETK_MEM_DEBUG_LEVEL > 2
	#define ETK_MEMORY_INFO(...) \
		do { \
			printf("[INFO] "); \
			printf(__VA_ARGS__); \
			printf("\n"); \
		} while (false)
#else
	#define ETK_MEMORY_INFO(...) do {} while (false)
#endif
#if ETK_MEM_DEBUG_LEVEL > 3
	#define ETK_MEMORY_DEBUG(...) \
		do { \
			printf("[DEBUG] "); \
			printf(__VA_ARGS__); \
			printf("\n"); \
		} while (false)
#else
	#define ETK_MEMORY_DEBUG(...) do {} while (false)
#endif

#if ETK_MEM_DEBUG_LEVEL > 4
	#define ETK_MEMORY_VERBOSE(...) \
		do { \
			printf("[VERBOSE] "); \
			printf(__VA_ARGS__); \
			printf("\n"); \
		} while (false)
#else
	#define ETK_MEMORY_VERBOSE(...) do {} while (false)
#endif

#if ETK_MEMORY_CHECKER > 1
	// Max stric size of filename, variable Name, and fonction Name
	#define ETK_MEM_MAX_STRING_SIZE (77)
#endif
/**
 * @brief Class to save allocation elements
 */
class MemoryElementSystem {
	public:
		bool used; //!< for list system
		char* pointerAllocated; //!< pointer really allocated
		char* pointerGiveToUser; //!< pointer sent to the USER (in case of check of memory overflow)
		size_t sizeUser; //!< User request size
		size_t sizeAllocate; //!< data size really allocated by the tool
		size_t sizeData; //!< current data size of allocated memory
		#if ETK_MEMORY_CHECKER > 1
			size_t id; //!< Element ID to know the allocation Order
			char variableName[ETK_MEM_MAX_STRING_SIZE]; //!< Variable name when allocate
			char functionName[ETK_MEM_MAX_STRING_SIZE]; //!< function name that allocate this buffer
			char fileName[ETK_MEM_MAX_STRING_SIZE]; //!< function name that allocate this buffer
			size_t functionLine; //!< function line where the buffer was allocated
		#endif
};

class memoryAllocatorHandle {
	private:
		// to prevent double access:
		pthread_mutex_t m_mutex;
		#if ETK_MEMORY_CHECKER > 1
			// Basic header to check the memory everflow (abstract element)
			uint8_t* m_blockCheckMemory;
			// To know the size of pre header and Post-header
			uint32_t m_checkBorneSize;
		#endif
		// To do statictic memory allocation (Total of memory allocate from the start of program)
		uint64_t m_totalMemAllocated;
		// To do statictic memory allocation (Current size of allocated memory)
		uint64_t m_currentMemAllocated;
		// To do statictic memory allocation (Current size of allocated memory)
		int64_t m_currentMemAllocatedCount;
		int64_t m_currentMemAllocatedCountSize[64];
		int64_t m_totalMemAllocatedCountSize[64];
		// To do statictic memory allocation (Max of memory allocated in the same Time)
		uint64_t m_maxMemoryAllocated;
		// To do statictic memory allocation (number of allocation)
		int64_t m_dynamicID;
		// To know if this memory system is initialized
		bool m_memSystemInitialize;
		// List of element to remember allocate...
		size_t m_memListElementSize;
		MemoryElementSystem* m_memListElements;
	public:
		memoryAllocatorHandle():
		  m_mutex(PTHREAD_MUTEX_INITIALIZER),
		  #if ETK_MEMORY_CHECKER > 1
		  	// Basic header to check the memory everflow (abstract element)
		  	m_blockCheckMemory(nullptr),
		  	m_checkBorneSize(10*8),
		  #endif
		  m_totalMemAllocated(0),
		  m_currentMemAllocated(0),
		  m_currentMemAllocatedCount(0),
		  m_maxMemoryAllocated(0),
		  m_dynamicID(0),
		  m_memSystemInitialize(false),
		  m_memListElementSize(1024),
		  m_memListElements(nullptr) {
			#if ETK_MEMORY_CHECKER > 1
				static const uint8_t blockCheckMemory[] = {
					0xFF, 0xEE, 0xDD, 0xCC, 0xBB, 0xAA, 0x99, 0x88,
					0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00,
					0x55, 0xAA, 0x5A, 0xA5, 0x11, 0xFF, 0x15, 0xB2,
					0x55, 0xAA, 0x5A, 0xA5, 0x11, 0xFF, 0x15, 0xB2,
					0x55, 0xAA, 0x5A, 0xA5, 0x11, 0xFF, 0x15, 0xB2,
					0x55, 0xAA, 0x5A, 0xA5, 0x11, 0xFF, 0x15, 0xB2,
					0x55, 0xAA, 0x5A, 0xA5, 0x11, 0xFF, 0x15, 0xB2,
					0x55, 0xAA, 0x5A, 0xA5, 0x11, 0xFF, 0x15, 0xB2,
					0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
					0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF
				};
				m_blockCheckMemory = (uint8_t*)blockCheckMemory;
			#endif
			lock();
			memset(m_totalMemAllocatedCountSize, 0, sizeof(m_totalMemAllocatedCountSize));
			memset(m_currentMemAllocatedCountSize, 0, sizeof(m_currentMemAllocatedCountSize));
			if (m_memSystemInitialize == true) {
				return;
			}
			int systemRet;
			if (m_memListElements == nullptr) {
				m_memListElements = new MemoryElementSystem[m_memListElementSize];
			}
			for (size_t iii=0; iii<m_memListElementSize; ++iii) {
				m_memListElements[iii].used = false;
			}
			m_memSystemInitialize = true;
			unLock();
		}
		/**
		 * @brief Update statistique
		 * @param[in] _dataSize Allocated size
		 */
		void addMemory(size_t _dataSize) {
			m_totalMemAllocated += _dataSize;
			m_currentMemAllocated += _dataSize;
			if (m_currentMemAllocated > m_maxMemoryAllocated) {
				m_maxMemoryAllocated = m_currentMemAllocated;
			}
			m_currentMemAllocatedCount++;
			for (int32_t iii=0; iii<64; ++iii) {
				if (_dataSize <= (uint64_t(1) << iii)) {
					m_totalMemAllocatedCountSize[iii]++;
					break;
				}
			}
			for (int32_t iii=0; iii<64; ++iii) {
				if (_dataSize <= (uint64_t(1) << iii)) {
					m_currentMemAllocatedCountSize[iii]++;
					break;
				}
			}
		}
		void lock() {
			pthread_mutex_lock(&m_mutex);
		}
		void unLock() {
			pthread_mutex_unlock(&m_mutex);
		}
		/**
		 * @brief Update memory statistique
		 * @param[in] dataSize Removed size.
		 */
		void removeMemory(size_t _dataSize) {
			m_currentMemAllocated -= _dataSize;
			m_currentMemAllocatedCount--;
			for (int32_t iii=0; iii<64; ++iii) {
				if (_dataSize <= (uint64_t(1) << iii)) {
					m_currentMemAllocatedCountSize[iii]--;
					break;
				}
			}
		}
		
		/**
		 * @brief Get a current free element of the structure
		 * @return the free Element find or nullptr
		 */
		MemoryElementSystem* getFreeElement() {
			for (size_t iii=0; iii<m_memListElementSize; ++iii) {
				if (m_memListElements[iii].used == false) {
					return &(m_memListElements[iii]);
				}
			}
			// resize Linker size:
			m_memListElementSize *= 2;
			ETK_MEMORY_DEBUG("Realloate the allocator memory system: %ld", uint64_t(m_memListElementSize));
			MemoryElementSystem* tmp = new MemoryElementSystem[m_memListElementSize];
			if (tmp == nullptr) {
				m_memListElementSize /= 2;
				return nullptr;
			}
			for (size_t iii=0; iii<m_memListElementSize; ++iii) {
				tmp[iii].used = false;
			}
			memcpy(tmp, m_memListElements, sizeof(MemoryElementSystem) * m_memListElementSize / 2);
			delete[] m_memListElements;
			m_memListElements = tmp;
			// try again
			for (size_t iii=0; iii<m_memListElementSize; ++iii) {
				if (m_memListElements[iii].used == false) {
					return &(m_memListElements[iii]);
				}
			}
			return nullptr;
		}
		/**
		 * @brief Get the element structure reference if it existed
		 * @param[in] pointerAdresse pointer to retreave the element
		 * @return get the element reference for the curent adress pointer
		 */
		MemoryElementSystem *getAdressedElement(char* _pointerAdresse) {
			for (size_t iii=0; iii<m_memListElementSize; ++iii) {
				if (m_memListElements[iii].used == true) {
					if (m_memListElements[iii].pointerGiveToUser == _pointerAdresse) {
						return &(m_memListElements[iii]);
					}
				}
			}
			return nullptr;
		}
		
		#if ETK_MEMORY_CHECKER > 1
			/**
			 * @brief Verify the curent Memory header
			 * This function vereify the memeory with the common header and header size.
			 * @param[in] pointerAdresse Start pointer to verify data
			 * @return the check result :
			 *    - true  : if an error existe
			 *    - false : if no error
			 */
			bool checkMem(char* _pointerAdresse) {
				uint8_t *pointer = (uint8_t*)_pointerAdresse;
				for (size_t iii=0; iii<m_checkBorneSize; ++iii) {
					if (*(pointer++) != m_blockCheckMemory[iii]) {
						return true;
					}
				}
				return false;
			}
		#endif
		
		
		#if ETK_MEMORY_CHECKER > 1
			/**
			 * @brief Display the current buffer to check error.
			 * Desactivated by debault (only for extreme debug)
			 * @param[in] _pointerAdresse pointer to start the print
			 * @param[in] _size number of char to display
			 */
			void displayBuffer(char* _pointerAdresse, uint32_t _size) {
				/*
				uint8_t *pointer = (uint8_t *)_pointerAdresse;
				uint32_t i;
				for (i=0; i<_size ;i++) {
					if (i%50 == 0) {
						printf("\n");
					}
					printf("%02X ", pointer[i]);
				}
				printf("\n");
				*/
			}
		#endif
		
		
		#if ETK_MEMORY_CHECKER > 1
			/**
			 * @brief Get the filename (without all the Path)
			 * @param[in] _fileLink pointer on the name with the Path
			 * @return The last pointer of the filename
			 */
			const char *getFileName(const char* _fileLink) {
				const char *element_2 = _fileLink;
				const char *element_1 = _fileLink;
				const char *element_0 = _fileLink;
				const char * pch = nullptr;
				pch = _fileLink;
				while (pch != nullptr) {
					element_2 = element_1;
					element_1 = element_0;
					element_0 = pch;
					pch = strchr(pch+1, '/');
				}
				return element_2;
			}
		#endif
		void displayMemoryProperty(MemoryElementSystem& _element) {
			#if ETK_MEMORY_CHECKER > 1
				bool errorOccured = false;
				ETK_MEMORY_WARNING("Not FREE : %p ==> %p : %ld Bytes var=%s",
				                   _element.pointerAllocated,
				                   _element.pointerGiveToUser,
				                   _element.sizeUser,
				                   _element.variableName);
				ETK_MEMORY_WARNING("%8d : %s() line=%ld file=%s",
				                   (uint32_t)_element.id,
				                   _element.functionName,
				                   _element.functionLine,
				                   _element.fileName);
				if (checkMem(_element.pointerAllocated) == true) {
					ETK_MEMORY_ERROR("MEM LOG   (L): %s : %ld Bytes @ %p ==> user @ %p (depassement pre)",
					                 _element.variableName,
					                 _element.sizeUser,
					                 _element.pointerAllocated,
					                 _element.pointerGiveToUser);
					errorOccured = true;
				}
				if (checkMem(_element.pointerAllocated + _element.sizeUser + m_checkBorneSize) == true) {
					ETK_MEMORY_ERROR("MEM LOG   (L): %s : %ld Bytes @ %p ==> user @ %p (depassement post)",
					                 _element.variableName,
					                 _element.sizeUser,
					                 _element.pointerAllocated,
					                 _element.pointerGiveToUser);
					errorOccured = true;
				}
				if (errorOccured == true) {
					displayBuffer(_element.pointerAllocated,
					              _element.sizeAllocate);
					assert(false);
				}
			#else
				ETK_MEMORY_WARNING("Not LOG : %p ==> %p : %d Bytes",
				                   _element.pointerAllocated,
				                   _element.pointerGiveToUser,
				                   _element.sizeUser);
			#endif
		}
		
		uint64_t* createSnapshoot() {
			lock();
			size_t countElement = 0;
			for (size_t iii=0; iii<m_memListElementSize; ++iii) {
				if (m_memListElements[iii].used == true) {
					countElement++;
				}
			}
			if (countElement == 0) {
				unLock();
				return nullptr;
			}
			ETK_MEMORY_VERBOSE("find %ld element in memory", (uint64_t)countElement);
			uint64_t* out = new uint64_t[countElement+10];
			memset(out, 0, sizeof(uint64_t)*(countElement+10));
			countElement = 0;
			for (size_t iii=0; iii<m_memListElementSize; ++iii) {
				if (m_memListElements[iii].used == true) {
					out[countElement++] = uint64_t(m_memListElements[iii].pointerAllocated);
				}
			}
			unLock();
			return out;
		}
		
		bool checkSnapshoot(uint64_t* _handle) {
			if (_handle == nullptr) {
				return false;
			}
			lock();
			bool haveError = false;
			for (size_t iii=0; iii<m_memListElementSize; ++iii) {
				if (m_memListElements[iii].used == true) {
					uint64_t* dataBase = _handle;
					bool find = false;
					size_t jjj = 0;
					while (dataBase[jjj] != 0) {
						if (dataBase[jjj] == uint64_t(m_memListElements[iii].pointerAllocated)) {
							find = true;
							break;
						}
						jjj++;
						//dataBase++;
					}
					if (find == false) {
						haveError = true;
						displayMemoryProperty(m_memListElements[iii]);
					}
				}
			}
			unLock();
			return haveError == false;
		}
		
		void clearSnapshoot(uint64_t* _handle) {
			if (_handle == nullptr) {
				return;
			}
			delete[] (uint64_t*)_handle;
		}
		
		
		
		void* allocate(size_t _num,
		               size_t _size,
		               const char* _variableName,
		               const char* _functionName,
		               int32_t _line,
		               const char* _fileName) {
			MemoryElementSystem* myElement;
			lock();
			m_dynamicID++;
			myElement = getFreeElement();
			// check free handle
			if (myElement != nullptr) {
				#if ETK_MEMORY_CHECKER > 1
					const char *fileNameShort = nullptr;
					myElement->id = m_dynamicID;
				#endif
				// if an element is free : 
				myElement->sizeUser = _size * _num;
				myElement->sizeData = _size;
				#if ETK_MEMORY_CHECKER > 1
					myElement->sizeAllocate = myElement->sizeUser + m_checkBorneSize*2;
					if (_variableName == nullptr) {
						strncpy(myElement->variableName, "---", ETK_MEM_MAX_STRING_SIZE);
					} else {
						strncpy(myElement->variableName, _variableName, ETK_MEM_MAX_STRING_SIZE);
					}
					myElement->variableName[ETK_MEM_MAX_STRING_SIZE-1] = 0;
					if (_functionName == nullptr) {
						strncpy(myElement->functionName, "---", ETK_MEM_MAX_STRING_SIZE);
					} else {
						strncpy(myElement->functionName, _functionName, ETK_MEM_MAX_STRING_SIZE);
					}
					myElement->functionName[ETK_MEM_MAX_STRING_SIZE-1] = 0;
					if (_fileName == nullptr) {
						strncpy(myElement->fileName, "---", ETK_MEM_MAX_STRING_SIZE);
					} else {
						fileNameShort = getFileName(_fileName);
						strncpy(myElement->fileName, fileNameShort, ETK_MEM_MAX_STRING_SIZE);
					}
					myElement->fileName[ETK_MEM_MAX_STRING_SIZE-1] = 0;
					myElement->functionLine = _line;
				#else
					myElement->sizeAllocate = myElement->sizeUser;
				#endif
				myElement->pointerAllocated = nullptr;
				myElement->pointerGiveToUser = nullptr;
				// real allocation :
				myElement->pointerAllocated = new char[myElement->sizeAllocate];
				if (myElement->pointerAllocated != nullptr) {
					// set edded memory
					addMemory(myElement->sizeUser);
					// save curent pointer
					#if ETK_MEMORY_CHECKER > 1
						myElement->pointerGiveToUser = myElement->pointerAllocated + m_checkBorneSize;
					#else
						myElement->pointerGiveToUser = myElement->pointerAllocated;
					#endif
					ETK_MEMORY_VERBOSE("MEM allocate (L): %s : %ld Bytes @ %p ==> user @ %p", _variableName, _num*_size, myElement->pointerAllocated, myElement->pointerGiveToUser);
					// set bornes:
					#if ETK_MEMORY_CHECKER > 1
						memcpy(myElement->pointerAllocated, m_blockCheckMemory, m_checkBorneSize);
					#endif
					#if ETK_MEMORY_CHECKER > 1
						memcpy(myElement->pointerAllocated + myElement->sizeUser + m_checkBorneSize, m_blockCheckMemory, m_checkBorneSize);
					#endif
					// add to the elements list
					myElement->used = true;
				} else {
					ETK_MEMORY_VERBOSE("MEM allocate (L): %s : %zu Bytes @ (ERROR)", _variableName, myElement->sizeUser);
				}
				unLock();
				// else : no memory allocated ==> nothing to save
				return myElement->pointerGiveToUser;
			} else {
				// if no free handle:
				void * localPointer = nullptr;
				localPointer = new char[_num * _size];
				if (localPointer != nullptr) {
					ETK_MEMORY_VERBOSE("MEM allocate (-): %s : %lu Bytes @ %p (No log...)", _variableName, _num*_size, localPointer);
					// set edded memory
					//addMemory(_num * _size); // not availlable can not un add memory
					m_totalMemAllocated += _num * _size;
				} else {
					ETK_MEMORY_VERBOSE("MEM allocate (-): %s : %lu Bytes @ (ERROR)", _variableName, _num*_size);
				}
				unLock();
				return localPointer;
			}
		}
		
		void remove(void* _pointerData, const char* _variableName, const char* _functionName, int32_t _line, const char* _fileName) {
			MemoryElementSystem * myElement;
			lock();
			char* asyncFree = nullptr;
			myElement = getAdressedElement((char*)_pointerData);
			// check free handle
			if (myElement != nullptr) {
				bool errorOccured = false;
				// We know this element :
				#if ETK_MEMORY_CHECKER > 1
					// check end and Start :
					if (checkMem(myElement->pointerAllocated) == true) {
						ETK_MEMORY_ERROR("MEM free   (L): %s : %zu Bytes @ %p ==> user @ %p (depassement pre)",_variableName, myElement->sizeUser, myElement->pointerAllocated, myElement->pointerGiveToUser);
						errorOccured = true;
					}
					if (checkMem(myElement->pointerAllocated + myElement->sizeUser + m_checkBorneSize) == true) {
						ETK_MEMORY_ERROR("MEM free   (L): %s : %zu Bytes @ %p ==> user @ %p (depassement post)",_variableName, myElement->sizeUser, myElement->pointerAllocated, myElement->pointerGiveToUser);
						errorOccured = true;
					}
					if (errorOccured == false) {
						ETK_MEMORY_VERBOSE("MEM free   (L): %s : %zu Bytes @ %p ==> user @ %p",_variableName, myElement->sizeUser, myElement->pointerAllocated, myElement->pointerGiveToUser);
					} else {
						displayBuffer(myElement->pointerAllocated, myElement->sizeAllocate);
						//ETK_ASSERT(1 == 0, "Memory error detected");
					}
				#else
					ETK_MEMORY_VERBOSE("MEM free   (L): %s : %d Bytes @ %p ==> user @ %p",_variableName, myElement->sizeUser, myElement->pointerAllocated, myElement->pointerGiveToUser);
				#endif
				asyncFree = myElement->pointerAllocated;
				myElement->pointerAllocated = nullptr;
				removeMemory(myElement->sizeUser);
				myElement->used = false;
			}
			unLock();
			if (asyncFree != nullptr) {
				// free Buffer:
				delete[] asyncFree;
				return;
			}
			//Unknown element
			ETK_MEMORY_WARNING("MEM free   (-): %s : ?? Bytes @ %p ==> unsaved element",_variableName, _pointerData);
			delete (char*)_pointerData;
		}
		
		void displayMemorySize(size_t _size, const char* _name) {
			if (_size > 1024*1024*1024) {
				uint32_t teraByte = _size/(1024*1024*1024);
				uint32_t megaByte = (_size/(1024*1024)%1024);
				uint32_t kiloByte = (_size/1024) % 1024;
				uint32_t byte = _size % 1024;
				ETK_MEMORY_DEBUG("MEM : %s: %4dT %4dM %4dk %4dB", _name, teraByte, megaByte, kiloByte, byte);
			} else if (_size > 1024*1024) {
				uint32_t megaByte = _size/(1024*1024);
				uint32_t kiloByte = (_size/1024) % 1024;
				uint32_t byte = _size % 1024;
				ETK_MEMORY_DEBUG("MEM : %s:      %4dM %4dk %4dB", _name, megaByte, kiloByte, byte);
			} else if (m_totalMemAllocated > 1024) {
				uint32_t megaByte = _size/(1024*1024);
				uint32_t kiloByte = (_size/1024) % 1024;
				uint32_t byte = _size % 1024;
				ETK_MEMORY_DEBUG("MEM : %s:            %4dk %4dB", _name, kiloByte, byte);
			} else {
				uint32_t megaByte = _size/(1024*1024);
				uint32_t kiloByte = (_size/1024) % 1024;
				uint32_t byte = _size % 1024;
				ETK_MEMORY_DEBUG("MEM : %s:                  %4dB", _name, byte);
			}
		}
		
		void display(bool _statusOnly) {
			lock();
			ETK_MEMORY_DEBUG("MEM: Log : ------------------------------");
			ETK_MEMORY_DEBUG("MEM: (current/total) allocation: %ld / %ld ", int64_t(m_currentMemAllocatedCount), uint64_t(m_dynamicID));
			for (int32_t iii=0; iii<64; ++iii) {
				if (m_currentMemAllocatedCountSize[iii] != 0) {
					ETK_MEMORY_DEBUG("MEM: Number (current/Total) of allocation: 2<<%2d: %8ld / %8ld     %9ld Bytes",
					                 iii,
					                 uint64_t(m_currentMemAllocatedCountSize[iii]),
					                 uint64_t(m_totalMemAllocatedCountSize[iii]),
					                 (uint64_t(1)<<iii));
				}
			}
			ETK_MEMORY_DEBUG("MEM: number of element that can be registered %ld", m_memListElementSize);
			displayMemorySize(m_memListElementSize*sizeof(MemoryElementSystem) + sizeof(memoryAllocatorHandle),   "System allocator     ");
			displayMemorySize(m_totalMemAllocated,   "Total allocated      ");
			displayMemorySize(m_currentMemAllocated, "Total Current Use    ");
			displayMemorySize(m_maxMemoryAllocated,  "Max simultaneous Use ");
			if (_statusOnly == true) {
				unLock();
				return;
			}
			ETK_MEMORY_DEBUG("MEM : Log : ----------- Memory -----------");
			for (size_t iii=0; iii<m_memListElementSize; ++iii) {
				if (m_memListElements[iii].used == true) {
					displayMemoryProperty(m_memListElements[iii]);
				}
			}
			ETK_MEMORY_DEBUG("MEM : -----------------------------------");
			unLock();
		}
		
		bool check() {
			bool detectError = false;
			lock();
			for (size_t iii=0; iii<m_memListElementSize; ++iii) {
				if (m_memListElements[iii].used == true) {
					#if ETK_MEMORY_CHECKER > 1
						bool errorOccured = false;
						if (checkMem(m_memListElements[iii].pointerAllocated) == true) {
							ETK_MEMORY_ERROR("MEM CHECK  (L): %s : %ld Bytes @ %p ==> user @ %p (depassement pre)",m_memListElements[iii].variableName, m_memListElements[iii].sizeUser, m_memListElements[iii].pointerAllocated, m_memListElements[iii].pointerGiveToUser);
							errorOccured = true;
						}
						if (checkMem(m_memListElements[iii].pointerAllocated + m_memListElements[iii].sizeUser + m_checkBorneSize) == true) {
							ETK_MEMORY_ERROR("MEM CHECK  (L): %s : %ld Bytes @ %p ==> user @ %p (depassement post)",m_memListElements[iii].variableName, m_memListElements[iii].sizeUser, m_memListElements[iii].pointerAllocated, m_memListElements[iii].pointerGiveToUser);
							errorOccured = true;
						}
						if (errorOccured == true) {
							detectError = true;
							displayBuffer(m_memListElements[iii].pointerAllocated, m_memListElements[iii].sizeAllocate);
							// Clean all the erreor to prevent the other error display
							memcpy(m_memListElements[iii].pointerAllocated, m_blockCheckMemory, m_checkBorneSize);
							// Clean all the erreor to prevent the other error display
							memcpy(m_memListElements[iii].pointerAllocated + m_memListElements[iii].sizeUser + m_checkBorneSize, m_blockCheckMemory, m_checkBorneSize);
						}
					#endif
				}
			}
			unLock();
			return detectError;
		}
		
		bool checkPointer(void* _pointer) {
			lock();
			for (size_t iii=0; iii<m_memListElementSize; ++iii) {
				if (m_memListElements[iii].used == true) {
					bool find = false;
					if (m_memListElements[iii].pointerAllocated == _pointer) {
						find = true;
					}
					if (m_memListElements[iii].pointerGiveToUser == _pointer) {
						find = true;
					}
					if (find == true) {
						unLock();
						return true;
					}
				}
			}
			unLock();
			ETK_MEMORY_ERROR("MEM Check pointer: Can not find the pointer in the system DB...");
			return false;
		}
};

// This permit to initialize the handle just in time ...
static memoryAllocatorHandle& getHandle() {
	static memoryAllocatorHandle tmp;
	return tmp;
}

uint64_t* etk::memory::createSnapshoot() {
	return getHandle().createSnapshoot();
}

bool etk::memory::checkSnapshoot(uint64_t* _handle) {
	return getHandle().checkSnapshoot(_handle);
}

void etk::memory::clearSnapshoot(uint64_t* _handle) {
	getHandle().clearSnapshoot(_handle);
}

void* etk::memory::allocate(size_t _num,
                            size_t _size,
                            const char* _variableName,
                            const char* _functionName,
                            int32_t _line,
                            const char* _fileName) {
	return getHandle().allocate(_num, _size, _variableName, _functionName, _line, _fileName);
}

void etk::memory::remove(void* _pointerData, const char* _variableName, const char* _functionName, int32_t _line, const char* _fileName) {
	getHandle().remove(_pointerData, _variableName, _functionName, _line, _fileName);
}

void etk::memory::display(bool _statusOnly) {
	getHandle().display(_statusOnly);
}

bool etk::memory::check() {
	return getHandle().check();
}

bool etk::memory::checkPointer(void* _pointer) {
	return getHandle().checkPointer(_pointer);
}

#endif

