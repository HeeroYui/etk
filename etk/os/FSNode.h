/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_FILE_SYSTEM_NODE_H__
#define __ETK_FILE_SYSTEM_NODE_H__

#include <etk/UString.h>
#include <etk/os/FSNodeRight.h>

#ifdef __TARGET_OS__Android
#	include <etk/archive/Archive.h>
#endif

#define MAX_FILE_NAME      (10240)

//http://developer.android.com/guide/topics/data/data-storage.html

namespace etk
{
	void setArgZero(const etk::UString& _val);
	/**
	 * List of Type that a node can have (this wrap some type that not exist on Windows)
	 */
	enum typeNode {
		FSN_UNKNOW, //!< Type of the node is not known
		FSN_BLOCK, //!< The node is a block aceess device (Not availlable on Windows)
		FSN_CHARACTER, //!< The node is a Char device type (Not availlable on Windows)
		FSN_FOLDER, //!< The node is a folder
		FSN_FIFO, //!< The node is a Fifo (Not availlable on Windows)
		FSN_LINK, //!< The node is a Link
		FSN_FILE, //!< The node is a File
		FSN_SOCKET, //!< The node is a socket
	};
	
	etk::CCout& operator <<(etk::CCout &_os, const enum etk::typeNode &_obj);
	
	enum seekNode{
		FSN_SEEK_START,
		FSN_SEEK_END,
		FSN_SEEK_CURRENT,
	};
	
	enum FSNType {
		FSN_TYPE_UNKNOW,
		// user might done abstraction ==> acces of the sdcard when possible ...
		FSN_TYPE_DIRECT,
		FSN_TYPE_RELATIF,
		
		// depend on case
		//     - PC      : ~/
		//     - Android : /sdcard/
		//     - Apple   : ????
		FSN_TYPE_HOME,
		
		// depend of the case
		//     - PC      : /usr/shared/programName/
		//     - Android : Internal at the executable file (pointer on static area)
		//     - Apple   : Internal at the executable file
		FSN_TYPE_DATA,
		
		// depend on case
		//     - PC      : ~/.local/programName/
		//     - Android : /data/data/programName/files/
		//     - Apple   : ????
		FSN_TYPE_USER_DATA,
		
		// depend on case
		//     - PC      : ~/.programName/cache/
		//     - Android : /data/data/programName/cache/
		//     - Apple   : ????
		FSN_TYPE_CACHE,
		
		// depend on case
		//     - try on FSN_TYPE_USER_DATA/theme/themeName/xxx
		//     - try on FSN_TYPE_DATA/theme/themeName/xxx
		//     - try on FSN_TYPE_EWOL_DATA/theme/themeName/xxx ==> later when the lib will be accessible in packages
		//     and jump to the default theme file
		//     - try on FSN_TYPE_USER_DATA/theme/default/xxx
		//     - try on FSN_TYPE_DATA/theme/default/xxx
		//     - try on FSN_TYPE_EWOL_DATA/theme/default/xxx ==> later when the lib will be accessible in packages
		FSN_TYPE_THEME,
		FSN_TYPE_THEME_DATA
	};
	
	etk::CCout& operator <<(etk::CCout &_os, const enum etk::FSNType &_obj);
	
