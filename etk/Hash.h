/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/types.h>

#ifndef __ETK_HACH_H__
#define __ETK_HACH_H__

#undef __class__
#define __class__ "etk::Hash"


namespace etk {
	/**
	 * @brief internel data of the [class[etk::hash]] class, it contain
	 * the name and the value of the hash vector.
	 * @not-in-doc
	 */
	template<class MY_TYPE> class HashData {
		public:
			std::string m_key; //!< name of the current hash
			MY_TYPE m_value; //!< data of the current Hash
			/**
			 * @brief Constructor of the data for hash table.
			 * @param[in] _key name of the hash table.
			 * @param[in] _val Value of the hash element.
			 */
			HashData(const std::string& _key, const MY_TYPE& _val) :
			  m_key(_key),
			  m_value(_val) {
				// nothing to do ...
			}
	};
	/**
	 * @brief Hash table tamplate is a simple classical hash interface.
	 * A hash table is a equivalent of the dictionary in python, this is a
	 * simple interfaace between a name and a value:
	 * :** "name" : 19
	 * :** "name 2" : 99
	 * 
	 * [note]The name is unique and the value is what you want.[/note]
	 * 
	 * A simple example of use:
	 * [code style=c++]
	 * // Create a integer hash table
	 * Hash<int> myValue;
	 * // add some element (note add and set is the same function)
	 * myValue.add("example", 98837);
	 * myValue.add("plop", 88);
	 * // Display an element:
	 * printf("my value is : %d", myValue["example"]);
	 * // Change value of an element:
	 * myValue.set("example", 99);
	 * // Remove an element:
	 * myValue.remove("plop");
	 * //Clean all the table:
	 * myValue.clear();
	 * [/code]
	 */
	template<class MY_TYPE> class Hash {
		private:
			std::vector<HashData<MY_TYPE>* > m_data; //!< Data of the hash ==> the Hash table is composed of pointer, this permit to have high speed when resize the vestor ...
		public:
			/**
			 * @brief Contructor of the Hach table.
			 * @param[in] _count Number ob basic elent in the vector.
			 */
			Hash(int32_t _count = 0) :
			  m_data(_count) {
				// nothing to do
			}
			/**
			 * @brief Destructor of the Hash table(clear all element in the table)
			 */
			~Hash() {
				clear();
			}
			/**
			 * @brief Remove all entry in the Hash table.
			 * @note It does not delete pointer if your value is a pointer type...
			 */
			void clear() {
				for (size_t iii = 0; iii < m_data.size(); ++iii) {
					if (m_data[iii] != NULL) {
						delete(m_data[iii]);
						m_data[iii]=NULL;
					}
				}
				m_data.clear();
			}
			/**
			 * @brief Get a current element ID in the Hash table
			 * @param[in] _key Name of the hash requested
			 * @return Id of the element in the table or -1 of it does not existed
			 */
			int64_t getId(const std::string& _key) const {
				for (size_t iii=0; iii<m_data.size(); iii++) {
					if (m_data[iii] != NULL) {
						//TK_INFO("Compare key : '" << m_data[iii]->m_key << "' with '" << _key << "'" );
						if (m_data[iii]->m_key == _key) {
							return iii;
						}
					}
				}
				//TK_ERROR(" ==> not fund key '" << _key << "'" );
				return -1;
			}
			/**
			 * @brief Check if an element exist or not
			 * @param[in] _key Name of the hash requested
			 * @return true if the element exist
			 */
			bool exist(const std::string& _name) const {
				int64_t elementId = getId(_name);
				//TK_INFO(" Exist ? '" << _name << "' id=" << elementId );
				if (elementId<0) {
					//TK_INFO("     ==> return false" );
					return false;
				}
				//TK_INFO("     ==> return true" );
				return true;
			}
			/**
			 * @brief Get a current element in the hash table, with his name.
			 * @param[in] _key Name of the hash requested
			 * @return Reference on the Element
			 */
			MY_TYPE& get(const std::string& _key) const {
				static MY_TYPE g_error;
				int64_t elementId = getId(_key);
				if (elementId<0) {
					TK_ERROR("try to acces at an unexistant hash element : " << _key);
					return g_error;
				}
				return m_data[elementId]->m_value;
			}
			/**
			 * @brief Get an copy Element an a special position
			 * @param[in] _key Name of the hash requested
			 * @return An reference on the copy of selected element
			 */
			MY_TYPE& operator[] (const std::string& _key) {
				return get(_key);
			}
			//! @previous
			const MY_TYPE& operator[] (const std::string& _key) const {
				return get(_key);
			}
			/**
			 * @brief Add an element OR set an element value
			 * @note add and set is the same function.
			 * @param[in] _key Name of the value to set in the hash table.
			 * @param[in] _value Value to set in the hash table.
			 */
			void add(const std::string& _key, const MY_TYPE& _value) {
				int64_t elementId = getId(_key);
				if (elementId <0) {
					HashData<MY_TYPE>* tmp = new HashData<MY_TYPE>(_key, _value);
					if (NULL == tmp) {
						TK_ERROR("allocation error in Hash table : '" << _key << "'");
						return;
					}
					m_data.push_back(tmp);
					return;
				}
				m_data[elementId]->m_value = _value;
			}
			/**
			 * @previous
			 */
			void set(const std::string& _key, const MY_TYPE& _value) {
				add(_key, _value);
			}
			/**
			 * @brief Remove an element in the hash table.
			 * @param[in] _key Name of the element to remove.
			 */
			void remove(const std::string& _key) {
				int64_t elementId = getId(_key);
				if (elementId <0) {
					//nothing to do ==> not existed
					return;
				}
				delete(m_data[elementId]);
				m_data[elementId] = NULL;
				m_data.remove(elementId);
			}
			/**
			 * @brief Get the number of element in the hash table
			 * @return number of elements
			 */
			int32_t size() const {
				return m_data.size();
			}
			/**
			 * @brief get an element with his id.
			 * @param[in] _pos Position on the element in the hash table.
			 * @return requested element at this position.
			 * @note this is a dangerous use of the hash table. Maybe you will use a simple vector.
			 */
			MY_TYPE& operator[] (size_t _pos) {
				return getValue(_pos);
			}
			/**
			 * @previous
			 */
			const MY_TYPE& operator[] (size_t _pos) const {
				return getValue(_pos);
			}
			/**
			 * @brief Get the name of the element at a specific position.
			 * @param[in] _pos Position of the element in the hash table.
			 * @return name of the element (key).
			 */
			const std::string& getKey(size_t _pos) const {
				// NOTE :Do not change log level, this generate error only in debug mode
				#if DEBUG_LEVEL > 2
					if(_pos>m_data.size()){
						TK_CRITICAL("Access to an unexistant data in hach : " << _pos << "/ " << m_data.size());
					}
				#endif
				return m_data[_pos]->m_key;
			}
			/**
			 * @brief Get all the element name (keys).
			 * @return a vector of all name (key).
			 */
			std::vector<std::string> getKeys() const {
				std::vector<std::string> keys;
				for (size_t iii = 0; iii < m_data.size(); ++iii) {
					if (m_data[iii] != NULL) {
						keys.push_back(m_data[iii]->m_key);
					}
				}
				return keys;
			}
			/**
			 * @brief Get a value of the hash table at a specific position.
			 * @param[in] _posPosition of the element in the hash table.
			 * @return Value availlable at this position.
			 */
			const MY_TYPE& getValue(size_t _pos) const {
				// NOTE :Do not change log level, this generate error only in debug mode
				#if DEBUG_LEVEL > 2
					if(_pos>m_data.size()){
						TK_CRITICAL("Access to an unexistant data in hach : " << _pos << "/ " << m_data.size());
					}
				#endif
				return m_data[_pos]->m_value;
			}
			/**
			 * @previous
			 */
			MY_TYPE& getValue(size_t _pos) {
				// NOTE :Do not change log level, this generate error only in debug mode
				#if DEBUG_LEVEL > 2
					if(_pos>m_data.size()){
						TK_CRITICAL("Access to an unexistant data in hach : " << _pos << "/ " << m_data.size());
					}
				#endif
				return m_data[_pos]->m_value;
			}
	};
};

#undef __class__
#define __class__ NULL

#endif

