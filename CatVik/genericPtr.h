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
	genericPtr(const int &val);
	genericPtr(int *val);
	genericPtr(const double &val);
	genericPtr(double *val);
	genericPtr(const bool &val);
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

	friend ostream& operator<<(ostream& os, const genericPtr &val);
	friend istream& operator>>(istream& is, genericPtr &val);

	void setVal(const genericPtr &val);
};

