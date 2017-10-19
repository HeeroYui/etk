/** @file
 * @author Edouard DUPIN
 * @copyright 2017, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#pragma once
#include <etk/types.hpp>
#include <etk/String.hpp>

// TO facilitate debug when have a problem ...
#define ETK_FUNCTION_DEBUG(...) do {} while(false)
//#define ETK_FUNCTION_DEBUG      printf

namespace etk {
	template <typename ETK_TYPE_FUNCTOR, typename ETK_TYPE_FUNCTION>
	class FunctionPrivateLambda;
	template <typename ETK_TYPE_FUNCTION>
	class FunctionPrivateFunction;
	template <typename ETK_TYPE_FUNCTION>
	class FunctionPrivate;
	
	template <typename ETK_TYPE_FUNCTION_RETURN, typename... ETK_TYPE_FUNCTION_ARGS>
	class FunctionPrivate<ETK_TYPE_FUNCTION_RETURN(ETK_TYPE_FUNCTION_ARGS...)> {
		public:
			virtual ~FunctionPrivate() {
				
			}
			virtual ETK_TYPE_FUNCTION_RETURN operator()(ETK_TYPE_FUNCTION_ARGS... _args) const = 0;
			virtual FunctionPrivate<ETK_TYPE_FUNCTION_RETURN(ETK_TYPE_FUNCTION_ARGS...)>* copy() {
				ETK_FUNCTION_DEBUG("    COPY NULLPTR \n");
				return nullptr;
			}
	};
	template <typename ETK_TYPE_FUNCTION_FUNCTOR, typename ETK_TYPE_FUNCTION_RETURN, typename... ETK_TYPE_FUNCTION_ARGS>
	class FunctionPrivateLambda<ETK_TYPE_FUNCTION_FUNCTOR, ETK_TYPE_FUNCTION_RETURN(ETK_TYPE_FUNCTION_ARGS...)>:
	  public FunctionPrivate<ETK_TYPE_FUNCTION_RETURN(ETK_TYPE_FUNCTION_ARGS...)> {
		private:
			mutable ETK_TYPE_FUNCTION_FUNCTOR m_dataPointer;
		public:
			FunctionPrivateLambda(ETK_TYPE_FUNCTION_FUNCTOR _functor):
			  m_dataPointer(_functor) {
				ETK_FUNCTION_DEBUG("    CREATE FunctionPrivateLambda \n");
			}
			/*
			FunctionPrivateLambda(const ETK_TYPE_FUNCTION_FUNCTOR& _functor):
			  m_dataPointer(_functor) {
				ETK_FUNCTION_DEBUG("    CREATE FunctionPrivateLambda \n");
			}
			*/
			~FunctionPrivateLambda() {
				
			}
			ETK_TYPE_FUNCTION_RETURN operator()(ETK_TYPE_FUNCTION_ARGS... _args) const {
				return m_dataPointer(etk::forward<ETK_TYPE_FUNCTION_ARGS>(_args)...);
			}
			FunctionPrivate<ETK_TYPE_FUNCTION_RETURN(ETK_TYPE_FUNCTION_ARGS...)>* copy() {
				ETK_FUNCTION_DEBUG("    COPY FunctionPrivateLambda \n");
				return ETK_NEW(FunctionPrivateLambda, m_dataPointer);
			}
	};
	
	template <typename ETK_TYPE_FUNCTION>
	class Function;
	
	extern uint32_t MM___pppppp;
	template <typename ETK_TYPE_FUNCTION_RETURN, typename... ETK_TYPE_FUNCTION_ARGS>
	class Function<ETK_TYPE_FUNCTION_RETURN(ETK_TYPE_FUNCTION_ARGS...)> {
		private:
			typedef FunctionPrivate<ETK_TYPE_FUNCTION_RETURN(ETK_TYPE_FUNCTION_ARGS...)> FunctionPrivateTypedef;
			FunctionPrivateTypedef* m_pointerPrivate;
			uint32_t m_pppppp;
		public:
			Function():
			  m_pointerPrivate(nullptr) {
				m_pppppp = MM___pppppp++;
				ETK_FUNCTION_DEBUG("[%d=0X%lx] create Function 1 \n", m_pppppp, (uint64_t)this);
			}
			Function(const etk::NullPtr&):
			  m_pointerPrivate(nullptr) {
				m_pppppp = MM___pppppp++;
				ETK_FUNCTION_DEBUG("[%d=0X%lx] create Function 2\n", m_pppppp, (uint64_t)this);
			}
			Function(const Function& _obj):
			  m_pointerPrivate(nullptr) {
				m_pppppp = MM___pppppp++;
				ETK_FUNCTION_DEBUG("[%d=0X%lx] create Function (copy constructor) ---------------------- [%d=0X%lx]\n", m_pppppp, (uint64_t)this, _obj.m_pppppp, (uint64_t)&_obj);
				if (_obj.m_pointerPrivate != nullptr) {
					m_pointerPrivate = _obj.m_pointerPrivate->copy();
				}
				ETK_FUNCTION_DEBUG("[%d=0X%lx] create Function (copy constructor) ------- (done) ------- [%d=0X%lx]\n", m_pppppp, (uint64_t)this, _obj.m_pppppp, (uint64_t)&_obj);
			}
			Function(Function&& _obj):
			  m_pointerPrivate(nullptr) {
				m_pppppp = MM___pppppp++;
				ETK_FUNCTION_DEBUG("[%d] create Function 2\n", m_pppppp);
				_obj.swap(*this);
				ETK_FUNCTION_DEBUG("[%d] create Function 2 (done)\n", m_pppppp);
			}
			template <typename ETK_TYPE_FUNCTION_FUNCTOR,
			          typename etk::EnableIf<    !etk::IsSame<ETK_TYPE_FUNCTION_FUNCTOR,Function>::value
			                                  && !etk::IsSame<ETK_TYPE_FUNCTION_FUNCTOR,etk::NullPtr>::value, int
			                                >::type = 0
			         >
			Function(ETK_TYPE_FUNCTION_FUNCTOR _functor):
			  m_pointerPrivate(nullptr) {
				m_pppppp = MM___pppppp++;
				ETK_FUNCTION_DEBUG("[%d=0X%lx] create Function 4 \n", m_pppppp, (uint64_t)this);
				typedef FunctionPrivateLambda<ETK_TYPE_FUNCTION_FUNCTOR, ETK_TYPE_FUNCTION_RETURN(ETK_TYPE_FUNCTION_ARGS...)> FunctionPrivateLambdaTypedef;
				m_pointerPrivate = ETK_NEW(FunctionPrivateLambdaTypedef, _functor);
				ETK_FUNCTION_DEBUG("[%d=0X%lx] create Function 4 (done)\n", m_pppppp, (uint64_t)this);
			}
			~Function() {
				ETK_FUNCTION_DEBUG("[%d=0X%lx] DELETE Function \n", m_pppppp, (uint64_t)this);
				ETK_DELETE(FunctionPrivateTypedef, m_pointerPrivate);
				m_pointerPrivate = nullptr;
			}
			ETK_TYPE_FUNCTION_RETURN operator()(ETK_TYPE_FUNCTION_ARGS... _args) const {
				if (m_pointerPrivate == nullptr) {
					ETK_FUNCTION_DEBUG("[%d=0X%lx] call Function (With nullptr !!! ==> must assert ...)\n", m_pppppp, (uint64_t)this);
					throw;
				}
				ETK_FUNCTION_DEBUG("[%d=0X%lx] call Function \n", m_pppppp, (uint64_t)this);
				return (*m_pointerPrivate)(etk::forward<ETK_TYPE_FUNCTION_ARGS>(_args)...);
			}
			Function& operator= (const Function& _obj){
				ETK_FUNCTION_DEBUG("[%d=0X%lx] operator=(set) Function [%d=0X%lx]\n", m_pppppp, (uint64_t)this, _obj.m_pppppp, (uint64_t)&_obj);
				Function(_obj).swap(*this);
				ETK_FUNCTION_DEBUG("[%d=0X%lx] operator=(set) Function [%d=0X%lx] (done)\n", m_pppppp, (uint64_t)this, _obj.m_pppppp, (uint64_t)&_obj);
				return *this;
			}
			Function& operator= (Function&& _obj){
				ETK_FUNCTION_DEBUG("[%d=0X%lx] operator=(move) Function [%d=0X%lx]\n", m_pppppp, (uint64_t)this, _obj.m_pppppp, (uint64_t)&_obj);
				Function(etk::move(_obj)).swap(*this);
				ETK_FUNCTION_DEBUG("[%d=0X%lx] operator=(move) Function [%d=0X%lx] (done)\n", m_pppppp, (uint64_t)this, _obj.m_pppppp, (uint64_t)&_obj);
				return *this;
			}
			Function& operator= (etk::NullPtr _obj) {
				ETK_DELETE(FunctionPrivateTypedef, m_pointerPrivate);
				m_pointerPrivate = nullptr;
				ETK_FUNCTION_DEBUG("[%d=0X%lx] operator = nullptr 0X%lx\n", m_pppppp, (uint64_t)this, (uint64_t)m_pointerPrivate);
				return *this;
			}
			
			void swap(Function& _obj) {
				ETK_FUNCTION_DEBUG("[%d=0X%lx] swap [%d=0X%lx]\n", m_pppppp, (uint64_t)this, _obj.m_pppppp, (uint64_t)_obj);
				etk::swap(m_pointerPrivate, _obj.m_pointerPrivate);
				etk::swap(m_pppppp, _obj.m_pppppp);
				ETK_FUNCTION_DEBUG("[%d=0X%lx] swap [%d=0X%lx] (done)\n", m_pppppp, (uint64_t)this, _obj.m_pppppp, (uint64_t)_obj);
			}
			template <typename ETK_TYPE_FUNCTION_FUNCTOR,
			          typename etk::EnableIf<    !etk::IsSame<ETK_TYPE_FUNCTION_FUNCTOR,Function>::value
			                                  && !etk::IsSame<ETK_TYPE_FUNCTION_FUNCTOR,etk::NullPtr>::value, int
			                                >::type = 0
			         >
			Function& operator= (ETK_TYPE_FUNCTION_FUNCTOR&& _functor){
				ETK_FUNCTION_DEBUG("[%d=0X%lx] operator = FUNCTOR \n", m_pppppp, (uint64_t)this);
				Function(etk::forward<ETK_TYPE_FUNCTION_FUNCTOR>(_functor)).swap(*this);
				ETK_FUNCTION_DEBUG("[%d=0X%lx] operator = FUNCTOR (done)\n", m_pppppp, (uint64_t)this);
				return *this;
			}
			template <typename ETK_TYPE_FUNCTION_FUNCTOR,
			          typename etk::EnableIf<    !etk::IsSame<ETK_TYPE_FUNCTION_FUNCTOR,Function>::value
			                                  && !etk::IsSame<ETK_TYPE_FUNCTION_FUNCTOR,etk::NullPtr>::value, int
			                                >::type = 0
			         >
			Function& operator= (const ETK_TYPE_FUNCTION_FUNCTOR& _functor){
				ETK_FUNCTION_DEBUG("[%d=0X%lx] operator = const FUNCTOR& \n", m_pppppp, (uint64_t)this);
				Function(_functor).swap(*this);
				ETK_FUNCTION_DEBUG("[%d=0X%lx] operator = const FUNCTOR& (done)\n", m_pppppp, (uint64_t)this);
				return *this;
			}
			operator bool() const {
				return m_pointerPrivate != nullptr;
			}
			bool operator!= (etk::NullPtr) const {
				ETK_FUNCTION_DEBUG("[%d=0X%lx] operator != nullptr ==> 0X%lx %s\n", m_pppppp, (uint64_t)this, (uint64_t)m_pointerPrivate, (m_pointerPrivate != nullptr)?"true":"false");
				return m_pointerPrivate != nullptr;
			}
			bool operator== (etk::NullPtr) const {
				ETK_FUNCTION_DEBUG("[%d=0X%lx] operator == nullptr ==> 0X%lx %s\n", m_pppppp, (uint64_t)this, (uint64_t)m_pointerPrivate, (m_pointerPrivate == nullptr)?"true":"false");
				return m_pointerPrivate == nullptr;
			}
			etk::String toString() const {
				etk::String out = "etk::Function<..(...)>(@";
				out += etk::toString((uint64_t)m_pointerPrivate);
				out += ")";
				return out;
			}
	};
	//! @not_in_doc
	template <typename ETK_TYPE_FUNCTION_RETURN, typename... ETK_TYPE_FUNCTION_ARGS>
	etk::Stream& operator <<(etk::Stream& _os, const etk::Function<ETK_TYPE_FUNCTION_RETURN(ETK_TYPE_FUNCTION_ARGS...)>& _obj) {
		_os << _obj.toString();
		return _os;
	}
}
