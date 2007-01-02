// a class to store long values with a possible NULL state

#ifndef __DB_NULL_H__
#define __DB_NULL_H__

class CNullableLong {

protected:

	long value;
	bool is_null;

public:

	CNullableLong(void) { is_null = true; }
	CNullableLong(long value) { is_null = false; this->value = value; }

	void SetNull( bool isNull ) { is_null = isNull; }
	bool IsNull(void) { return is_null; }

	operator long&() { return value; }

};


#endif
