
template<> const Color<uint8_t, 1> Color<uint8_t, 1>::emptyColor(0);
template<> const Color<uint8_t, 2> Color<uint8_t, 2>::emptyColor(0,0);
template<> const Color<uint8_t, 3> Color<uint8_t, 3>::emptyColor(0,0,0);
template<> const Color<uint8_t, 4> Color<uint8_t, 4>::emptyColor(0,0,0,0xFF);

// this work ...
template<> template<> Color<uint8_t,1>::Color(const Color<uint8_t, 1>& _obj) {
	m_element[0] = _obj.r();
}
template<> template<> Color<uint8_t,2>::Color(const Color<uint8_t, 1>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = 0;
}
template<> template<> Color<uint8_t,3>::Color(const Color<uint8_t, 1>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = 0;
	m_element[2] = 0;
}
template<> template<> Color<uint8_t,4>::Color(const Color<uint8_t, 1>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = 0;
	m_element[2] = 0;
	m_element[3] = 0;
}
template<> template<> Color<uint8_t,1>::Color(const Color<uint8_t, 2>& _obj) {
	m_element[0] = _obj.r();
}
template<> template<> Color<uint8_t,2>::Color(const Color<uint8_t, 2>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
}
template<> template<> Color<uint8_t,3>::Color(const Color<uint8_t, 2>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
	m_element[2] = 0;
}
template<> template<> Color<uint8_t,4>::Color(const Color<uint8_t, 2>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
	m_element[2] = 0;
	m_element[3] = 0;
}
template<> template<> Color<uint8_t,1>::Color(const Color<uint8_t, 3>& _obj) {
	m_element[0] = _obj.r();
}
template<> template<> Color<uint8_t,2>::Color(const Color<uint8_t, 3>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
}
template<> template<> Color<uint8_t,3>::Color(const Color<uint8_t, 3>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
	m_element[2] = _obj.b();
}
template<> template<> Color<uint8_t,4>::Color(const Color<uint8_t, 3>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
	m_element[2] = _obj.b();
	m_element[3] = 0;
}
template<> template<> Color<uint8_t,1>::Color(const Color<uint8_t, 4>& _obj) {
	m_element[0] = _obj.r();
}
template<> template<> Color<uint8_t,2>::Color(const Color<uint8_t, 4>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
}
template<> template<> Color<uint8_t,3>::Color(const Color<uint8_t, 4>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
	m_element[2] = _obj.b();
}
template<> template<> Color<uint8_t,4>::Color(const Color<uint8_t, 4>& _obj) {
	m_element[0] = _obj.r();
	m_element[1] = _obj.g();
	m_element[2] = _obj.b();
	m_element[3] = _obj.a();
}

// ===========================================================================================================

template<> template<> Color<uint8_t,1>::Color(const Color<uint16_t, 1>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()>>8);
}
template<> template<> Color<uint8_t,2>::Color(const Color<uint16_t, 1>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()>>8);
	m_element[1] = 0;
}
template<> template<> Color<uint8_t,3>::Color(const Color<uint16_t, 1>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()>>8);
	m_element[1] = 0;
	m_element[2] = 0;
}
template<> template<> Color<uint8_t,4>::Color(const Color<uint16_t, 1>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()>>8);
	m_element[1] = 0;
	m_element[2] = 0;
	m_element[3] = 0;
}
template<> template<> Color<uint8_t,1>::Color(const Color<uint16_t, 2>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()>>8);
}
template<> template<> Color<uint8_t,2>::Color(const Color<uint16_t, 2>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()>>8);
	m_element[1] = (uint8_t)(_obj.g()>>8);
}
template<> template<> Color<uint8_t,3>::Color(const Color<uint16_t, 2>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()>>8);
	m_element[1] = (uint8_t)(_obj.g()>>8);
	m_element[2] = 0;
}
template<> template<> Color<uint8_t,4>::Color(const Color<uint16_t, 2>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()>>8);
	m_element[1] = (uint8_t)(_obj.g()>>8);
	m_element[2] = 0;
	m_element[3] = 0;
}
template<> template<> Color<uint8_t,1>::Color(const Color<uint16_t, 3>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()>>8);
}
template<> template<> Color<uint8_t,2>::Color(const Color<uint16_t, 3>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()>>8);
	m_element[1] = (uint8_t)(_obj.g()>>8);
}
template<> template<> Color<uint8_t,3>::Color(const Color<uint16_t, 3>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()>>8);
	m_element[1] = (uint8_t)(_obj.g()>>8);
	m_element[2] = (uint8_t)(_obj.b()>>8);
}
template<> template<> Color<uint8_t,4>::Color(const Color<uint16_t, 3>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()>>8);
	m_element[1] = (uint8_t)(_obj.g()>>8);
	m_element[2] = (uint8_t)(_obj.b()>>8);
	m_element[3] = 0;
}
template<> template<> Color<uint8_t,1>::Color(const Color<uint16_t, 4>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()>>8);
}
template<> template<> Color<uint8_t,2>::Color(const Color<uint16_t, 4>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()>>8);
	m_element[1] = (uint8_t)(_obj.g()>>8);
}
template<> template<> Color<uint8_t,3>::Color(const Color<uint16_t, 4>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()>>8);
	m_element[1] = (uint8_t)(_obj.g()>>8);
	m_element[2] = (uint8_t)(_obj.b()>>8);
}
template<> template<> Color<uint8_t,4>::Color(const Color<uint16_t, 4>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()>>8);
	m_element[1] = (uint8_t)(_obj.g()>>8);
	m_element[2] = (uint8_t)(_obj.b()>>8);
	m_element[3] = (uint8_t)(_obj.a()>>8);
}