	/*
	note : The filename can be
		Direct mode :
			DIRECT:/sdfsdfsdf/
			/XX ==> for Linux / Mac / Android
			[a-zA-Z]:/xxx ==> for Windows
		
		Data mode :
			DATA:folder/File.ccc
		
		User data mode :
			USERDATA:folder/File.ccc
		
		Cache Data :
			CACHE:folder/File.ccc
		
		Theme data :
			THEME:folder/file.xxx
		
		Get the root folder :
			ROOT:
			/
			[a-zA-Z]: ==> create more risk ...
		
		Get the Home folder :
			HOME:
			~
	*/
	/**
	 * @brief FS node is for File system IO access This class is independent of the OS, If you acces to a file in windows, it might generate the right loke Linux (it is important to know that windows right is lighter than linux)
	 */
	class FSNode
	{
		private:
			etk::UString m_userFileName; //!< the name requested by the User
			etk::UString m_systemFileName; //!< the compleate filename for the system
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
			FSNode(const etk::UString& _path="~");
			/**
			 * @brief Destructor
			 * @note you will have some warning if you did not close your files
			 */
			~FSNode(void);
		private:
			/**
			 * @brief Internal methode that create the internal Real system name (transform DATA: HOME: DATA:GUI: in the real name of the files)
			 */
			void generateFileSystemPath(void);
			/**
			 * @brief Update the internal data of the right type, and times
			 */
			void updateFileSystemProperty(void);
			/**
			 * @brief Common set name of the Node (if the user decide to change the node selection
			 * @param[in] _newName Name of the Node
			 */
			void privateSetName(const etk::UString& _newName);
		private:
			#ifdef __TARGET_OS__Android
				/**
				 * @brief Explocitly for Android that data are stored in the .apk that is a .zip not compressed
				 * @return true : Load is OK
				 * @return false : An error Occured
				 */
				bool loadDataZip(void);
				const etk::Archive::Content* m_zipContent;
				int32_t m_zipReadingOffset;
			#endif
		public:
			/**
			 * @brief Check if the node exist.
			 * @return true : The node existed.
			 * @return false : The node does not exist.
			 */
			bool exist(void) const { return (m_typeNode!=etk::FSN_UNKNOW); };
			/**
			 * @brief Get the node type
			 * @return the requested type, FSN_UNKNOW if it does not existed
			 */
			enum typeNode getNodeType(void) const { return m_typeNode; };
			/**
			 * @brief Get the node Right
			 * @return the requested right
			 */
			etk::FSNodeRight getRight(void) const { return m_rights; };
			/**
			 * @brief Set the specific right of the node
			 * @param[in] _newRight new right to set
			 * @return true : action done
			 * @return false : action not done
			 */
			bool setRight(etk::FSNodeRight _newRight);
			/**
			 * @brief Change the Node seeing (not rename the node, for this @ref Move)
			 * @param[in] _newName New node name to show
			 * @return true : action done
			 * @return false : action not done
			 */
			void setName(const etk::UString& _newName);
			/**
			 * @brief Get the Generate FileSystem name
			 * @return the requested filename
			 */
			etk::UString getFileSystemName(void) const;
			/**
			 * @brief Get the current folder of the Node. (file system name)
			 * @return the common name define (like /xxxxx/xxxxx/ or c:/xxxxx/xxxxx/)
			 * @note Auto remove of ../../../ and //
			 */
			etk::UString getNameFolder(void) const;
			/**
			 * @brief Get the current compleate node name (file system name)
			 * @return All the user name definition (like /xxxxx/xxxxx/myFile.kkk or c:/xxxxx/xxxxx/myFile.kkk)
			 * @note Auto remove of ../../../ and //
			 */
			etk::UString getName(void) const;
			/**
			 * @brief Get the file or current folder name (if it was a folder)
			 * @return the name of the node (like myFile.kkk)
			 */
			etk::UString getNameFile(void) const;
			/**
			 * @brief Get the current folder of the Node.
			 * @return the common name define (like DATA:xxxxx/xxxxx/)
			 * @note Auto remove of ../../../ and //
			 */
			etk::UString getRelativeFolder(void) const;
			/**
			 * @brief update the Time of the file with the current time
			 * @return true : action done
			 * @return false : action not done
			 */
			bool touch(void);
			/**
			 * @brief Move the Node at a new path
			 * @param[in] _path The new path
			 * @return true : action done
			 * @return false : action not done
			 */
			bool move(const etk::UString& _path);
			/**
			 * @brief Get the node type (DATA/DIRECT...)
			 * @return the requested type
			 */
			enum FSNType getTypeAccess(void) const { return m_type; };
			/**
			 * @brief Remove the current node ( if folder, this remove all subfolder but not the Link subfolder)
			 * @return true : action done
			 * @return false : action not done
			 */
			bool remove(void);
			/**
			 * @brief Get the creating time of the File
			 * @return The time requested
			 */
			uint64_t timeCreated(void) const;
			/**
			 * @brief Get the creating time of the File
			 * @return The time requested (in string)
			 */
			etk::UString timeCreatedString(void) const;
			/**
			 * @brief Get the modifying time of the File
			 * @return The time requested
			 */
			uint64_t timeModified(void) const;
			/**
			 * @brief Get the modifying time of the File
			 * @return The time requested (in string)
			 */
			etk::UString timeModifiedString(void) const;
			/**
			 * @brief Get the Accessed time of the File
			 * @return The time requested
			 */
			uint64_t timeAccessed(void) const;
			/**
			 * @brief Get the Accessed time of the File
			 * @return The time requested (in string)
			 */
			etk::UString timeAccessedString(void) const;
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
			friend etk::CCout& operator <<( etk::CCout &_os,const etk::FSNode &_obj);
			
