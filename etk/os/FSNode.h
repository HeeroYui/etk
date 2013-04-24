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

#define MAX_FILE_NAME      (10240)

//http://developer.android.com/guide/topics/data/data-storage.html

namespace etk
{
	void SetArgZero(const etk::UString& val);
	/**
	 * List of Type that a node can have (this wrap some type that not exist on Windows)
	 */
	typedef enum {
		FSN_UNKNOW, //!< Type of the node is not known
		FSN_BLOCK, //!< The node is a block aceess device (Not availlable on Windows)
		FSN_CHARACTER, //!< The node is a Char device type (Not availlable on Windows)
		FSN_FOLDER, //!< The node is a folder
		FSN_FIFO, //!< The node is a Fifo (Not availlable on Windows)
		FSN_LINK, //!< The node is a Link
		FSN_FILE, //!< The node is a File
		FSN_SOCKET, //!< The node is a socket
	} typeNode_te;
	
	etk::CCout& operator <<(etk::CCout &os, const etk::typeNode_te &obj);
	
	typedef enum {
		FSN_SEEK_START,
		FSN_SEEK_END,
		FSN_SEEK_CURRENT,
	} seekNode_te;
	
	typedef enum {
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
	} FSNType_te;
	
	etk::CCout& operator <<(etk::CCout &os, const etk::FSNType_te &obj);
	
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
			FSNType_te m_type; //!< the Type of data requested by the User
			typeNode_te m_typeNode; //!< type of the current file/Folder/Link
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
			 * @param[in] path Path of the curent file /folder ...
			 */
			FSNode(const etk::UString& path="~");
			/**
			 * @brief Destructor
			 * @note you will have some warning if you did not close your files
			 */
			~FSNode(void);
		private:
			/**
			 * @brief Internal methode that create the internal Real system name (transform DATA: HOME: DATA:GUI: in the real name of the files)
			 */
			void GenerateFileSystemPath(void);
			/**
			 * @brief Update the internal data of the right type, and times
			 */
			void UpdateFileSystemProperty(void);
			/**
			 * @brief Get the Generate FileSystem name
			 * @return the requested filename
			 */
			etk::UString GetFileSystemName(void) const;
			/**
			 * @brief Common set name of the Node (if the user decide to change the node selection
			 * @param[in] newName Name of the Node
			 */
			void PrivateSetName(const etk::UString& newName);
		private:
			#ifdef __TARGET_OS__Android
				/**
				 * @brief Explocitly for Android that data are stored in the .apk that is a .zip not compressed
				 * @return true : Load is OK
				 * @return false : An error Occured
				 */
				bool LoadDataZip(void);
				int32_t m_idZipFile;
				char* m_zipData;
				int32_t m_zipDataSize;
				int32_t m_zipReadingOffset;
			#endif
		public:
			/**
			 * @brief Check if the node exist.
			 * @return true : The node existed.
			 * @return false : The node does not exist.
			 */
			bool Exist(void) const { return (m_typeNode!=etk::FSN_UNKNOW); };
			/**
			 * @brief Get the node type
			 * @return the requested type, FSN_UNKNOW if it does not existed
			 */
			typeNode_te GetNodeType(void) const { return m_typeNode; };
			/**
			 * @brief Get the node Right
			 * @return the requested right
			 */
			etk::FSNodeRight GetRight(void) const { return m_rights; };
			/**
			 * @brief Set the specific right of the node
			 * @param[in] newRight new right to set
			 * @return true : action done
			 * @return false : action not done
			 */
			bool SetRight(etk::FSNodeRight newRight);
			/**
			 * @brief Change the Node seeing (not rename the node, for this @ref Move)
			 * @param[in] newName New node name to show
			 * @return true : action done
			 * @return false : action not done
			 */
			void SetName(const etk::UString& newName);
			/**
			 * @brief Get the current folder of the Node. (file system name)
			 * @return the common name define (like /xxxxx/xxxxx/ or c:/xxxxx/xxxxx/)
			 * @note Auto remove of ../../../ and //
			 */
			etk::UString GetNameFolder(void) const;
			/**
			 * @brief Get the current compleate node name (file system name)
			 * @return All the user name definition (like /xxxxx/xxxxx/myFile.kkk or c:/xxxxx/xxxxx/myFile.kkk)
			 * @note Auto remove of ../../../ and //
			 */
			etk::UString GetName(void) const;
			/**
			 * @brief Get the file or current folder name (if it was a folder)
			 * @return the name of the node (like myFile.kkk)
			 */
			etk::UString GetNameFile(void) const;
			/**
			 * @brief Get the current folder of the Node.
			 * @return the common name define (like DATA:xxxxx/xxxxx/)
			 * @note Auto remove of ../../../ and //
			 */
			etk::UString GetRelativeFolder(void) const;
			/**
			 * @brief update the Time of the file with the current time
			 * @return true : action done
			 * @return false : action not done
			 */
			bool Touch(void);
			/**
			 * @brief Move the Node at a new path
			 * @param[in] path The new path
			 * @return true : action done
			 * @return false : action not done
			 */
			bool Move(const etk::UString& path);
			/**
			 * @brief Get the node type (DATA/DIRECT...)
			 * @return the requested type
			 */
			FSNType_te GetTypeAccess(void) const { return m_type; };
			/**
			 * @brief Remove the current node ( if folder, this remove all subfolder but not the Link subfolder)
			 * @return true : action done
			 * @return false : action not done
			 */
			bool Remove(void);
			/**
			 * @brief Get the creating time of the File
			 * @return The time requested
			 */
			uint64_t TimeCreated(void) const;
			/**
			 * @brief Get the creating time of the File
			 * @return The time requested (in string)
			 */
			etk::UString TimeCreatedString(void) const;
			/**
			 * @brief Get the modifying time of the File
			 * @return The time requested
			 */
			uint64_t TimeModified(void) const;
			/**
			 * @brief Get the modifying time of the File
			 * @return The time requested (in string)
			 */
			etk::UString TimeModifiedString(void) const;
			/**
			 * @brief Get the Accessed time of the File
			 * @return The time requested
			 */
			uint64_t TimeAccessed(void) const;
			/**
			 * @brief Get the Accessed time of the File
			 * @return The time requested (in string)
			 */
			etk::UString TimeAccessedString(void) const;
			/**
			 * @brief copy the other FSnode ==> for vector
			 * @param[in] obj input node
			 * @return the current modify node
			 */
			const etk::FSNode& operator=  (const etk::FSNode &obj );
			/**
			 * @brief Check if the 2 node are link with the same file
			 * @param[in] obj input node
			 * @return true : same node, false otherwise
			 */
			bool operator== (const etk::FSNode &obj ) const;
			/**
			 * @brief Check if the 2 node are NOT link with the same file
			 * @param[in] obj input node
			 * @return false : same node, true otherwise
			 */
			bool operator!= (const etk::FSNode &obj ) const;
			/**
			 * @brief Write in the statard debug IO the current node
			 * @param[in] os std debug IO
			 * @param[in] obj Node to display
			 * @return std debug IO
			 */
			friend etk::CCout& operator <<( etk::CCout &os,const etk::FSNode &obj);
			