// ===========================================================================================================

template<> template<> Color<uint8_t,1>::Color(const Color<uint32_t, 1>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()>>24);
}
template<> template<> Color<uint8_t,2>::Color(const Color<uint32_t, 1>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()>>24);
	m_element[1] = 0;
}
template<> template<> Color<uint8_t,3>::Color(const Color<uint32_t, 1>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()>>24);
	m_element[1] = 0;
	m_element[2] = 0;
}
template<> template<> Color<uint8_t,4>::Color(const Color<uint32_t, 1>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()>>24);
	m_element[1] = 0;
	m_element[2] = 0;
	m_element[3] = 0;
}
template<> template<> Color<uint8_t,1>::Color(const Color<uint32_t, 2>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()>>24);
}
template<> template<> Color<uint8_t,2>::Color(const Color<uint32_t, 2>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()>>24);
	m_element[1] = (uint8_t)(_obj.g()>>24);
}
template<> template<> Color<uint8_t,3>::Color(const Color<uint32_t, 2>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()>>24);
	m_element[1] = (uint8_t)(_obj.g()>>24);
	m_element[2] = 0;
}
template<> template<> Color<uint8_t,4>::Color(const Color<uint32_t, 2>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()>>24);
	m_element[1] = (uint8_t)(_obj.g()>>24);
	m_element[2] = 0;
	m_element[3] = 0;
}
template<> template<> Color<uint8_t,1>::Color(const Color<uint32_t, 3>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()>>24);
}
template<> template<> Color<uint8_t,2>::Color(const Color<uint32_t, 3>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()>>24);
	m_element[1] = (uint8_t)(_obj.g()>>24);
}
template<> template<> Color<uint8_t,3>::Color(const Color<uint32_t, 3>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()>>24);
	m_element[1] = (uint8_t)(_obj.g()>>24);
	m_element[2] = (uint8_t)(_obj.b()>>24);
}
template<> template<> Color<uint8_t,4>::Color(const Color<uint32_t, 3>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()>>24);
	m_element[1] = (uint8_t)(_obj.g()>>24);
	m_element[2] = (uint8_t)(_obj.b()>>24);
	m_element[3] = 0;
}
template<> template<> Color<uint8_t,1>::Color(const Color<uint32_t, 4>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()>>24);
}
template<> template<> Color<uint8_t,2>::Color(const Color<uint32_t, 4>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()>>24);
	m_element[1] = (uint8_t)(_obj.g()>>24);
}
template<> template<> Color<uint8_t,3>::Color(const Color<uint32_t, 4>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()>>24);
	m_element[1] = (uint8_t)(_obj.g()>>24);
	m_element[2] = (uint8_t)(_obj.b()>>24);
}
template<> template<> Color<uint8_t,4>::Color(const Color<uint32_t, 4>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()>>24);
	m_element[1] = (uint8_t)(_obj.g()>>24);
	m_element[2] = (uint8_t)(_obj.b()>>24);
	m_element[3] = (uint8_t)(_obj.a()>>24);
}

// ===========================================================================================================

