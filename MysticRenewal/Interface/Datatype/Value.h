#pragma once
#include "Stdafx.h"

class CValue;

typedef std::vector<CValue> CValueVector;
typedef std::unordered_map<std::string, CValue> CValueMap;
typedef std::unordered_map<int, CValue> CValueMapIntKey;

class CValue
{
public:
	static const CValue Null;

	CValue();
	explicit CValue(unsigned char v);
	explicit CValue(int v);
	explicit CValue(float v);
	explicit CValue(double v);
	explicit CValue(bool v);
	explicit CValue(const char* v);
	explicit CValue(const std::string& v);

	explicit CValue(const CValueVector& v);
	explicit CValue(CValueVector&& v);

	explicit CValue(const CValueMap& v);
	explicit CValue(CValueMap&& v);

	explicit CValue(const CValueMapIntKey& v);
	explicit CValue(CValueMapIntKey&& v);

	CValue(const CValue& other);
	CValue(CValue&& other);
	~CValue();

	// assignment operator
	CValue& operator= (const CValue& other);
	CValue& operator= (CValue&& other);

	CValue& operator= (unsigned char v);
	CValue& operator= (int v);
	CValue& operator= (float v);
	CValue& operator= (double v);
	CValue& operator= (bool v);
	CValue& operator= (const char* v);
	CValue& operator= (const std::string& v);

	CValue& operator= (const CValueVector& v);
	CValue& operator= (CValueVector&& v);

	CValue& operator= (const CValueMap& v);
	CValue& operator= (CValueMap&& v);

	CValue& operator= (const CValueMapIntKey& v);
	CValue& operator= (CValueMapIntKey&& v);

	unsigned char asByte() const;
	int asInt() const;
	float asFloat() const;
	double asDouble() const;
	bool asBool() const;
	std::string asString() const;

	CValueVector& asCValueVector();
	const CValueVector& asCValueVector() const;

	CValueMap& asCValueMap();
	const CValueMap& asCValueMap() const;

	CValueMapIntKey& asIntKeyMap();
	const CValueMapIntKey& asIntKeyMap() const;

	inline bool isNull() const { return _type == Type::NONE; }

	enum class Type
	{
		NONE,
		BYTE,
		INTEGER,
		FLOAT,
		DOUBLE,
		BOOLEAN,
		STRING,
		VECTOR,
		MAP,
		INT_KEY_MAP
	};

	inline Type getType() const { return _type; };

	std::string getDescription();

private:
	void clear();

	union
	{
		unsigned char byteVal;
		int intVal;
		float floatVal;
		double doubleVal;
		bool boolVal;
	}_baseData;

	std::string _strData;
	CValueVector* _vectorData;
	CValueMap* _mapData;
	CValueMapIntKey* _intKeyMapData;

	Type _type;
};
