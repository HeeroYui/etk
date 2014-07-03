// this work ...
template<> template<> Color<float,1>::Color(const Color<uint8_t, 1>& _obj) {
	m_element[0] = (float)_obj.r() / 255.0f;
}
template<> template<> Color<float,2>::Color(const Color<uint8_t, 1>& _obj) {
	m_element[0] = (float)_obj.r() / 255.0f;
	m_element[1] = 0;
}
template<> template<> Color<float,3>::Color(const Color<uint8_t, 1>& _obj) {
	m_element[0] = (float)_obj.r() / 255.0f;
	m_element[1] = 0;
	m_element[2] = 0;
}
template<> template<> Color<float,4>::Color(const Color<uint8_t, 1>& _obj) {
	m_element[0] = (float)_obj.r() / 255.0f;
	m_element[1] = 0;
	m_element[2] = 0;
	m_element[3] = 0;
}
template<> template<> Color<float,1>::Color(const Color<uint8_t, 2>& _obj) {
	m_element[0] = (float)_obj.r() / 255.0f;
}
template<> template<> Color<float,2>::Color(const Color<uint8_t, 2>& _obj) {
	m_element[0] = (float)_obj.r() / 255.0f;
	m_element[1] = (float)_obj.g() / 255.0f;
}
template<> template<> Color<float,3>::Color(const Color<uint8_t, 2>& _obj) {
	m_element[0] = (float)_obj.r() / 255.0f;
	m_element[1] = (float)_obj.g() / 255.0f;
	m_element[2] = 0;
}
template<> template<> Color<float,4>::Color(const Color<uint8_t, 2>& _obj) {
	m_element[0] = (float)_obj.r() / 255.0f;
	m_element[1] = (float)_obj.g() / 255.0f;
	m_element[2] = 0;
	m_element[3] = 0;
}
template<> template<> Color<float,1>::Color(const Color<uint8_t, 3>& _obj) {
	m_element[0] = (float)_obj.r() / 255.0f;
}
template<> template<> Color<float,2>::Color(const Color<uint8_t, 3>& _obj) {
	m_element[0] = (float)_obj.r() / 255.0f;
	m_element[1] = (float)_obj.g() / 255.0f;
}
template<> template<> Color<float,3>::Color(const Color<uint8_t, 3>& _obj) {
	m_element[0] = (float)_obj.r() / 255.0f;
	m_element[1] = (float)_obj.g() / 255.0f;
	m_element[2] = (float)_obj.b() / 255.0f;
}
template<> template<> Color<float,4>::Color(const Color<uint8_t, 3>& _obj) {
	m_element[0] = (float)_obj.r() / 255.0f;
	m_element[1] = (float)_obj.g() / 255.0f;
	m_element[2] = (float)_obj.b() / 255.0f;
	m_element[3] = 0;
}
template<> template<> Color<float,1>::Color(const Color<uint8_t, 4>& _obj) {
	m_element[0] = (float)_obj.r() / 255.0f;
}
template<> template<> Color<float,2>::Color(const Color<uint8_t, 4>& _obj) {
	m_element[0] = (float)_obj.r() / 255.0f;
	m_element[1] = (float)_obj.g() / 255.0f;
}
template<> template<> Color<float,3>::Color(const Color<uint8_t, 4>& _obj) {
	m_element[0] = (float)_obj.r() / 255.0f;
	m_element[1] = (float)_obj.g() / 255.0f;
	m_element[2] = (float)_obj.b() / 255.0f;
}
template<> template<> Color<float,4>::Color(const Color<uint8_t, 4>& _obj) {
	m_element[0] = (float)_obj.r() / 255.0f;
	m_element[1] = (float)_obj.g() / 255.0f;
	m_element[2] = (float)_obj.b() / 255.0f;
	m_element[3] = (float)_obj.a() / 255.0f;
}

// ===========================================================================================================

