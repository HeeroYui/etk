/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#pragma once
#include <etk/types.hpp>
//#include <ememory/UniquePtr.hpp>

//#define ETK_FUNCTION_ENABLE_NEW

namespace etk {
	template <typename ETK_TYPE_FUNCTION>
	class FunctionPrivateSpecific;
	template <typename ETK_TYPE_FUNCTION>
	class FunctionPrivate;
	
	template <typename ETK_TYPE_FUNCTION_RETURN, typename... ETK_TYPE_FUNCTION_ARGS>
	class FunctionPrivate<ETK_TYPE_FUNCTION_RETURN(ETK_TYPE_FUNCTION_ARGS...)> {
		public:
			virtual ~FunctionPrivate() {
				
			}
			// other constructors, from nullptr, from function pointers
			virtual ETK_TYPE_FUNCTION_RETURN operator()(ETK_TYPE_FUNCTION_ARGS... _args) const = 0;
			FunctionPrivate<ETK_TYPE_FUNCTION_RETURN(ETK_TYPE_FUNCTION_ARGS...)>* copy() {
				return nullptr;
			}
	};
	template <typename ETK_TYPE_FUNCTION_RETURN, typename... ETK_TYPE_FUNCTION_ARGS>
	class FunctionPrivateSpecific<ETK_TYPE_FUNCTION_RETURN(ETK_TYPE_FUNCTION_ARGS...)>:
	  public FunctionPrivate<ETK_TYPE_FUNCTION_RETURN(ETK_TYPE_FUNCTION_ARGS...)> {
		private:
			// function pointer types for the type-erasure behaviors
			// all these char* parameters are actually casted from some functor type
			typedef ETK_TYPE_FUNCTION_RETURN (*invoke_fn_t)(void*, ETK_TYPE_FUNCTION_ARGS&&...);
			#ifdef ETK_FUNCTION_ENABLE_NEW
				typedef void* (*construct_fn_t)();
			#endif
			typedef void (*destroy_fn_t)(void*);
			// type-aware generic functions for invoking
			// the specialization of these functions won't be capable with
			//   the above function pointer types, so we need some cast
			template <typename ETK_TYPE_FUNCTION_FUNCTOR>
			static ETK_TYPE_FUNCTION_RETURN invoke_fn(ETK_TYPE_FUNCTION_FUNCTOR* _functor,
			                                          ETK_TYPE_FUNCTION_ARGS&&... _args) {
				return (*_functor)(etk::forward<ETK_TYPE_FUNCTION_ARGS>(_args)...);
			}
			#ifdef ETK_FUNCTION_ENABLE_NEW
				template <typename ETK_TYPE_FUNCTION_FUNCTOR>
				static void* construct_fn() {
					// the functor type must be copy-constructible
					return new ETK_TYPE_FUNCTION_FUNCTOR();
				}
			#endif
			template <typename ETK_TYPE_FUNCTION_FUNCTOR>
			static void destroy_fn(ETK_TYPE_FUNCTION_FUNCTOR* _functor) {
				_functor->~ETK_TYPE_FUNCTION_FUNCTOR();
			}
			// These pointers are storing behaviors.
			invoke_fn_t invoke_f;
			#ifdef ETK_FUNCTION_ENABLE_NEW
				construct_fn_t construct_f;
			#endif
			destroy_fn_t destroy_f;
			// Erase the type of any functor and store it into a char*
			// so the storage size should be obtained as well
			void* m_dataPointer;
		public:
			FunctionPrivateSpecific():
			  invoke_f(nullptr),
			  #ifdef ETK_FUNCTION_ENABLE_NEW
			    construct_f(nullptr),
			  #endif
			  destroy_f(nullptr),
			  m_dataPointer(nullptr) {
				
			}
			FunctionPrivateSpecific(etk::NullPtr):
			  invoke_f(nullptr),
			  #ifdef ETK_FUNCTION_ENABLE_NEW
			    construct_f(nullptr),
			  #endif
			  destroy_f(nullptr),
			  m_dataPointer(nullptr) {
				
			}
			#ifdef ETK_FUNCTION_ENABLE_NEW
			// construct from any functor type
			template <typename ETK_TYPE_FUNCTION_FUNCTOR>
			FunctionPrivateSpecific(ETK_TYPE_FUNCTION_FUNCTOR _functor):
			  // specialize functions and erase their type info by casting
			  invoke_f(reinterpret_cast<invoke_fn_t>(invoke_fn<ETK_TYPE_FUNCTION_FUNCTOR>)),
			  construct_f(reinterpret_cast<construct_fn_t>(construct_fn<ETK_TYPE_FUNCTION_FUNCTOR>)),
			  destroy_f(reinterpret_cast<destroy_fn_t>(destroy_fn<ETK_TYPE_FUNCTION_FUNCTOR>)),
			  m_dataPointer(nullptr) {
				m_dataPointer = construct_f();
			}
			// copy constructor
			/*
			FunctionPrivateSpecific(const FunctionPrivateSpecific& _obj):
			  invoke_f(_obj.invoke_f),
			  construct_f(_obj.construct_f),
			  destroy_f(_obj.destroy_f),
			  m_dataSize(_obj.m_dataSize) {
				if (invoke_f) {
					// when the source is not a null function, copy its internal functor
					delete(m_dataPointer);
					m_dataPointer = new char[m_dataSize];
					construct_f(m_dataPointer, _obj.m_dataPointer);
				}
			}
			*/
			#else
			// move from any functor type
			template <typename ETK_TYPE_FUNCTION_FUNCTOR>
			FunctionPrivateSpecific(ETK_TYPE_FUNCTION_FUNCTOR&& _functor):
			  // specialize functions and erase their type info by casting
			  invoke_f(reinterpret_cast<invoke_fn_t>(invoke_fn<ETK_TYPE_FUNCTION_FUNCTOR>)),
			  #ifdef ETK_FUNCTION_ENABLE_NEW
			    construct_f(reinterpret_cast<construct_fn_t>(construct_fn<ETK_TYPE_FUNCTION_FUNCTOR>)),
			  #endif
			  destroy_f(reinterpret_cast<destroy_fn_t>(destroy_fn<ETK_TYPE_FUNCTION_FUNCTOR>)),
			  m_dataPointer(nullptr) {
				m_dataPointer = etk::move(_functor);
			}
			
			#endif
			~FunctionPrivateSpecific() {
				if (m_dataPointer != nullptr) {
					destroy_f(m_dataPointer);
					m_dataPointer = nullptr;
				}
			}
			// other constructors, from nullptr, from function pointers
			ETK_TYPE_FUNCTION_RETURN operator()(ETK_TYPE_FUNCTION_ARGS... _args) const {
				return invoke_f(m_dataPointer,
				                etk::forward<ETK_TYPE_FUNCTION_ARGS>(_args)...);
			}
			
			bool operator!= (etk::NullPtr) const {
				return m_dataPointer != nullptr;
			}
			bool operator== (etk::NullPtr) const {
				return m_dataPointer == nullptr;
			}
	};
	template <typename ETK_TYPE_FUNCTION>
	class Function;
	
