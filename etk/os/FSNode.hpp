/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

#include <etk/types.hpp>

#pragma once

#include <etk/os/FSNodeRight.hpp>
/**
 * @brief Local maximum file name size
 */
#define MAX_FILE_NAME      (10240)

//http://developer.android.com/guide/topics/data/data-storage.html


#ifdef __TARGET_OS__Android
	#define HAVE_ZIP_DATA
#endif

#ifdef __TARGET_OS__Windows
	#define HAVE_ZIP_DATA
#endif

#ifdef __TARGET_OS__Web
	#define HAVE_ZIP_DATA
#endif


#ifdef HAVE_ZIP_DATA
namespace etk {
	class ArchiveContent;
}
#endif
namespace etk {
	/**
	 * @brief Set the firt argument of the application start (this permit to get the real position of the execution path and executable position
	 * @param[in] _val First parameter.
	 */
	void setArgZero(const std::string& _val);
	/**
	 * @brief Simplify a path with all the complication that mean ".." or "///\//"
	 * @param[in] _input Parth to simplify
	 * @return the simplified path.
	 */
	std::string simplifyPath(std::string _input);
	/**
	 * @brief Get application name.
	 * @return The application name
	 */
	std::string FSNodeGetApplicationName();
	/**
	 * @brief Get application binary path.
	 * @return The application path
	 */
	std::string FSNodeGetApplicationPath();
	/**
	 * @brief List of Type that a node can have (this wrap some type that not exist on Windows)
	 */
	enum typeNode {
		typeNode_unknow, //!< Type of the node is not known
		typeNode_block, //!< The node is a block aceess device (Not availlable on Windows)
		typeNode_character, //!< The node is a Char device type (Not availlable on Windows)
		typeNode_folder, //!< The node is a folder
		typeNode_fifo, //!< The node is a Fifo (Not availlable on Windows)
		typeNode_link, //!< The node is a Link
		typeNode_file, //!< The node is a File
		typeNode_socket, //!< The node is a socket
	};
	//! @not_in_doc
	std::ostream& operator <<(std::ostream &_os, const enum etk::typeNode &_obj);
	/**
	 * @brief Seek mode availlable (just to wrap it ...)
	 */
	enum seekNode{
		seekNode_start, //!< request seek position start at the START of the file
		seekNode_end, //!< request seek position start at the END of the file
		seekNode_current, //!< request seek position start at the CURRENT position in the file
	};
	/**
	 * @brief Type of the file/folder/... accessible in the Node
	 */
	enum FSNType {
		FSNType_unknow, //!< Unknow type of the node (many time no file name seted)
		// user might done abstraction ==> acces of the sdcard when possible ...
		FSNType_direct, //!< Access at the file System with a direct naming like "/home/plop/xxx.txt"
		FSNType_relatif, //!< Access at the file System with a relative naming like "../plop/xxx.txt"
		
		// depend on case
		//     - PC      : ~/
		//     - Android : /sdcard/
		//     - Apple   : ????
		FSNType_home, //!< acces at the home path of the system (with name of the current user)
		
		// depend of the case
		//     - PC      : /usr/shared/programName/
		//     - Android : Internal at the executable file (pointer on static area)
		//     - Apple   : Internal at the executable file
		FSNType_data, //!< Access on the application data (internal application data are the one provided with the binary)
		
		// depend on case
		//     - PC      : ~/.local/programName/
		//     - Android : /data/data/programName/files/
		//     - Apple   : ????
		FSNType_userData, //!< Access on the user application data (where the data are stored when the application stop)
		
		// depend on case
		//     - PC      : ~/.programName/cache/
		//     - Android : /data/data/programName/cache/
		//     - Apple   : ????
		FSNType_cache, //!< Access on the application temporary path (remove when user want and whe the compter restart or have not enought memory)
		
		// depend on case
		//     - try on USER_DATA:/theme/themeName/xxx
		//     - try on DATA:/theme/themeName/xxx
		//     and jump to the default theme file
		//     - try on USER_DATA:/theme/default/xxx
		//     - try on DATA:/theme/default/xxx
		FSNType_theme, //!< Theme area
		FSNType_themeData //!< Theme data area
	};
	//! @not_in_doc
	std::ostream& operator <<(std::ostream &_os, const enum etk::FSNType &_obj);
	
