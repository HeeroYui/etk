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
	
	#define DEFINE_METHOD_CHECKER(RETURN_TYPE, METHOD_NAME, PARAMETERS) \
		template<typename ETK_TYPE> \
		struct Is_ ## METHOD_NAME ## _MemberFunctionExists { \
			private: \
				typedef char True; \
				typedef char (&False)[2]; \
				template<typename U, RETURN_TYPE (U::*)PARAMETERS = &U::METHOD_NAME> \
				struct Checker { \
				    typedef True Type; \
				}; \
				template<typename U> \
				static typename Checker<U>::Type Tester(const U*); \
				static False Tester(...); \
			public: \
				enum { value = (sizeof(Tester(static_cast<const ETK_TYPE*>(0))) == sizeof(True)) }; \
		} \
	// Use example:
	// Is_swap_MemberFunctionExists<T>::value
	DEFINE_METHOD_CHECKER(void, swap, (ETK_TYPE&));
	class String;
	DEFINE_METHOD_CHECKER(etk::String, toString, ());
	
	/*
	#if 0
	template<typename T>
	struct hasEtkStreamExporter {
		typedef char yes[1];
		typedef char no[2];
		template<typename U> static yes& test( U& );
		template<typename U> static no& test(...);
		
		static etk::Stream &s;
		static T const &t;
		
		static bool const value = sizeof( test( s << t ) ) == sizeof( yes ); // line 48
	};
	#else
	namespace hasEtkStreamExporterImpl {
		typedef char no;
		typedef char yes[2];
		struct AnyType {
			template<typename ETK_TYPE> AnyType(const ETK_TYPE&);
		};
		no operator<<( etk::Stream&, const AnyType& );
		yes& test( etk::Stream& );
		no test( no );
		template<typename ETK_TYPE>
		struct hasEtkStreamExporter {
			static etk::Stream& sss;
			static const ETK_TYPE& ttt;
			static bool const value = sizeof( test(sss << ttt) ) == sizeof( yes );
		};
	}
	
	template<typename ETK_TYPE>
	struct hasEtkStreamExporter:
		etk::hasEtkStreamExporterImpl::hasEtkStreamExporter<ETK_TYPE> {
	};
	#endif
	#if 1
	template <typename T>
	class hasMemberToString {
		typedef char one;
		typedef long two;
		template <typename C> static one test( decltype(T::toString()) );
		template <typename C> static two test(...);
	public:
		enum { value = sizeof(test<T>(0)) == sizeof(char) };
	};
	#else
	namespace hasMemberToStringImpl {
		typedef char no;
		typedef char yes[2];
		struct AnyType {
			template<typename ETK_TYPE> AnyType(const ETK_TYPE&);
		};
		no operator<<( etk::Stream&, const AnyType& );
		yes& test( etk::Stream& );
		no test( no );
		template<typename ETK_TYPE>
		struct hasMemberToString {
			static etk::Stream& sss;
			static const ETK_TYPE& ttt;
			static bool const value = sizeof( test(sss << ttt) ) == sizeof( yes );
		};
	}
	
	template<typename ETK_TYPE>
	struct hasMemberToString:
		etk::hasMemberToStringImpl::hasMemberToString<ETK_TYPE> {
	};
	#endif
	*/
}
