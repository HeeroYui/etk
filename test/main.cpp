/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <etk/types.h>
#include <etk/debug.h>
#include <vector>
#include <string>
#include <etk/Hash.h>
#include <etk/os/FSNode.h>
#include <etk/archive/Archive.h>
#include <etk/log.h>
#include <etk/Color.h>
#include <etk/RegExp.h>
#include <etk/stdTools.h>
#include <string>
#include <regex>

#undef __class__
#define __class__	"etktest"

void testHash() {
	TK_INFO("==> Start test of Hach table");
	etk::Hash<std::string> testData;
	testData.add("TEST", "testData");
	testData.add("TEST", "testData333");
	testData.add("TEST2", "22222222222222222");
	testData.add("TEST4", "4444444444444444444");
	testData.add("TEST3", "3333333333");
	testData.add("TEST1", "11111111111");
	testData.add("TEST55", "555555555555555((((5555");
	TK_INFO(" count =" << testData.size());
	for (int32_t iii=0; iii< testData.size(); iii++) {
		TK_INFO(" id=" << iii << " key='" << testData.getKey(iii) << "' val='" << testData.getValue(iii) << "'");
	}
	TK_INFO(" direct acces at the key  key='TEST4' val='" << testData["TEST4"] << "'");
	TK_INFO("==> End test of Hach table");
}

void testFSNode() {
	TK_INFO("==> Start test of FSNode");
	std::string fileName("USERDATA:myFileTest.txt");
	etk::FSNode myNodeTest1(fileName);
	TK_INFO("********************************************");
	TK_INFO("** Filename=\"" << fileName << "\"");
	TK_INFO("********************************************");
	TK_INFO("      GetNameFolder()      ='" << myNodeTest1.getNameFolder() << "'");
	TK_INFO("      GetName()            ='" << myNodeTest1.getName() << "'");
	TK_INFO("      GetNameFile()        ='" << myNodeTest1.getNameFile() << "'");
	TK_INFO("      GetRelativeFolder()  ='" << myNodeTest1.getRelativeFolder() << "'");
	TK_INFO("      getFileSystemName()  ='" << myNodeTest1.getFileSystemName() << "'");
	TK_INFO("      exist                =" << myNodeTest1.exist());
	if (true==myNodeTest1.exist()) {
		TK_ERROR(" ==> remove the file ==> bad for the test");
	} else {
		TK_INFO("      Display time when file does not exist :");
		TK_INFO("          TimeCreatedString()  ='" << myNodeTest1.timeCreatedString() << "'");
		TK_INFO("          TimeModifiedString() ='" << myNodeTest1.timeModifiedString() << "'");
		TK_INFO("          TimeAccessedString() ='" << myNodeTest1.timeAccessedString() << "'");
	}
	myNodeTest1.touch();
	if (false==myNodeTest1.exist()) {
		TK_ERROR(" ==> Error, can not create the file ....");
	} else {
		TK_INFO("      Display time when file does exist :");
		TK_INFO("          TimeCreatedString()  ='" << myNodeTest1.timeCreatedString() << "'");
		TK_INFO("          TimeModifiedString() ='" << myNodeTest1.timeModifiedString() << "'");
		TK_INFO("          TimeAccessedString() ='" << myNodeTest1.timeAccessedString() << "'");
	}
	etk::FSNode myNodeTest2(fileName);
	TK_INFO("********************************************");
	TK_INFO("** Filename2=\"" << myNodeTest2<< "\"");
	TK_INFO("********************************************");
	TK_INFO("      GetNameFolder()      ='" << myNodeTest2.getNameFolder() << "'");
	TK_INFO("      GetName()            ='" << myNodeTest2.getName() << "'");
	TK_INFO("      GetNameFile()        ='" << myNodeTest2.getNameFile() << "'");
	TK_INFO("      GetRelativeFolder()  ='" << myNodeTest2.getRelativeFolder() << "'");
	TK_INFO("      getFileSystemName()  ='" << myNodeTest2.getFileSystemName() << "'");
	TK_INFO("      exist                =" << myNodeTest2.exist());
	if (false==myNodeTest1.exist()) {
		TK_ERROR(" ==> Error, can not create the file ....");
	} else {
		TK_INFO("      Display time when file does exist :");
		TK_INFO("          TimeCreatedString()  ='" << myNodeTest2.timeCreatedString() << "'");
		TK_INFO("          TimeModifiedString() ='" << myNodeTest2.timeModifiedString() << "'");
		TK_INFO("          TimeAccessedString() ='" << myNodeTest2.timeAccessedString() << "'");
	}
	// Try remove the file : 
	myNodeTest1.remove();
	if (true==myNodeTest1.exist()) {
		TK_ERROR(" ==> The file might be removed ==> but it is not the case ...");
	} else {
		TK_INFO(" ==> The file is removed");
	}
	TK_INFO("********************************************");
	TK_INFO("==> Stop test of FSNode");
}