	/*
	note : The filename can be
		Direct mode:
			DIRECT:/sdfsdfsdf/
			/XX ==> for Linux / Mac / Android
			[a-zA-Z]:/xxx ==> for Windows
		
		Data mode:
			DATA:folder/File.ccc
			{libName}DATA:folder/File.ccc ==> try to read in appl data and in next in "libName" lib data folder
			{@libName}DATA:folder/File.ccc ==> try to read ONLY in "libName" lib data folder
		
		User data mode:
			USERDATA:folder/File.ccc
			{libName}USERDATA:folder/File.ccc
			{@libName}USERDATA:folder/File.ccc
		
		Cache Data:
			CACHE:folder/File.ccc
		
		Theme data:
			THEME:folder/file.xxx
			THEME:GUI:folder/file.xxx
			{libName}THEME:GUI:folder/file.xxx
			{@libName}THEME:GUI:folder/file.xxx
		
		Get the root folder:
			ROOT:
			/
			[a-zA-Z]: ==> create more risk ...
		
		Get the Home folder:
			HOME:
			~
		
		Get the relative folder:
			REL:
			./
	*/
	/**
	 * @brief FS node is for File System IO access (named classicly "node in linux EXT)
	 * This class is independent of the OS, If you acces to a file in windows, it might
	 * generate the right like Linux (it is important to know that windows right is lighter than linux)
	 */
	class FSNode {
		private:
			std::string m_libSearch; //!< the name Of the subLib that system must church subData
			std::string m_userFileName; //!< the name requested by the User
			std::string m_systemFileName; //!< the compleate filename for the system
			enum FSNType m_type; //!< the Type of data requested by the User
			enum typeNode m_typeNode; //!< type of the current file/Folder/Link
			etk::FSNodeRight m_rights; //!< IO right of the current file
			// specific when file Access :
			FILE * m_PointerFile; //!< When reading file, this is the Real pointer access
			uint64_t m_timeCreate; //!< Creating  date of the file
			uint64_t m_timeModify; //!< Last modify time of the file
			uint64_t m_timeAccess; //!< Last acces time of the file
			uint32_t m_idOwner; //!< Id of the owner of the Node
			uint32_t m_idGroup; //!< Id of the group of the Node
		public:
			/**
			 * @brief Constructor
			 * @param[in] _path Path of the curent file /folder ...
			 */
			FSNode(const std::string& _path = "~");
			#if __CPP_VERSION__ >= 2011
				FSNode(const std::u32string& _path);
			#endif
			/**
			 * @brief Destructor
			 * @note you will have some warning if you did not close your files
			 */
			~FSNode();
		private:
			/**
			 * @brief Internal methode that create the internal Real system name (transform DATA: HOME: DATA:GUI: in the real name of the files)
			 */
			void generateFileSystemPath();
			/**
			 * @brief Update the internal data of the right type, and times
			 */
			void updateFileSystemProperty();
			/**
			 * @brief Common set name of the Node (if the user decide to change the node selection
			 * @param[in] _newName Name of the Node
			 */
			void privateSetName(std::string _newName);
			#if __CPP_VERSION__ >= 2011
				void privateSetName(const std::u32string& _newName);
			#endif
		private:
			#ifdef HAVE_ZIP_DATA
				/**
				 * @brief Explocitly for Android that data are stored in the .apk that is a .zip not compressed
				 * @return true : Load is OK
				 * @return false : An error Occured
				 */
				bool loadDataZip();
				const etk::ArchiveContent* m_zipContent;
				int32_t m_zipReadingOffset;
			#endif
		public:
			/**
			 * @brief Check if the node exist.
			 * @return true : The node existed.
			 * @return false : The node does not exist.
			 */
			bool exist() const {
				return (m_typeNode!=etk::typeNode_unknow);
			};
			/**
			 * @brief Get the node type
			 * @return the requested type, typeNode_unknow if it does not existed
			 */
			enum typeNode getNodeType() const {
				return m_typeNode;
			};
			/**
			 * @brief Get the node Right
			 * @return the requested right
			 */
			etk::FSNodeRight getRight() const {
				return m_rights;
			};
			/**
			 * @brief Set the specific right of the node
			 * @param[in] _newRight new right to set
			 * @return true : action done
			 * @return false : action not done
			 */
			bool setRight(etk::FSNodeRight _newRight);
			/**
			 * @brief Change the Node seeing (not rename the node, for this @ref etk::FSNodeMove)
			 * @param[in] _newName New node name to show
			 * @return true action done
			 * @return false action not done
			 */
			void setName(const std::string& _newName);
			#if __CPP_VERSION__ >= 2011
				void setName(const std::u32string& _newName);
			#endif
			/**
			 * @brief Get the Generate FileSystem name
			 * @return the requested filename
			 */
			std::string getFileSystemName() const;
			#if __CPP_VERSION__ >= 2011
				std::u32string getUFileSystemName() const;
			#endif
			/**
			 * @brief Get the current folder of the Node. (file system name)
			 * @return the common name define (like /xxxxx/xxxxx/ or c:/xxxxx/xxxxx/)
			 * @note Auto remove of ../../../ and //
			 */
			std::string getNameFolder() const;
			#if __CPP_VERSION__ >= 2011
				std::u32string getUNameFolder() const;
			#endif
			/**
			 * @brief Get the current compleate node name (file system name)
			 * @return All the user name definition (like /xxxxx/xxxxx/myFile.kkk or c:/xxxxx/xxxxx/myFile.kkk)
			 * @note Auto remove of ../../../ and //
			 */
			std::string getName() const;
			#if __CPP_VERSION__ >= 2011
				std::u32string getUName() const;
			#endif
			/**
			 * @brief Get the file or current file name (if it was a file)
			 * @return the name of the node (like myFile.kkk)
			 */
			std::string getNameFile() const;
			#if __CPP_VERSION__ >= 2011
				std::u32string getUNameFile() const;
			#endif
			/**
			 * @brief Get the current folder of the Node.
			 * @return the common name define (like DATA:xxxxx/xxxxx/)
			 * @note Auto remove of ../../../ and //
			 */
			std::string getRelativeFolder() const;
			#if __CPP_VERSION__ >= 2011
				std::u32string getURelativeFolder() const;
			#endif
			/**
			 * @brief update the Time of the file with the current time
			 * @return true : action done
			 * @return false : action not done
			 */
			bool touch();
			/**
			 * @brief Move the Node at a new path
			 * @param[in] _path The new path
			 * @return true : action done
			 * @return false : action not done
			 */
			bool move(const std::string& _path);
			#if __CPP_VERSION__ >= 2011
				bool move(const std::u32string& _path);
			#endif
			/**
			 * @brief Get the node type (DATA/DIRECT...)
			 * @return the requested type
			 */
			enum FSNType getTypeAccess() const {
				return m_type;
			};
			/**
			 * @brief Remove the current node ( if folder, this remove all subfolder but not the Link subfolder)
			 * @return true : action done
			 * @return false : action not done
			 */
			bool remove();
			/**
			 * @brief Get the creating time of the File
			 * @return The time requested
			 */
			uint64_t timeCreated() const;
			/**
			 * @brief Get the creating time of the File
			 * @return The time requested (in string)
			 */
			std::string timeCreatedString() const;
			#if __CPP_VERSION__ >= 2011
				std::u32string timeUCreatedString() const;
			#endif
			/**
			 * @brief Get the modifying time of the File
			 * @return The time requested
			 */
			uint64_t timeModified() const;
			/**
			 * @brief Get the modifying time of the File
			 * @return The time requested (in string)
			 */
			std::string timeModifiedString() const;
			#if __CPP_VERSION__ >= 2011
				std::u32string timeUModifiedString() const;
			#endif
			/**
			 * @brief Get the Accessed time of the File
			 * @return The time requested
			 */
			uint64_t timeAccessed() const;
			/**
			 * @brief Get the Accessed time of the File
			 * @return The time requested (in string)
			 */
			std::string timeAccessedString() const;
			#if __CPP_VERSION__ >= 2011
				std::u32string timeUAccessedString() const;
			#endif
			/**
			 * @brief copy the other FSnode ==> for vector
			 * @param[in] _obj input node
			 * @return the current modify node
			 */
			const etk::FSNode& operator= (const etk::FSNode &_obj );
			/**
			 * @brief Check if the 2 node are link with the same file
			 * @param[in] _obj input node
			 * @return true : same node, false otherwise
			 */
			bool operator== (const etk::FSNode &_obj ) const;
			/**
			 * @brief Check if the 2 node are NOT link with the same file
			 * @param[in] _obj input node
			 * @return false : same node, true otherwise
			 */
			bool operator!= (const etk::FSNode &_obj ) const;
			/**
			 * @brief Write in the statard debug IO the current node
			 * @param[in] _os std debug IO
			 * @param[in] _obj Node to display
			 * @return std debug IO
			 */
			friend std::ostream& operator <<( std::ostream &_os,const etk::FSNode &_obj);
			
