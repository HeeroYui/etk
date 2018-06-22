/**
 * @author Edouard DUPIN
 * @copyright 2017, Edouard DUPIN, all right reserved
 * @license MPL-2 (see license file)
 */
#pragma once
#include <etk/types.hpp>
#include <etk/String.hpp>


namespace etk {
	/**
	 * @brief Global exception handle
	 */
	class Exception {
		private:
			const char* m_type = null; //!< type of the exception
			const etk::String m_what = "? ? ?"; //!< problem exception type
			const char* m_function = null; //!< Function where the exception is generated
			const char* m_file = null; //!< File where the excepton append
			size_t m_line = 0; //!< Line of the exception
		public:
			/**
			 * @brief Default constructor.
			 */
			Exception();
			/**
			 * @brief Generic Constructor.
			 * @param[in] _type Type of the exception
			 * @param[in] _what The explanation of the problem.
			 * @param[in] _function Function name to find faster the source of the problem.
			 * @param[in] _file File of the exception throw.
			 * @param[in] _line Line of the file throw.
			 */
			Exception(const char* _type, const etk::String& _what);
			/**
			 * @brief virtualize destructor.
			 */
			virtual ~Exception() = default;
			/**
			 * @brief Get the type of the exception.
			 * @return String name of the exception.
			 */
			const char* which() const;
			/**
			 * @brief Get the explanation of the problem.
			 * @return Descriptive string.
			 */
			const etk::String what() const;
			/**
			 * @brief Get the Name of the file where the exception is generated.
			 * @return File string or null
			 */
			const char* file() const;
			/**
			 * @brief Set the file Name.
			 * @param[in] _value File string or null
			 */
			etk::Exception& setFile(const char* _value);
			/**
			 * @brief Get the Name of the fuction where the exception is generated.
			 * @return Function string or null
			 */
			const char* function() const;
			/**
			 * @brief Set the function Name.
			 * @param[in] _value Function string or null
			 */
			etk::Exception& setFunction(const char* _value);
			/**
			 * @brief Line Index in the file where thre throw append
			 * @return Line in the file
			 */
			size_t line() const;
			/**
			 * @brief Set the file line.
			 * @param[in] _value File line.
			 */
			etk::Exception& setLine(size_t _value);
			/**
			 * @brief Convert the class in String.
			 * @return generating desription of class
			 */
			etk::String toString() const;
	};
	#define ETK_THROW_EXCEPTION(ex) throw ex.setFunction(__PRETTY_FUNCTION__).setFile(__FILE__).setLine(__LINE__)
	
	//! @brief Generic 
	namespace exception {
		class InvalidArgument : public etk::Exception {
			public:
				/**
				 * @brief Contructor of an generic Exception.
				 * @param[in] _what The explanation of the problem.
				 */
				InvalidArgument(const etk::String& _what):
				  etk::Exception("INVALID-ARGUMENT", _what) {
					
				}
		};
		class DomainError : public etk::Exception {
			public:
				/**
				 * @brief Contructor of an generic Exception.
				 * @param[in] _what The explanation of the problem.
				 */
				DomainError(const etk::String& _what):
				  etk::Exception("DOMAIN-ERROR", _what) {
					
				}
		};
		class LengthError : public etk::Exception {
			public:
				/**
				 * @brief Contructor of an generic Exception.
				 * @param[in] _what The explanation of the problem.
				 */
				LengthError(const etk::String& _what):
				  etk::Exception("LENGTH-ERROR", _what) {
					
				}
		};
		class OutOfRange : public etk::Exception {
			public:
				/**
				 * @brief Contructor of an generic Exception.
				 * @param[in] _what The explanation of the problem.
				 */
				OutOfRange(const etk::String& _what):
				  etk::Exception("OUT-OF-RANGE", _what) {
					
				}
		};
		class RangeError : public etk::Exception {
			public:
				/**
				 * @brief Contructor of an generic Exception.
				 * @param[in] _what The explanation of the problem.
				 */
				RangeError(const etk::String& _what):
				  etk::Exception("RANGE-ERROR", _what) {
					
				}
		};
		class OverflowError : public etk::Exception {
			public:
				/**
				 * @brief Contructor of an generic Exception.
				 * @param[in] _what The explanation of the problem.
				 */
				OverflowError(const etk::String& _what):
				  etk::Exception("OVERFLOW-ERROR", _what) {
					
				}
		};
		class UnderflowError : public etk::Exception {
			public:
				/**
				 * @brief Contructor of an generic Exception.
				 * @param[in] _what The explanation of the problem.
				 */
				UnderflowError(const etk::String& _what):
				  etk::Exception("UNDERFLOW-ERROR", _what) {
					
				}
		};
		class CastError : public etk::Exception {
			public:
				/**
				 * @brief Contructor of an generic Exception.
				 * @param[in] _what The explanation of the problem.
				 */
				CastError(const etk::String& _what):
				  etk::Exception("CAST-ERROR", _what) {
					
				}
		};
		class AllocationError : public etk::Exception {
			public:
				/**
				 * @brief Contructor of an generic Exception.
				 * @param[in] _what The explanation of the problem.
				 */
				AllocationError(const etk::String& _what):
				  etk::Exception("ALLOCATION-ERROR", _what) {
					
				}
		};
		class RuntimeError : public etk::Exception {
			public:
				/**
				 * @brief Contructor of an generic Exception.
				 * @param[in] _what The explanation of the problem.
				 */
				RuntimeError(const etk::String& _what):
				  etk::Exception("RUNTIME-ERROR", _what) {
					
				}
		};
		class NullPointerError : public etk::Exception {
			public:
				/**
				 * @brief Contructor of an generic Exception.
				 * @param[in] _what The explanation of the problem.
				 */
				NullPointerError(const etk::String& _what):
				  etk::Exception("NULL-POINTER-ERROR", _what) {
					
				}
		};
	}
}
