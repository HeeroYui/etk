/** @file
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/fs/Type.hpp>
#include <etk/String.hpp>

namespace etk {
	/**
	 * @brief Uniform resource interface manage internal resource and nerwork resource (like URL)
	 * Format is manage like : __SCHEME__://__USER__@__SERVER__:__PORT__/__PATH__?__PARAMETERS__
	 */
	class Uri {
		private:
			etk::String m_scheme; //!< 
			etk::String m_user; //!< 
			etk::String m_server; //!< 
			uint16_t m_port; //!< 
			etk::Path m_path; //!< 
			etk::Vector<etk::Pair<etk::String,etk::String>> m_parameters; //!< 
		public:
			ETK_CONSTRUCTOR_MOVE_DEFAULT(Uri);
			ETK_CONSTRUCTOR_COPY_DEFAULT(Uri);
			/**
			 * @brief Default contructor.
			 */
			Uri();
			/**
			 * @brief Contructor with basic URI.
			 * @param[in] _value Element basic URI
			 */
			Uri(const etk::String& _value);
			/**
			 * @brief Contructor with basic URI.
			 * @param[in] _value Element basic URI
			 */
			Uri(const char * _value);
			
			etk::String getScheme() const;
			void setScheme(const etk::String &_value);
			
			etk::String getUser() const;
			void setUser(const etk::String &_value);
			
			etk::String getServer() const;
			void setServer(const etk::String &_value);
			
			uint16_t getPort() const;
			void setPort(const uint16_t &_value);
			
			etk::Path getPath() const;
			void setPath(const etk::Path &_value);
			
			etk::Parameters getParameters() const;
			void setParameters(const etk::Parameters &_value);
	};
}