			/**
			 * @brief Count the number of subFolder in the curent Folder
			 * @return >=0 nb of subElement
			 * @return -1 an error occured ==> not a folder ???
			 */
			int64_t folderCount();
			/**
			 * @brief Get the List of all node inside a node (folder only)
			 * @param[in] _showHidenFile Add hidden file/folder/...
			 * @param[in] _getFolderAndOther get folder
			 * @param[in] _getFile Get files
			 * @param[in] _temporaryFile add Tmp file like .bck or ~
			 * @return The requested list
			 */
			std::vector<etk::FSNode*> folderGetSubList(bool _showHidenFile = true,
			                                           bool _getFolderAndOther = true,
			                                           bool _getFile = true,
			                                           bool _temporaryFile = true);
			/**
			 * @brief Get the List of all node inside a node (folder only)
			 * @param[in] _showHidenFile Add hidden file/folder/...
			 * @param[in] _getFolderAndOther get folder
			 * @param[in] _getFile Get files
			 * @param[in] _filter Generic regex string to filter file names
			 * @return The requested list
			 */
			std::vector<etk::FSNode*> folderGetSubList(bool _showHidenFile = true,
			                                           bool _getFolderAndOther = true,
			                                           bool _getFile = true,
			                                           const std::string& _filter = ".*");
			/**
			 * @brief Get the List of all node inside a node (folder only)
			 * @param[in] _getFolder get folder
			 * @param[in] _getFile Get files
			 * @param[in] _filter Generic regex string to filter file names
			 * @return The requested list
			 */
			std::vector<std::string> folderGetSub(bool _getFolder, bool _getFile, const std::string& _filter);
			/**
			 * @brief Get the father node of this node
			 * @return The requested node
			 */
			etk::FSNode folderGetParent();
			/**
			 * @brief Get all the File inside a Folder (done recursively)
			 * @param[out] _output List of all the File names (You must clear it before set it in)
			 * @param[in] _recursiveEnable Activate the recursive mode (enable by default)
			 */
			void folderGetRecursiveFiles(std::vector<std::string>& _output, bool _recursiveEnable=true);
			#if __CPP_VERSION__ >= 2011
				void folderGetRecursiveFiles(std::vector<std::u32string>& _output, bool _recursiveEnable=true);
			#endif
			/**
			 * @brief Check if the file have an extention ( ***.ccc)
			 * @return true The file have an extention.
			 * @return false The file have NO extention.
			 */
			bool fileHasExtention();
			/**
			 * @brief Get the extention of the Node
			 * @return the requested extention
			 */
			std::string fileGetExtention();
			#if __CPP_VERSION__ >= 2011
				std::u32string fileUGetExtention();
			#endif
			/**
			 * @brief Get the File size
			 * @return the requested size
			 */
			uint64_t fileSize();
			/**
			 * @brief Open the file in Read mode
			 * @return true : action done
			 * @return false : action not done
			 */
			bool fileOpenRead();
			/**
			 * @brief Open the file in write Mode
			 * @note You can not do it with the DATA: file ==> this is not allowed in some Board like Android)
			 * @return true : action done
			 * @return false : action not done
			 */
			bool fileOpenWrite();
			/**
			 * @brief Open the file in write Append Mode
			 * @note You can not do it with the DATA: file ==> this is not allowed in some Board like Android)
			 * @return true : action done
			 * @return false : action not done
			 */
			bool fileOpenAppend();
			/**
			 * @brief Check if the current file is Open
			 * @return true : File is open in write or in read
			 * @return false : File is NOT open in write or in read
			 */
			bool fileIsOpen();
			/**
			 * @brief Close the curent file
			 * @return true : action done
			 * @return false : action not done
			 */
			bool fileClose();
			/**
			 * @brief Get the pointer on the start line and the next line (or null)
			 * @param[in,out] _elementLine Pointer to an array of chars where the string read is copied.
			 * @param[in] _maxData Maximum number of characters to be copied into str (including the terminating null-character).
			 * @return the pointer on the end of the cuurent line.
			 */
			char* fileGets(char* _elementLine, int64_t _maxData);
			/**
			 * @brief Get a unique data in the file
			 * @return the next element in the file.
			 */
			char fileGet();
			/**
			 * @brief Get a compleate line in a text file
			 * @param[out] _output the next element in the file.
			 * @return true The file is not ended.
			 * @return false The file is ended.
			 */
			bool fileGets(std::string& _output);
			/**
			 * @brief Write data on the file
			 * @param[in] _input data to write.
			 * @return true Write done corectly.
			 * @return false ErrorOn write.
			 */
			bool filePut(char _input);
			/**
			 * @brief Write data on the file
			 * @param[in] _input data to write.
			 * @return true Write done corectly.
			 * @return false ErrorOn write.
			 */
			bool filePuts(const std::string& _input);
			/**
			 * @brief Read data from the file
			 * @param[in,out] _data Pointer on the buffer that might be set the data
			 * @param[in] _blockSize Size of one block of data
			 * @param[in] _nbBlock Number of block needed
			 * @return Number of element read (in block number)
			 */
			int64_t fileRead(void* _data, int64_t _blockSize, int64_t _nbBlock);
			/**
			 * @brief Write data on the file
			 * @param[in] _data Pointer on the buffer that might be set on the file
			 * @param[in] _blockSize Size of one block of data
			 * @param[in] _nbBlock Number of block needed
			 * @return Number of element written (in block number)
			 */
			int64_t fileWrite(const void* _data, int64_t _blockSize, int64_t _nbBlock);
			// TODO: etk::FSNode& operator<< (const std::ostream& _data);
			/**
			 * @brief Stream write mode
			 * @param[in] _data Stream to write
			 * @return The current FSNode reference to add other stream.
			 * @note not stable API ...
			 */
			etk::FSNode& operator<< (const std::stringstream& _data);
			//! @copydoc etk::FSNode::operator<<(const std::stringstream&)
			etk::FSNode& operator<< (const std::string& _data);
			//! @copydoc etk::FSNode::operator<<(const std::stringstream&)
			etk::FSNode& operator<< (const char* _data);
			//! @copydoc etk::FSNode::operator<<(const std::stringstream&)
			etk::FSNode& operator<< (const int32_t _data);
			//! @copydoc etk::FSNode::operator<<(const std::stringstream&)
			etk::FSNode& operator<< (const uint32_t _data);
			//! @copydoc etk::FSNode::operator<<(const std::stringstream&)
			etk::FSNode& operator<< (const float _data);
			/**
			 * @brief Get the position in the file.
			 * @return the requested position.
			 */
			int64_t fileTell();
			/**
			 * @brief Move in the file Position
			 * @param[in] _offset Offset to apply at the file
			 * @param[in] _origin Origin  of the position
			 * @return true : action done
			 * @return false : action not done
			 */
			bool fileSeek(long int _offset, enum etk::seekNode _origin);
			/**
			 * @brief Flush the current file
			 */
			void fileFlush();
			/**
			 * @brief Read all element in a file and set it in a generic vector
			 * @return the read vector
			 */
			template<typename T> std::vector<T> fileReadAll() {
				std::vector<T> value;
				value.resize(fileSize());
				fileRead(&value[0], sizeof(T), fileSize()/sizeof(T));
				return value;
			}
			/**
			 * @brief Read all element in a file and set it in a generic std::string
			 * @return the read string
			 */
			std::string fileReadAllString() {
				std::string value;
				value.resize(fileSize());
				fileRead(&value[0], sizeof(char), fileSize()/sizeof(char));
				return value;
			}
			#if __CPP_VERSION__ >= 2011
			std::u32string fileReadAllU32String() {
				return utf8::convertUnicode(fileReadAllString());
			}
			#endif
			/**
			 * @brief Write all the vector in a file
			 * @param[in] _value Data to write in the File
			 */
			template<typename T>
			void fileWriteAll(const std::vector<T>& _value) {
				fileWrite(static_cast<const void*>(&(_value[0])), sizeof(T), _value.size()/sizeof(T));
			}
			/**
			 * @brief Write all the vector in a file
			 * @param[in] _value String data to write in the File
			 */
			void fileWriteAll(const std::string& _value) {
				fileWrite(static_cast<const void*>(&(_value[0])), sizeof(char), _value.size()/sizeof(char));
			}
			#if __CPP_VERSION__ >= 2011
				void fileWriteAll(const std::u32string& _value) {
					fileWriteAll(u32char::convertToUtf8(_value));
				}
			#endif
		private:
			/**
			 * @brief Order the list of subnode the folder first and the alphabetical order
			 * @param[in,out] _list The list to order
			 */
			void sortElementList(std::vector<etk::FSNode *>& _list);
	};
	//! @not_in_doc
	std::ostream& operator <<(std::ostream &_os, const etk::FSNode &_obj);
	
