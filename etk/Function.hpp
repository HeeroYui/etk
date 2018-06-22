/** @file
 * @author Edouard DUPIN
 * @copyright 2017, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#pragma once
#include <etk/types.hpp>
#include <etk/String.hpp>
#include <etk/Exception.hpp>

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
				return null;
			}
			virtual void copyIn(char* _buffer) {
				ETK_FUNCTION_DEBUG("    COPY NULLPTR \n");
				return;
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
			virtual void copyIn(char* _buffer) {
				ETK_FUNCTION_DEBUG("    COPY NULLPTR \n");
				new (_buffer) FunctionPrivateLambda(m_dataPointer);
				return;
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
			bool m_local;
			char m_buffer[16];
			uint32_t m_pppppp;
		public:
			Function():
			  m_pointerPrivate(null),
			  m_local(false) {
				memset(m_buffer, 0, sizeof(m_buffer));
				m_pppppp = MM___pppppp++;
				ETK_FUNCTION_DEBUG("[%d=0X%lx] create Function 1 \n", m_pppppp, (uint64_t)this);
			}
			Function(const etk::NullPtr&):
			  m_pointerPrivate(null),
			  m_local(false) {
				memset(m_buffer, 0, sizeof(m_buffer));
				m_pppppp = MM___pppppp++;
				ETK_FUNCTION_DEBUG("[%d=0X%lx] create Function 2\n", m_pppppp, (uint64_t)this);
			}
			Function(const Function& _obj):
			  m_pointerPrivate(null),
			  m_local(false) {
				memset(m_buffer, 0, sizeof(m_buffer));
				m_pppppp = MM___pppppp++;
				ETK_FUNCTION_DEBUG("[%d=0X%lx] create Function (copy constructor) ---------------------- [%d=0X%lx]\n", m_pppppp, (uint64_t)this, _obj.m_pppppp, (uint64_t)&_obj);
				if (_obj.m_local == true) {
					((FunctionPrivateTypedef*)_obj.m_buffer)->copyIn(m_buffer);
					m_local = true;
				} else if (_obj.m_pointerPrivate != null) {
					m_pointerPrivate = _obj.m_pointerPrivate->copy();
				}
				ETK_FUNCTION_DEBUG("[%d=0X%lx] create Function (copy constructor) ------- (done) ------- [%d=0X%lx]\n", m_pppppp, (uint64_t)this, _obj.m_pppppp, (uint64_t)&_obj);
			}
			Function(Function&& _obj):
			  m_pointerPrivate(null),
			  m_local(false) {
				memset(m_buffer, 0, sizeof(m_buffer));
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
			  m_pointerPrivate(null),
			  m_local(false) {
				memset(m_buffer, 0, sizeof(m_buffer));
				m_pppppp = MM___pppppp++;
				ETK_FUNCTION_DEBUG("[%d=0X%lx] create Function 4 \n", m_pppppp, (uint64_t)this);
				typedef FunctionPrivateLambda<ETK_TYPE_FUNCTION_FUNCTOR, ETK_TYPE_FUNCTION_RETURN(ETK_TYPE_FUNCTION_ARGS...)> FunctionPrivateLambdaTypedef;
				if (sizeof(FunctionPrivateLambdaTypedef) <= sizeof(m_buffer)) {
					new(m_buffer) FunctionPrivateLambdaTypedef(_functor);
					m_local = true;
				} else {
					m_pointerPrivate = ETK_NEW(FunctionPrivateLambdaTypedef, _functor);
				}
				ETK_FUNCTION_DEBUG("[%d=0X%lx] create Function 4 (done)\n", m_pppppp, (uint64_t)this);
			}
			~Function() {
				ETK_FUNCTION_DEBUG("[%d=0X%lx] DELETE Function \n", m_pppppp, (uint64_t)this);
				ETK_DELETE(FunctionPrivateTypedef, m_pointerPrivate);
				m_pointerPrivate = null;
				if (m_local == true) {
					// force the cast:
					FunctionPrivateTypedef* tmp = (FunctionPrivateTypedef*)m_buffer;
					tmp->~FunctionPrivate();
					m_local = false;
					memset(m_buffer, 0, sizeof(m_buffer));
				}
			}
			ETK_TYPE_FUNCTION_RETURN operator()(ETK_TYPE_FUNCTION_ARGS... _args) const {
				if (    m_pointerPrivate == null
				     && m_local == false) {
					ETK_FUNCTION_DEBUG("[%d=0X%lx] call Function (With null !!! ==> must assert ...)\n", m_pppppp, (uint64_t)this);
					ETK_THROW_EXCEPTION(etk::exception::NullPointerError("etk::Function call empty pointer"));
				}
				ETK_FUNCTION_DEBUG("[%d=0X%lx] call Function \n", m_pppppp, (uint64_t)this);
				if (m_local == true) {
					return (*((FunctionPrivateTypedef*)m_buffer))(etk::forward<ETK_TYPE_FUNCTION_ARGS>(_args)...);
				}
				return (*m_pointerPrivate)(etk::forward<ETK_TYPE_FUNCTION_ARGS>(_args)...);
			}
			Function& operator= (const Function& _obj) {
				ETK_FUNCTION_DEBUG("[%d=0X%lx] operator=(set) Function [%d=0X%lx]\n", m_pppppp, (uint64_t)this, _obj.m_pppppp, (uint64_t)&_obj);
				Function(_obj).swap(*this);
				ETK_FUNCTION_DEBUG("[%d=0X%lx] operator=(set) Function [%d=0X%lx] (done)\n", m_pppppp, (uint64_t)this, _obj.m_pppppp, (uint64_t)&_obj);
				return *this;
			}
			Function& operator= (Function&& _obj) {
				ETK_FUNCTION_DEBUG("[%d=0X%lx] operator=(move) Function [%d=0X%lx]\n", m_pppppp, (uint64_t)this, _obj.m_pppppp, (uint64_t)&_obj);
				Function(etk::move(_obj)).swap(*this);
				ETK_FUNCTION_DEBUG("[%d=0X%lx] operator=(move) Function [%d=0X%lx] (done)\n", m_pppppp, (uint64_t)this, _obj.m_pppppp, (uint64_t)&_obj);
				return *this;
			}
			Function& operator= (etk::NullPtr _obj) {
				ETK_DELETE(FunctionPrivateTypedef, m_pointerPrivate);
				m_pointerPrivate = null;
				if (m_local == true) {
					// force the cast:
					FunctionPrivateTypedef* tmp = (FunctionPrivateTypedef*)m_buffer;
					tmp->~FunctionPrivate();
					m_local = false;
					memset(m_buffer, 0, sizeof(m_buffer));
				}
				ETK_FUNCTION_DEBUG("[%d=0X%lx] operator = null 0X%lx\n", m_pppppp, (uint64_t)this, (uint64_t)m_pointerPrivate);
				return *this;
			}
			
			void swap(Function& _obj) {
				ETK_FUNCTION_DEBUG("[%d=0X%lx] swap [%d=0X%lx]\n", m_pppppp, (uint64_t)this, _obj.m_pppppp, (uint64_t)_obj);
				etk::swap(m_pointerPrivate, _obj.m_pointerPrivate);
				etk::swap(m_pppppp, _obj.m_pppppp);
				etk::swap(m_local, _obj.m_local);
				// TODO : This is dangerous ==> to check ...
				for (size_t iii=0; iii<sizeof(m_buffer); ++iii) {
					char tmp = m_buffer[iii];
					m_buffer[iii] = _obj.m_buffer[iii];
					_obj.m_buffer[iii] = tmp;
				}
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
				return    m_pointerPrivate != null
				       || m_local == true ;
			}
			bool operator!= (etk::NullPtr) const {
				ETK_FUNCTION_DEBUG("[%d=0X%lx] operator != null ==> 0X%lx %s\n", m_pppppp, (uint64_t)this, (uint64_t)m_pointerPrivate, (m_pointerPrivate != null)?"true":"false");
				return    m_pointerPrivate != null
				       || m_local == true;
			}
			bool operator== (etk::NullPtr) const {
				ETK_FUNCTION_DEBUG("[%d=0X%lx] operator == null ==> 0X%lx %s\n", m_pppppp, (uint64_t)this, (uint64_t)m_pointerPrivate, (m_pointerPrivate == null)?"true":"false");
				return    m_pointerPrivate == null
				       && m_local == false;
			}
			etk::String toString() const {
				etk::String out = "etk::Function<..(...)>(@";
				if (m_local == true) {
					out += etk::toString((uint64_t)m_buffer);
				} else {
					out += etk::toString((uint64_t)m_pointerPrivate);
				}
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
