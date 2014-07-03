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
	m_element[3] = 0;
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
	m_element[3] = 0;
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
	m_element[3] = 0;
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
	m_element[3] = 0;
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
	m_element[3] = 0;
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
	m_element[3] = 0;
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
	m_element[3] = 0;
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
	m_element[3] = 0;
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
	m_element[3] = 0;
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
	m_element[0] = (uint16_t)(_obj.r()*65535.0f);
}
template<> template<> Color<uint16_t,2>::Color(const Color<float, 1>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()*65535.0f);
	m_element[1] = 0;
}
template<> template<> Color<uint16_t,3>::Color(const Color<float, 1>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()*65535.0f);
	m_element[1] = 0;
	m_element[2] = 0;
}
template<> template<> Color<uint16_t,4>::Color(const Color<float, 1>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()*65535.0f);
	m_element[1] = 0;
	m_element[2] = 0;
	m_element[3] = 0;
}
template<> template<> Color<uint16_t,1>::Color(const Color<float, 2>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()*65535.0f);
}
template<> template<> Color<uint16_t,2>::Color(const Color<float, 2>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()*65535.0f);
	m_element[1] = (uint16_t)(_obj.g()*65535.0f);
}
template<> template<> Color<uint16_t,3>::Color(const Color<float, 2>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()*65535.0f);
	m_element[1] = (uint16_t)(_obj.g()*65535.0f);
	m_element[2] = 0;
}
template<> template<> Color<uint16_t,4>::Color(const Color<float, 2>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()*65535.0f);
	m_element[1] = (uint16_t)(_obj.g()*65535.0f);
	m_element[2] = 0;
	m_element[3] = 0;
}
template<> template<> Color<uint16_t,1>::Color(const Color<float, 3>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()*65535.0f);
}
template<> template<> Color<uint16_t,2>::Color(const Color<float, 3>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()*65535.0f);
	m_element[1] = (uint16_t)(_obj.g()*65535.0f);
}
template<> template<> Color<uint16_t,3>::Color(const Color<float, 3>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()*65535.0f);
	m_element[1] = (uint16_t)(_obj.g()*65535.0f);
	m_element[2] = (uint16_t)(_obj.b()*65535.0f);
}
template<> template<> Color<uint16_t,4>::Color(const Color<float, 3>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()*65535.0f);
	m_element[1] = (uint16_t)(_obj.g()*65535.0f);
	m_element[2] = (uint16_t)(_obj.b()*65535.0f);
	m_element[3] = 0;
}
template<> template<> Color<uint16_t,1>::Color(const Color<float, 4>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()*65535.0f);
}
template<> template<> Color<uint16_t,2>::Color(const Color<float, 4>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()*65535.0f);
	m_element[1] = (uint16_t)(_obj.g()*65535.0f);
}
template<> template<> Color<uint16_t,3>::Color(const Color<float, 4>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()*65535.0f);
	m_element[1] = (uint16_t)(_obj.g()*65535.0f);
	m_element[2] = (uint16_t)(_obj.b()*65535.0f);
}
template<> template<> Color<uint16_t,4>::Color(const Color<float, 4>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()*65535.0f);
	m_element[1] = (uint16_t)(_obj.g()*65535.0f);
	m_element[2] = (uint16_t)(_obj.b()*65535.0f);
	m_element[3] = (uint16_t)(_obj.a()*65535.0f);
}

// ===========================================================================================================

template<> template<> Color<uint16_t,1>::Color(const Color<double, 1>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()*65535.0);
}
template<> template<> Color<uint16_t,2>::Color(const Color<double, 1>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()*65535.0);
	m_element[1] = 0;
}
template<> template<> Color<uint16_t,3>::Color(const Color<double, 1>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()*65535.0);
	m_element[1] = 0;
	m_element[2] = 0;
}
template<> template<> Color<uint16_t,4>::Color(const Color<double, 1>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()*65535.0);
	m_element[1] = 0;
	m_element[2] = 0;
	m_element[3] = 0;
}
template<> template<> Color<uint16_t,1>::Color(const Color<double, 2>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()*65535.0);
}
template<> template<> Color<uint16_t,2>::Color(const Color<double, 2>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()*65535.0);
	m_element[1] = (uint16_t)(_obj.g()*65535.0);
}
template<> template<> Color<uint16_t,3>::Color(const Color<double, 2>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()*65535.0);
	m_element[1] = (uint16_t)(_obj.g()*65535.0);
	m_element[2] = 0;
}
template<> template<> Color<uint16_t,4>::Color(const Color<double, 2>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()*65535.0);
	m_element[1] = (uint16_t)(_obj.g()*65535.0);
	m_element[2] = 0;
	m_element[3] = 0;
}
template<> template<> Color<uint16_t,1>::Color(const Color<double, 3>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()*65535.0);
}
template<> template<> Color<uint16_t,2>::Color(const Color<double, 3>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()*65535.0);
	m_element[1] = (uint16_t)(_obj.g()*65535.0);
}
template<> template<> Color<uint16_t,3>::Color(const Color<double, 3>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()*65535.0);
	m_element[1] = (uint16_t)(_obj.g()*65535.0);
	m_element[2] = (uint16_t)(_obj.b()*65535.0);
}
template<> template<> Color<uint16_t,4>::Color(const Color<double, 3>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()*65535.0);
	m_element[1] = (uint16_t)(_obj.g()*65535.0);
	m_element[2] = (uint16_t)(_obj.b()*65535.0);
	m_element[3] = 0;
}
template<> template<> Color<uint16_t,1>::Color(const Color<double, 4>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()*65535.0);
}
template<> template<> Color<uint16_t,2>::Color(const Color<double, 4>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()*65535.0);
	m_element[1] = (uint16_t)(_obj.g()*65535.0);
}
template<> template<> Color<uint16_t,3>::Color(const Color<double, 4>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()*65535.0);
	m_element[1] = (uint16_t)(_obj.g()*65535.0);
	m_element[2] = (uint16_t)(_obj.b()*65535.0);
}
template<> template<> Color<uint16_t,4>::Color(const Color<double, 4>& _obj) {
	m_element[0] = (uint16_t)(_obj.r()*65535.0);
	m_element[1] = (uint16_t)(_obj.g()*65535.0);
	m_element[2] = (uint16_t)(_obj.b()*65535.0);
	m_element[3] = (uint16_t)(_obj.a()*65535.0);
}

// ===========================================================================================================