	/**
	 * @brief Set manualy the folder of the Data.(like /usr/shared/applName/ for linux)
	 * @param[in] _folder folder path of the cathegorie
	 * @param[in] _applName Base name of the application
	 */
	void setBaseFolderData(const char* _folder, const char* _applName=nullptr);
	/**
	 * @brief Set the user data folder (like /home/machin/.local/applName/ for linux)
	 * @param[in] _folder folder path of the cathegorie
	 */
	void setBaseFolderDataUser(const char* _folder);
	/**
	 * @brief Set the Cach folder for the application (like /tmp)
	 * @param[in] _folder folder path of the cathegorie
	 */
	void setBaseFolderCache(const char* _folder);
	/**
	 * @brief Initialyse all the subFolder usable by the user like DATA/HOME/CACHE/USERDATA
	 * @param[in] _applName the name of the application
	 */
	void initDefaultFolder(const char* _applName);
	/**
	 * @brief Get the home folder of the user
	 * @return the home folder : like : "/home/machin/"
	 */
	std::string getUserHomeFolder();
	#if __CPP_VERSION__ >= 2011
		std::u32string getUUserHomeFolder();
	#endif
	/**
	 * @brief Get the folder of the Program is running
	 * @return the basic folder name (ex : run ./appl in the pwd=/home/machin/sousFolder ==> this return the pwd folder)
	 */
	std::string getUserRunFolder();
	#if __CPP_VERSION__ >= 2011
		std::u32string getUUserRunFolder();
	#endif
	
