

namespace etk {
	#if __CPP_VERSION__ >= 2011
		template<> etk::String toString<etk::UString>(const etk::UString& _input) {
			etk::String out;
			for (size_t iii=0; iii<_input.size(); ++iii) {
				char output[10];
				u32char::convertUtf8(_input[iii], output);
				out += output;
			}
			return out;
		}
		template<> etk::String toString<char32_t>(const char32_t& _input) {
			etk::String out;
			char output[10];
			u32char::convertUtf8(_input, output);
			out += output;
			return out;
		}
	#endif
};

#if __CPP_VERSION__ >= 2011
	static etk::UString transform_toUString(const char* _input) {
		if (_input == nullptr) {
			return U"";
		}
		etk::UString out;
		char tmpData[20];
		int64_t pos = 0;
		int64_t inputLen = strlen(_input);
		while (pos < inputLen) {
			int32_t lenMax = inputLen - pos;
			//4 case
			if (    1<=lenMax
			     && 0x00 == (_input[pos+0] & 0x80) ) {
				tmpData[0] = _input[pos+0];
				tmpData[1] = '\0';
				pos += 1;
			} else if (    2<=lenMax
			            && 0xC0 == (_input[pos+0] & 0xE0)
			            && 0x80 == (_input[pos+1] & 0xC0) ) {
				tmpData[0] = _input[pos+0];
				tmpData[1] = _input[pos+1];
				tmpData[2] = '\0';
				pos += 2;
			} else if (    3<=lenMax
			            && 0xE0 == (_input[pos+0] & 0xF0)
			            && 0x80 == (_input[pos+1] & 0xC0)
			            && 0x80 == (_input[pos+2] & 0xC0)) {
				tmpData[0] = _input[pos+0];
				tmpData[1] = _input[pos+1];
				tmpData[2] = _input[pos+2];
				tmpData[3] = '\0';
				pos += 3;
			} else if (    4<=lenMax
			            && 0xF0 == (_input[pos+0] & 0xF8)
			            && 0x80 == (_input[pos+1] & 0xC0)
			            && 0x80 == (_input[pos+2] & 0xC0)
			            && 0x80 == (_input[pos+3] & 0xC0)) {
				tmpData[0] = _input[pos+0];
				tmpData[1] = _input[pos+1];
				tmpData[2] = _input[pos+2];
				tmpData[3] = _input[pos+3];
				tmpData[4] = '\0';
				pos += 4;
			} else {
				tmpData[0] = '\0';
				pos += 1;
			}
			out += utf8::convertChar32(tmpData);
		}
		return out;
	}
#endif
#if __CPP_VERSION__ >= 2011
	namespace etk {
		template<> etk::UString toUString<char*>(char* const & _input) {
			return transform_toUString(_input);
		}
		template<> etk::UString toUString<etk::String>(const etk::String& _input) {
			return transform_toUString(_input.c_str());
		}
		template<> etk::UString toUString<int8_t>(const int8_t& _val) {
			return etk::toUString(etk::toString(_val));
		};
		template<> etk::UString toUString<int16_t>(const int16_t& _val) {
			return etk::toUString(etk::toString(_val));
		};
		template<> etk::UString toUString<int32_t>(const int32_t& _val) {
			return etk::toUString(etk::toString(_val));
		};
		template<> etk::UString toUString<int64_t>(const int64_t& _val) {
			return etk::toUString(etk::toString(_val));
		};
		template<> etk::UString toUString<uint8_t>(const uint8_t& _val) {
			return etk::toUString(etk::toString(_val));
		};
		template<> etk::UString toUString<uint16_t>(const uint16_t& _val) {
			return etk::toUString(etk::toString(_val));
		};
		template<> etk::UString toUString<uint32_t>(const uint32_t& _val) {
			return etk::toUString(etk::toString(_val));
		};
		template<> etk::UString toUString<uint64_t>(const uint64_t& _val) {
			return etk::toUString(etk::toString(_val));
		};
		template<> etk::UString toUString<float>(const float& _val) {
			return etk::toUString(etk::toString(_val));
		};
		template<> etk::UString toUString<double>(const double& _val) {
			return etk::toUString(etk::toString(_val));
		};
		template<> etk::UString toUString<long double>(const long double& _val) {
			return etk::toUString(etk::toString(_val));
		};
		template<> etk::UString toUString<bool>(const bool& _val) {
			if (_val == true) {
				return U"true";
			}
			return U"false";
		}
	};
	
	bool etk::string_to_bool(const etk::UString& _str) {
		if(    true == compare_no_case(_str, U"true")
		    || true == compare_no_case(_str, U"enable")
		    || true == compare_no_case(_str, U"yes")
		    || _str == U"1") {
			return true;
		}
		return false;
	}
	
	double etk::string_to_double(const etk::UString& _str) {
		return etk::string_to_double(etk::toString(_str));
	}
	long double etk::string_to_long_double(const etk::UString& _str) {
		return etk::string_to_long_double(etk::toString(_str));
	}
	float etk::string_to_float(const etk::UString& _str) {
		return etk::string_to_float(etk::toString(_str));
	}
	int8_t etk::string_to_int8_t(const etk::UString& _str) {
		return etk::string_to_int8_t(etk::toString(_str));
	}
	int16_t etk::string_to_int16_t(const etk::UString& _str) {
		return etk::string_to_int16_t(etk::toString(_str));
	}
	int32_t etk::string_to_int32_t(const etk::UString& _str) {
		return etk::string_to_int32_t(etk::toString(_str));
	}
	int64_t etk::string_to_int64_t(const etk::UString& _str) {
		return etk::string_to_int64_t(etk::toString(_str));
	}
	uint8_t etk::string_to_uint8_t(const etk::UString& _str) {
		return etk::string_to_uint8_t(etk::toString(_str));
	}
	uint16_t etk::string_to_uint16_t(const etk::UString& _str) {
		return etk::string_to_uint16_t(etk::toString(_str));
	}
	uint32_t etk::string_to_uint32_t(const etk::UString& _str) {
		return etk::string_to_uint32_t(etk::toString(_str));
	}
	uint64_t etk::string_to_uint64_t(const etk::UString& _str) {
		return etk::string_to_uint64_t(etk::toString(_str));
	}
