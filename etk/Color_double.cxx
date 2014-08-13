
template<> const float Color<double, 1>::defaultAlpha(1.0);
template<> const float Color<double, 2>::defaultAlpha(1.0);
template<> const float Color<double, 3>::defaultAlpha(1.0);
template<> const float Color<double, 4>::defaultAlpha(1.0);
template<> const Color<double, 1> Color<double, 1>::emptyColor(0.0);
template<> const Color<double, 2> Color<double, 2>::emptyColor(0.0,0.0);
template<> const Color<double, 3> Color<double, 3>::emptyColor(0.0,0.0,0.0);
template<> const Color<double, 4> Color<double, 4>::emptyColor(0.0,0.0,0.0,1.0);

// this work ...
template<> template<> Color<double,1>::Color(const Color<uint8_t, 1>& _obj) {
	m_element[0] = (double)_obj.r() * 0.003921569;
}
template<> template<> Color<double,2>::Color(const Color<uint8_t, 1>& _obj) {
	m_element[0] = (double)_obj.r() * 0.003921569;
	m_element[1] = 0;
}
template<> template<> Color<double,3>::Color(const Color<uint8_t, 1>& _obj) {
	m_element[0] = (double)_obj.r() * 0.003921569;
	m_element[1] = 0;
	m_element[2] = 0;
}
template<> template<> Color<double,4>::Color(const Color<uint8_t, 1>& _obj) {
	m_element[0] = (double)_obj.r() * 0.003921569;
	m_element[1] = 0;
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<double,1>::Color(const Color<uint8_t, 2>& _obj) {
	m_element[0] = (double)_obj.r() * 0.003921569;
}
template<> template<> Color<double,2>::Color(const Color<uint8_t, 2>& _obj) {
	m_element[0] = (double)_obj.r() * 0.003921569;
	m_element[1] = (double)_obj.g() * 0.003921569;
}
template<> template<> Color<double,3>::Color(const Color<uint8_t, 2>& _obj) {
	m_element[0] = (double)_obj.r() * 0.003921569;
	m_element[1] = (double)_obj.g() * 0.003921569;
	m_element[2] = 0;
}
template<> template<> Color<double,4>::Color(const Color<uint8_t, 2>& _obj) {
	m_element[0] = (double)_obj.r() * 0.003921569;
	m_element[1] = (double)_obj.g() * 0.003921569;
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<double,1>::Color(const Color<uint8_t, 3>& _obj) {
	m_element[0] = (double)_obj.r() * 0.003921569;
}
template<> template<> Color<double,2>::Color(const Color<uint8_t, 3>& _obj) {
	m_element[0] = (double)_obj.r() * 0.003921569;
	m_element[1] = (double)_obj.g() * 0.003921569;
}
template<> template<> Color<double,3>::Color(const Color<uint8_t, 3>& _obj) {
	m_element[0] = (double)_obj.r() * 0.003921569;
	m_element[1] = (double)_obj.g() * 0.003921569;
	m_element[2] = (double)_obj.b() * 0.003921569;
}
template<> template<> Color<double,4>::Color(const Color<uint8_t, 3>& _obj) {
	m_element[0] = (double)_obj.r() * 0.003921569;
	m_element[1] = (double)_obj.g() * 0.003921569;
	m_element[2] = (double)_obj.b() * 0.003921569;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<double,1>::Color(const Color<uint8_t, 4>& _obj) {
	m_element[0] = (double)_obj.r() * 0.003921569;
}
template<> template<> Color<double,2>::Color(const Color<uint8_t, 4>& _obj) {
	m_element[0] = (double)_obj.r() * 0.003921569;
	m_element[1] = (double)_obj.g() * 0.003921569;
}
template<> template<> Color<double,3>::Color(const Color<uint8_t, 4>& _obj) {
	m_element[0] = (double)_obj.r() * 0.003921569;
	m_element[1] = (double)_obj.g() * 0.003921569;
	m_element[2] = (double)_obj.b() * 0.003921569;
}
template<> template<> Color<double,4>::Color(const Color<uint8_t, 4>& _obj) {
	m_element[0] = (double)_obj.r() * 0.003921569;
	m_element[1] = (double)_obj.g() * 0.003921569;
	m_element[2] = (double)_obj.b() * 0.003921569;
	m_element[3] = (double)_obj.a() * 0.003921569;
}

// ===========================================================================================================

template<> template<> Color<double,1>::Color(const Color<uint16_t, 1>& _obj) {
	m_element[0] = (double)_obj.r() * 0.000015259;
}
template<> template<> Color<double,2>::Color(const Color<uint16_t, 1>& _obj) {
	m_element[0] = (double)_obj.r() * 0.000015259;
	m_element[1] = 0;
}
template<> template<> Color<double,3>::Color(const Color<uint16_t, 1>& _obj) {
	m_element[0] = (double)_obj.r() * 0.000015259;
	m_element[1] = 0;
	m_element[2] = 0;
}
template<> template<> Color<double,4>::Color(const Color<uint16_t, 1>& _obj) {
	m_element[0] = (double)_obj.r() * 0.000015259;
	m_element[1] = 0;
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<double,1>::Color(const Color<uint16_t, 2>& _obj) {
	m_element[0] = (double)_obj.r() * 0.000015259;
}
template<> template<> Color<double,2>::Color(const Color<uint16_t, 2>& _obj) {
	m_element[0] = (double)_obj.r() * 0.000015259;
	m_element[1] = (double)_obj.g() * 0.000015259;
}
template<> template<> Color<double,3>::Color(const Color<uint16_t, 2>& _obj) {
	m_element[0] = (double)_obj.r() * 0.000015259;
	m_element[1] = (double)_obj.g() * 0.000015259;
	m_element[2] = 0;
}
template<> template<> Color<double,4>::Color(const Color<uint16_t, 2>& _obj) {
	m_element[0] = (double)_obj.r() * 0.000015259;
	m_element[1] = (double)_obj.g() * 0.000015259;
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<double,1>::Color(const Color<uint16_t, 3>& _obj) {
	m_element[0] = (double)_obj.r() * 0.000015259;
}
template<> template<> Color<double,2>::Color(const Color<uint16_t, 3>& _obj) {
	m_element[0] = (double)_obj.r() * 0.000015259;
	m_element[1] = (double)_obj.g() * 0.000015259;
}
template<> template<> Color<double,3>::Color(const Color<uint16_t, 3>& _obj) {
	m_element[0] = (double)_obj.r() * 0.000015259;
	m_element[1] = (double)_obj.g() * 0.000015259;
	m_element[2] = (double)_obj.b() * 0.000015259;
}
template<> template<> Color<double,4>::Color(const Color<uint16_t, 3>& _obj) {
	m_element[0] = (double)_obj.r() * 0.000015259;
	m_element[1] = (double)_obj.g() * 0.000015259;
	m_element[2] = (double)_obj.b() * 0.000015259;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<double,1>::Color(const Color<uint16_t, 4>& _obj) {
	m_element[0] = (double)_obj.r() * 0.000015259;
}
template<> template<> Color<double,2>::Color(const Color<uint16_t, 4>& _obj) {
	m_element[0] = (double)_obj.r() * 0.000015259;
	m_element[1] = (double)_obj.g() * 0.000015259;
}
template<> template<> Color<double,3>::Color(const Color<uint16_t, 4>& _obj) {
	m_element[0] = (double)_obj.r() * 0.000015259;
	m_element[1] = (double)_obj.g() * 0.000015259;
	m_element[2] = (double)_obj.b() * 0.000015259;
}
template<> template<> Color<double,4>::Color(const Color<uint16_t, 4>& _obj) {
	m_element[0] = (double)_obj.r() * 0.000015259;
	m_element[1] = (double)_obj.g() * 0.000015259;
	m_element[2] = (double)_obj.b() * 0.000015259;
	m_element[3] = (double)_obj.a() * 0.000015259;
}

// ===========================================================================================================

template<> template<> Color<double,1>::Color(const Color<uint32_t, 1>& _obj) {
	m_element[0] = (double)_obj.r() / 4294967295.0;
}
template<> template<> Color<double,2>::Color(const Color<uint32_t, 1>& _obj) {
	m_element[0] = (double)_obj.r() / 4294967295.0;
	m_element[1] = 0;
}
template<> template<> Color<double,3>::Color(const Color<uint32_t, 1>& _obj) {
	m_element[0] = (double)_obj.r() / 4294967295.0;
	m_element[1] = 0;
	m_element[2] = 0;
}
template<> template<> Color<double,4>::Color(const Color<uint32_t, 1>& _obj) {
	m_element[0] = (double)_obj.r() / 4294967295.0;
	m_element[1] = 0;
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<double,1>::Color(const Color<uint32_t, 2>& _obj) {
	m_element[0] = (double)_obj.r() / 4294967295.0;
}
template<> template<> Color<double,2>::Color(const Color<uint32_t, 2>& _obj) {
	m_element[0] = (double)_obj.r() / 4294967295.0;
	m_element[1] = (double)_obj.g() / 4294967295.0;
}
template<> template<> Color<double,3>::Color(const Color<uint32_t, 2>& _obj) {
	m_element[0] = (double)_obj.r() / 4294967295.0;
	m_element[1] = (double)_obj.g() / 4294967295.0;
	m_element[2] = 0;
}
template<> template<> Color<double,4>::Color(const Color<uint32_t, 2>& _obj) {
	m_element[0] = (double)_obj.r() / 4294967295.0;
	m_element[1] = (double)_obj.g() / 4294967295.0;
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<double,1>::Color(const Color<uint32_t, 3>& _obj) {
	m_element[0] = (double)_obj.r() / 4294967295.0;
}
template<> template<> Color<double,2>::Color(const Color<uint32_t, 3>& _obj) {
	m_element[0] = (double)_obj.r() / 4294967295.0;
	m_element[1] = (double)_obj.g() / 4294967295.0;
}
template<> template<> Color<double,3>::Color(const Color<uint32_t, 3>& _obj) {
	m_element[0] = (double)_obj.r() / 4294967295.0;
	m_element[1] = (double)_obj.g() / 4294967295.0;
	m_element[2] = (double)_obj.b() / 4294967295.0;
}
template<> template<> Color<double,4>::Color(const Color<uint32_t, 3>& _obj) {
	m_element[0] = (double)_obj.r() / 4294967295.0;
	m_element[1] = (double)_obj.g() / 4294967295.0;
	m_element[2] = (double)_obj.b() / 4294967295.0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<double,1>::Color(const Color<uint32_t, 4>& _obj) {
	m_element[0] = (double)_obj.r() / 4294967295.0;
}
template<> template<> Color<double,2>::Color(const Color<uint32_t, 4>& _obj) {
	m_element[0] = (double)_obj.r() / 4294967295.0;
	m_element[1] = (double)_obj.g() / 4294967295.0;
}
template<> template<> Color<double,3>::Color(const Color<uint32_t, 4>& _obj) {
	m_element[0] = (double)_obj.r() / 4294967295.0;
	m_element[1] = (double)_obj.g() / 4294967295.0;
	m_element[2] = (double)_obj.b() / 4294967295.0;
}
template<> template<> Color<double,4>::Color(const Color<uint32_t, 4>& _obj) {
	m_element[0] = (double)_obj.r() / 4294967295.0;
	m_element[1] = (double)_obj.g() / 4294967295.0;
	m_element[2] = (double)_obj.b() / 4294967295.0;
	m_element[3] = (double)_obj.a() / 4294967295.0;
}

// ===========================================================================================================

template<> template<> Color<double,1>::Color(const Color<float, 1>& _obj) {
	m_element[0] = (double)_obj.r();
}
template<> template<> Color<double,2>::Color(const Color<float, 1>& _obj) {
	m_element[0] = (double)_obj.r();
	m_element[1] = 0;
}
template<> template<> Color<double,3>::Color(const Color<float, 1>& _obj) {
	m_element[0] = (double)_obj.r();
	m_element[1] = 0;
	m_element[2] = 0;
}
template<> template<> Color<double,4>::Color(const Color<float, 1>& _obj) {
	m_element[0] = (double)_obj.r();
	m_element[1] = 0;
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<double,1>::Color(const Color<float, 2>& _obj) {
	m_element[0] = (double)_obj.r();
}
template<> template<> Color<double,2>::Color(const Color<float, 2>& _obj) {
	m_element[0] = (double)_obj.r();
	m_element[1] = (double)_obj.g();
}
template<> template<> Color<double,3>::Color(const Color<float, 2>& _obj) {
	m_element[0] = (double)_obj.r();
	m_element[1] = (double)_obj.g();
	m_element[2] = 0;
}
template<> template<> Color<double,4>::Color(const Color<float, 2>& _obj) {
	m_element[0] = (double)_obj.r();
	m_element[1] = (double)_obj.g();
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<double,1>::Color(const Color<float, 3>& _obj) {
	m_element[0] = (double)_obj.r();
}
template<> template<> Color<double,2>::Color(const Color<float, 3>& _obj) {
	m_element[0] = (double)_obj.r();
	m_element[1] = (double)_obj.g();
}
template<> template<> Color<double,3>::Color(const Color<float, 3>& _obj) {
	m_element[0] = (double)_obj.r();
	m_element[1] = (double)_obj.g();
	m_element[2] = (double)_obj.b();
}
template<> template<> Color<double,4>::Color(const Color<float, 3>& _obj) {
	m_element[0] = (double)_obj.r();
	m_element[1] = (double)_obj.g();
	m_element[2] = (double)_obj.b();
	m_element[3] = defaultAlpha;
}
template<> template<> Color<double,1>::Color(const Color<float, 4>& _obj) {
	m_element[0] = (double)_obj.r();
}
template<> template<> Color<double,2>::Color(const Color<float, 4>& _obj) {
	m_element[0] = (double)_obj.r();
	m_element[1] = (double)_obj.g();
}
template<> template<> Color<double,3>::Color(const Color<float, 4>& _obj) {
	m_element[0] = (double)_obj.r();
	m_element[1] = (double)_obj.g();
	m_element[2] = (double)_obj.b();
}
template<> template<> Color<double,4>::Color(const Color<float, 4>& _obj) {
	m_element[0] = (double)_obj.r();
	m_element[1] = (double)_obj.g();
	m_element[2] = (double)_obj.b();
	m_element[3] = (double)_obj.a();
}

// ===========================================================================================================

template<> template<> Color<double,1>::Color(const Color<double, 1>& _obj) {
	m_element[0] = _obj.r();
}
template<> template<> Color<double,2>::Color(const Color<double, 1>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = 0;
}
template<> template<> Color<double,3>::Color(const Color<double, 1>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = 0;
	m_element[2] = 0;
}
template<> template<> Color<double,4>::Color(const Color<double, 1>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = 0;
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<double,1>::Color(const Color<double, 2>& _obj) {
	m_element[0] = _obj.r();
}
template<> template<> Color<double,2>::Color(const Color<double, 2>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
}
template<> template<> Color<double,3>::Color(const Color<double, 2>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
	m_element[2] = 0;
}
template<> template<> Color<double,4>::Color(const Color<double, 2>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<double,1>::Color(const Color<double, 3>& _obj) {
	m_element[0] = _obj.r();
}
template<> template<> Color<double,2>::Color(const Color<double, 3>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
}
template<> template<> Color<double,3>::Color(const Color<double, 3>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
	m_element[2] = _obj.b();
}
template<> template<> Color<double,4>::Color(const Color<double, 3>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
	m_element[2] = _obj.b();
	m_element[3] = defaultAlpha;
}
template<> template<> Color<double,1>::Color(const Color<double, 4>& _obj) {
	m_element[0] = _obj.r();
}
template<> template<> Color<double,2>::Color(const Color<double, 4>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
}
template<> template<> Color<double,3>::Color(const Color<double, 4>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
	m_element[2] = _obj.b();
}
template<> template<> Color<double,4>::Color(const Color<double, 4>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
	m_element[2] = _obj.b();
	m_element[3] = _obj.a();
}

// ===========================================================================================================

/*
template<> std::string to_string<Color<double, 1>>(const Color<double, 1>& _val) {
	return _val.getString();
}
template<> std::u32string to_u32string<Color<double, 1>>(const Color<double, 1>& _val) {
	return to_u32string(_val.getString());
}

template<> bool from_string<Color<double, 1>>(Color<double, 1>& _variableRet, const std::u32string& _value) {
	_variableRet = Color<double, 1>(to_string(_value));
	return true;
}
template<> bool from_string<Color<double, 1>>(Color<double, 1>& _variableRet, const std::string& _value) {
	_variableRet = Color<double, 1>(_value);
	return true;
}




template<> std::string to_string<Color<double, 2>>(const Color<double, 2>& _val) {
	return _val.getString();
}
template<> std::u32string to_u32string<Color<double, 2>>(const Color<double, 2>& _val) {
	return to_u32string(_val.getString());
}

template<> bool from_string<Color<double, 2>>(Color<double, 2>& _variableRet, const std::u32string& _value) {
	_variableRet = Color<double, 2>(to_string(_value));
	return true;
}
template<> bool from_string<Color<double, 2>>(Color<double, 2>& _variableRet, const std::string& _value) {
	_variableRet = Color<double, 2>(_value);
	return true;
}




template<> std::string to_string<Color<double, 3>>(const Color<double, 3>& _val) {
	return _val.getString();
}
template<> std::u32string to_u32string<Color<double, 3>>(const Color<double, 3>& _val) {
	return to_u32string(_val.getString());
}

template<> bool from_string<Color<double, 3>>(Color<double, 3>& _variableRet, const std::u32string& _value) {
	_variableRet = Color<double, 3>(to_string(_value));
	return true;
}
template<> bool from_string<Color<double, 3>>(Color<double, 3>& _variableRet, const std::string& _value) {
	_variableRet = Color<double, 3>(_value);
	return true;
}



template<> std::string to_string<Color<double, 4>>(const Color<double, 4>& _val) {
	return _val.getString();
}
template<> std::u32string to_u32string<Color<double, 4>>(const Color<double, 4>& _val) {
	return to_u32string(_val.getString());
}

template<> bool from_string<Color<double, 4>>(Color<double, 4>& _variableRet, const std::u32string& _value) {
	_variableRet = Color<double, 4>(to_string(_value));
	return true;
}
template<> bool from_string<Color<double, 4>>(Color<double, 4>& _variableRet, const std::string& _value) {
	_variableRet = Color<double, 4>(_value);
	return true;
}
*/