			/**
			 * @brief Count the number of subFolder in the curent Folder
			 * @return >=0 nb of subElement
			 * @return -1 an error occured ==> not a folder ???
			 */
			int64_t folderCount(void);
			/**
			 * @brief Get the List of all node inside a node (folder only)
			 * @param[in] _showHidenFile Add hidden file/folder/...
			 * @param[in] _getFolderAndOther get folder
			 * @param[in] _getFile Get files
			 * @param[in] _temporaryFile add Tmp file like .bck or ~
			 * @return The requested list
			 */
			etk::Vector<etk::FSNode*> folderGetSubList(bool _showHidenFile=true,
			                                           bool _getFolderAndOther=true,
			                                           bool _getFile=true,
			                                           bool _temporaryFile=true);
			/**
			 * @brief Get the father node of this node
			 * @return The requested node
			 */
			etk::FSNode folderGetParent(void);
			/**
			 * @brief Get all the File inside a Folder (done recursively)
			 * @param[out] _output List of all the File names (You must clear it before set it in)
			 * @param[in] _recursiveEnable Activate the recursive mode (enable by default)
			 */
			void folderGetRecursiveFiles(etk::Vector<etk::UString>& _output, bool _recursiveEnable=true);
			/**
			 * @brief Check if the file have an extention ( ***.ccc)
			 * @return true The file have an extention.
			 * @return false The file have NO extention.
			 */
			bool fileHasExtention(void);
			/**
			 * @brief Get the extention of the Node
			 * @return the requested extention
			 */
			etk::UString fileGetExtention(void);
			/**
			 * @brief Get the File size
			 * @return the requested size
			 */
			uint64_t fileSize(void);
			/**
			 * @brief Open the file in Read mode
			 * @return true : action done
			 * @return false : action not done
			 */
			bool fileOpenRead(void);
			/**
			 * @brief Open the file in write Mode
			 * @note You can not do it with the DATA: file ==> this is not allowed in some Board like Android)
			 * @return true : action done
			 * @return false : action not done
			 */
			bool fileOpenWrite(void);
			/**
			 * @brief Open the file in write Append Mode
			 * @note You can not do it with the DATA: file ==> this is not allowed in some Board like Android)
			 * @return true : action done
			 * @return false : action not done
			 */
			bool fileOpenAppend(void);
			/**
			 * @brief Close the cuurent file
			 * @return true : action done
			 * @return false : action not done
			 */
			bool fileClose(void);
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
			char fileGet(void);
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
			int64_t fileWrite(void* _data, int64_t _blockSize, int64_t _nbBlock);
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
			void fileFlush(void);
		private:
			/**
			 * @brief Order the list of subnode the folder first and the alphabetical order
			 * @param[in,out] _list The list to order
			 */
			void sortElementList(etk::Vector<etk::FSNode *>& _list);
	};
	
	etk::CCout& operator <<(etk::CCout &_os, const etk::FSNode &_obj);
	
	/**
	 * @brief Set manualy the folder of the Data.(like /usr/shared/applName/ for linux)
	 * @param[in] _folder folder path of the cathegorie
	 */
	void setBaseFolderData(const char* _folder);
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
	etk::UString getUserHomeFolder(void);
	/**
	 * @brief Get the folder of the Program is running
	 * @return the basic folder name (ex : run ./appl in the pwd=/home/machin/sousFolder ==> this return the pwd folder)
	 */
	etk::UString getUserRunFolder(void);
	