			/**
			 * @brief Count the number of subFolder in the curent Folder
			 * @return >=0 nb of subElement
			 * @return -1 an error occured ==> not a folder ???
			 */
			int64_t FolderCount(void);
			/**
			 * @brief Get the List of all node inside a node (folder only)
			 * @param[in] showHidenFile Add hidden file/folder/...
			 * @param[in] getFolderAndOther get folder
			 * @param[in] getFile Get files
			 * @param[in] temporaryFile add Tmp file like .bck or ~
			 * @return The requested list
			 */
			etk::Vector<etk::FSNode *> FolderGetSubList(bool showHidenFile=true,
			                                            bool getFolderAndOther=true,
			                                            bool getFile=true,
			                                            bool temporaryFile=true);
			/**
			 * @brief Get the father node of this node
			 * @return The requested node
			 */
			etk::FSNode FolderGetParent(void);
			/**
			 * @brief Get all the File inside a Folder (done recursively)
			 * @param[out] output List of all the File names (You must clear it before set it in)
			 */
			void FolderGetRecursiveFiles(etk::Vector<etk::UString>& output);
			/**
			 * @brief Check if the file have an extention ( ***.ccc)
			 * @return true The file have an extention.
			 * @return false The file have NO extention.
			 */
			bool FileHasExtention(void);
			/**
			 * @brief Get the extention of the Node
			 * @return the requested extention
			 */
			etk::UString FileGetExtention(void);
			/**
			 * @brief Get the File size
			 * @return the requested size
			 */
			uint64_t FileSize(void);
			/**
			 * @brief Open the file in Read mode
			 * @return true : action done
			 * @return false : action not done
			 */
			bool FileOpenRead(void);
			/**
			 * @brief Open the file in write Mode
			 * @note You can not do it with the DATA: file ==> this is not allowed in some Board like Android)
			 * @return true : action done
			 * @return false : action not done
			 */
			bool FileOpenWrite(void);
			/**
			 * @brief Open the file in write Append Mode
			 * @note You can not do it with the DATA: file ==> this is not allowed in some Board like Android)
			 * @return true : action done
			 * @return false : action not done
			 */
			bool FileOpenAppend(void);
			/**
			 * @brief Close the cuurent file
			 * @return true : action done
			 * @return false : action not done
			 */
			bool FileClose(void);
			/**
			 * @brief Get the pointer on the start line and the next line (or null)
			 * @param[in,out] elementLine Pointer to an array of chars where the string read is copied.
			 * @param[in] maxData Maximum number of characters to be copied into str (including the terminating null-character).
			 * @return the pointer on the end of the cuurent line.
			 */
			char* FileGets(char * elementLine, int64_t maxData);
			/**
			 * @brief Read data from the file
			 * @param[in,out] data Pointer on the buffer that might be set the data
			 * @param[in] blockSize Size of one block of data
			 * @param[in] nbBlock Number of block needed
			 * @return Number of element read (in block number)
			 */
			int64_t FileRead(void * data, int64_t blockSize, int64_t nbBlock);
			/**
			 * @brief Write data on the file
			 * @param[in] data Pointer on the buffer that might be set on the file
			 * @param[in] blockSize Size of one block of data
			 * @param[in] nbBlock Number of block needed
			 * @return Number of element written (in block number)
			 */
			int64_t FileWrite(void * data, int64_t blockSize, int64_t nbBlock);
			/**
			 * @brief Move in the file Position
			 * @param[in] offset Offset to apply at the file
			 * @param[in] origin Origin  of the position
			 * @return true : action done
			 * @return false : action not done
			 */
			bool FileSeek(long int offset, etk::seekNode_te origin);
			/**
			 * @brief Flush the current file
			 */
			void FileFlush(void);
		private:
			/**
			 * @brief Order the list of subnode the folder first and the alphabetical order
			 * @param[in,out] list The list to order
			 */
			void SortElementList(etk::Vector<etk::FSNode *> &list);
	};
	
	etk::CCout& operator <<(etk::CCout &os, const etk::FSNode &obj);
	
	/**
	 * @brief Set manualy the folder of the Data.(like /usr/shared/applName/ for linux)
	 * @param[in] folder folder path of the cathegorie
	 */
	void SetBaseFolderData(const char * folder);
	/**
	 * @brief Set the user data folder (like /home/machin/.local/applName/ for linux)
	 * @param[in] folder folder path of the cathegorie
	 */
	void SetBaseFolderDataUser(const char * folder);
	/**
	 * @brief Set the Cach folder for the application (like /tmp)
	 * @param[in] folder folder path of the cathegorie
	 */
	void SetBaseFolderCache(const char * folder);
	/**
	 * @brief Initialyse all the subFolder usable by the user like DATA/HOME/CACHE/USERDATA
	 * @param[in] applName the name of the application
	 */
	void InitDefaultFolder(const char * applName);
	/**
	 * @brief Get the home folder of the user
	 * @return the home folder : like : "/home/machin/"
	 */
	etk::UString GetUserHomeFolder(void);
	/**
	 * @brief Get the folder of the Program is running
	 * @return the basic folder name (ex : run ./appl in the pwd=/home/machin/sousFolder ==> this return the pwd folder)
	 */
	etk::UString GetUserRunFolder(void);
	
	namespace theme
	{
		// TODO : Add an INIT ...
		/**
		 * @brief Set the Folder of a subset of a theme ...
		 * @param[in] refName Theme cathegorie ex : "GUI" "SHADER" "DEFAULT" 
		 * @param[in] folderName The associated folder of the Theme (like "myTheme/folder/folder2/")
		 */
		void SetName(etk::UString refName, etk::UString folderName);
		/**
		 * @brief get the folder from a Reference theme
		 * @param[in] refName Theme cathegorie ex : "GUI" "SHADER" "DEFAULT" 
		 * @return the path of the theme
		 */
		etk::UString GetName(etk::UString refName);
		/**
		 * @brief Get the list of all the theme folder availlable in the user Home/appl
		 * @return The list of elements
		 */
		etk::Vector<etk::UString> List(void);
	};
	
	/**
	 * @brief Simple access for : Remove folder and subFolder, files pipes ...
	 * @param[in] path Folder/File/Pipe path of the node
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	bool FSNodeRemove(const etk::UString& path);
	/**
	 * @brief Simple access for : count the number of element in a path (if it is not a path ==> return -1)
	 * @param[in] path Folder/File/Pipe path of the node
	 * @return number of File inside
	 * @return -1 : An error occured
	 */
	int64_t FSNodeGetCount(const etk::UString& path);
	/**
	 * @brief Simple access for : Create a file or a folder depending of the request
	 * @param[in] path Folder/File/Pipe path of the node
	 * @param[in] right Right of the creation
	 * @param[in] type Type of the element that might be created
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	bool FSNodeCreate(const etk::UString& path, etk::FSNodeRight right, etk::typeNode_te type=etk::FSN_FOLDER);
	/**
	 * @brief Simple access for : chexk the exestance of an element
	 * @param[in] path Folder/File/Pipe path of the node
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	bool FSNodeExist(const etk::UString& path);
	/**
	 * @brief Simple access for : chexk the exestance of an element
	 * @param[in] path Folder/File/Pipe path of the node sources
	 * @param[in] path Folder/File/Pipe path of the node destination
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	bool FSNodeMove(const etk::UString& path1, const etk::UString& path2);
	/**
	 * @brief Simple access for : Get right of the current Node
	 * @param[in] path Folder/File/Pipe path of the node
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	etk::FSNodeRight FSNodeGetRight(const etk::UString& path);
	/**
	 * @brief Simple access for : Get type of the current node
	 * @param[in] path Folder/File/Pipe path of the node
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	etk::typeNode_te FSNodeGetType(const etk::UString& path);
	/**
	 * @brief Simple access for : Getting creation time of the current node
	 * @param[in] path Folder/File/Pipe path of the node
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	uint64_t FSNodeGetTimeCreated(const etk::UString& path);
	/**
	 * @brief Simple access for : Getting Modification time of the current node
	 * @param[in] path Folder/File/Pipe path of the node
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	uint64_t FSNodeGetTimeModified(const etk::UString& path);
	/**
	 * @brief Simple access for : Getting Accessing time of the current node
	 * @param[in] path Folder/File/Pipe path of the node
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	uint64_t FSNodeGetTimeAccessed(const etk::UString& path);
	/**
	 * @brief Simple access for : Update Modification time with the current time of the node (>)
	 * @param[in] path Folder/File/Pipe path of the node
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	bool FSNodeTouch(const etk::UString& path);
	/**
	 * @brief Simple access for : Basic write on the node (like console echo)
	 * @param[in] path Folder/File/Pipe path of the node
	 * @param[in] dataTowrite write data in the Node
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	bool FSNodeEcho(const etk::UString& path, const etk::UString& dataTowrite);
	/**
	 * @brief Simple access for : Basic write on the node (like console echo) in adding mode (>>)
	 * @param[in] path Folder/File/Pipe path of the node
	 * @param[in] dataTowrite write data in the Node
	 * @return true : Action done corectly
	 * @return false : An error occured
	 */
	bool FSNodeEchoAdd(const etk::UString& path, const etk::UString& dataTowrite);
};

#endif