template<> template<> Color<float,1>::Color(const Color<uint16_t, 1>& _obj) {
	m_element[0] = (float)_obj.r() / 65535.0f;
}
template<> template<> Color<float,2>::Color(const Color<uint16_t, 1>& _obj) {
	m_element[0] = (float)_obj.r() / 65535.0f;
	m_element[1] = 0;
}
template<> template<> Color<float,3>::Color(const Color<uint16_t, 1>& _obj) {
	m_element[0] = (float)_obj.r() / 65535.0f;
	m_element[1] = 0;
	m_element[2] = 0;
}
template<> template<> Color<float,4>::Color(const Color<uint16_t, 1>& _obj) {
	m_element[0] = (float)_obj.r() / 65535.0f;
	m_element[1] = 0;
	m_element[2] = 0;
	m_element[3] = 0;
}
template<> template<> Color<float,1>::Color(const Color<uint16_t, 2>& _obj) {
	m_element[0] = (float)_obj.r() / 65535.0f;
}
template<> template<> Color<float,2>::Color(const Color<uint16_t, 2>& _obj) {
	m_element[0] = (float)_obj.r() / 65535.0f;
	m_element[1] = (float)_obj.g() / 65535.0f;
}
template<> template<> Color<float,3>::Color(const Color<uint16_t, 2>& _obj) {
	m_element[0] = (float)_obj.r() / 65535.0f;
	m_element[1] = (float)_obj.g() / 65535.0f;
	m_element[2] = 0;
}
template<> template<> Color<float,4>::Color(const Color<uint16_t, 2>& _obj) {
	m_element[0] = (float)_obj.r() / 65535.0f;
	m_element[1] = (float)_obj.g() / 65535.0f;
	m_element[2] = 0;
	m_element[3] = 0;
}
template<> template<> Color<float,1>::Color(const Color<uint16_t, 3>& _obj) {
	m_element[0] = (float)_obj.r() / 65535.0f;
}
template<> template<> Color<float,2>::Color(const Color<uint16_t, 3>& _obj) {
	m_element[0] = (float)_obj.r() / 65535.0f;
	m_element[1] = (float)_obj.g() / 65535.0f;
}
template<> template<> Color<float,3>::Color(const Color<uint16_t, 3>& _obj) {
	m_element[0] = (float)_obj.r() / 65535.0f;
	m_element[1] = (float)_obj.g() / 65535.0f;
	m_element[2] = (float)_obj.b() / 65535.0f;
}
template<> template<> Color<float,4>::Color(const Color<uint16_t, 3>& _obj) {
	m_element[0] = (float)_obj.r() / 65535.0f;
	m_element[1] = (float)_obj.g() / 65535.0f;
	m_element[2] = (float)_obj.b() / 65535.0f;
	m_element[3] = 0;
}
template<> template<> Color<float,1>::Color(const Color<uint16_t, 4>& _obj) {
	m_element[0] = (float)_obj.r() / 65535.0f;
}
template<> template<> Color<float,2>::Color(const Color<uint16_t, 4>& _obj) {
	m_element[0] = (float)_obj.r() / 65535.0f;
	m_element[1] = (float)_obj.g() / 65535.0f;
}
template<> template<> Color<float,3>::Color(const Color<uint16_t, 4>& _obj) {
	m_element[0] = (float)_obj.r() / 65535.0f;
	m_element[1] = (float)_obj.g() / 65535.0f;
	m_element[2] = (float)_obj.b() / 65535.0f;
}
template<> template<> Color<float,4>::Color(const Color<uint16_t, 4>& _obj) {
	m_element[0] = (float)_obj.r() / 65535.0f;
	m_element[1] = (float)_obj.g() / 65535.0f;
	m_element[2] = (float)_obj.b() / 65535.0f;
	m_element[3] = (float)_obj.a() / 65535.0f;
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
	m_element[3] = 0;
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
	m_element[3] = 0;
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
	m_element[3] = 0;
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
	m_element[3] = 0;
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
	m_element[3] = 0;
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
	m_element[3] = 0;
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
	m_element[3] = 0;
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
	m_element[3] = 0;
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
	m_element[3] = 0;
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

// ===========================================================================================================




/*
template<int MY_TYPE_SIZE> template<> Color<float,MY_TYPE_SIZE>::Color(const etk::Color<uint8_t, 4>& _obj) {
	if (MY_TYPE_SIZE >= 1) {
		m_element[0] = (float)_obj.r() / 255.0f;
	}
	if (MY_TYPE_SIZE >= 2) {
		m_element[1] = (float)_obj.g() / 255.0f;
	}
	if (MY_TYPE_SIZE >= 3) {
		m_element[2] = (float)_obj.b() / 255.0f;
	}
	if (MY_TYPE_SIZE >= 4) {
		m_element[3] = (float)_obj.a() / 255.0f;
	}
}
*/
/*
template<> template<int MY_TYPE_SIZE> Color<float,4>::Color(const etk::Color<uint8_t, MY_TYPE_SIZE>& _obj) {
	if (MY_TYPE_SIZE >= 1) {
		m_element[0] = (float)_obj.r() / 255.0f;
	}
	if (MY_TYPE_SIZE >= 2) {
		m_element[1] = (float)_obj.g() / 255.0f;
	}
	if (MY_TYPE_SIZE >= 3) {
		m_element[2] = (float)_obj.b() / 255.0f;
	}
	if (MY_TYPE_SIZE >= 4) {
		m_element[3] = (float)_obj.a() / 255.0f;
	}
}
*/


/*
template<int MY_TYPE_SIZE> Color<float,MY_TYPE_SIZE>::Color(const etk::Color<uint8_t, 4>& _obj) {
	if (MY_TYPE_SIZE >= 1) {
		if (MY_TYPE_SIZE_2 >= 1) {
			m_element[0] = (float)_obj.m_element[0] / 255.0f;
		}
	}
	if (MY_TYPE_SIZE >= 2) {
		if (MY_TYPE_SIZE_2 >= 2) {
			m_element[1] = (float)_obj.m_element[1] / 255.0f;
		} else {
			m_element[1] = 0;
		}
	}
	if (MY_TYPE_SIZE >= 3) {
		if (MY_TYPE_SIZE_2 >= 3) {
			m_element[2] = (float)_obj.m_element[2] / 255.0f;
		} else {
			m_element[2] = 0;
		}
	}
	if (MY_TYPE_SIZE >= 4) {
		if (MY_TYPE_SIZE_2 >= 4) {
			m_element[3] = (float)_obj.m_element[3] / 255.0f;
		} else {
			m_element[3] = 0;
		}
	}
}

template<int MY_TYPE_SIZE> Color<float,MY_TYPE_SIZE>::Color(const etk::Color<uint8_t, 4>& _obj) {
	if (MY_TYPE_SIZE >= 1) {
		m_element[0] = (float)_obj.m_element[0] / 255.0f;
	}
	if (MY_TYPE_SIZE >= 2) {
		m_element[1] = (float)_obj.m_element[1] / 255.0f;
	}
	if (MY_TYPE_SIZE >= 3) {
		m_element[2] = (float)_obj.m_element[2] / 255.0f;
	}
	if (MY_TYPE_SIZE >= 4) {
		m_element[3] = (float)_obj.m_element[3] / 255.0f;
	}
}
*/