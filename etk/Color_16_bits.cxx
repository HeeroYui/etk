
template<> const uint16_t Color<uint16_t, 1>::defaultAlpha(0xFFFF);
template<> const uint16_t Color<uint16_t, 2>::defaultAlpha(0xFFFF);
template<> const uint16_t Color<uint16_t, 3>::defaultAlpha(0xFFFF);
template<> const uint16_t Color<uint16_t, 4>::defaultAlpha(0xFFFF);
template<> const Color<uint16_t, 1> Color<uint16_t, 1>::emptyColor(0);
template<> const Color<uint16_t, 2> Color<uint16_t, 2>::emptyColor(0,0);
template<> const Color<uint16_t, 3> Color<uint16_t, 3>::emptyColor(0,0,0);
template<> const Color<uint16_t, 4> Color<uint16_t, 4>::emptyColor(0,0,0,0xFFFF);

// this work ...
template<> template<> Color<uint16_t,1>::Color(const Color<uint8_t, 1>& _obj) {
	m_element[0] = (uint16_t)_obj.r() << 8;
}
template<> template<> Color<uint16_t,2>::Color(const Color<uint8_t, 1>& _obj) {
	m_element[0] = (uint16_t)_obj.r() << 8;
	m_element[1] = 0;
}
template<> template<> Color<uint16_t,3>::Color(const Color<uint8_t, 1>& _obj) {
	m_element[0] = (uint16_t)_obj.r() << 8;
	m_element[1] = 0;
	m_element[2] = 0;
}
template<> template<> Color<uint16_t,4>::Color(const Color<uint8_t, 1>& _obj) {
	m_element[0] = (uint16_t)_obj.r() << 8;
	m_element[1] = 0;
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<uint16_t,1>::Color(const Color<uint8_t, 2>& _obj) {
	m_element[0] = (uint16_t)_obj.r() << 8;
}
template<> template<> Color<uint16_t,2>::Color(const Color<uint8_t, 2>& _obj) {
	m_element[0] = (uint16_t)_obj.r() << 8;
	m_element[1] = (uint16_t)_obj.g() << 8;
}
template<> template<> Color<uint16_t,3>::Color(const Color<uint8_t, 2>& _obj) {
	m_element[0] = (uint16_t)_obj.r() << 8;
	m_element[1] = (uint16_t)_obj.g() << 8;
	m_element[2] = 0;
}
template<> template<> Color<uint16_t,4>::Color(const Color<uint8_t, 2>& _obj) {
	m_element[0] = (uint16_t)_obj.r() << 8;
	m_element[1] = (uint16_t)_obj.g() << 8;
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<uint16_t,1>::Color(const Color<uint8_t, 3>& _obj) {
	m_element[0] = (uint16_t)_obj.r() << 8;
}
template<> template<> Color<uint16_t,2>::Color(const Color<uint8_t, 3>& _obj) {
	m_element[0] = (uint16_t)_obj.r() << 8;
	m_element[1] = (uint16_t)_obj.g() << 8;
}
template<> template<> Color<uint16_t,3>::Color(const Color<uint8_t, 3>& _obj) {
	m_element[0] = (uint16_t)_obj.r() << 8;
	m_element[1] = (uint16_t)_obj.g() << 8;
	m_element[2] = (uint16_t)_obj.b() << 8;
}
template<> template<> Color<uint16_t,4>::Color(const Color<uint8_t, 3>& _obj) {
	m_element[0] = (uint16_t)_obj.r() << 8;
	m_element[1] = (uint16_t)_obj.g() << 8;
	m_element[2] = (uint16_t)_obj.b() << 8;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<uint16_t,1>::Color(const Color<uint8_t, 4>& _obj) {
	m_element[0] = (uint16_t)_obj.r() << 8;
}
template<> template<> Color<uint16_t,2>::Color(const Color<uint8_t, 4>& _obj) {
	m_element[0] = (uint16_t)_obj.r() << 8;
	m_element[1] = (uint16_t)_obj.g() << 8;
}
template<> template<> Color<uint16_t,3>::Color(const Color<uint8_t, 4>& _obj) {
	m_element[0] = (uint16_t)_obj.r() << 8;
	m_element[1] = (uint16_t)_obj.g() << 8;
	m_element[2] = (uint16_t)_obj.b() << 8;
}
template<> template<> Color<uint16_t,4>::Color(const Color<uint8_t, 4>& _obj) {
	m_element[0] = (uint16_t)_obj.r() << 8;
	m_element[1] = (uint16_t)_obj.g() << 8;
	m_element[2] = (uint16_t)_obj.b() << 8;
	m_element[3] = (uint16_t)_obj.a() << 8;
}

// ===========================================================================================================

template<> template<> Color<uint16_t,1>::Color(const Color<uint16_t, 1>& _obj) {
	m_element[0] = _obj.r();
}
template<> template<> Color<uint16_t,2>::Color(const Color<uint16_t, 1>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = 0;
}
template<> template<> Color<uint16_t,3>::Color(const Color<uint16_t, 1>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = 0;
	m_element[2] = 0;
}
template<> template<> Color<uint16_t,4>::Color(const Color<uint16_t, 1>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = 0;
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<uint16_t,1>::Color(const Color<uint16_t, 2>& _obj) {
	m_element[0] = _obj.r();
}
template<> template<> Color<uint16_t,2>::Color(const Color<uint16_t, 2>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
}
template<> template<> Color<uint16_t,3>::Color(const Color<uint16_t, 2>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
	m_element[2] = 0;
}
template<> template<> Color<uint16_t,4>::Color(const Color<uint16_t, 2>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<uint16_t,1>::Color(const Color<uint16_t, 3>& _obj) {
	m_element[0] = _obj.r();
}
template<> template<> Color<uint16_t,2>::Color(const Color<uint16_t, 3>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
}
template<> template<> Color<uint16_t,3>::Color(const Color<uint16_t, 3>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
	m_element[2] = _obj.b();
}
template<> template<> Color<uint16_t,4>::Color(const Color<uint16_t, 3>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
	m_element[2] = _obj.b();
	m_element[3] = defaultAlpha;
}
template<> template<> Color<uint16_t,1>::Color(const Color<uint16_t, 4>& _obj) {
	m_element[0] = _obj.r();
}
template<> template<> Color<uint16_t,2>::Color(const Color<uint16_t, 4>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
}
template<> template<> Color<uint16_t,3>::Color(const Color<uint16_t, 4>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
	m_element[2] = _obj.b();
}
template<> template<> Color<uint16_t,4>::Color(const Color<uint16_t, 4>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
	m_element[2] = _obj.b();
	m_element[3] = _obj.a();
}

// ===========================================================================================================

template<> template<> Color<uint16_t,1>::Color(const Color<uint32_t, 1>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()>>16);
}
template<> template<> Color<uint16_t,2>::Color(const Color<uint32_t, 1>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()>>16);
	m_element[1] = 0;
}
template<> template<> Color<uint16_t,3>::Color(const Color<uint32_t, 1>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()>>16);
	m_element[1] = 0;
	m_element[2] = 0;
}
template<> template<> Color<uint16_t,4>::Color(const Color<uint32_t, 1>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()>>16);
	m_element[1] = 0;
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<uint16_t,1>::Color(const Color<uint32_t, 2>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()>>16);
}
template<> template<> Color<uint16_t,2>::Color(const Color<uint32_t, 2>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()>>16);
	m_element[1] = (uint16_t)(_obj.g()>>16);
}
template<> template<> Color<uint16_t,3>::Color(const Color<uint32_t, 2>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()>>16);
	m_element[1] = (uint16_t)(_obj.g()>>16);
	m_element[2] = 0;
}
template<> template<> Color<uint16_t,4>::Color(const Color<uint32_t, 2>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()>>16);
	m_element[1] = (uint16_t)(_obj.g()>>16);
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<uint16_t,1>::Color(const Color<uint32_t, 3>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()>>16);
}
template<> template<> Color<uint16_t,2>::Color(const Color<uint32_t, 3>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()>>16);
	m_element[1] = (uint16_t)(_obj.g()>>16);
}
template<> template<> Color<uint16_t,3>::Color(const Color<uint32_t, 3>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()>>16);
	m_element[1] = (uint16_t)(_obj.g()>>16);
	m_element[2] = (uint16_t)(_obj.b()>>16);
}
template<> template<> Color<uint16_t,4>::Color(const Color<uint32_t, 3>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()>>16);
	m_element[1] = (uint16_t)(_obj.g()>>16);
	m_element[2] = (uint16_t)(_obj.b()>>16);
	m_element[3] = defaultAlpha;
}
template<> template<> Color<uint16_t,1>::Color(const Color<uint32_t, 4>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()>>16);
}
template<> template<> Color<uint16_t,2>::Color(const Color<uint32_t, 4>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()>>16);
	m_element[1] = (uint16_t)(_obj.g()>>16);
}
template<> template<> Color<uint16_t,3>::Color(const Color<uint32_t, 4>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()>>16);
	m_element[1] = (uint16_t)(_obj.g()>>16);
	m_element[2] = (uint16_t)(_obj.b()>>16);
}
template<> template<> Color<uint16_t,4>::Color(const Color<uint32_t, 4>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()>>16);
	m_element[1] = (uint16_t)(_obj.g()>>16);
	m_element[2] = (uint16_t)(_obj.b()>>16);
	m_element[3] = (uint16_t)(_obj.a()>>16);
}

