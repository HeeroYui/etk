/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/types.hpp>
//#include <ememory/UniquePtr.hpp>

#pragma once

namespace etk {
	template <typename ETK_TYPE_FUNCTION>
	class Function;
	
	template <typename ETK_TYPE_FUNCTION_RETURN, typename... ETK_TYPE_FUNCTION_ARGS>
	class Function<ETK_TYPE_FUNCTION_RETURN(ETK_TYPE_FUNCTION_ARGS...)> {
		// function pointer types for the type-erasure behaviors
		// all these char* parameters are actually casted from some functor type
		typedef ETK_TYPE_FUNCTION_RETURN (*invoke_fn_t)(char*, ETK_TYPE_FUNCTION_ARGS&&...);
		typedef void (*construct_fn_t)(char*, char*);
		typedef void (*destroy_fn_t)(char*);
		// type-aware generic functions for invoking
		// the specialization of these functions won't be capable with
		//   the above function pointer types, so we need some cast
		template <typename ETK_TYPE_FUNCTION_FUNCTOR>
		static ETK_TYPE_FUNCTION_RETURN invoke_fn(ETK_TYPE_FUNCTION_FUNCTOR* _functor,
		                                          ETK_TYPE_FUNCTION_ARGS... _args) {
			return (*_functor)(etk::move<ETK_TYPE_FUNCTION_ARGS>(_args)...);
		}
		template <typename ETK_TYPE_FUNCTION_FUNCTOR>
		static void construct_fn(ETK_TYPE_FUNCTION_FUNCTOR* _constructDestination,
		                         ETK_TYPE_FUNCTION_FUNCTOR* _constructSource) {
			// the functor type must be copy-constructible
			new (_constructDestination) Function(*_constructSource);
		}
		template <typename ETK_TYPE_FUNCTION_FUNCTOR>
		static void destroy_fn(ETK_TYPE_FUNCTION_FUNCTOR* _functor) {
			_functor->~Function();
		}
		// These pointers are storing behaviors.
		invoke_fn_t invoke_f;
		construct_fn_t construct_f;
		destroy_fn_t destroy_f;
		// Erase the type of any functor and store it into a char*
		// so the storage size should be obtained as well
		char* m_dataPointer;
		size_t m_dataSize;
	public:
		Function()
			: invoke_f(nullptr)
			, construct_f(nullptr)
			, destroy_f(nullptr)
			, m_dataPointer(nullptr)
			, m_dataSize(0)
		{}
	
		// construct from any functor type
		template <typename ETK_TYPE_FUNCTION_FUNCTOR>
		Function(ETK_TYPE_FUNCTION_FUNCTOR _functor):
		  // specialize functions and erase their type info by casting
		  invoke_f(reinterpret_cast<invoke_fn_t>(invoke_fn<ETK_TYPE_FUNCTION_FUNCTOR>)),
		  construct_f(reinterpret_cast<construct_fn_t>(construct_fn<ETK_TYPE_FUNCTION_FUNCTOR>)),
		  destroy_f(reinterpret_cast<destroy_fn_t>(destroy_fn<ETK_TYPE_FUNCTION_FUNCTOR>)),
		  m_dataPointer(new char[sizeof(ETK_TYPE_FUNCTION_FUNCTOR)]),
		  m_dataSize(sizeof(ETK_TYPE_FUNCTION_FUNCTOR)) {
			// copy the functor to internal storage
			construct_f(m_dataPointer, reinterpret_cast<char*>(&_functor));
		}
		// copy constructor
		Function(Function const& _obj):
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
		~Function() {
			if (m_dataPointer != nullptr) {
				destroy_f(m_dataPointer);
				delete m_dataPointer;
			}
		}
		// other constructors, from nullptr, from function pointers
		ETK_TYPE_FUNCTION_RETURN operator()(ETK_TYPE_FUNCTION_ARGS... _args) {
			return invoke_f(m_dataPointer,
			                etk::move<ETK_TYPE_FUNCTION_ARGS>(_args)...);
		}
		bool operator!= (nullptr_t) const {
			return m_dataPointer != nullptr;
		}
		bool operator== (nullptr_t) const {
			return m_dataPointer == nullptr;
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