#pragma once

class Callback
{
public:
	virtual ~Callback() {}
	virtual void triggerCallback() {}
};

template <class T>
class CallbackT : public Callback
{
	T*		_ref;
	void (T::*_method)();
public:
	CallbackT(T* ref, void (T::*method)()) {
		this->_ref = ref;
		this->_method = method;
	}
	~CallbackT(void) {}

	void		triggerCallback() {
		(this->_ref->*_method)();
	}
};