#endif

#if __CPP_VERSION__ >= 2011
	bool etk::compare_no_case(const etk::UString& _obj, const etk::UString& _val) {
		if (_val.size() != _obj.size()) {
			return false;
		}
		for(size_t iii=0; iii<_val.size(); ++iii) {
			if (std::tolower(_val[iii]) != std::tolower(_obj[iii])) {
				return false;
			}
		}
		return true;
	}
#endif


class DoubleChar {
	public:
		char32_t lower;
		char32_t upper;
};
DoubleChar conversionTable[] = {
#if __CPP_VERSION__ >= 2011
	{U'ç', U'Ç'},

	{U'á', U'Á'}, {U'à', U'À'}, {U'ä', U'Ä'}, {U'â', U'Â'}, {U'å', U'Å'}, {U'ã', U'Ã'},
	{U'é', U'É'}, {U'è', U'È'}, {U'ë', U'Ë'}, {U'ê', U'Ê'}, 
	{U'ú', U'Ú'}, {U'ù', U'Ù'}, {U'ü', U'Ü'}, {U'û', U'Û'},
	{U'í', U'Í'}, {U'ì', U'Ì'}, {U'ï', U'Ï'}, {U'î', U'Î'},
	{U'ó', U'Ó'}, {U'ò', U'Ò'}, {U'ö', U'Ö'}, {U'ô', U'Ô'}, {U'õ', U'Õ'},
	{U'ý', U'Ý'}, {U'ỳ', U'Ỳ'}, {U'ÿ', U'Ÿ'}, {U'ŷ', U'Ŷ'},

	{U'ñ', U'Ñ'}, {U'ǹ', U'Ǹ'},

	{U'ḧ', U'Ḧ'}, {U'ĥ', U'Ĥ'},

	{U'ẅ', U'Ẅ'}, {U'ŵ', U'Ŵ'}, {U'ẁ', U'Ẁ'},

	{U'ẍ', U'Ẍ'},

	{U'æ', U'Æ'},
	{U'ð', U'Ð'},
	{U'ø', U'Ø'}
#endif
};
size_t conversionTableSize = sizeof(conversionTable)/sizeof(DoubleChar);

static char32_t localToUpper(char32_t _input) {
	if (_input >= 'a' && _input <= 'z') {
		return _input + ((int)'A'-(int)'a');
	}
	for (size_t iii = 0; iii < conversionTableSize; ++iii) {
		if (conversionTable[iii].lower == _input) {
			return conversionTable[iii].upper;
		}
	}
	return _input;
}

static char32_t localToLower(char32_t _input) {
	if (_input >= 'A' && _input <= 'Z') {
		return _input + ((int)'a'-(int)'A');
	}
	for (size_t iii = 0; iii < conversionTableSize; ++iii) {
		if (conversionTable[iii].upper == _input) {
			return conversionTable[iii].lower;
		}
	}
	return _input;
}


#if __CPP_VERSION__ >= 2011
	etk::UString etk::tolower(etk::UString _obj) {
		for(size_t iii=0 ; iii<_obj.size() ; iii++) {
			_obj[iii] = localToLower(_obj[iii]);
		}
		return _obj;
	}