// ===========================================================================================================

template<> template<> Color<uint16_t,1>::Color(const Color<float, 1>& _obj) {
	m_element[0] = (uint16_t)(std::avg(0.0f, _obj.r(), 1.0f)*65535.0f);
}
template<> template<> Color<uint16_t,2>::Color(const Color<float, 1>& _obj) {
	m_element[0] = (uint16_t)(std::avg(0.0f, _obj.r(), 1.0f)*65535.0f);
	m_element[1] = 0;
}
template<> template<> Color<uint16_t,3>::Color(const Color<float, 1>& _obj) {
	m_element[0] = (uint16_t)(std::avg(0.0f, _obj.r(), 1.0f)*65535.0f);
	m_element[1] = 0;
	m_element[2] = 0;
}
template<> template<> Color<uint16_t,4>::Color(const Color<float, 1>& _obj) {
	m_element[0] = (uint16_t)(std::avg(0.0f, _obj.r(), 1.0f)*65535.0f);
	m_element[1] = 0;
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<uint16_t,1>::Color(const Color<float, 2>& _obj) {
	m_element[0] = (uint16_t)(std::avg(0.0f, _obj.r(), 1.0f)*65535.0f);
}
template<> template<> Color<uint16_t,2>::Color(const Color<float, 2>& _obj) {
	m_element[0] = (uint16_t)(std::avg(0.0f, _obj.r(), 1.0f)*65535.0f);
	m_element[1] = (uint16_t)(std::avg(0.0f, _obj.g(), 1.0f)*65535.0f);
}
template<> template<> Color<uint16_t,3>::Color(const Color<float, 2>& _obj) {
	m_element[0] = (uint16_t)(std::avg(0.0f, _obj.r(), 1.0f)*65535.0f);
	m_element[1] = (uint16_t)(std::avg(0.0f, _obj.g(), 1.0f)*65535.0f);
	m_element[2] = 0;
}
template<> template<> Color<uint16_t,4>::Color(const Color<float, 2>& _obj) {
	m_element[0] = (uint16_t)(std::avg(0.0f, _obj.r(), 1.0f)*65535.0f);
	m_element[1] = (uint16_t)(std::avg(0.0f, _obj.g(), 1.0f)*65535.0f);
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<uint16_t,1>::Color(const Color<float, 3>& _obj) {
	m_element[0] = (uint16_t)(std::avg(0.0f, _obj.r(), 1.0f)*65535.0f);
}
template<> template<> Color<uint16_t,2>::Color(const Color<float, 3>& _obj) {
	m_element[0] = (uint16_t)(std::avg(0.0f, _obj.r(), 1.0f)*65535.0f);
	m_element[1] = (uint16_t)(std::avg(0.0f, _obj.g(), 1.0f)*65535.0f);
}
template<> template<> Color<uint16_t,3>::Color(const Color<float, 3>& _obj) {
	m_element[0] = (uint16_t)(std::avg(0.0f, _obj.r(), 1.0f)*65535.0f);
	m_element[1] = (uint16_t)(std::avg(0.0f, _obj.g(), 1.0f)*65535.0f);
	m_element[2] = (uint16_t)(std::avg(0.0f, _obj.b(), 1.0f)*65535.0f);
}
template<> template<> Color<uint16_t,4>::Color(const Color<float, 3>& _obj) {
	m_element[0] = (uint16_t)(std::avg(0.0f, _obj.r(), 1.0f)*65535.0f);
	m_element[1] = (uint16_t)(std::avg(0.0f, _obj.g(), 1.0f)*65535.0f);
	m_element[2] = (uint16_t)(std::avg(0.0f, _obj.b(), 1.0f)*65535.0f);
	m_element[3] = defaultAlpha;
}
template<> template<> Color<uint16_t,1>::Color(const Color<float, 4>& _obj) {
	m_element[0] = (uint16_t)(std::avg(0.0f, _obj.r(), 1.0f)*65535.0f);
}
template<> template<> Color<uint16_t,2>::Color(const Color<float, 4>& _obj) {
	m_element[0] = (uint16_t)(std::avg(0.0f, _obj.r(), 1.0f)*65535.0f);
	m_element[1] = (uint16_t)(std::avg(0.0f, _obj.g(), 1.0f)*65535.0f);
}
template<> template<> Color<uint16_t,3>::Color(const Color<float, 4>& _obj) {
	m_element[0] = (uint16_t)(std::avg(0.0f, _obj.r(), 1.0f)*65535.0f);
	m_element[1] = (uint16_t)(std::avg(0.0f, _obj.g(), 1.0f)*65535.0f);
	m_element[2] = (uint16_t)(std::avg(0.0f, _obj.b(), 1.0f)*65535.0f);
}
template<> template<> Color<uint16_t,4>::Color(const Color<float, 4>& _obj) {
	m_element[0] = (uint16_t)(std::avg(0.0f, _obj.r(), 1.0f)*65535.0f);
	m_element[1] = (uint16_t)(std::avg(0.0f, _obj.g(), 1.0f)*65535.0f);
	m_element[2] = (uint16_t)(std::avg(0.0f, _obj.b(), 1.0f)*65535.0f);
	m_element[3] = (uint16_t)(std::avg(0.0f, _obj.a(), 1.0f)*65535.0f);
}

// ===========================================================================================================

template<> template<> Color<uint16_t,1>::Color(const Color<double, 1>& _obj) {
	m_element[0] = (uint16_t)(std::avg(0.0, _obj.r(), 1.0)*65535.0);
}
template<> template<> Color<uint16_t,2>::Color(const Color<double, 1>& _obj) {
	m_element[0] = (uint16_t)(std::avg(0.0, _obj.r(), 1.0)*65535.0);
	m_element[1] = 0;
}
template<> template<> Color<uint16_t,3>::Color(const Color<double, 1>& _obj) {
	m_element[0] = (uint16_t)(std::avg(0.0, _obj.r(), 1.0)*65535.0);
	m_element[1] = 0;
	m_element[2] = 0;
}
template<> template<> Color<uint16_t,4>::Color(const Color<double, 1>& _obj) {
	m_element[0] = (uint16_t)(std::avg(0.0, _obj.r(), 1.0)*65535.0);
	m_element[1] = 0;
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<uint16_t,1>::Color(const Color<double, 2>& _obj) {
	m_element[0] = (uint16_t)(std::avg(0.0, _obj.r(), 1.0)*65535.0);
}
template<> template<> Color<uint16_t,2>::Color(const Color<double, 2>& _obj) {
	m_element[0] = (uint16_t)(std::avg(0.0, _obj.r(), 1.0)*65535.0);
	m_element[1] = (uint16_t)(std::avg(0.0, _obj.g(), 1.0)*65535.0);
}
template<> template<> Color<uint16_t,3>::Color(const Color<double, 2>& _obj) {
	m_element[0] = (uint16_t)(std::avg(0.0, _obj.r(), 1.0)*65535.0);
	m_element[1] = (uint16_t)(std::avg(0.0, _obj.g(), 1.0)*65535.0);
	m_element[2] = 0;
}
template<> template<> Color<uint16_t,4>::Color(const Color<double, 2>& _obj) {
	m_element[0] = (uint16_t)(std::avg(0.0, _obj.r(), 1.0)*65535.0);
	m_element[1] = (uint16_t)(std::avg(0.0, _obj.g(), 1.0)*65535.0);
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<uint16_t,1>::Color(const Color<double, 3>& _obj) {
	m_element[0] = (uint16_t)(std::avg(0.0, _obj.r(), 1.0)*65535.0);
}
template<> template<> Color<uint16_t,2>::Color(const Color<double, 3>& _obj) {
	m_element[0] = (uint16_t)(std::avg(0.0, _obj.r(), 1.0)*65535.0);
	m_element[1] = (uint16_t)(std::avg(0.0, _obj.g(), 1.0)*65535.0);
}
template<> template<> Color<uint16_t,3>::Color(const Color<double, 3>& _obj) {
	m_element[0] = (uint16_t)(std::avg(0.0, _obj.r(), 1.0)*65535.0);
	m_element[1] = (uint16_t)(std::avg(0.0, _obj.g(), 1.0)*65535.0);
	m_element[2] = (uint16_t)(std::avg(0.0, _obj.b(), 1.0)*65535.0);
}
template<> template<> Color<uint16_t,4>::Color(const Color<double, 3>& _obj) {
	m_element[0] = (uint16_t)(std::avg(0.0, _obj.r(), 1.0)*65535.0);
	m_element[1] = (uint16_t)(std::avg(0.0, _obj.g(), 1.0)*65535.0);
	m_element[2] = (uint16_t)(std::avg(0.0, _obj.b(), 1.0)*65535.0);
	m_element[3] = defaultAlpha;
}
template<> template<> Color<uint16_t,1>::Color(const Color<double, 4>& _obj) {
	m_element[0] = (uint16_t)(std::avg(0.0, _obj.r(), 1.0)*65535.0);
}
template<> template<> Color<uint16_t,2>::Color(const Color<double, 4>& _obj) {
	m_element[0] = (uint16_t)(std::avg(0.0, _obj.r(), 1.0)*65535.0);
	m_element[1] = (uint16_t)(std::avg(0.0, _obj.g(), 1.0)*65535.0);
}
template<> template<> Color<uint16_t,3>::Color(const Color<double, 4>& _obj) {
	m_element[0] = (uint16_t)(std::avg(0.0, _obj.r(), 1.0)*65535.0);
	m_element[1] = (uint16_t)(std::avg(0.0, _obj.g(), 1.0)*65535.0);
	m_element[2] = (uint16_t)(std::avg(0.0, _obj.b(), 1.0)*65535.0);
}
template<> template<> Color<uint16_t,4>::Color(const Color<double, 4>& _obj) {
	m_element[0] = (uint16_t)(std::avg(0.0, _obj.r(), 1.0)*65535.0);
	m_element[1] = (uint16_t)(std::avg(0.0, _obj.g(), 1.0)*65535.0);
	m_element[2] = (uint16_t)(std::avg(0.0, _obj.b(), 1.0)*65535.0);
	m_element[3] = (uint16_t)(std::avg(0.0, _obj.a(), 1.0)*65535.0);
}

// ===========================================================================================================


template<> std::string to_string<Color<uint16_t, 1>>(const Color<uint16_t, 1>& _val) {
	return _val.getString();
}
template<> std::u32string to_u32string<Color<uint16_t, 1>>(const Color<uint16_t, 1>& _val) {
	return to_u32string(_val.getString());
}

template<> bool from_string<Color<uint16_t, 1>>(Color<uint16_t, 1>& _variableRet, const std::u32string& _value) {
	_variableRet = Color<uint16_t, 1>(to_string(_value));
	return true;
}
template<> bool from_string<Color<uint16_t, 1>>(Color<uint16_t, 1>& _variableRet, const std::string& _value) {
	_variableRet = Color<uint16_t, 1>(_value);
	return true;
}



template<> std::string to_string<Color<uint16_t, 2>>(const Color<uint16_t, 2>& _val) {
	return _val.getString();
}
template<> std::u32string to_u32string<Color<uint16_t, 2>>(const Color<uint16_t, 2>& _val) {
	return to_u32string(_val.getString());
}

template<> bool from_string<Color<uint16_t, 2>>(Color<uint16_t, 2>& _variableRet, const std::u32string& _value) {
	_variableRet = Color<uint16_t, 2>(to_string(_value));
	return true;
}
template<> bool from_string<Color<uint16_t, 2>>(Color<uint16_t, 2>& _variableRet, const std::string& _value) {
	_variableRet = Color<uint16_t, 2>(_value);
	return true;
}



template<> std::string to_string<Color<uint16_t, 3>>(const Color<uint16_t, 3>& _val) {
	return _val.getString();
}
template<> std::u32string to_u32string<Color<uint16_t, 3>>(const Color<uint16_t, 3>& _val) {
	return to_u32string(_val.getString());
}

template<> bool from_string<Color<uint16_t, 3>>(Color<uint16_t, 3>& _variableRet, const std::u32string& _value) {
	_variableRet = Color<uint16_t, 3>(to_string(_value));
	return true;
}
template<> bool from_string<Color<uint16_t, 3>>(Color<uint16_t, 3>& _variableRet, const std::string& _value) {
	_variableRet = Color<uint16_t, 3>(_value);
	return true;
}



template<> std::string to_string<Color<uint16_t, 4>>(const Color<uint16_t, 4>& _val) {
	return _val.getString();
}
template<> std::u32string to_u32string<Color<uint16_t, 4>>(const Color<uint16_t, 4>& _val) {
	return to_u32string(_val.getString());
}

template<> bool from_string<Color<uint16_t, 4>>(Color<uint16_t, 4>& _variableRet, const std::u32string& _value) {
	_variableRet = Color<uint16_t, 4>(to_string(_value));
	return true;
}
template<> bool from_string<Color<uint16_t, 4>>(Color<uint16_t, 4>& _variableRet, const std::string& _value) {
	_variableRet = Color<uint16_t, 4>(_value);
	return true;
}
