
template<> const Color<double, 1> Color<double, 1>::emptyColor(0.0);
template<> const Color<double, 2> Color<double, 2>::emptyColor(0.0,0.0);
template<> const Color<double, 3> Color<double, 3>::emptyColor(0.0,0.0,0.0);
template<> const Color<double, 4> Color<double, 4>::emptyColor(0.0,0.0,0.0,1.0);

// this work ...
template<> template<> Color<double,1>::Color(const Color<uint8_t, 1>& _obj) {
	m_element[0] = (double)_obj.r() / 255.0;
}
template<> template<> Color<double,2>::Color(const Color<uint8_t, 1>& _obj) {
	m_element[0] = (double)_obj.r() / 255.0;
	m_element[1] = 0;
}
template<> template<> Color<double,3>::Color(const Color<uint8_t, 1>& _obj) {
	m_element[0] = (double)_obj.r() / 255.0;
	m_element[1] = 0;
	m_element[2] = 0;
}
template<> template<> Color<double,4>::Color(const Color<uint8_t, 1>& _obj) {
	m_element[0] = (double)_obj.r() / 255.0;
	m_element[1] = 0;
	m_element[2] = 0;
	m_element[3] = 0;
}
template<> template<> Color<double,1>::Color(const Color<uint8_t, 2>& _obj) {
	m_element[0] = (double)_obj.r() / 255.0;
}
template<> template<> Color<double,2>::Color(const Color<uint8_t, 2>& _obj) {
	m_element[0] = (double)_obj.r() / 255.0;
	m_element[1] = (double)_obj.g() / 255.0;
}
template<> template<> Color<double,3>::Color(const Color<uint8_t, 2>& _obj) {
	m_element[0] = (double)_obj.r() / 255.0;
	m_element[1] = (double)_obj.g() / 255.0;
	m_element[2] = 0;
}
template<> template<> Color<double,4>::Color(const Color<uint8_t, 2>& _obj) {
	m_element[0] = (double)_obj.r() / 255.0;
	m_element[1] = (double)_obj.g() / 255.0;
	m_element[2] = 0;
	m_element[3] = 0;
}
template<> template<> Color<double,1>::Color(const Color<uint8_t, 3>& _obj) {
	m_element[0] = (double)_obj.r() / 255.0;
}
template<> template<> Color<double,2>::Color(const Color<uint8_t, 3>& _obj) {
	m_element[0] = (double)_obj.r() / 255.0;
	m_element[1] = (double)_obj.g() / 255.0;
}
template<> template<> Color<double,3>::Color(const Color<uint8_t, 3>& _obj) {
	m_element[0] = (double)_obj.r() / 255.0;
	m_element[1] = (double)_obj.g() / 255.0;
	m_element[2] = (double)_obj.b() / 255.0;
}
template<> template<> Color<double,4>::Color(const Color<uint8_t, 3>& _obj) {
	m_element[0] = (double)_obj.r() / 255.0;
	m_element[1] = (double)_obj.g() / 255.0;
	m_element[2] = (double)_obj.b() / 255.0;
	m_element[3] = 0;
}
template<> template<> Color<double,1>::Color(const Color<uint8_t, 4>& _obj) {
	m_element[0] = (double)_obj.r() / 255.0;
}
template<> template<> Color<double,2>::Color(const Color<uint8_t, 4>& _obj) {
	m_element[0] = (double)_obj.r() / 255.0;
	m_element[1] = (double)_obj.g() / 255.0;
}
template<> template<> Color<double,3>::Color(const Color<uint8_t, 4>& _obj) {
	m_element[0] = (double)_obj.r() / 255.0;
	m_element[1] = (double)_obj.g() / 255.0;
	m_element[2] = (double)_obj.b() / 255.0;
}
template<> template<> Color<double,4>::Color(const Color<uint8_t, 4>& _obj) {
	m_element[0] = (double)_obj.r() / 255.0;
	m_element[1] = (double)_obj.g() / 255.0;
	m_element[2] = (double)_obj.b() / 255.0;
	m_element[3] = (double)_obj.a() / 255.0;
}