template<> template<> Color<uint8_t,1>::Color(const Color<float, 1>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()*255.0f);
}
template<> template<> Color<uint8_t,2>::Color(const Color<float, 1>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()*255.0f);
	m_element[1] = 0;
}
template<> template<> Color<uint8_t,3>::Color(const Color<float, 1>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()*255.0f);
	m_element[1] = 0;
	m_element[2] = 0;
}
template<> template<> Color<uint8_t,4>::Color(const Color<float, 1>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()*255.0f);
	m_element[1] = 0;
	m_element[2] = 0;
	m_element[3] = 0;
}
template<> template<> Color<uint8_t,1>::Color(const Color<float, 2>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()*255.0f);
}
template<> template<> Color<uint8_t,2>::Color(const Color<float, 2>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()*255.0f);
	m_element[1] = (uint8_t)(_obj.g()*255.0f);
}
template<> template<> Color<uint8_t,3>::Color(const Color<float, 2>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()*255.0f);
	m_element[1] = (uint8_t)(_obj.g()*255.0f);
	m_element[2] = 0;
}
template<> template<> Color<uint8_t,4>::Color(const Color<float, 2>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()*255.0f);
	m_element[1] = (uint8_t)(_obj.g()*255.0f);
	m_element[2] = 0;
	m_element[3] = 0;
}
template<> template<> Color<uint8_t,1>::Color(const Color<float, 3>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()*255.0f);
}
template<> template<> Color<uint8_t,2>::Color(const Color<float, 3>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()*255.0f);
	m_element[1] = (uint8_t)(_obj.g()*255.0f);
}
template<> template<> Color<uint8_t,3>::Color(const Color<float, 3>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()*255.0f);
	m_element[1] = (uint8_t)(_obj.g()*255.0f);
	m_element[2] = (uint8_t)(_obj.b()*255.0f);
}
template<> template<> Color<uint8_t,4>::Color(const Color<float, 3>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()*255.0f);
	m_element[1] = (uint8_t)(_obj.g()*255.0f);
	m_element[2] = (uint8_t)(_obj.b()*255.0f);
	m_element[3] = 0;
}
template<> template<> Color<uint8_t,1>::Color(const Color<float, 4>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()*255.0f);
}
template<> template<> Color<uint8_t,2>::Color(const Color<float, 4>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()*255.0f);
	m_element[1] = (uint8_t)(_obj.g()*255.0f);
}
template<> template<> Color<uint8_t,3>::Color(const Color<float, 4>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()*255.0f);
	m_element[1] = (uint8_t)(_obj.g()*255.0f);
	m_element[2] = (uint8_t)(_obj.b()*255.0f);
}
template<> template<> Color<uint8_t,4>::Color(const Color<float, 4>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()*255.0f);
	m_element[1] = (uint8_t)(_obj.g()*255.0f);
	m_element[2] = (uint8_t)(_obj.b()*255.0f);
	m_element[3] = (uint8_t)(_obj.a()*255.0f);
}

// ===========================================================================================================

template<> template<> Color<uint8_t,1>::Color(const Color<double, 1>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()*256.0);
}
template<> template<> Color<uint8_t,2>::Color(const Color<double, 1>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()*256.0);
	m_element[1] = 0;
}
template<> template<> Color<uint8_t,3>::Color(const Color<double, 1>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()*256.0);
	m_element[1] = 0;
	m_element[2] = 0;
}
template<> template<> Color<uint8_t,4>::Color(const Color<double, 1>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()*256.0);
	m_element[1] = 0;
	m_element[2] = 0;
	m_element[3] = 0;
}
template<> template<> Color<uint8_t,1>::Color(const Color<double, 2>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()*256.0);
}
template<> template<> Color<uint8_t,2>::Color(const Color<double, 2>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()*256.0);
	m_element[1] = (uint8_t)(_obj.g()*256.0);
}
template<> template<> Color<uint8_t,3>::Color(const Color<double, 2>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()*256.0);
	m_element[1] = (uint8_t)(_obj.g()*256.0);
	m_element[2] = 0;
}
template<> template<> Color<uint8_t,4>::Color(const Color<double, 2>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()*256.0);
	m_element[1] = (uint8_t)(_obj.g()*256.0);
	m_element[2] = 0;
	m_element[3] = 0;
}
template<> template<> Color<uint8_t,1>::Color(const Color<double, 3>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()*256.0);
}
template<> template<> Color<uint8_t,2>::Color(const Color<double, 3>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()*256.0);
	m_element[1] = (uint8_t)(_obj.g()*256.0);
}
template<> template<> Color<uint8_t,3>::Color(const Color<double, 3>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()*256.0);
	m_element[1] = (uint8_t)(_obj.g()*256.0);
	m_element[2] = (uint8_t)(_obj.b()*256.0);
}
template<> template<> Color<uint8_t,4>::Color(const Color<double, 3>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()*256.0);
	m_element[1] = (uint8_t)(_obj.g()*256.0);
	m_element[2] = (uint8_t)(_obj.b()*256.0);
	m_element[3] = 0;
}
template<> template<> Color<uint8_t,1>::Color(const Color<double, 4>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()*256.0);
}
template<> template<> Color<uint8_t,2>::Color(const Color<double, 4>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()*256.0);
	m_element[1] = (uint8_t)(_obj.g()*256.0);
}
template<> template<> Color<uint8_t,3>::Color(const Color<double, 4>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()*256.0);
	m_element[1] = (uint8_t)(_obj.g()*256.0);
	m_element[2] = (uint8_t)(_obj.b()*256.0);
}
template<> template<> Color<uint8_t,4>::Color(const Color<double, 4>& _obj) {
	m_element[0] = (uint8_t)(_obj.r()*256.0);
	m_element[1] = (uint8_t)(_obj.g()*256.0);
	m_element[2] = (uint8_t)(_obj.b()*256.0);
	m_element[3] = (uint8_t)(_obj.a()*256.0);
}

// ===========================================================================================================