#endif

#if __CPP_VERSION__ >= 2011
	etk::UString etk::toupper(etk::UString _obj) {
		for(size_t iii=0 ; iii<_obj.size() ; iii++) {
			_obj[iii] = localToUpper(_obj[iii]);
		}
		return _obj;
	}
#endif


#if __CPP_VERSION__ >= 2011
	bool etk::end_with(const etk::UString& _obj, const etk::UString& _val, bool _caseSensitive) {
		if (_val.size() == 0) {
			return false;
		}
		if (_val.size() > _obj.size()) {
			return false;
		}
		if (true == _caseSensitive) {
			for( int64_t iii=_val.size()-1, jjj=_obj.size()-1;
			     iii>=0 && jjj>=0;
			     iii--, jjj--) {
				if (_obj[jjj] != _val[iii]) {
					return false;
				}
			}
			return true;
		}
		for( int64_t iii=_val.size()-1, jjj=_obj.size()-1;
		     iii>=0 && jjj>=0;
		     iii--, jjj--) {
			if (std::tolower(_val[iii]) != std::tolower(_obj[jjj])) {
				return false;
			}
		}
		return true;
	}
#endif

#if __CPP_VERSION__ >= 2011
	bool etk::start_with(const etk::UString& _obj, const etk::UString& _val, bool _caseSensitive) {
		if (_val.size() == 0) {
			return false;
		}
		if (_val.size() > _obj.size()) {
			return false;
		}
		if (_caseSensitive == true) {
			for( size_t iii = 0;
			     iii < _val.size();
			     iii++) {
				if (_obj[iii] != _val[iii]) {
					return false;
				}
			}
			return true;
		}
		for( size_t iii = 0;
		     iii < _val.size();
		     iii++) {
			if (std::tolower(_val[iii]) != std::tolower(_obj[iii])) {
				return false;
			}
		}
		return true;
	}
	
	etk::UString etk::replace(const etk::UString& _obj, char32_t _val, char32_t _replace) {
		etk::UString copy(_obj);
		for( size_t iii = 0;
		     iii < copy.size();
		     iii++) {
			if (copy[iii] == _val) {
				copy[iii] = _replace;
			}
		}
		return copy;
	}
#endif

#if __CPP_VERSION__ >= 2011
	etk::UString etk::extract_line(const etk::UString& _obj, int32_t _pos) {
		// search back : '\n'
		size_t startPos = _obj.rfind('\n', _pos);
		if ((int64_t)startPos == _pos) {
			startPos = 0;
		} else {
			startPos++;
		}
		// search forward : '\n'
		size_t stopPos = _pos;
		if (_obj[_pos] != '\n') {
			stopPos = _obj.find('\n', _pos);
			if ((int64_t)stopPos == _pos) {
				stopPos = _obj.size();
			}
		}
		if (startPos == etk::String::npos) {
			startPos = 0;
		} else if (startPos >= _obj.size() ) {
			return U"";
		}
		if (stopPos == etk::String::npos) {
			return U"";
		} else if (stopPos >= _obj.size() ) {
			stopPos = _obj.size();
		}
		return etk::UString(_obj, startPos, stopPos - startPos);
	}
#endif

#if __CPP_VERSION__ >= 2011
	etk::Vector<etk::UString> etk::split(const etk::UString& _input, char32_t _val) {
		etk::Vector<etk::UString> list;
		size_t lastStartPos = 0;
		for(size_t iii=0; iii<_input.size(); iii++) {
			if (_input[iii]==_val) {
				list.pushBack(etk::UString(_input, lastStartPos, iii - lastStartPos));
				lastStartPos = iii+1;
			}
		}
		if (lastStartPos<_input.size()) {
			list.pushBack(etk::UString(_input, lastStartPos));
		}
		return list;
	}
#endif



#if __CPP_VERSION__ >= 2011
	void etk::sort(etk::Vector<etk::UString *> &_list) {
		etk::Vector<etk::UString *> tmpList(_list);
		_list.clear();
		for(size_t iii=0; iii<tmpList.size(); iii++) {
			size_t findPos = 0;
			for(size_t jjj=0; jjj<_list.size(); jjj++) {
				//TK_DEBUG("compare : \""<<*tmpList[iii] << "\" and \"" << *m_listDirectory[jjj] << "\"");
				if (*tmpList[iii] > *_list[jjj]) {
					findPos = jjj+1;
				}
			}
			//TK_DEBUG("position="<<findPos);
			_list.insert(_list.begin()+findPos, tmpList[iii]);
		}
	}
#endif

