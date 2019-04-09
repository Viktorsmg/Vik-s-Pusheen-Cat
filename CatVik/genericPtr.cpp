#include "genericPtr.h"

void genericPtr::set(const genericPtr & val) {
	switch (val.type) {
		case 1:
			ptr = new int(*(int*)val.ptr); break;
		case 2:
			ptr = new double(*(double*)val.ptr); break;
		case 3:
			ptr = new bool(*(bool*)val.ptr); break;
		case 0:
			ptr = nullptr; break;
		default:
			//Big panic!
			break;
	}
	type = val.type;
	selfcontained = true;
}

void genericPtr::unset() {
	switch (type) {
		case 1:
			delete (int*)ptr; break;
		case 2:
			delete (double*)ptr; break;
		case 3:
			delete (bool*)ptr; break;
		case 0:
			; break; //Nothing to delete...
		default:
			//Big panic!
			break;
	}
}

genericPtr::genericPtr() {
	ptr = nullptr;
	type = 0;
}

genericPtr::genericPtr(const int &val) {
	ptr = new int(val);
	type = 1;
	selfcontained = true;
}

genericPtr::genericPtr(int * val) {
	ptr = val;
	type = 1;
	selfcontained = false;
}

genericPtr::genericPtr(const double & val) {
	ptr = new double(val);
	type = 2;
	selfcontained = true;
}

genericPtr::genericPtr(double * val) {
	ptr = val;
	type = 2;
	selfcontained = false;
}

genericPtr::genericPtr(const bool & val) {
	ptr = new bool(val);
	type = 3;
	selfcontained = true;
}

genericPtr::genericPtr(bool * val) {
	ptr = val;
	type = 3;
	selfcontained = false;
}

genericPtr::genericPtr(const genericPtr &val) {
	if (val.selfcontained) set(val); else { ptr = val.ptr; type = val.type; selfcontained = false; }
}


genericPtr::~genericPtr() {
	if (selfcontained) {
		switch (type) {
			case 1:
				delete (int*)ptr; break;
			case 2:
				delete (double*)ptr; break;
			case 3:
				delete (bool*)ptr; break;
			case 0:
				break;
			default:
				break;
				//big bad memory leak oh noes!!1!!111!
		}
	}
}

genericPtr& genericPtr::operator=(const genericPtr &val) {
	if(this == &val) return *this;

	if(val.selfcontained){
		unset(); set(val);
	} else {
		ptr = val.ptr; type = val.type; selfcontained = false;
	}
	return *this;
}

genericPtr& genericPtr::operator=(double val) {
	if (selfcontained) {
		unset(); set(val);
	} else {
		switch (type) {
			case 1:
				*(int*)ptr = (int)val; break;
			case 2:
				*(double*)ptr = val; break;
			case 3:
				*(bool*)ptr = (bool)val; break;
		}
	}
	return *this;
}

double genericPtr::get_double() const {
	switch (type) {
		case 1:
			return double(*(int*)ptr); break;
		case 2:
			return *(double*)ptr; break;
		case 3:
			return double(*(bool*)ptr); break;
		default:
			break;
			//Big bad!
	}
	return 0.0;
}

signed char genericPtr::get_type() const {
	return type;
}

bool genericPtr::is_selfcontained() const {
	return selfcontained;
}

#include <string>

string genericPtr::to_string() const {
	switch (type) {
		case 1:
			return std::to_string(*(int*)ptr);
		case 2:
			return std::to_string(*(double*)ptr);
		case 3:
			return std::to_string(*(bool*)ptr);
	}
	return string();
}

#include "commonMath.h"

genericPtr& genericPtr::operator+=(double val) {
	switch (type) {
		case 1:
			if (fabs(val) < 1.0) *(int*)ptr += isign(val);
			*(int*)ptr += int(val + 0.5); 
			break;
		case 2:
			*(double*)ptr += val; break;
		case 3:
			if (val > 0.0) *(bool*)ptr = true; else *(bool*)ptr = false; break;
		case 0:
			//Bad 
			break;
		default:
			break;
			//Big bad!
	}

	return *this;
}

genericPtr & genericPtr::operator-=(double val) {
	return *this += -val;
}

void genericPtr::setVal(const genericPtr &val) {
	if (type != val.type) return;
	switch (type) {
		case 1:
			*(int*)ptr = *(int*)val.ptr; break;
		case 2:
			*(double*)ptr = *(double*)val.ptr; break;
		case 3:
			*(bool*)ptr = *(bool*)val.ptr; break;
		case 0:
			break;
		default:
			break;
			//what de friggies? o ma gad
	}
}

ostream & operator<<(ostream & os, const genericPtr &val) {
	switch (val.type) {
		case 1:
			return os << *(int*)val.ptr;
		case 2:
			return os << *(double*)val.ptr;
		case 3:
			return os << *(bool*)val.ptr;
		case 0:
			return os << 0;
		default:
			return os << "genericPtr Error!";
	}
}

istream& operator>>(istream &is, genericPtr &val) {
	switch (val.type) {
		case 1:
			return is >> *(int*)val.ptr;
		case 2:
			return is >> *(double*)val.ptr;
		case 3:
			return is >> *(bool*)val.ptr;
		case 0:
			return is;
		default:
			break;
			//big poopoo bad bad
	}
	return is;
}
