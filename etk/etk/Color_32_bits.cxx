
template<> const uint32_t Color<uint32_t, 1>::defaultAlpha(0xFFFFFFFF);
template<> const uint32_t Color<uint32_t, 2>::defaultAlpha(0xFFFFFFFF);
template<> const uint32_t Color<uint32_t, 3>::defaultAlpha(0xFFFFFFFF);
template<> const uint32_t Color<uint32_t, 4>::defaultAlpha(0xFFFFFFFF);
template<> const Color<uint32_t, 1> Color<uint32_t, 1>::emptyColor(0);
template<> const Color<uint32_t, 2> Color<uint32_t, 2>::emptyColor(0,0);
template<> const Color<uint32_t, 3> Color<uint32_t, 3>::emptyColor(0,0,0);
template<> const Color<uint32_t, 4> Color<uint32_t, 4>::emptyColor(0,0,0,0xFFFFFFFF);

// this work ...
template<> template<> Color<uint32_t,1>::Color(const Color<uint8_t, 1>& _obj) {
	m_element[0] = (uint32_t)_obj.r() << 24;
}
template<> template<> Color<uint32_t,2>::Color(const Color<uint8_t, 1>& _obj) {
	m_element[0] = (uint32_t)_obj.r() << 24;
	m_element[1] = 0;
}
template<> template<> Color<uint32_t,3>::Color(const Color<uint8_t, 1>& _obj) {
	m_element[0] = (uint32_t)_obj.r() << 24;
	m_element[1] = 0;
	m_element[2] = 0;
}
template<> template<> Color<uint32_t,4>::Color(const Color<uint8_t, 1>& _obj) {
	m_element[0] = (uint32_t)_obj.r() << 24;
	m_element[1] = 0;
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<uint32_t,1>::Color(const Color<uint8_t, 2>& _obj) {
	m_element[0] = (uint32_t)_obj.r() << 24;
}
template<> template<> Color<uint32_t,2>::Color(const Color<uint8_t, 2>& _obj) {
	m_element[0] = (uint32_t)_obj.r() << 24;
	m_element[1] = (uint32_t)_obj.g() << 24;
}
template<> template<> Color<uint32_t,3>::Color(const Color<uint8_t, 2>& _obj) {
	m_element[0] = (uint32_t)_obj.r() << 24;
	m_element[1] = (uint32_t)_obj.g() << 24;
	m_element[2] = 0;
}
template<> template<> Color<uint32_t,4>::Color(const Color<uint8_t, 2>& _obj) {
	m_element[0] = (uint32_t)_obj.r() << 24;
	m_element[1] = (uint32_t)_obj.g() << 24;
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<uint32_t,1>::Color(const Color<uint8_t, 3>& _obj) {
	m_element[0] = (uint32_t)_obj.r() << 24;
}
template<> template<> Color<uint32_t,2>::Color(const Color<uint8_t, 3>& _obj) {
	m_element[0] = (uint32_t)_obj.r() << 24;
	m_element[1] = (uint32_t)_obj.g() << 24;
}
template<> template<> Color<uint32_t,3>::Color(const Color<uint8_t, 3>& _obj) {
	m_element[0] = (uint32_t)_obj.r() << 24;
	m_element[1] = (uint32_t)_obj.g() << 24;
	m_element[2] = (uint32_t)_obj.b() << 24;
}
template<> template<> Color<uint32_t,4>::Color(const Color<uint8_t, 3>& _obj) {
	m_element[0] = (uint32_t)_obj.r() << 24;
	m_element[1] = (uint32_t)_obj.g() << 24;
	m_element[2] = (uint32_t)_obj.b() << 24;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<uint32_t,1>::Color(const Color<uint8_t, 4>& _obj) {
	m_element[0] = (uint32_t)_obj.r() << 24;
}
template<> template<> Color<uint32_t,2>::Color(const Color<uint8_t, 4>& _obj) {
	m_element[0] = (uint32_t)_obj.r() << 24;
	m_element[1] = (uint32_t)_obj.g() << 24;
}
template<> template<> Color<uint32_t,3>::Color(const Color<uint8_t, 4>& _obj) {
	m_element[0] = (uint32_t)_obj.r() << 24;
	m_element[1] = (uint32_t)_obj.g() << 24;
	m_element[2] = (uint32_t)_obj.b() << 24;
}
template<> template<> Color<uint32_t,4>::Color(const Color<uint8_t, 4>& _obj) {
	m_element[0] = (uint32_t)_obj.r() << 24;
	m_element[1] = (uint32_t)_obj.g() << 24;
	m_element[2] = (uint32_t)_obj.b() << 24;
	m_element[3] = (uint32_t)_obj.a() << 24;
}

// ===========================================================================================================

template<> template<> Color<uint32_t,1>::Color(const Color<uint16_t, 1>& _obj) {
	m_element[0] = (uint32_t)_obj.r() << 16;
}
template<> template<> Color<uint32_t,2>::Color(const Color<uint16_t, 1>& _obj) {
	m_element[0] = (uint32_t)_obj.r() << 16;
	m_element[1] = 0;
}
template<> template<> Color<uint32_t,3>::Color(const Color<uint16_t, 1>& _obj) {
	m_element[0] = (uint32_t)_obj.r() << 16;
	m_element[1] = 0;
	m_element[2] = 0;
}
template<> template<> Color<uint32_t,4>::Color(const Color<uint16_t, 1>& _obj) {
	m_element[0] = (uint32_t)_obj.r() << 16;
	m_element[1] = 0;
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<uint32_t,1>::Color(const Color<uint16_t, 2>& _obj) {
	m_element[0] = (uint32_t)_obj.r() << 16;
}
template<> template<> Color<uint32_t,2>::Color(const Color<uint16_t, 2>& _obj) {
	m_element[0] = (uint32_t)_obj.r() << 16;
	m_element[1] = (uint32_t)_obj.g() << 16;
}
template<> template<> Color<uint32_t,3>::Color(const Color<uint16_t, 2>& _obj) {
	m_element[0] = (uint32_t)_obj.r() << 16;
	m_element[1] = (uint32_t)_obj.g() << 16;
	m_element[2] = 0;
}
template<> template<> Color<uint32_t,4>::Color(const Color<uint16_t, 2>& _obj) {
	m_element[0] = (uint32_t)_obj.r() << 16;
	m_element[1] = (uint32_t)_obj.g() << 16;
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<uint32_t,1>::Color(const Color<uint16_t, 3>& _obj) {
	m_element[0] = (uint32_t)_obj.r() << 16;
}
template<> template<> Color<uint32_t,2>::Color(const Color<uint16_t, 3>& _obj) {
	m_element[0] = (uint32_t)_obj.r() << 16;
	m_element[1] = (uint32_t)_obj.g() << 16;
}
template<> template<> Color<uint32_t,3>::Color(const Color<uint16_t, 3>& _obj) {
	m_element[0] = (uint32_t)_obj.r() << 16;
	m_element[1] = (uint32_t)_obj.g() << 16;
	m_element[2] = (uint32_t)_obj.b() << 16;
}
template<> template<> Color<uint32_t,4>::Color(const Color<uint16_t, 3>& _obj) {
	m_element[0] = (uint32_t)_obj.r() << 16;
	m_element[1] = (uint32_t)_obj.g() << 16;
	m_element[2] = (uint32_t)_obj.b() << 16;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<uint32_t,1>::Color(const Color<uint16_t, 4>& _obj) {
	m_element[0] = (uint32_t)_obj.r() << 16;
}
template<> template<> Color<uint32_t,2>::Color(const Color<uint16_t, 4>& _obj) {
	m_element[0] = (uint32_t)_obj.r() << 16;
	m_element[1] = (uint32_t)_obj.g() << 16;
}
template<> template<> Color<uint32_t,3>::Color(const Color<uint16_t, 4>& _obj) {
	m_element[0] = (uint32_t)_obj.r() << 16;
	m_element[1] = (uint32_t)_obj.g() << 16;
	m_element[2] = (uint32_t)_obj.b() << 16;
}
template<> template<> Color<uint32_t,4>::Color(const Color<uint16_t, 4>& _obj) {
	m_element[0] = (uint32_t)_obj.r() << 16;
	m_element[1] = (uint32_t)_obj.g() << 16;
	m_element[2] = (uint32_t)_obj.b() << 16;
	m_element[3] = (uint32_t)_obj.a() << 16;
}

// ===========================================================================================================

template<> template<> Color<uint32_t,1>::Color(const Color<uint32_t, 1>& _obj) {
	m_element[0] = _obj.r();
}
template<> template<> Color<uint32_t,2>::Color(const Color<uint32_t, 1>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = 0;
}
template<> template<> Color<uint32_t,3>::Color(const Color<uint32_t, 1>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = 0;
	m_element[2] = 0;
}
template<> template<> Color<uint32_t,4>::Color(const Color<uint32_t, 1>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = 0;
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<uint32_t,1>::Color(const Color<uint32_t, 2>& _obj) {
	m_element[0] = _obj.r();
}
template<> template<> Color<uint32_t,2>::Color(const Color<uint32_t, 2>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
}
template<> template<> Color<uint32_t,3>::Color(const Color<uint32_t, 2>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
	m_element[2] = 0;
}
template<> template<> Color<uint32_t,4>::Color(const Color<uint32_t, 2>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<uint32_t,1>::Color(const Color<uint32_t, 3>& _obj) {
	m_element[0] = _obj.r();
}
template<> template<> Color<uint32_t,2>::Color(const Color<uint32_t, 3>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
}
template<> template<> Color<uint32_t,3>::Color(const Color<uint32_t, 3>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
	m_element[2] = _obj.b();
}
template<> template<> Color<uint32_t,4>::Color(const Color<uint32_t, 3>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
	m_element[2] = _obj.b();
	m_element[3] = defaultAlpha;
}
template<> template<> Color<uint32_t,1>::Color(const Color<uint32_t, 4>& _obj) {
	m_element[0] = _obj.r();
}
template<> template<> Color<uint32_t,2>::Color(const Color<uint32_t, 4>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
}
template<> template<> Color<uint32_t,3>::Color(const Color<uint32_t, 4>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
	m_element[2] = _obj.b();
}
template<> template<> Color<uint32_t,4>::Color(const Color<uint32_t, 4>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
	m_element[2] = _obj.b();
	m_element[3] = _obj.a();
}

// ===========================================================================================================

template<> template<> Color<uint32_t,1>::Color(const Color<float, 1>& _obj) {
	m_element[0] = (uint32_t)(etk::avg(0.0f, _obj.r(), 1.0f)*4294967295.0f);
}
template<> template<> Color<uint32_t,2>::Color(const Color<float, 1>& _obj) {
	m_element[0] = (uint32_t)(etk::avg(0.0f, _obj.r(), 1.0f)*4294967295.0f);
	m_element[1] = 0;
}
template<> template<> Color<uint32_t,3>::Color(const Color<float, 1>& _obj) {
	m_element[0] = (uint32_t)(etk::avg(0.0f, _obj.r(), 1.0f)*4294967295.0f);
	m_element[1] = 0;
	m_element[2] = 0;
}
template<> template<> Color<uint32_t,4>::Color(const Color<float, 1>& _obj) {
	m_element[0] = (uint32_t)(etk::avg(0.0f, _obj.r(), 1.0f)*4294967295.0f);
	m_element[1] = 0;
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<uint32_t,1>::Color(const Color<float, 2>& _obj) {
	m_element[0] = (uint32_t)(etk::avg(0.0f, _obj.r(), 1.0f)*4294967295.0f);
}
template<> template<> Color<uint32_t,2>::Color(const Color<float, 2>& _obj) {
	m_element[0] = (uint32_t)(etk::avg(0.0f, _obj.r(), 1.0f)*4294967295.0f);
	m_element[1] = (uint32_t)(etk::avg(0.0f, _obj.g(), 1.0f)*4294967295.0f);
}
template<> template<> Color<uint32_t,3>::Color(const Color<float, 2>& _obj) {
	m_element[0] = (uint32_t)(etk::avg(0.0f, _obj.r(), 1.0f)*4294967295.0f);
	m_element[1] = (uint32_t)(etk::avg(0.0f, _obj.g(), 1.0f)*4294967295.0f);
	m_element[2] = 0;
}
template<> template<> Color<uint32_t,4>::Color(const Color<float, 2>& _obj) {
	m_element[0] = (uint32_t)(etk::avg(0.0f, _obj.r(), 1.0f)*4294967295.0f);
	m_element[1] = (uint32_t)(etk::avg(0.0f, _obj.g(), 1.0f)*4294967295.0f);
	m_element[2] = 0;
	m_element[3] = defaultAlpha;
}
template<> template<> Color<uint32_t,1>::Color(const Color<float, 3>& _obj) {
	m_element[0] = (uint32_t)(etk::avg(0.0f, _obj.r(), 1.0f)*4294967295.0f);
}
template<> template<> Color<uint32_t,2>::Color(const Color<float, 3>& _obj) {
	m_element[0] = (uint32_t)(etk::avg(0.0f, _obj.r(), 1.0f)*4294967295.0f);
	m_element[1] = (uint32_t)(etk::avg(0.0f, _obj.g(), 1.0f)*4294967295.0f);
}
template<> template<> Color<uint32_t,3>::Color(const Color<float, 3>& _obj) {
	m_element[0] = (uint32_t)(etk::avg(0.0f, _obj.r(), 1.0f)*4294967295.0f);
	m_element[1] = (uint32_t)(etk::avg(0.0f, _obj.g(), 1.0f)*4294967295.0f);
	m_element[2] = (uint32_t)(etk::avg(0.0f, _obj.b(), 1.0f)*4294967295.0f);
}
template<> template<> Color<uint32_t,4>::Color(const Color<float, 3>& _obj) {
	m_element[0] = (uint32_t)(etk::avg(0.0f, _obj.r(), 1.0f)*4294967295.0f);
	m_element[1] = (uint32_t)(etk::avg(0.0f, _obj.g(), 1.0f)*4294967295.0f);
	m_element[2] = (uint32_t)(etk::avg(0.0f, _obj.b(), 1.0f)*4294967295.0f);
	m_element[3] = defaultAlpha;
}
template<> template<> Color<uint32_t,1>::Color(const Color<float, 4>& _obj) {
	m_element[0] = (uint32_t)(etk::avg(0.0f, _obj.r(), 1.0f)*4294967295.0f);
}
template<> template<> Color<uint32_t,2>::Color(const Color<float, 4>& _obj) {
	m_element[0] = (uint32_t)(etk::avg(0.0f, _obj.r(), 1.0f)*4294967295.0f);
	m_element[1] = (uint32_t)(etk::avg(0.0f, _obj.g(), 1.0f)*4294967295.0f);
}
template<> template<> Color<uint32_t,3>::Color(const Color<float, 4>& _obj) {
	m_element[0] = (uint32_t)(etk::avg(0.0f, _obj.r(), 1.0f)*4294967295.0f);
	m_element[1] = (uint32_t)(etk::avg(0.0f, _obj.g(), 1.0f)*4294967295.0f);
	m_element[2] = (uint32_t)(etk::avg(0.0f, _obj.b(), 1.0f)*4294967295.0f);
}
template<> template<> Color<uint32_t,4>::Color(const Color<float, 4>& _obj) {
	m_element[0] = (uint32_t)(etk::avg(0.0f, _obj.r(), 1.0f)*4294967295.0f);
	m_element[1] = (uint32_t)(etk::avg(0.0f, _obj.g(), 1.0f)*4294967295.0f);
	m_element[2] = (uint32_t)(etk::avg(0.0f, _obj.b(), 1.0f)*4294967295.0f);
	m_element[3] = (uint32_t)(etk::avg(0.0f, _obj.a(), 1.0f)*4294967295.0f);
}

// ===========================================================================================================

template<> template<> Color<uint32_t,1>::Color(const Color<double, 1>& _obj) {
	m_element[0] = (uint32_t)(etk::avg(0.0, _obj.r(), 1.0)*4294967295.0);
}
template<> template<> Color<uint32_t,2>::Color(const Color<double, 1>& _obj) {
	m_element[0] = (uint32_t)(etk::avg(0.0, _obj.r(), 1.0)*4294967295.0);
	m_element[1] = 0;
}
template<> template<> Color<uint32_t,3>::Color(const Color<double, 1>& _obj) {
	m_element[0] = (uint32_t)(etk::avg(0.0, _obj.r(), 1.0)*4294967295.0);
	m_element[1] = 0;
	m_element[2] = 0;
}
template<> template<> Color<uint32_t,4>::Color(const Color<double, 1>& _obj) {
	m_element[0] = (uint32_t)(etk::avg(0.0, _obj.r(), 1.0)*4294967295.0);
	m_element[1] = 0;
	m_element[2] = 0;
	m_element[3] = 0xFFFFFF;
}
template<> template<> Color<uint32_t,1>::Color(const Color<double, 2>& _obj) {
	m_element[0] = (uint32_t)(etk::avg(0.0, _obj.r(), 1.0)*4294967295.0);
}
template<> template<> Color<uint32_t,2>::Color(const Color<double, 2>& _obj) {
	m_element[0] = (uint32_t)(etk::avg(0.0, _obj.r(), 1.0)*4294967295.0);
	m_element[1] = (uint32_t)(etk::avg(0.0, _obj.g(), 1.0)*4294967295.0);
}
template<> template<> Color<uint32_t,3>::Color(const Color<double, 2>& _obj) {
	m_element[0] = (uint32_t)(etk::avg(0.0, _obj.r(), 1.0)*4294967295.0);
	m_element[1] = (uint32_t)(etk::avg(0.0, _obj.g(), 1.0)*4294967295.0);
	m_element[2] = 0;
}
template<> template<> Color<uint32_t,4>::Color(const Color<double, 2>& _obj) {
	m_element[0] = (uint32_t)(etk::avg(0.0, _obj.r(), 1.0)*4294967295.0);
	m_element[1] = (uint32_t)(etk::avg(0.0, _obj.g(), 1.0)*4294967295.0);
	m_element[2] = 0;
	m_element[3] = 0xFFFFFF;
}
template<> template<> Color<uint32_t,1>::Color(const Color<double, 3>& _obj) {
	m_element[0] = (uint32_t)(etk::avg(0.0, _obj.r(), 1.0)*4294967295.0);
}
template<> template<> Color<uint32_t,2>::Color(const Color<double, 3>& _obj) {
	m_element[0] = (uint32_t)(etk::avg(0.0, _obj.r(), 1.0)*4294967295.0);
	m_element[1] = (uint32_t)(etk::avg(0.0, _obj.g(), 1.0)*4294967295.0);
}
template<> template<> Color<uint32_t,3>::Color(const Color<double, 3>& _obj) {
	m_element[0] = (uint32_t)(etk::avg(0.0, _obj.r(), 1.0)*4294967295.0);
	m_element[1] = (uint32_t)(etk::avg(0.0, _obj.g(), 1.0)*4294967295.0);
	m_element[2] = (uint32_t)(etk::avg(0.0, _obj.b(), 1.0)*4294967295.0);
}
template<> template<> Color<uint32_t,4>::Color(const Color<double, 3>& _obj) {
	m_element[0] = (uint32_t)(etk::avg(0.0, _obj.r(), 1.0)*4294967295.0);
	m_element[1] = (uint32_t)(etk::avg(0.0, _obj.g(), 1.0)*4294967295.0);
	m_element[2] = (uint32_t)(etk::avg(0.0, _obj.b(), 1.0)*4294967295.0);
	m_element[3] = 0xFFFFFF;
}
template<> template<> Color<uint32_t,1>::Color(const Color<double, 4>& _obj) {
	m_element[0] = (uint32_t)(etk::avg(0.0, _obj.r(), 1.0)*4294967295.0);
}
template<> template<> Color<uint32_t,2>::Color(const Color<double, 4>& _obj) {
	m_element[0] = (uint32_t)(etk::avg(0.0, _obj.r(), 1.0)*4294967295.0);
	m_element[1] = (uint32_t)(etk::avg(0.0, _obj.g(), 1.0)*4294967295.0);
}
template<> template<> Color<uint32_t,3>::Color(const Color<double, 4>& _obj) {
	m_element[0] = (uint32_t)(etk::avg(0.0, _obj.r(), 1.0)*4294967295.0);
	m_element[1] = (uint32_t)(etk::avg(0.0, _obj.g(), 1.0)*4294967295.0);
	m_element[2] = (uint32_t)(etk::avg(0.0, _obj.b(), 1.0)*4294967295.0);
}
template<> template<> Color<uint32_t,4>::Color(const Color<double, 4>& _obj) {
	m_element[0] = (uint32_t)(etk::avg(0.0, _obj.r(), 1.0)*4294967295.0);
	m_element[1] = (uint32_t)(etk::avg(0.0, _obj.g(), 1.0)*4294967295.0);
	m_element[2] = (uint32_t)(etk::avg(0.0, _obj.b(), 1.0)*4294967295.0);
	m_element[3] = (uint32_t)(etk::avg(0.0, _obj.a(), 1.0)*4294967295.0);
}

// ===========================================================================================================


template<> etk::String toString<Color<uint32_t, 1> >(const Color<uint32_t, 1>& _val) {
	return _val.getString();
}
#if __cplusplus >= 201103L
	template<> etk::UString toUString<Color<uint32_t, 1>>(const Color<uint32_t, 1>& _val) {
		return toUString(_val.getString());
	}
	template<> bool from_string<Color<uint32_t, 1>>(Color<uint32_t, 1>& _variableRet, const etk::UString& _value) {
		_variableRet = Color<uint32_t, 1>(toString(_value));
		return true;
	}
#endif
template<> bool from_string<Color<uint32_t, 1> >(Color<uint32_t, 1>& _variableRet, const etk::String& _value) {
	_variableRet = Color<uint32_t, 1>(_value);
	return true;
}

template<> etk::String toString<Color<uint32_t, 2> >(const Color<uint32_t, 2>& _val) {
	return _val.getString();
}
#if __cplusplus >= 201103L
	template<> etk::UString toUString<Color<uint32_t, 2>>(const Color<uint32_t, 2>& _val) {
		return toUString(_val.getString());
	}
	template<> bool from_string<Color<uint32_t, 2>>(Color<uint32_t, 2>& _variableRet, const etk::UString& _value) {
		_variableRet = Color<uint32_t, 2>(toString(_value));
		return true;
	}
#endif
template<> bool from_string<Color<uint32_t, 2> >(Color<uint32_t, 2>& _variableRet, const etk::String& _value) {
	_variableRet = Color<uint32_t, 2>(_value);
	return true;
}



template<> etk::String toString<Color<uint32_t, 3> >(const Color<uint32_t, 3>& _val) {
	return _val.getString();
}
#if __cplusplus >= 201103L
	template<> etk::UString toUString<Color<uint32_t, 3>>(const Color<uint32_t, 3>& _val) {
		return toUString(_val.getString());
	}
	template<> bool from_string<Color<uint32_t, 3>>(Color<uint32_t, 3>& _variableRet, const etk::UString& _value) {
		_variableRet = Color<uint32_t, 3>(toString(_value));
		return true;
	}
#endif
template<> bool from_string<Color<uint32_t, 3> >(Color<uint32_t, 3>& _variableRet, const etk::String& _value) {
	_variableRet = Color<uint32_t, 3>(_value);
	return true;
}



template<> etk::String toString<Color<uint32_t, 4> >(const Color<uint32_t, 4>& _val) {
	return _val.getString();
}
#if __cplusplus >= 201103L
	template<> etk::UString toUString<Color<uint32_t, 4>>(const Color<uint32_t, 4>& _val) {
		return toUString(_val.getString());
	}
	template<> bool from_string<Color<uint32_t, 4>>(Color<uint32_t, 4>& _variableRet, const etk::UString& _value) {
		_variableRet = Color<uint32_t, 4>(toString(_value));
		return true;
	}
#endif
template<> bool from_string<Color<uint32_t, 4> >(Color<uint32_t, 4>& _variableRet, const etk::String& _value) {
	_variableRet = Color<uint32_t, 4>(_value);
	return true;
}