void testArchive() {
	TK_INFO("==> Start test of archive");
	etk::Archive* tmpArchive = etk::Archive::load("testzip.zip");
	tmpArchive->display();
	
	TK_INFO("==> End test of archive");
}

/*
void testDimension() {
	TK_INFO("==> test of Dimension (START)");
	
	ewol::Dimension myDimention(vec2(5,5), ewol::Dimension::Centimeter);
	TK_INFO("    set dimension at : " << myDimention);
	TK_INFO("    set dimension at : " << myDimention.GetCentimeter() << " cm");
	TK_INFO("    set dimension at : " << myDimention.GetMillimeter() << " mm");
	TK_INFO("    set dimension at : " << myDimention.GetKilometer() << " km");
	TK_INFO("    set dimension at : " << myDimention.GetMeter() << " m");
	TK_INFO("    set dimension at : " << myDimention.GetInch() << " Inch");
	TK_INFO("    set dimension at : " << myDimention.GetFoot() << " ft");
	TK_INFO("    set dimension at : " << myDimention.GetPourcent() << " %");
	TK_INFO("    set dimension at : " << myDimention.GetPixel() << " px");
	
	TK_INFO("==> test of Dimension (STOP)");
	exit(0);
}
*/

void testColor() {
	TK_INFO("==> test of COLOR (START)");
	etk::Color<uint8_t, 4> colorRGBA8(0x52,0x0F, 0x65, 0x44);
	etk::Color<uint16_t, 4> colorRGBA16(0x52,0x0F, 0x65, 0x44);
	etk::Color<uint32_t, 4> colorRGBA32(0x52,0x0F, 0x65, 0x44);
	etk::Color<float, 4> colorRGBAF(0.1,0.2, 0.8, 1.0);
	etk::Color<uint8_t, 3> colorRGB8(0x52,0x0F, 0x65);
	etk::Color<uint16_t, 3> colorRGB16(0x52,0x0F, 0x65);
	etk::Color<uint32_t, 3> colorRGB32(0x52,0x0F, 0x65);
	etk::Color<float, 3> colorRGBF(0.1,0.2, 0.8);
	etk::Color<uint8_t, 1> colorMono8(0x52);
	etk::Color<uint16_t, 1> colorMono16(0x52);
	etk::Color<uint32_t, 1> colorMono32(0x52);
	etk::Color<float, 1> colorMonoF(5200.22);
	etk::Color<double, 1> colorMonoD(520000.22);

	etk::Color<uint8_t, 4> colorRGBA8__("#520F6544");
	etk::Color<uint16_t, 4> colorRGBA16__("rgba[U16](0x52, 0x0F, 0x65, 0x44)");
	etk::Color<uint32_t, 4> colorRGBA32__("rgba[U32](0x52,0x0F, 0x65, 0x44)");
	etk::Color<float, 4> colorRGBAF__("rgba[FLOAT](0.1,0.2,0.8,1.0)");
	etk::Color<uint8_t, 3> colorRGB8__("rgba[U8](0x52,0x0F, 0x65)");
	etk::Color<uint16_t, 3> colorRGB16__("rgba[U16](0x52,0x0F, 0x65)");
	etk::Color<uint32_t, 3> colorRGB32__("rgba[U32](0x52,0x0F, 0x65)");
	etk::Color<float, 3> colorRGBF__("rgba[FLOAT](0.1,0.2, 0.8)");
	/*
	etk::Color<uint8_t, 1> colorMono8__("mono[U8](0x52)");
	etk::Color<uint16_t, 1> colorMono16__("mono[U16](0x52)");
	etk::Color<uint32_t, 1> colorMono32__("mono[U32](0x52)");
	etk::Color<float, 1> colorMonoF__("mono[FLOAT](5200.22)");
	etk::Color<double, 1> colorMonoD__("mono[DOUBLE](520000.22)");
	*/
	etk::Color<float, 4> colorRGBAf__(colorRGBA8);
	etk::Color<uint32_t, 2> colorXX332__(colorRGBA8);
	
	TK_INFO("Create a color : RGBA 8 : " << colorRGBA8);
	TK_INFO("Create a color : RGBA 8 : " << colorRGBAf__ << " (converted)");
	TK_INFO("Create a color : XX 32 : " << colorXX332__ << " (converted)");
	TK_INFO("Create a color : RGBA 16 : " << colorRGBA16);
	TK_INFO("Create a color : RGBA 32 : " << colorRGBA32);
	TK_INFO("Create a color : RGBA float : " << colorRGBAF);
	TK_INFO("Create a color : RGB 8 : " << colorRGB8);
	TK_INFO("Create a color : RGB 16 : " << colorRGB16);
	TK_INFO("Create a color : RGB 32 : " << colorRGB32);
	TK_INFO("Create a color : RGB float : " << colorRGBF);
	TK_INFO("Create a color : MONO 8 : " << colorMono8);
	TK_INFO("Create a color : MONO 16 : " << colorMono16);
	TK_INFO("Create a color : MONO 32 : " << colorMono32);
	TK_INFO("Create a color : MONO float : " << colorMonoF);
	TK_INFO("Create a color : MONO double : " << colorMonoD);
	TK_INFO("==> test of Color (STOP)");
}