	namespace theme {
		// TODO : Add an INIT ...
		/**
		 * @brief Set the Folder of a subset of a theme ...
		 * @param[in] _refName Theme cathegorie ex : "GUI" "SHADER" "DEFAULT" 
		 * @param[in] _folderName The associated folder of the Theme (like "myTheme/folder/folder2/")
		 */
		void setName(const std::string& _refName, const std::string& _folderName);
		#if __CPP_VERSION__ >= 2011
			//! @previous
			void setName(const std::u32string& _refName, const std::u32string& _folderName);
		#endif
		/**
		 * @brief get the folder from a Reference theme
		 * @param[in] _refName Theme cathegorie ex : "GUI" "SHADER" "DEFAULT" 
		 * @return the path of the theme
		 */
		std::string getName(const std::string& _refName);
		#if __CPP_VERSION__ >= 2011
			//! @previous
			std::u32string getName(const std::u32string& _refName);
		#endif
		/**
		 * @brief Set the default folder of a subset of a theme ...
		 * @param[in] _refName Theme cathegorie ex : "GUI" "SHADER" "DEFAULT" 
		 * @param[in] _folderName The associated default folder of the Theme (like "myTheme/color/default/")
		 */
		void setNameDefault(const std::string& _refName, const std::string& _folderName);
		#if __CPP_VERSION__ >= 2011
			//! @previous
			void setNameDefault(const std::u32string& _refName, const std::u32string& _folderName);
		#endif
		/**
		 * @brief get the default folder from a Reference theme 
		 * @param[in] _refName Theme cathegorie ex : "GUI" "SHADER" "DEFAULT" 
		 * @return the path of the theme
		 */
		std::string getNameDefault(const std::string& _refName);
		#if __CPP_VERSION__ >= 2011
			//! @previous
			std::u32string getNameDefault(const std::u32string& _refName);
		#endif
		/**
		 * @brief Get the list of all the theme folder availlable in the user Home/appl
		 * @return The list of elements
		 */
		std::vector<std::string> list();
		#if __CPP_VERSION__ >= 2011
			//! @previous
			std::vector<std::u32string> listU();
		#endif
	};
	/**
	 * @brief Get the size of a specific file
	 * @param[in] _path Folder/File/Pipe path of the node
	 * @return size of the file
	 */
	uint64_t FSNodeGetSize(const std::string& _path);
	#if __CPP_VERSION__ >= 2011
		uint64_t FSNodeGetSize(const std::u32string& _path);
	#endif
	
