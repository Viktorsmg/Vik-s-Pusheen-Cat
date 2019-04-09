#pragma once

#include <iostream>
using std::ostream;
using std::istream;
using std::string;

class genericPtr {

	//0 - nullptr
	//1 - int
	//2 - double
	//3 - bool
	void *ptr;

	//0 - nullptr
	//1 - int
	//2 - double
	//3 - bool
	signed char type;

	//true - points to an object it owns (created), will delete when it dies
	//false - points to some other object, can be used as universal access, no delete
	bool selfcontained;

	void set(const genericPtr &val);
	void unset();

public:


	genericPtr();
	explicit genericPtr(const int &val);
	genericPtr(int *val);
	explicit genericPtr(const double &val);
	genericPtr(double *val);
	explicit genericPtr(const bool &val);
	genericPtr(bool *val);

	genericPtr(const genericPtr &val);

	~genericPtr();

	genericPtr& operator=(const genericPtr &val);
	genericPtr& operator=(double val);

	double get_double() const;
	signed char get_type() const;
	bool is_selfcontained() const;

	string to_string() const;

	genericPtr& operator+=(double val);
	genericPtr& operator-=(double val);

	template<typename streamtype>
	friend streamtype& operator<<(streamtype& os, const genericPtr &val);
	template<typename streamtype>
	friend streamtype& operator>>(streamtype& is, genericPtr &val);

	void setVal(const genericPtr &val);
};

template<typename streamtype>
streamtype& operator<<(streamtype& os, const genericPtr &val) {
	switch (val.type) {
		case 1:
			os << *(int*)val.ptr; break;
		case 2:
			os << *(double*)val.ptr; break;
		case 3:
			os << *(bool*)val.ptr; break;
		case 0:
			os << 0; break;
		default:
			os << "genericPtr Error!"; break;
	}
	return os;
}

template<typename streamtype>
streamtype& operator>>(streamtype& is, genericPtr &val) {
	switch (val.type) {
		case 1:
			is >> *(int*)val.ptr; break;
		case 2:
			is >> *(double*)val.ptr; break;
		case 3:
			is >> *(bool*)val.ptr; break;
		case 0:
			break;
		default:
			break;
			//big poopoo bad bad
	}
	return is;
}