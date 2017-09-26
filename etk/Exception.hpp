/**
 * @author Edouard DUPIN
 * @copyright 2017, Edouard DUPIN, all right reserved
 * @license MPL-2 (see license file)
 */
#pragma once
#include <etk/types.hpp>
#include <etk/String.hpp>


namespace etk {
	//class String;
	/**
	 * @brief Global exception handle
	 */
	class Exception {
		private:
			const char* m_type; //!< type of the exception
			const etk::String m_what; //!< problem exception type
			const char* m_function; //!< Function where the exception is generated
		public:
			/**
			 * @brief Default constructor.
			 */
			Exception();
			/**
			 * @brief Generic Constructor.
			 * @param[in] _type Type of the exception
			 * @param[in] _what The explanation of the problem.
			 * @param[in] _function Function name to find faster the source od the problem.
			 */
			Exception(const char* _type, const etk::String& _what, const char* _function = nullptr);
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
			 * @brief Get the Name of the fuction where the exception is generated.
			 * @return Function string or nullptr
			 */
			const char* where() const;
			/**
			 * @brief Convert the class in String.
			 * @return generating desription of class
			 */
			etk::String toString() const;
	};
	//! @brief Generic 
	namespace exception {
		class InvalidArgument : public etk::Exception {
			public:
				/**
				 * @brief Contructor of an generic Exception.
				 * @param[in] _what The explanation of the problem.
				 * @param[in] _function Function name to find faster the source od the problem.
				 */
				InvalidArgument(const etk::String& _what, const char* _function = nullptr):
				  etk::Exception("INVALID-ARGUMENT", _what, _function) {
					
				}
		};
		class DomainError : public etk::Exception {
			public:
				/**
				 * @brief Contructor of an generic Exception.
				 * @param[in] _what The explanation of the problem.
				 * @param[in] _function Function name to find faster the source od the problem.
				 */
				DomainError(const etk::String& _what, const char* _function = nullptr):
				  etk::Exception("DOMAIN-ERROR", _what, _function) {
					
				}
		};
		class LengthError : public etk::Exception {
			public:
				/**
				 * @brief Contructor of an generic Exception.
				 * @param[in] _what The explanation of the problem.
				 * @param[in] _function Function name to find faster the source od the problem.
				 */
				LengthError(const etk::String& _what, const char* _function = nullptr):
				  etk::Exception("LENGTH-ERROR", _what, _function) {
					
				}
		};
		class OutOfRange : public etk::Exception {
			public:
				/**
				 * @brief Contructor of an generic Exception.
				 * @param[in] _what The explanation of the problem.
				 * @param[in] _function Function name to find faster the source od the problem.
				 */
				OutOfRange(const etk::String& _what, const char* _function = nullptr):
				  etk::Exception("OUT-OF-RANGE", _what, _function) {
					
				}
		};
		class RangeError : public etk::Exception {
			public:
				/**
				 * @brief Contructor of an generic Exception.
				 * @param[in] _what The explanation of the problem.
				 * @param[in] _function Function name to find faster the source od the problem.
				 */
				RangeError(const etk::String& _what, const char* _function = nullptr):
				  etk::Exception("RANGE-ERROR", _what, _function) {
					
				}
		};
		class OverflowError : public etk::Exception {
			public:
				/**
				 * @brief Contructor of an generic Exception.
				 * @param[in] _what The explanation of the problem.
				 * @param[in] _function Function name to find faster the source od the problem.
				 */
				OverflowError(const etk::String& _what, const char* _function = nullptr):
				  etk::Exception("OVERFLOW-ERROR", _what, _function) {
					
				}
		};
		class UnderflowError : public etk::Exception {
			public:
				/**
				 * @brief Contructor of an generic Exception.
				 * @param[in] _what The explanation of the problem.
				 * @param[in] _function Function name to find faster the source od the problem.
				 */
				UnderflowError(const etk::String& _what, const char* _function = nullptr):
				  etk::Exception("UNDERFLOW-ERROR", _what, _function) {
					
				}
		};
		class CastError : public etk::Exception {
			public:
				/**
				 * @brief Contructor of an generic Exception.
				 * @param[in] _what The explanation of the problem.
				 * @param[in] _function Function name to find faster the source od the problem.
				 */
				CastError(const etk::String& _what, const char* _function = nullptr):
				  etk::Exception("CAST-ERROR", _what, _function) {
					
				}
		};
		class AllocationError : public etk::Exception {
			public:
				/**
				 * @brief Contructor of an generic Exception.
				 * @param[in] _what The explanation of the problem.
				 * @param[in] _function Function name to find faster the source od the problem.
				 */
				AllocationError(const etk::String& _what, const char* _function = nullptr):
				  etk::Exception("ALLOCATION-ERROR", _what, _function) {
					
				}
		};
	}
}