	/**
	 * @brief Simple access for : Remove folder and subFolder, files pipes ...
	 * @param[in] _path Folder/File/Pipe path of the node
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	bool FSNodeRemove(const std::string& _path);
	#if __CPP_VERSION__ >= 2011
		bool FSNodeRemove(const std::u32string& _path);
	#endif
	/**
	 * @brief Simple access for : count the number of element in a path (if it is not a path ==> return -1)
	 * @param[in] _path Folder/File/Pipe path of the node
	 * @return number of File inside
	 * @return -1 : An error occured
	 */
	int64_t FSNodeGetCount(const std::string& _path);
	#if __CPP_VERSION__ >= 2011
		int64_t FSNodeGetCount(const std::u32string& _path);
	#endif
	/**
	 * @brief Simple access for : Create a file or a folder depending of the request
	 * @param[in] _path Folder/File/Pipe path of the node
	 * @param[in] _right Right of the creation
	 * @param[in] _type Type of the element that might be created
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	bool FSNodeCreate(const std::string& _path, etk::FSNodeRight _right, enum etk::typeNode _type=etk::typeNode_folder);
	#if __CPP_VERSION__ >= 2011
		bool FSNodeCreate(const std::u32string& _path, etk::FSNodeRight _right, enum etk::typeNode _type=etk::typeNode_folder);
	#endif
	/**
	 * @brief Simple access for : chexk the exestance of an element
	 * @param[in] _path Folder/File/Pipe path of the node
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	bool FSNodeExist(const std::string& _path);
	#if __CPP_VERSION__ >= 2011
		bool FSNodeExist(const std::u32string& _path);
	#endif
	/**
	 * @brief Simple access for : chexk the exestance of an element
	 * @param[in] _path1 Folder/File/Pipe path of the node sources
	 * @param[in] _path2 Folder/File/Pipe path of the node destination
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	bool FSNodeMove(const std::string& _path1, const std::string& _path2);
	#if __CPP_VERSION__ >= 2011
		bool FSNodeMove(const std::u32string& _path1, const std::u32string& _path2);
	#endif
	/**
	 * @brief Simple access for : Get right of the current Node
	 * @param[in] _path Folder/File/Pipe path of the node
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	etk::FSNodeRight FSNodeGetRight(const std::string& _path);
	#if __CPP_VERSION__ >= 2011
		etk::FSNodeRight FSNodeGetRight(const std::u32string& _path);
	#endif
	/**
	 * @brief Simple access for : Get type of the current node
	 * @param[in] _path Folder/File/Pipe path of the node
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	enum etk::typeNode FSNodeGetType(const std::string& _path);
	#if __CPP_VERSION__ >= 2011
		enum etk::typeNode FSNodeGetType(const std::u32string& _path);
	#endif
	/**
	 * @brief Simple access for : Getting creation time of the current node
	 * @param[in] _path Folder/File/Pipe path of the node
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	uint64_t FSNodeGetTimeCreated(const std::string& _path);
	#if __CPP_VERSION__ >= 2011
		uint64_t FSNodeGetTimeCreated(const std::u32string& _path);
	#endif
	/**
	 * @brief Simple access for : Getting Modification time of the current node
	 * @param[in] _path Folder/File/Pipe path of the node
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	uint64_t FSNodeGetTimeModified(const std::string& _path);
	#if __CPP_VERSION__ >= 2011
		uint64_t FSNodeGetTimeModified(const std::u32string& _path);
	#endif
	/**
	 * @brief Simple access for : Getting Accessing time of the current node
	 * @param[in] _path Folder/File/Pipe path of the node
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	uint64_t FSNodeGetTimeAccessed(const std::string& _path);
	#if __CPP_VERSION__ >= 2011
		uint64_t FSNodeGetTimeAccessed(const std::u32string& _path);
	#endif
	/**
	 * @brief Simple access for : Update Modification time with the current time of the node (>)
	 * @param[in] _path Folder/File/Pipe path of the node
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	bool FSNodeTouch(const std::string& _path);
	#if __CPP_VERSION__ >= 2011
		bool FSNodeTouch(const std::u32string& _path);
	#endif
	/**
	 * @brief Simple access for : Basic write on the node (like console echo)
	 * @param[in] _path Folder/File/Pipe path of the node
	 * @param[in] _dataTowrite write data in the Node
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	bool FSNodeEcho(const std::string& _path, const std::string& _dataTowrite);
	#if __CPP_VERSION__ >= 2011
		bool FSNodeEcho(const std::u32string& _path, const std::u32string& _dataTowrite);
	#endif
	/**
	 * @brief Simple access for : Basic write on the node (like console echo) in adding mode (>>)
	 * @param[in] _path Folder/File/Pipe path of the node
	 * @param[in] _dataTowrite write data in the Node
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	bool FSNodeEchoAdd(const std::string& _path, const std::string& _dataTowrite);
	#if __CPP_VERSION__ >= 2011
		bool FSNodeEchoAdd(const std::u32string& _path, const std::u32string& _dataTowrite);
	#endif
	/**
	 * @brief move file to generate an history of the current file
	 * @param[in] _path Folder/File/Pipe path of the node
	 * @param[in] _historyCount number of saved file in the history (-xxx)
	 */
	void FSNodeHistory(const std::string& _path, int32_t _historyCount);
	#if __CPP_VERSION__ >= 2011
		void FSNodeHistory(const std::u32string& _path, int32_t _historyCount);
	#endif
	/**
	 * @brief Read all the data from a file
	 * @param[in] _path Folder/File/Pipe path of the node
	 * @return all the data of the file in a string
	 */
	std::string FSNodeReadAllData(const std::string& _path);
	/**
	 * @brief Write all the data in a file
	 * @param[in] _path Folder/File/Pipe path of the node
	 * @param[in] _data All the data of the file in a string
	 */
	void FSNodeWriteAllData(const std::string& _path, const std::string& _data);
	/**
	 * @brief Read all the data from a file
	 * @param[in] _path Folder/File/Pipe path of the node
	 * @return all the data of the file in a typed vector
	 */
	template<typename TTT> std::vector<TTT> FSNodeReadAllDataType(const std::string& _path) {
		std::vector<TTT> out;
		etk::FSNode node(_path);
		if (node.fileOpenRead() == false) {
			//TK_ERROR("can not open file : '" << node << "'");
			return out;
		}
		uint64_t nbByte = node.fileSize();
		out.resize(nbByte/sizeof(TTT));
		if (out.size()*sizeof(TTT) != nbByte) {
			//TK_WARNING("Error in reading the file missing some byte at the end ...");
		}
		node.fileRead(&out[0], sizeof(TTT), nbByte/sizeof(TTT));
		node.fileClose();
		return out;
	}
	/**
	 * @brief Write all the data in a file
	 * @param[in] _path Folder/File/Pipe path of the node
	 * @param[in] _data All the data of the file in a vector Typed bits ...
	 */
	template<typename TTT> void FSNodeWriteAllDataType(const std::string& _path, const std::vector<TTT>& _data) {
		etk::FSNode node(_path);
		if (node.fileOpenWrite() == false) {
			//TK_ERROR("can not open file : '" << node << "'");
			return;
		}
		node.fileWrite(&_data[0], sizeof(TTT), _data.size());
		node.fileClose();
	}
	/**
	 * @brief get the system name of the current path
	 * @param[in] _path "DATA:xxx" etk file name.
	 * @return return real file name "/aaa/bbb/ccc/xxx"
	 */
	std::string FSNodeGetRealName(const std::string& _path);
	
	/**
	 * @brief Get all the Path contain in the specidy path:
	 * @param[in] _path Generic path to parse ...
	 * @return The list of path found
	 * @code
	 *     auto out = etk::FSNodeExplodeMultiplePath("{ewol}DATA:font");
	 *     // out contain: {"DATA:font", "{@ewol}DATA:font"}
	 * @endcode
	 * @code
	 *     auto out = etk::FSNodeExplodeMultiplePath("{@ewol}DATA:font");
	 *     // out contain: {"{@ewol}DATA:font"}
	 * @endcode
	 */
	std::vector<std::string> FSNodeExplodeMultiplePath(const std::string& _path);
};