	template <typename ETK_TYPE_FUNCTION_RETURN, typename... ETK_TYPE_FUNCTION_ARGS>
	class Function<ETK_TYPE_FUNCTION_RETURN(ETK_TYPE_FUNCTION_ARGS...)> {
		private:
			FunctionPrivate<ETK_TYPE_FUNCTION_RETURN(ETK_TYPE_FUNCTION_ARGS...)>* m_pointerPrivate;
			
		public:
			Function():
			  m_pointerPrivate(nullptr) {
				
			}
			Function(etk::NullPtr):
			  m_pointerPrivate(nullptr) {
				
			}
			#ifdef ETK_FUNCTION_ENABLE_NEW
				// construct from any functor type
				template <typename ETK_TYPE_FUNCTION_FUNCTOR>
				Function(ETK_TYPE_FUNCTION_FUNCTOR _functor):
				  m_pointerPrivate(new FunctionPrivateSpecific<ETK_TYPE_FUNCTION_RETURN(ETK_TYPE_FUNCTION_ARGS...)>(_functor)) {
					
				}
				// copy constructor
				Function(const Function& _obj):
				  m_pointerPrivate(nullptr) {
					if (_obj.m_pointerPrivate != nullptr) {
						m_pointerPrivate = _obj.m_pointerPrivate->copy();
					}
				}
			#else
				// construct from any functor type
				template <typename ETK_TYPE_FUNCTION_FUNCTOR>
				Function(ETK_TYPE_FUNCTION_FUNCTOR&& _functor):
				  m_pointerPrivate(new FunctionPrivateSpecific<ETK_TYPE_FUNCTION_RETURN(ETK_TYPE_FUNCTION_ARGS...)>(_functor)) {
					
				}
			#endif
			// copy constructor
			Function(Function&& _obj):
			  m_pointerPrivate(_obj.m_pointerPrivate) {
				_obj.m_pointerPrivate = nullptr;
			}
			~Function() {
				delete m_pointerPrivate;
				m_pointerPrivate = nullptr;
			}
			// other constructors, from nullptr, from function pointers
			ETK_TYPE_FUNCTION_RETURN operator()(ETK_TYPE_FUNCTION_ARGS... _args) const {
				if (m_pointerPrivate == nullptr) {
					throw;
				}
				return (*m_pointerPrivate)(etk::forward<ETK_TYPE_FUNCTION_ARGS>(_args)...);
			}
			
			bool operator!= (etk::NullPtr) const {
				return m_pointerPrivate != nullptr;
			}
			bool operator== (etk::NullPtr) const {
				return m_pointerPrivate == nullptr;
			}
			#ifdef ETK_FUNCTION_ENABLE_NEW
			Function& operator= (const Function& _obj) {
				delete m_pointerPrivate;
				m_pointerPrivate = nullptr;
				if (_obj.m_pointerPrivate != nullptr) {
					m_pointerPrivate = _obj.m_pointerPrivate->copy();
				}
				return *this;
			}
			#endif
			Function& operator= (Function&& _obj) {
				delete m_pointerPrivate;
				m_pointerPrivate = _obj.m_pointerPrivate;
				_obj.m_pointerPrivate = nullptr;
				return *this;
			}
	};


}

/*
// examples
int main()
{
	int i = 0;
	auto fn = [i](etk::String const& s) mutable
	{
		std::cout << ++i << ". " << s << std::endl;
	};
	fn("first"); // 1. first
	fn("second"); // 2. second

	// construct from lambda
	::function<void(std::string const&)> f(fn);
	f("third"); // 3. third

	// copy from another function
	::function<void(std::string const&)> g(f);
	f("forth - f"); // 4. forth - f
	g("forth - g"); // 4. forth - g

	// capture and copy non-trivial types like std::string
	std::string x("xxxx");
	::function<void()> h([x]() { std::cout << x << std::endl; });
	h();

	::function<void()> k(h);
	k();
	return 0;
}
*/