// ===========================================================================================================

template<> template<> Color<double,1>::Color(const Color<uint16_t, 1>& _obj) {
	m_element[0] = (double)_obj.r() / 65535.0;
}
template<> template<> Color<double,2>::Color(const Color<uint16_t, 1>& _obj) {
	m_element[0] = (double)_obj.r() / 65535.0;
	m_element[1] = 0;
}
template<> template<> Color<double,3>::Color(const Color<uint16_t, 1>& _obj) {
	m_element[0] = (double)_obj.r() / 65535.0;
	m_element[1] = 0;
	m_element[2] = 0;
}
template<> template<> Color<double,4>::Color(const Color<uint16_t, 1>& _obj) {
	m_element[0] = (double)_obj.r() / 65535.0;
	m_element[1] = 0;
	m_element[2] = 0;
	m_element[3] = 0;
}
template<> template<> Color<double,1>::Color(const Color<uint16_t, 2>& _obj) {
	m_element[0] = (double)_obj.r() / 65535.0;
}
template<> template<> Color<double,2>::Color(const Color<uint16_t, 2>& _obj) {
	m_element[0] = (double)_obj.r() / 65535.0;
	m_element[1] = (double)_obj.g() / 65535.0;
}
template<> template<> Color<double,3>::Color(const Color<uint16_t, 2>& _obj) {
	m_element[0] = (double)_obj.r() / 65535.0;
	m_element[1] = (double)_obj.g() / 65535.0;
	m_element[2] = 0;
}
template<> template<> Color<double,4>::Color(const Color<uint16_t, 2>& _obj) {
	m_element[0] = (double)_obj.r() / 65535.0;
	m_element[1] = (double)_obj.g() / 65535.0;
	m_element[2] = 0;
	m_element[3] = 0;
}
template<> template<> Color<double,1>::Color(const Color<uint16_t, 3>& _obj) {
	m_element[0] = (double)_obj.r() / 65535.0;
}
template<> template<> Color<double,2>::Color(const Color<uint16_t, 3>& _obj) {
	m_element[0] = (double)_obj.r() / 65535.0;
	m_element[1] = (double)_obj.g() / 65535.0;
}
template<> template<> Color<double,3>::Color(const Color<uint16_t, 3>& _obj) {
	m_element[0] = (double)_obj.r() / 65535.0;
	m_element[1] = (double)_obj.g() / 65535.0;
	m_element[2] = (double)_obj.b() / 65535.0;
}
template<> template<> Color<double,4>::Color(const Color<uint16_t, 3>& _obj) {
	m_element[0] = (double)_obj.r() / 65535.0;
	m_element[1] = (double)_obj.g() / 65535.0;
	m_element[2] = (double)_obj.b() / 65535.0;
	m_element[3] = 0;
}
template<> template<> Color<double,1>::Color(const Color<uint16_t, 4>& _obj) {
	m_element[0] = (double)_obj.r() / 65535.0;
}
template<> template<> Color<double,2>::Color(const Color<uint16_t, 4>& _obj) {
	m_element[0] = (double)_obj.r() / 65535.0;
	m_element[1] = (double)_obj.g() / 65535.0;
}
template<> template<> Color<double,3>::Color(const Color<uint16_t, 4>& _obj) {
	m_element[0] = (double)_obj.r() / 65535.0;
	m_element[1] = (double)_obj.g() / 65535.0;
	m_element[2] = (double)_obj.b() / 65535.0;
}
template<> template<> Color<double,4>::Color(const Color<uint16_t, 4>& _obj) {
	m_element[0] = (double)_obj.r() / 65535.0;
	m_element[1] = (double)_obj.g() / 65535.0;
	m_element[2] = (double)_obj.b() / 65535.0;
	m_element[3] = (double)_obj.a() / 65535.0;
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
	m_element[3] = 0;
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
	m_element[3] = 0;
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
	m_element[3] = 0;
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
	m_element[3] = 0;
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
	m_element[3] = 0;
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
	m_element[3] = 0;
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
	m_element[3] = 0;
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
	m_element[3] = 0;
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
	m_element[3] = 0;
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
