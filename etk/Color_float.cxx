
template<> const float Color<float, 1>::defaultAlpha(1.0f);
template<> const float Color<float, 2>::defaultAlpha(1.0f);
template<> const float Color<float, 3>::defaultAlpha(1.0f);
template<> const float Color<float, 4>::defaultAlpha(1.0f);
template<> const Color<float, 1> Color<float, 1>::emptyColor(0.0f);
template<> const Color<float, 2> Color<float, 2>::emptyColor(0.0f,0.0f);
template<> const Color<float, 3> Color<float, 3>::emptyColor(0.0f,0.0f,0.0f);
template<> const Color<float, 4> Color<float, 4>::emptyColor(0.0f,0.0f,0.0f,1.0f);

// this work ...
template<> template<> Color<float,1>::Color(const Color<uint8_t, 1>& _obj) {
	m_element[0] = (float)_obj.r() * 0.003921569f;
}
template<> template<> Color<float,2>::Color(const Color<uint8_t, 1>& _obj) {
	m_element[0] = (float)_obj.r() * 0.003921569f;
	m_element[1] = 0;
}
template<> template<> Color<float,3>::Color(const Color<uint8_t, 1>& _obj) {
	m_element[0] = (float)_obj.r() * 0.003921569f;
	m_element[1] = 0;
	m_element[2] = 0;
}
template<> template<> Color<float,4>::Color(const Color<uint8_t, 1>& _obj) {
	m_element[0] = (float)_obj.r() * 0.003921569f;
	m_element[1] = 0;
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<float,1>::Color(const Color<uint8_t, 2>& _obj) {
	m_element[0] = (float)_obj.r() * 0.003921569f;
}
template<> template<> Color<float,2>::Color(const Color<uint8_t, 2>& _obj) {
	m_element[0] = (float)_obj.r() * 0.003921569f;
	m_element[1] = (float)_obj.g() * 0.003921569f;
}
template<> template<> Color<float,3>::Color(const Color<uint8_t, 2>& _obj) {
	m_element[0] = (float)_obj.r() * 0.003921569f;
	m_element[1] = (float)_obj.g() * 0.003921569f;
	m_element[2] = 0;
}
template<> template<> Color<float,4>::Color(const Color<uint8_t, 2>& _obj) {
	m_element[0] = (float)_obj.r() * 0.003921569f;
	m_element[1] = (float)_obj.g() * 0.003921569f;
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<float,1>::Color(const Color<uint8_t, 3>& _obj) {
	m_element[0] = (float)_obj.r() * 0.003921569f;
}
template<> template<> Color<float,2>::Color(const Color<uint8_t, 3>& _obj) {
	m_element[0] = (float)_obj.r() * 0.003921569f;
	m_element[1] = (float)_obj.g() * 0.003921569f;
}
template<> template<> Color<float,3>::Color(const Color<uint8_t, 3>& _obj) {
	m_element[0] = (float)_obj.r() * 0.003921569f;
	m_element[1] = (float)_obj.g() * 0.003921569f;
	m_element[2] = (float)_obj.b() * 0.003921569f;
}
template<> template<> Color<float,4>::Color(const Color<uint8_t, 3>& _obj) {
	m_element[0] = (float)_obj.r() * 0.003921569f;
	m_element[1] = (float)_obj.g() * 0.003921569f;
	m_element[2] = (float)_obj.b() * 0.003921569f;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<float,1>::Color(const Color<uint8_t, 4>& _obj) {
	m_element[0] = (float)_obj.r() * 0.003921569f;
}
template<> template<> Color<float,2>::Color(const Color<uint8_t, 4>& _obj) {
	m_element[0] = (float)_obj.r() * 0.003921569f;
	m_element[1] = (float)_obj.g() * 0.003921569f;
}
template<> template<> Color<float,3>::Color(const Color<uint8_t, 4>& _obj) {
	m_element[0] = (float)_obj.r() * 0.003921569f;
	m_element[1] = (float)_obj.g() * 0.003921569f;
	m_element[2] = (float)_obj.b() * 0.003921569f;
}
template<> template<> Color<float,4>::Color(const Color<uint8_t, 4>& _obj) {
	m_element[0] = (float)_obj.r() * 0.003921569f;
	m_element[1] = (float)_obj.g() * 0.003921569f;
	m_element[2] = (float)_obj.b() * 0.003921569f;
	m_element[3] = (float)_obj.a() * 0.003921569f;
}

// ===========================================================================================================

template<> template<> Color<float,1>::Color(const Color<uint16_t, 1>& _obj) {
	m_element[0] = (float)_obj.r() * 0.000015259f;
}
template<> template<> Color<float,2>::Color(const Color<uint16_t, 1>& _obj) {
	m_element[0] = (float)_obj.r() * 0.000015259f;
	m_element[1] = 0;
}
template<> template<> Color<float,3>::Color(const Color<uint16_t, 1>& _obj) {
	m_element[0] = (float)_obj.r() * 0.000015259f;
	m_element[1] = 0;
	m_element[2] = 0;
}
template<> template<> Color<float,4>::Color(const Color<uint16_t, 1>& _obj) {
	m_element[0] = (float)_obj.r() * 0.000015259f;
	m_element[1] = 0;
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<float,1>::Color(const Color<uint16_t, 2>& _obj) {
	m_element[0] = (float)_obj.r() * 0.000015259f;
}
template<> template<> Color<float,2>::Color(const Color<uint16_t, 2>& _obj) {
	m_element[0] = (float)_obj.r() * 0.000015259f;
	m_element[1] = (float)_obj.g() * 0.000015259f;
}
template<> template<> Color<float,3>::Color(const Color<uint16_t, 2>& _obj) {
	m_element[0] = (float)_obj.r() * 0.000015259f;
	m_element[1] = (float)_obj.g() * 0.000015259f;
	m_element[2] = 0;
}
template<> template<> Color<float,4>::Color(const Color<uint16_t, 2>& _obj) {
	m_element[0] = (float)_obj.r() * 0.000015259f;
	m_element[1] = (float)_obj.g() * 0.000015259f;
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<float,1>::Color(const Color<uint16_t, 3>& _obj) {
	m_element[0] = (float)_obj.r() * 0.000015259f;
}
template<> template<> Color<float,2>::Color(const Color<uint16_t, 3>& _obj) {
	m_element[0] = (float)_obj.r() * 0.000015259f;
	m_element[1] = (float)_obj.g() * 0.000015259f;
}
template<> template<> Color<float,3>::Color(const Color<uint16_t, 3>& _obj) {
	m_element[0] = (float)_obj.r() * 0.000015259f;
	m_element[1] = (float)_obj.g() * 0.000015259f;
	m_element[2] = (float)_obj.b() * 0.000015259f;
}
template<> template<> Color<float,4>::Color(const Color<uint16_t, 3>& _obj) {
	m_element[0] = (float)_obj.r() * 0.000015259f;
	m_element[1] = (float)_obj.g() * 0.000015259f;
	m_element[2] = (float)_obj.b() * 0.000015259f;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<float,1>::Color(const Color<uint16_t, 4>& _obj) {
	m_element[0] = (float)_obj.r() * 0.000015259f;
}
template<> template<> Color<float,2>::Color(const Color<uint16_t, 4>& _obj) {
	m_element[0] = (float)_obj.r() * 0.000015259f;
	m_element[1] = (float)_obj.g() * 0.000015259f;
}
template<> template<> Color<float,3>::Color(const Color<uint16_t, 4>& _obj) {
	m_element[0] = (float)_obj.r() * 0.000015259f;
	m_element[1] = (float)_obj.g() * 0.000015259f;
	m_element[2] = (float)_obj.b() * 0.000015259f;
}
template<> template<> Color<float,4>::Color(const Color<uint16_t, 4>& _obj) {
	m_element[0] = (float)_obj.r() * 0.000015259f;
	m_element[1] = (float)_obj.g() * 0.000015259f;
	m_element[2] = (float)_obj.b() * 0.000015259f;
	m_element[3] = (float)_obj.a() * 0.000015259f;
}

// ===========================================================================================================

template<> template<> Color<float,1>::Color(const Color<uint32_t, 1>& _obj) {
	m_element[0] = (float)_obj.r() / 4294967295.0f;
}
template<> template<> Color<float,2>::Color(const Color<uint32_t, 1>& _obj) {
	m_element[0] = (float)_obj.r() / 4294967295.0f;
	m_element[1] = 0;
}
template<> template<> Color<float,3>::Color(const Color<uint32_t, 1>& _obj) {
	m_element[0] = (float)_obj.r() / 4294967295.0f;
	m_element[1] = 0;
	m_element[2] = 0;
}
template<> template<> Color<float,4>::Color(const Color<uint32_t, 1>& _obj) {
	m_element[0] = (float)_obj.r() / 4294967295.0f;
	m_element[1] = 0;
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<float,1>::Color(const Color<uint32_t, 2>& _obj) {
	m_element[0] = (float)_obj.r() / 4294967295.0f;
}
template<> template<> Color<float,2>::Color(const Color<uint32_t, 2>& _obj) {
	m_element[0] = (float)_obj.r() / 4294967295.0f;
	m_element[1] = (float)_obj.g() / 4294967295.0f;
}
template<> template<> Color<float,3>::Color(const Color<uint32_t, 2>& _obj) {
	m_element[0] = (float)_obj.r() / 4294967295.0f;
	m_element[1] = (float)_obj.g() / 4294967295.0f;
	m_element[2] = 0;
}
template<> template<> Color<float,4>::Color(const Color<uint32_t, 2>& _obj) {
	m_element[0] = (float)_obj.r() / 4294967295.0f;
	m_element[1] = (float)_obj.g() / 4294967295.0f;
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<float,1>::Color(const Color<uint32_t, 3>& _obj) {
	m_element[0] = (float)_obj.r() / 4294967295.0f;
}
template<> template<> Color<float,2>::Color(const Color<uint32_t, 3>& _obj) {
	m_element[0] = (float)_obj.r() / 4294967295.0f;
	m_element[1] = (float)_obj.g() / 4294967295.0f;
}
template<> template<> Color<float,3>::Color(const Color<uint32_t, 3>& _obj) {
	m_element[0] = (float)_obj.r() / 4294967295.0f;
	m_element[1] = (float)_obj.g() / 4294967295.0f;
	m_element[2] = (float)_obj.b() / 4294967295.0f;
}
template<> template<> Color<float,4>::Color(const Color<uint32_t, 3>& _obj) {
	m_element[0] = (float)_obj.r() / 4294967295.0f;
	m_element[1] = (float)_obj.g() / 4294967295.0f;
	m_element[2] = (float)_obj.b() / 4294967295.0f;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<float,1>::Color(const Color<uint32_t, 4>& _obj) {
	m_element[0] = (float)_obj.r() / 4294967295.0f;
}
template<> template<> Color<float,2>::Color(const Color<uint32_t, 4>& _obj) {
	m_element[0] = (float)_obj.r() / 4294967295.0f;
	m_element[1] = (float)_obj.g() / 4294967295.0f;
}
template<> template<> Color<float,3>::Color(const Color<uint32_t, 4>& _obj) {
	m_element[0] = (float)_obj.r() / 4294967295.0f;
	m_element[1] = (float)_obj.g() / 4294967295.0f;
	m_element[2] = (float)_obj.b() / 4294967295.0f;
}
template<> template<> Color<float,4>::Color(const Color<uint32_t, 4>& _obj) {
	m_element[0] = (float)_obj.r() / 4294967295.0f;
	m_element[1] = (float)_obj.g() / 4294967295.0f;
	m_element[2] = (float)_obj.b() / 4294967295.0f;
	m_element[3] = (float)_obj.a() / 4294967295.0f;
}

// ===========================================================================================================

template<> template<> Color<float,1>::Color(const Color<float, 1>& _obj) {
	m_element[0] = _obj.r();
}
template<> template<> Color<float,2>::Color(const Color<float, 1>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = 0;
}
template<> template<> Color<float,3>::Color(const Color<float, 1>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = 0;
	m_element[2] = 0;
}
template<> template<> Color<float,4>::Color(const Color<float, 1>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = 0;
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<float,1>::Color(const Color<float, 2>& _obj) {
	m_element[0] = _obj.r();
}
template<> template<> Color<float,2>::Color(const Color<float, 2>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
}
template<> template<> Color<float,3>::Color(const Color<float, 2>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
	m_element[2] = 0;
}
template<> template<> Color<float,4>::Color(const Color<float, 2>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<float,1>::Color(const Color<float, 3>& _obj) {
	m_element[0] = _obj.r();
}
template<> template<> Color<float,2>::Color(const Color<float, 3>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
}
template<> template<> Color<float,3>::Color(const Color<float, 3>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
	m_element[2] = _obj.b();
}
template<> template<> Color<float,4>::Color(const Color<float, 3>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
	m_element[2] = _obj.b();
	m_element[3] = defaultAlpha;
}
template<> template<> Color<float,1>::Color(const Color<float, 4>& _obj) {
	m_element[0] = _obj.r();
}
template<> template<> Color<float,2>::Color(const Color<float, 4>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
}
template<> template<> Color<float,3>::Color(const Color<float, 4>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
	m_element[2] = _obj.b();
}
template<> template<> Color<float,4>::Color(const Color<float, 4>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
	m_element[2] = _obj.b();
	m_element[3] = _obj.a();
}

// ===========================================================================================================

template<> template<> Color<float,1>::Color(const Color<double, 1>& _obj) {
	m_element[0] = (float)_obj.r();
}
template<> template<> Color<float,2>::Color(const Color<double, 1>& _obj) {
	m_element[0] = (float)_obj.r();
	m_element[1] = 0;
}
template<> template<> Color<float,3>::Color(const Color<double, 1>& _obj) {
	m_element[0] = (float)_obj.r();
	m_element[1] = 0;
	m_element[2] = 0;
}
template<> template<> Color<float,4>::Color(const Color<double, 1>& _obj) {
	m_element[0] = (float)_obj.r();
	m_element[1] = 0;
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<float,1>::Color(const Color<double, 2>& _obj) {
	m_element[0] = (float)_obj.r();
}
template<> template<> Color<float,2>::Color(const Color<double, 2>& _obj) {
	m_element[0] = (float)_obj.r();
	m_element[1] = (float)_obj.g();
}
template<> template<> Color<float,3>::Color(const Color<double, 2>& _obj) {
	m_element[0] = (float)_obj.r();
	m_element[1] = (float)_obj.g();
	m_element[2] = 0;
}
template<> template<> Color<float,4>::Color(const Color<double, 2>& _obj) {
	m_element[0] = (float)_obj.r();
	m_element[1] = (float)_obj.g();
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<float,1>::Color(const Color<double, 3>& _obj) {
	m_element[0] = (float)_obj.r();
}
template<> template<> Color<float,2>::Color(const Color<double, 3>& _obj) {
	m_element[0] = (float)_obj.r();
	m_element[1] = (float)_obj.g();
}
template<> template<> Color<float,3>::Color(const Color<double, 3>& _obj) {
	m_element[0] = (float)_obj.r();
	m_element[1] = (float)_obj.g();
	m_element[2] = (float)_obj.b();
}
template<> template<> Color<float,4>::Color(const Color<double, 3>& _obj) {
	m_element[0] = (float)_obj.r();
	m_element[1] = (float)_obj.g();
	m_element[2] = (float)_obj.b();
	m_element[3] = defaultAlpha;
}
template<> template<> Color<float,1>::Color(const Color<double, 4>& _obj) {
	m_element[0] = (float)_obj.r();
}
template<> template<> Color<float,2>::Color(const Color<double, 4>& _obj) {
	m_element[0] = (float)_obj.r();
	m_element[1] = (float)_obj.g();
}
template<> template<> Color<float,3>::Color(const Color<double, 4>& _obj) {
	m_element[0] = (float)_obj.r();
	m_element[1] = (float)_obj.g();
	m_element[2] = (float)_obj.b();
}
template<> template<> Color<float,4>::Color(const Color<double, 4>& _obj) {
	m_element[0] = (float)_obj.r();
	m_element[1] = (float)_obj.g();
	m_element[2] = (float)_obj.b();
	m_element[3] = (float)_obj.a();
}


template<> std::string to_string<Color<float, 1>>(const Color<float, 1>& _val) {
	return _val.getString();
}
template<> std::u32string to_u32string<Color<float, 1>>(const Color<float, 1>& _val) {
	return to_u32string(_val.getString());
}

template<> bool from_string<Color<float, 1>>(Color<float, 1>& _variableRet, const std::u32string& _value) {
	_variableRet = Color<float, 1>(to_string(_value));
	return true;
}
template<> bool from_string<Color<float, 1>>(Color<float, 1>& _variableRet, const std::string& _value) {
	_variableRet = Color<float, 1>(_value);
	return true;
}


template<> std::string to_string<Color<float, 2>>(const Color<float, 2>& _val) {
	return _val.getString();
}
template<> std::u32string to_u32string<Color<float, 2>>(const Color<float, 2>& _val) {
	return to_u32string(_val.getString());
}

template<> bool from_string<Color<float, 2>>(Color<float, 2>& _variableRet, const std::u32string& _value) {
	_variableRet = Color<float, 2>(to_string(_value));
	return true;
}
template<> bool from_string<Color<float, 2>>(Color<float, 2>& _variableRet, const std::string& _value) {
	_variableRet = Color<float, 2>(_value);
	return true;
}


template<> std::string to_string<Color<float, 3>>(const Color<float, 3>& _val) {
	return _val.getString();
}
template<> std::u32string to_u32string<Color<float, 3>>(const Color<float, 3>& _val) {
	return to_u32string(_val.getString());
}

template<> bool from_string<Color<float, 3>>(Color<float, 3>& _variableRet, const std::u32string& _value) {
	_variableRet = Color<float, 3>(to_string(_value));
	return true;
}
template<> bool from_string<Color<float, 3>>(Color<float, 3>& _variableRet, const std::string& _value) {
	_variableRet = Color<float, 3>(_value);
	return true;
}


template<> std::string to_string<Color<float, 4>>(const Color<float, 4>& _val) {
	return _val.getString();
}
template<> std::u32string to_u32string<Color<float, 4>>(const Color<float, 4>& _val) {
	return to_u32string(_val.getString());
}

template<> bool from_string<Color<float, 4>>(Color<float, 4>& _variableRet, const std::u32string& _value) {
	_variableRet = Color<float, 4>(to_string(_value));
	return true;
}
template<> bool from_string<Color<float, 4>>(Color<float, 4>& _variableRet, const std::string& _value) {
	_variableRet = Color<float, 4>(_value);
	return true;
}