	namespace theme
	{
		// TODO : Add an INIT ...
		/**
		 * @brief Set the Folder of a subset of a theme ...
		 * @param[in] _refName Theme cathegorie ex : "GUI" "SHADER" "DEFAULT" 
		 * @param[in] _folderName The associated folder of the Theme (like "myTheme/folder/folder2/")
		 */
		void setName(etk::UString _refName, etk::UString _folderName);
		/**
		 * @brief get the folder from a Reference theme
		 * @param[in] _refName Theme cathegorie ex : "GUI" "SHADER" "DEFAULT" 
		 * @return the path of the theme
		 */
		etk::UString getName(etk::UString _refName);
		/**
		 * @brief Get the list of all the theme folder availlable in the user Home/appl
		 * @return The list of elements
		 */
		etk::Vector<etk::UString> list(void);
	};
	
	/**
	 * @brief Simple access for : Remove folder and subFolder, files pipes ...
	 * @param[in] _path Folder/File/Pipe path of the node
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	bool FSNodeRemove(const etk::UString& _path);
	/**
	 * @brief Simple access for : count the number of element in a path (if it is not a path ==> return -1)
	 * @param[in] _path Folder/File/Pipe path of the node
	 * @return number of File inside
	 * @return -1 : An error occured
	 */
	int64_t FSNodeGetCount(const etk::UString& _path);
	/**
	 * @brief Simple access for : Create a file or a folder depending of the request
	 * @param[in] _path Folder/File/Pipe path of the node
	 * @param[in] _right Right of the creation
	 * @param[in] _type Type of the element that might be created
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	bool FSNodeCreate(const etk::UString& _path, etk::FSNodeRight _right, enum etk::typeNode _type=etk::FSN_FOLDER);
	/**
	 * @brief Simple access for : chexk the exestance of an element
	 * @param[in] _path Folder/File/Pipe path of the node
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	bool FSNodeExist(const etk::UString& _path);
	/**
	 * @brief Simple access for : chexk the exestance of an element
	 * @param[in] _path1 Folder/File/Pipe path of the node sources
	 * @param[in] _path2 Folder/File/Pipe path of the node destination
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	bool FSNodeMove(const etk::UString& _path1, const etk::UString& _path2);
	/**
	 * @brief Simple access for : Get right of the current Node
	 * @param[in] _path Folder/File/Pipe path of the node
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	etk::FSNodeRight FSNodeGetRight(const etk::UString& _path);
	/**
	 * @brief Simple access for : Get type of the current node
	 * @param[in] _path Folder/File/Pipe path of the node
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	enum etk::typeNode FSNodeGetType(const etk::UString& _path);
	/**
	 * @brief Simple access for : Getting creation time of the current node
	 * @param[in] _path Folder/File/Pipe path of the node
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	uint64_t FSNodeGetTimeCreated(const etk::UString& _path);
	/**
	 * @brief Simple access for : Getting Modification time of the current node
	 * @param[in] _path Folder/File/Pipe path of the node
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	uint64_t FSNodeGetTimeModified(const etk::UString& _path);
	/**
	 * @brief Simple access for : Getting Accessing time of the current node
	 * @param[in] _path Folder/File/Pipe path of the node
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	uint64_t FSNodeGetTimeAccessed(const etk::UString& _path);
	/**
	 * @brief Simple access for : Update Modification time with the current time of the node (>)
	 * @param[in] _path Folder/File/Pipe path of the node
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	bool FSNodeTouch(const etk::UString& _path);
	/**
	 * @brief Simple access for : Basic write on the node (like console echo)
	 * @param[in] _path Folder/File/Pipe path of the node
	 * @param[in] _dataTowrite write data in the Node
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	bool FSNodeEcho(const etk::UString& _path, const etk::UString& _dataTowrite);
	/**
	 * @brief Simple access for : Basic write on the node (like console echo) in adding mode (>>)
	 * @param[in] _path Folder/File/Pipe path of the node
	 * @param[in] _dataTowrite write data in the Node
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	bool FSNodeEchoAdd(const etk::UString& _path, const etk::UString& _dataTowrite);
	/**
	 * @brief move file to generate an history of the current file
	 * @param[in] _path Folder/File/Pipe path of the node
	 * @param[in] _historyCount number of saved file in the history (-xxx)
	 */
	void FSNodeHistory(const etk::UString& _path, int32_t _historyCount);
};

#endif