namespace etk {
	#if __CPP_VERSION__ >= 2011
		template<> bool from_string<etk::UString>(etk::UString& _variableRet, const etk::String& _value) {
			_variableRet = etk::toUString(_value);
			return true;
		}
		template<> bool from_string<int8_t>(int8_t& _variableRet, const etk::UString& _value) {
			_variableRet = string_to_int8_t(_value);
			return true;
		}
		template<> bool from_string<int16_t>(int16_t& _variableRet, const etk::UString& _value) {
			_variableRet = string_to_int16_t(_value);
			return true;
		}
		template<> bool from_string<int32_t>(int32_t& _variableRet, const etk::UString& _value) {
			_variableRet = string_to_int32_t(_value);
			return true;
		}
		template<> bool from_string<int64_t>(int64_t& _variableRet, const etk::UString& _value) {
			_variableRet = string_to_int64_t(_value);
			return true;
		}
		template<> bool from_string<uint8_t>(uint8_t& _variableRet, const etk::UString& _value) {
			_variableRet = string_to_uint8_t(_value);
			return true;
		}
		template<> bool from_string<uint16_t>(uint16_t& _variableRet, const etk::UString& _value) {
			_variableRet = string_to_uint16_t(_value);
			return true;
		}
		template<> bool from_string<uint32_t>(uint32_t& _variableRet, const etk::UString& _value) {
			_variableRet = string_to_uint32_t(_value);
			return true;
		}
		template<> bool from_string<uint64_t>(uint64_t& _variableRet, const etk::UString& _value) {
			_variableRet = string_to_uint64_t(_value);
			return true;
		}
		template<> bool from_string<float>(float& _variableRet, const etk::UString& _value) {
			_variableRet = string_to_float(_value);
			return true;
		}
		template<> bool from_string<double>(double& _variableRet, const etk::UString& _value) {
			_variableRet = string_to_double(_value);
			return true;
		}
		template<> bool from_string<long double>(long double& _variableRet, const etk::UString& _value) {
			_variableRet = string_to_long_double(_value);
			return true;
		}
		template<> bool from_string<bool>(bool& _variableRet, const etk::UString& _value) {
			_variableRet = string_to_bool(_value);
			return true;
		}
	#endif
};


#if __CPP_VERSION__ >= 2011
	std::ostream& std::operator <<(std::ostream& _os, const etk::UString& _obj) {
		_os << etk::toString(_obj).c_str();
		return _os;
	}
	
	std::ostream& std::operator <<(std::ostream& _os, const etk::Vector<etk::UString>& _obj) {
		_os << "{";
		for (size_t iii=0; iii< _obj.size(); iii++) {
			if (iii>0) {
				_os << " ~ ";
			}
			_os << _obj[iii];
		}
		_os << "}";
		return _os;
	}
#endif

namespace std {
	std::ostream& operator <<(std::ostream& _os, const std::chrono::system_clock::time_point& _obj) {
		std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(_obj.time_since_epoch());
		int64_t totalSecond = ns.count()/1000000000;
		int64_t millisecond = (ns.count()%1000000000)/1000000;
		int64_t microsecond = (ns.count()%1000000)/1000;
		int64_t nanosecond = ns.count()%1000;
		//_os << totalSecond << "s " << millisecond << "ms " << microsecond << "�s " << nanosecond << "ns";
		int32_t second = totalSecond % 60;
		int32_t minute = (totalSecond/60)%60;
		int32_t hour = (totalSecond/3600)%24;
		int32_t day = (totalSecond/(24*3600))%365;
		int32_t year = totalSecond/(24*3600*365);
		_os << year << "y " << day << "d " << hour << "h" << minute << ":"<< second << "s " << millisecond << "ms " << microsecond << "µs " << nanosecond << "ns";
		return _os;
	}
	std::ostream& operator <<(std::ostream& _os, const std::chrono::steady_clock::time_point& _obj) {
		std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(_obj.time_since_epoch());
		int64_t totalSecond = ns.count()/1000000000;
		int64_t millisecond = (ns.count()%1000000000)/1000000;
		int64_t microsecond = (ns.count()%1000000)/1000;
		int64_t nanosecond = ns.count()%1000;
		//_os << totalSecond << "s " << millisecond << "ms " << microsecond << "�s " << nanosecond << "ns";
		int32_t second = totalSecond % 60;
		int32_t minute = (totalSecond/60)%60;
		int32_t hour = (totalSecond/3600)%24;
		int32_t day = (totalSecond/(24*3600))%365;
		int32_t year = totalSecond/(24*3600*365);
		_os << year << "y " << day << "d " << hour << "h" << minute << ":"<< second << "s " << millisecond << "ms " << microsecond << "�s " << nanosecond << "ns";
		return _os;
	}
}