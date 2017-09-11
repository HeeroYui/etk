/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL-2 (see license file)
 */
#pragma once


namespace etk {
	template<class ETK_TYPE, ETK_TYPE val>
	struct IntegralConstant {
		static constexpr ETK_TYPE value = val;
		typedef ETK_TYPE typeValue;
		// using injected-class-name
		typedef IntegralConstant type;
		constexpr operator typeValue() const noexcept {
			return value;
		}
		constexpr typeValue operator()() const noexcept {
			return value;
		}
	};
	
	typedef	etk::IntegralConstant<bool, true> typeTrue;
	typedef	etk::IntegralConstant<bool, false> typeFalse;
	
	template<class ETK_TYPE>
	struct IsLeftValueReference:
	  etk::typeFalse {
		
	};
	template<class ETK_TYPE>
	struct IsLeftValueReference<ETK_TYPE&>: 
	  etk::typeTrue {
		
	};
	
	template<bool B, class ETK_TYPE = void>
	struct EnableIf {
		
	};
	
	template<class ETK_TYPE>
	struct EnableIf<true, ETK_TYPE> {
		typedef ETK_TYPE type;
	};
	
	template<class ETK_TYPE, class ETK_TYPE_2>
	struct IsSame :
	  etk::typeFalse {
		
	};
	
	template<class ETK_TYPE>
	struct IsSame<ETK_TYPE, ETK_TYPE> :
	  etk::typeTrue {
		
	};
	
	template<class ETK_TYPE>
	struct RemoveConst {
		typedef ETK_TYPE type;
	};
	template<class ETK_TYPE>
	struct RemoveConst<const ETK_TYPE> {
		typedef ETK_TYPE type;
	};
	
	template<class ETK_TYPE>
	struct RemoveVolatile {
		typedef ETK_TYPE type;
	};
	template<class ETK_TYPE>
	struct RemoveVolatile<volatile ETK_TYPE> {
		typedef ETK_TYPE type;
	};
	
	template<class ETK_TYPE>
	struct RemoveConstVolatile {
		typedef typename etk::RemoveVolatile<typename etk::RemoveConst<ETK_TYPE>::type>::type type;
	};
	
	template<class ETK_TYPE>
	struct IsVoid :
	  etk::IsSame<void, typename etk::RemoveConstVolatile<ETK_TYPE>::type> {
		
	};
	
	template<typename ETK_TYPE>
	struct IsEnum:
	  public etk::IntegralConstant<bool, __is_enum(ETK_TYPE)> {
		
	};
	
	template<typename ETK_TYPE>
	struct IsUnion:
	  public etk::IntegralConstant<bool, __is_union(ETK_TYPE)> {
		
	};
	
	template<typename ETK_TYPE>
	struct IsClass:
	  public etk::IntegralConstant<bool, __is_class(ETK_TYPE)> {
		
	};
	
	template<typename ETK_TYPE, typename ETK_TYPE_DERIVED>
	struct IsBaseOf:
	  public etk::IntegralConstant<bool, __is_base_of(ETK_TYPE, ETK_TYPE_DERIVED)> {
		
	};
	
	template<typename>
	struct IsFunction;
	
	template<typename>
	struct IsFunction :
	  public etk::typeFalse {
		
	};
	
	template<typename ETK_TYPE_RETURN, typename... ETK_TYPE_ARGS>
	struct IsFunction<ETK_TYPE_RETURN(ETK_TYPE_ARGS...)>:
	  public etk::typeTrue {
		
	};
	
	template<typename ETK_TYPE_RETURN, typename... ETK_TYPE_ARGS>
	struct IsFunction<ETK_TYPE_RETURN(ETK_TYPE_ARGS...)&>:
	  public etk::typeTrue {
		
	};
	
	template<typename ETK_TYPE_RETURN, typename... ETK_TYPE_ARGS>
	struct IsFunction<ETK_TYPE_RETURN(ETK_TYPE_ARGS...)&&>:
	  public etk::typeTrue {
		
	};
	
	template<typename ETK_TYPE_RETURN, typename... ETK_TYPE_ARGS>
	struct IsFunction<ETK_TYPE_RETURN(ETK_TYPE_ARGS...) const>:
	  public etk::typeTrue {
		
	};
	
	template<typename ETK_TYPE_RETURN, typename... ETK_TYPE_ARGS>
	struct IsFunction<ETK_TYPE_RETURN(ETK_TYPE_ARGS...) const &>:
	  public etk::typeTrue {
		
	};
	
	template<typename ETK_TYPE_RETURN, typename... ETK_TYPE_ARGS>
	struct IsFunction<ETK_TYPE_RETURN(ETK_TYPE_ARGS...) const &&>:
	  public etk::typeTrue {
		
	};
}