void testRegExpSingle(const std::string& _expression, const std::string& _search) {
	etk::RegExp<std::string> expression(_expression);
	TK_INFO("Parse RegEx: " << expression.getRegExDecorated());
	TK_INFO("         IN: " << etk::regexp::autoStr(_search));
	if (expression.parse(_search, 0, _search.size()) == true) {
		TK_INFO("    match [" << expression.start() << ".." << expression.stop() << "] ");
		TK_INFO("        ==> '" << etk::regexp::autoStr(std::string(_search, expression.start(), expression.stop() - expression.start())) << "'");
	}
}


void testRegExp() {
	std::string data;
	//std::string data = " a /* plop */ \n int eee = 22; // error value \nint main(void) {\n return 0;\n}\n";
	//std::string data = "alpha /* plop */ test";
	//std::string data = "pp \n // qdfqdfsdf \nde";
	//testRegExpSingle("/\\*.*\\*/", data);
	//testRegExpSingle("//.*$", data);
	//testRegExpSingle("/\\*.*", data);
	//testRegExpSingle("[a-z]", data);
	//std::string data = "  eesd a lzzml plophzzzzzhhhhhrlkmlkml";
	//testRegExpSingle("a.*plop(z{2,3}|h+)+r", data);
	
	//std::string data = "pp \n# plop // qdfqdfsdf \nde";
	//std::string data = "pp \n# plop //\\\n qdfqdfsdf \nde";
	//std::string data = "p#\ne";
	//testRegExpSingle("#(\\\\\\\\|\\\\\\n|.)*$", data);
	//testRegExpSingle("#.*$", data);
	
	//std::string data = "p//TODO:\ndse";
	//std::string data = "p// TODO:\ndse";
	//std::string data = "p// TODO :\ndse";
	//std::string data = "p// TODO 	: sdfgsdfsd \ndse";
	//testRegExpSingle("//[ \\t]*TODO[ \\t]*:.*$", data);
	
	data = "abc  m_def ghi";
	data =  "	protected:\n"
			"		vec2 m_offset; \n";
	//testRegExpSingle("\\@m_[A-Za-z_0-9]*\\@", data);
	
	
	data = " * @param[in] _mode Configuring mode.\n"
	"		 * @param[in] _time Time in second of the annimation display\n"
	"		 */\n"
	"		void setAnnimationTime(enum ";
	data = "virtual vec2 relativePosition(const vec2& _pos);";
	
	//testRegExpSingle("\\@(\\w|_)+[ \\t]*\\(", data);
	
	data = "include <ewol/Dimensio2n.h>\n"
		"#include <ewol/Dimension.h>\n"
		"'dfgd\'fg'\n"
		"\"dqf\\\"gsdfg\" // \"\n"
		"// TODO : sqdkfjsdldkqfj\n"
		"\n"
		"namespace ewol {\n"
		"	class Widget;\n"
		"	namespace widget {\n"
		"		class Manager;\n"
		"		class Windows;\n"
		"	};\n"
		"};\n"
		"#include <etk/types.h>\n";
	//testRegExpSingle("#(\\\\[\\\\\\n]|.)*$", data);
	
	
	data =  "	'dfgd\\'fg'  \n"
			"	vec2 m_offset; \n";
	//testRegExpSingle("'((\\\\[\\\\'])|.)*'", data);
	
	
	/*
	data = "ddfgdfgh";
	etk::RegExp<std::string> reg(".*");
	reg.setMaximize(true);
	
	TK_INFO("Parse RegEx : '" << reg.getRegExDecorated() << "'");
	if (reg.parse(data, 0, data.size()) == true) {
	//if (reg.processOneElement(data, 0, data.size()) == true) {
		TK_INFO("    match [" << reg.start() << ".." << reg.stop() << "] ");
		TK_INFO("        ==> '" << std::string(data, reg.start(), reg.stop()-reg.start()) << "'");
	}
	
	data = "plop \"\" sdfsdf s\"swdfsqd sdfgsdfg \" \" sdfsf";
	reg = etk::RegExp<std::string>("\"(\\\\[\\\\\"]|.)*\"");
	reg.setMaximize(false);
	TK_INFO("Parse RegEx : '" << reg.getRegExDecorated() << "'");
	if (reg.parse(data, 0, data.size()) == true) {
	//if (reg.processOneElement(data, 0, data.size()) == true) {
		TK_INFO("    match [" << reg.start() << ".." << reg.stop() << "] ");
		TK_INFO("        ==> '" << std::string(data, reg.start(), reg.stop()-reg.start()) << "'");
	}
	//TODO : good : "(\\+|[0-9])*" ==> really bad : "(+|[0-9])*"
	
	data = "void limit(const vec2& _origin, const vec2& _size);\n";
	reg = etk::RegExp<std::string>("\\@(\\w|_)+[ \\t]*\\(");
	reg.setMaximize(false);
	TK_INFO("Parse RegEx : '" << reg.getRegExDecorated() << "'");
	if (reg.parse(data, 0, data.size()) == true) {
	//if (reg.processOneElement(data, 0, data.size()) == true) {
		TK_INFO("    match [" << reg.start() << ".." << reg.stop() << "] ");
		TK_INFO("        ==> '" << std::string(data, reg.start(), reg.stop()-reg.start()) << "'");
	}
	data = "void limit const vec2& _origin, const vec2& _size);\n";
	if (reg.parse(data, 0, data.size()) == true) {
	//if (reg.processOneElement(data, 0, data.size()) == true) {
		TK_INFO("    match [" << reg.start() << ".." << reg.stop() << "] ");
		TK_INFO("        ==> '" << std::string(data, reg.start(), reg.stop()-reg.start()) << "'");
	}
	*/
	/*
	std::tr1::cmatch res;
	str = "<h2>Egg prices</h2>";
	std::tr1::regex rx("<h(.)>([^<]+)");
	std::tr1::regex_search(str.c_str(), res, rx);
	std::cout << res[1] << ". " << res[2] << "\n";
	*/
	{
		std::string lines[] = {"Roses are #ff0000",
		                       "violets are #0000ff",
		                       "all of my base are belong to you"};
		
		std::regex myRegex("#([a-f0-9]{6})");
		/*
		for (const auto &line : lines) {
			std::cout << line << ": " << std::regex_search(line, color_regex) << '\n';
		}
		*/
		
		std::smatch resultMatch;
		for (const auto &line : lines) {
			TK_DEBUG("in line : '" << line << "'");
			std::regex_search(line, resultMatch, myRegex);
			TK_DEBUG("    Find " << resultMatch.size() << " elements");
			for (size_t iii=0; iii<resultMatch.size(); ++iii) {
				int32_t posStart = std::distance(line.begin(), resultMatch[iii].first);
				int32_t posStop = std::distance(line.begin(), resultMatch[iii].second);
				TK_DEBUG("          [" << iii << "] " << *resultMatch[iii].first);
				TK_DEBUG("          [" << iii << "] " << *resultMatch[iii].second);
				TK_DEBUG("          [" << iii << "] " << std::string(line, posStart, posStop-posStart));
				/*
				std::ssub_match sub_match = color_match[i];
				std::string sub_match_str = sub_match.str();
				*/
			}
		}
	}
	
	{
		const std::string myData = "void limit(const vec2& _origin, const vec2& _size);\n plop(sf)";
		std::regex myRegex("\\b(\\w|_)+[ \\t]*\\(");
		
		std::smatch resultMatch;
		TK_DEBUG("in line : '" << myData << "'");
		std::regex_search(myData, resultMatch, myRegex);
		TK_DEBUG("    Find " << resultMatch.size() << " elements");
		for (size_t iii=0; iii<resultMatch.size(); ++iii) {
			int32_t posStart = std::distance(myData.begin(), resultMatch[iii].first);
			int32_t posStop = std::distance(myData.begin(), resultMatch[iii].second);
			TK_DEBUG("          [" << iii << "] " << *resultMatch[iii].first);
			TK_DEBUG("          [" << iii << "] " << *resultMatch[iii].second);
			TK_DEBUG("          [" << iii << "] " << std::string(myData, posStart, posStop-posStart));
			
		}
		
	}
	
	{
		const std::u32string data = utf8::convertUnicode("kjhkjhk");
		const std::u32string data2(U"kjhkjhk");
		const std::string data3("kjhkjhk");
		const char32_t data5[] = U"kjhkjhk";
		//std::basic_regex<char32_t, std::u32string> regexp(data2);
		//std::basic_regex<char32_t> regexp((const char32_t*)data2.c_str());
		std::basic_regex<char32_t> regexp2(data5);
	}
}
// http://en.cppreference.com/w/cpp/regex/regex_traits/lookup_classname
namespace std {
	// specify char32_t traits
	/**
	 * @brief Describes aspects of a regular expression.
	 *
	 * A regular expression traits class that satisfies the requirements of
	 * section [28.7].
	 *
	 * The class %regex is paramete	rized around a set of related types and
	 * functions used to complete the definition of its semantics.  This class
	 * satisfies the requirements of such a traits class.
	 */
	template<> struct regex_traits<char32_t> {
		public:
			typedef _Ch_type char32_t;
			typedef std::basic_string<char32_t> string_type;
			typedef std::locale locale_type;
		private:
			struct _RegexMask {
				typedef typename std::ctype<char32_t>::mask _BaseType;
				_BaseType _M_base;
				unsigned char _M_extended;
				static constexpr unsigned char _S_under = 1 << 0;
				// FIXME: _S_blank should be removed in the future,
				// when locale's complete.
				static constexpr unsigned char _S_blank = 1 << 1;
				static constexpr unsigned char _S_valid_mask = 0x3;
				constexpr _RegexMask(_BaseType __base = 0, unsigned char __extended = 0) :
				  _M_base(__base), _M_extended(__extended) {
					
				}
				constexpr _RegexMask operator&(_RegexMask __other) const {
					return _RegexMask(_M_base & __other._M_base, _M_extended & __other._M_extended);
				}
				constexpr _RegexMask operator|(_RegexMask __other) const {
					return _RegexMask(_M_base | __other._M_base, _M_extended | __other._M_extended);
				}
				constexpr _RegexMask operator^(_RegexMask __other) const {
					return _RegexMask(_M_base ^ __other._M_base, _M_extended ^ __other._M_extended);
				}
				constexpr _RegexMask operator~() const {
					return _RegexMask(~_M_base, ~_M_extended);
				}
				_RegexMask& operator&=(_RegexMask __other) {
					return *this = (*this) & __other;
				}
				_RegexMask& operator|=(_RegexMask __other) {
					return *this = (*this) | __other;
				}
				_RegexMask& operator^=(_RegexMask __other) {
					return *this = (*this) ^ __other;
				}
				constexpr bool operator==(_RegexMask __other) const {
					return    (_M_extended & _S_valid_mask) == (__other._M_extended & _S_valid_mask)
					       && _M_base == __other._M_base;
				}
				constexpr bool operator!=(_RegexMask __other) const {
					return !((*this) == __other);
				}
			};
		public:
			typedef _RegexMask char_class_type;
		public:
			/**
			 * @brief Constructs a default traits object.
			 */
			regex_traits() {
				
			}
			/**
			 * @brief Gives the length of a C-style string starting at @p __p.
			 *
			 * @param __p a pointer to the start of a character sequence.
			 *
			 * @returns the number of characters between @p *__p and the first
			 * default-initialized value of type @p char32_t.  In other words, uses
			 * the C-string algorithm for determining the length of a sequence of
			 * characters.
			 */
			static std::size_t length(const char32_t* __p) {
				return string_type::traits_type::length(__p);
			}
			
			/**
			 * @brief Performs the identity translation.
			 *
			 * @param __c A character to the locale-specific character set.
			 *
			 * @returns __c.
			 */
			char32_t translate(char32_t __c) const {
				return __c;
			}
			
			/**
			 * @brief Translates a character into a case-insensitive equivalent.
			 *
			 * @param __c A character to the locale-specific character set.
			 *
			 * @returns the locale-specific lower-case equivalent of __c.
			 * @throws std::bad_cast if the imbued locale does not support the ctype
			 *		 facet.
			 */
			char32_t translate_nocase(char32_t __c) const {
				typedef std::ctype<char32_t> __ctype_type;
				const __ctype_type& __fctyp(use_facet<__ctype_type>(_M_locale));
				return __fctyp.tolower(__c);
			}
			
			/**
			 * @brief Gets a sort key for a character sequence.
			 *
			 * @param __first beginning of the character sequence.
			 * @param __last  one-past-the-end of the character sequence.
			 *
			 * Returns a sort key for the character sequence designated by the
			 * iterator range [F1, F2) such that if the character sequence [G1, G2)
			 * sorts before the character sequence [H1, H2) then
			 * v.transform(G1, G2) < v.transform(H1, H2).
			 *
			 * What this really does is provide a more efficient way to compare a
			 * string to multiple other strings in locales with fancy collation
			 * rules and equivalence classes.
			 *
			 * @returns a locale-specific sort key equivalent to the input range.
			 *
			 * @throws std::bad_cast if the current locale does not have a collate
			 *         facet.
			 */
			template<typename _Fwd_iter> string_type transform(_Fwd_iter __first, _Fwd_iter __last) const {
				typedef std::collate<char32_t> __collate_type;
				const __collate_type& __fclt(use_facet<__collate_type>(_M_locale));
				string_type __s(__first, __last);
				return __fclt.transform(__s.data(), __s.data() + __s.size());
			}
			
			/**
			 * @brief Gets a sort key for a character sequence, independent of case.
			 *
			 * @param __first beginning of the character sequence.
			 * @param __last  one-past-the-end of the character sequence.
			 *
			 * Effects: if typeid(use_facet<collate<_Ch_type> >) ==
			 * typeid(collate_byname<_Ch_type>) and the form of the sort key
			 * returned by collate_byname<_Ch_type>::transform(__first, __last)
			 * is known and can be converted into a primary sort key
			 * then returns that key, otherwise returns an empty string.
			 *
			 * @todo Implement this function correctly.
			 */
			template<typename _Fwd_iter> string_type transform_primary(_Fwd_iter __first, _Fwd_iter __last) const {
				// TODO : this is not entirely correct.
				// This function requires extra support from the platform.
				//
				// Read http://gcc.gnu.org/ml/libstdc++/2013-09/msg00117.html and
				// http://www.open-std.org/Jtc1/sc22/wg21/docs/papers/2003/n1429.htm
				// for details.
				typedef std::ctype<char32_t> __ctype_type;
				const __ctype_type& __fctyp(use_facet<__ctype_type>(_M_locale));
				std::vector<char32_t> __s(__first, __last);
				__fctyp.tolower(__s.data(), __s.data() + __s.size());
				return this->transform(__s.data(), __s.data() + __s.size());
			}
			
			/**
			 * @brief Gets a collation element by name.
			 *
			 * @param __first beginning of the collation element name.
			 * @param __last  one-past-the-end of the collation element name.
			 *
			 * @returns a sequence of one or more characters that represents the
			 * collating element consisting of the character sequence designated by
			 * the iterator range [__first, __last). Returns an empty string if the
			 * character sequence is not a valid collating element.
			 */
			template<typename _Fwd_iter> string_type lookup_collatename(_Fwd_iter __first, _Fwd_iter __last) const;
			
			/**
			 * @brief Maps one or more characters to a named character
			 *		classification.
			 *
			 * @param __first beginning of the character sequence.
			 * @param __last  one-past-the-end of the character sequence.
			 * @param __icase ignores the case of the classification name.
			 *
			 * @returns an unspecified value that represents the character
			 * classification named by the character sequence designated by
			 * the iterator range [__first, __last). If @p icase is true,
			 * the returned mask identifies the classification regardless of
			 * the case of the characters to be matched (for example,
			 * [[:lower:]] is the same as [[:alpha:]]), otherwise a
			 * case-dependent classification is returned.  The value
			 * returned shall be independent of the case of the characters
			 * in the character sequence. If the name is not recognized then
			 * returns a value that compares equal to 0.
			 *
			 * At least the following names (or their wide-character equivalent) are
			 * supported.
			 * - d
			 * - w
			 * - s
			 * - alnum
			 * - alpha
			 * - blank
			 * - cntrl
			 * - digit
			 * - graph
			 * - lower
			 * - print
			 * - punct
			 * - space
			 * - upper
			 * - xdigit
			 */
			template<typename _Fwd_iter> char_class_type lookup_classname(_Fwd_iter __first, _Fwd_iter __last, bool __icase = false) const;
			
			/**
			 * @brief Determines if @p c is a member of an identified class.
			 *
			 * @param __c a character.
			 * @param __f a class type (as returned from lookup_classname).
			 *
			 * @returns true if the character @p __c is a member of the classification
			 * represented by @p __f, false otherwise.
			 *
			 * @throws std::bad_cast if the current locale does not have a ctype
			 *		 facet.
			 */
			bool isctype(_Ch_type __c, char_class_type __f) const;
			
			/**
			 * @brief Converts a digit to an int.
			 *
			 * @param __ch	a character representing a digit.
			 * @param __radix the radix if the numeric conversion (limited to 8, 10,
			 *			  or 16).
			 *
			 * @returns the value represented by the digit __ch in base radix if the
			 * character __ch is a valid digit in base radix; otherwise returns -1.
			 */
			int value(_Ch_type __ch, int __radix) const;
			
			/**
			 * @brief Imbues the regex_traits object with a copy of a new locale.
			 *
			 * @param __loc A locale.
			 *
			 * @returns a copy of the previous locale in use by the regex_traits
			 *		  object.
			 *
			 * @note Calling imbue with a different locale than the one currently in
			 *	   use invalidates all cached data held by *this.
			 */
			locale_type imbue(locale_type __loc) {
				std::swap(_M_locale, __loc);
				return __loc;
			}
			
			/**
			 * @brief Gets a copy of the current locale in use by the regex_traits
			 * object.
			 */
			locale_type getloc() const {
				return _M_locale;
			}
		protected:
			locale_type _M_locale;
	};

};
void testRegExp2() {
	std::u32string lines[] = {U"Roses are #ff0000",
	                          U"violets are #0000ff",
	                          U"all of my base are belong to you"};
	
	std::basic_regex<char32_t> color_regex(U"a");//([a-f0-9]{2})([a-f0-9]{2})([a-f0-9]{2})");
	
	for (const auto &line : lines) {
		std::cout << "search : " << std::regex_search(line, color_regex) << '\n';
	}
	std::match_results<std::u32string::const_iterator> color_match;
	for (const auto &line : lines) {
		std::regex_search(line, color_match, color_regex);
		std::cout << "matches for \n";
		/*
		for (size_t i = 0; i < color_match.size(); ++i) {
			std::ssub_match sub_match = color_match[i];
			std::string sub_match_str = sub_match.str();
			std::cout << i << ": " << sub_match_str << '\n';
		}
		*/
	}
};



int main(int argc, const char *argv[]) {
	// the only one init for etk:
	etk::log::setLevel(etk::log::logLevelVerbose);
	etk::setArgZero(argv[0]);
	etk::initDefaultFolder("ewolApplNoName");
	
	//testHash();
	////testFSNode();
	////testDimension();
	////testArchive();
	//testColor();
	//testRegExp();
	testRegExp2();
	return 0;
}

