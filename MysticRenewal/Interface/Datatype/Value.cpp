#include "Stdafx.h"

const CValue CValue::Null;

CValue::CValue()
: _vectorData(nullptr)
, _mapData(nullptr)
, _intKeyMapData(nullptr)
, _type(Type::NONE)
{

}

CValue::CValue(unsigned char v)
: _vectorData(nullptr)
, _mapData(nullptr)
, _intKeyMapData(nullptr)
, _type(Type::BYTE)
{
	_baseData.byteVal = v;
}

CValue::CValue(int v)
: _vectorData(nullptr)
, _mapData(nullptr)
, _intKeyMapData(nullptr)
, _type(Type::INTEGER)
{
	_baseData.intVal = v;
}

CValue::CValue(float v)
: _vectorData(nullptr)
, _mapData(nullptr)
, _intKeyMapData(nullptr)
, _type(Type::FLOAT)
{
	_baseData.floatVal = v;
}

CValue::CValue(double v)
: _vectorData(nullptr)
, _mapData(nullptr)
, _intKeyMapData(nullptr)
, _type(Type::DOUBLE)
{
	_baseData.doubleVal = v;
}

CValue::CValue(bool v)
: _vectorData(nullptr)
, _mapData(nullptr)
, _intKeyMapData(nullptr)
, _type(Type::BOOLEAN)
{
	_baseData.boolVal = v;
}

CValue::CValue(const char* v)
: _vectorData(nullptr)
, _mapData(nullptr)
, _intKeyMapData(nullptr)
, _type(Type::STRING)
{
	_strData = v;
}

CValue::CValue(const std::string& v)
: _vectorData(nullptr)
, _mapData(nullptr)
, _intKeyMapData(nullptr)
, _type(Type::STRING)
{
	_strData = v;
}

CValue::CValue(const CValueVector& v)
: _vectorData(new CValueVector())
, _mapData(nullptr)
, _intKeyMapData(nullptr)
, _type(Type::VECTOR)
{
	*_vectorData = v;
}

CValue::CValue(CValueVector&& v)
: _vectorData(new CValueVector())
, _mapData(nullptr)
, _intKeyMapData(nullptr)
, _type(Type::VECTOR)
{
	*_vectorData = std::move(v);
}

CValue::CValue(const CValueMap& v)
: _vectorData(nullptr)
, _mapData(new CValueMap())
, _intKeyMapData(nullptr)
, _type(Type::MAP)
{
	*_mapData = v;
}

CValue::CValue(CValueMap&& v)
: _vectorData(nullptr)
, _mapData(new CValueMap())
, _intKeyMapData(nullptr)
, _type(Type::MAP)
{
	*_mapData = std::move(v);
}

CValue::CValue(const CValueMapIntKey& v)
: _vectorData(nullptr)
, _mapData(nullptr)
, _intKeyMapData(new CValueMapIntKey())
, _type(Type::INT_KEY_MAP)
{
	*_intKeyMapData = v;
}

CValue::CValue(CValueMapIntKey&& v)
: _vectorData(nullptr)
, _mapData(nullptr)
, _intKeyMapData(new CValueMapIntKey())
, _type(Type::INT_KEY_MAP)
{
	*_intKeyMapData = std::move(v);
}

CValue::CValue(const CValue& other)
: _vectorData(nullptr)
, _mapData(nullptr)
, _intKeyMapData(nullptr)
{
	*this = other;
}

CValue::CValue(CValue&& other)
: _vectorData(nullptr)
, _mapData(nullptr)
, _intKeyMapData(nullptr)
{
	*this = std::move(other);
}

CValue::~CValue()
{
	clear();
}

CValue& CValue::operator= (const CValue& other)
{
	if (this != &other) {
		switch (other._type) {
		case Type::BYTE:
			_baseData.byteVal = other._baseData.byteVal;
			break;
		case Type::INTEGER:
			_baseData.intVal = other._baseData.intVal;
			break;
		case Type::FLOAT:
			_baseData.floatVal = other._baseData.floatVal;
			break;
		case Type::DOUBLE:
			_baseData.doubleVal = other._baseData.doubleVal;
			break;
		case Type::BOOLEAN:
			_baseData.boolVal = other._baseData.boolVal;
			break;
		case Type::STRING:
			_strData = other._strData;
			break;
		case Type::VECTOR:
			if (_vectorData == nullptr)
				_vectorData = new CValueVector();
			*_vectorData = *other._vectorData;
			break;
		case Type::MAP:
			if (_mapData == nullptr)
				_mapData = new CValueMap();
			*_mapData = *other._mapData;
			break;
		case Type::INT_KEY_MAP:
			if (_intKeyMapData == nullptr)
				_intKeyMapData = new CValueMapIntKey();
			*_intKeyMapData = *other._intKeyMapData;
			break;
		default:
			break;
		}
		_type = other._type;
	}
	return *this;
}

CValue& CValue::operator= (CValue&& other)
{
	if (this != &other) {
		switch (other._type) {
		case Type::BYTE:
			_baseData.byteVal = other._baseData.byteVal;
			break;
		case Type::INTEGER:
			_baseData.intVal = other._baseData.intVal;
			break;
		case Type::FLOAT:
			_baseData.floatVal = other._baseData.floatVal;
			break;
		case Type::DOUBLE:
			_baseData.doubleVal = other._baseData.doubleVal;
			break;
		case Type::BOOLEAN:
			_baseData.boolVal = other._baseData.boolVal;
			break;
		case Type::STRING:
			_strData = other._strData;
			break;
		case Type::VECTOR:
			CC_SAFE_DELETE(_vectorData);
			_vectorData = other._vectorData;
			break;
		case Type::MAP:
			CC_SAFE_DELETE(_mapData);
			_mapData = other._mapData;
			break;
		case Type::INT_KEY_MAP:
			CC_SAFE_DELETE(_intKeyMapData);
			_intKeyMapData = other._intKeyMapData;
			break;
		default:
			break;
		}
		_type = other._type;

		other._vectorData = nullptr;
		other._mapData = nullptr;
		other._intKeyMapData = nullptr;
		other._type = Type::NONE;
	}

	return *this;
}

CValue& CValue::operator= (unsigned char v)
{
	clear();
	_type = Type::BYTE;
	_baseData.byteVal = v;
	return *this;
}

CValue& CValue::operator= (int v)
{
	clear();
	_type = Type::INTEGER;
	_baseData.intVal = v;
	return *this;
}

CValue& CValue::operator= (float v)
{
	clear();
	_type = Type::FLOAT;
	_baseData.floatVal = v;
	return *this;
}

CValue& CValue::operator= (double v)
{
	clear();
	_type = Type::DOUBLE;
	_baseData.doubleVal = v;
	return *this;
}

CValue& CValue::operator= (bool v)
{
	clear();
	_type = Type::BOOLEAN;
	_baseData.boolVal = v;
	return *this;
}

CValue& CValue::operator= (const char* v)
{
	clear();
	_type = Type::STRING;
	_strData = v ? v : "";
	return *this;
}

CValue& CValue::operator= (const std::string& v)
{
	clear();
	_type = Type::STRING;
	_strData = v;
	return *this;
}

CValue& CValue::operator= (const CValueVector& v)
{
	clear();
	_type = Type::VECTOR;
	_vectorData = new CValueVector();
	*_vectorData = v;
	return *this;
}

CValue& CValue::operator= (CValueVector&& v)
{
	clear();
	_type = Type::VECTOR;
	_vectorData = new CValueVector();
	*_vectorData = std::move(v);
	return *this;
}

CValue& CValue::operator= (const CValueMap& v)
{
	clear();
	_type = Type::MAP;
	_mapData = new CValueMap();
	*_mapData = v;
	return *this;
}

CValue& CValue::operator= (CValueMap&& v)
{
	clear();
	_type = Type::MAP;
	_mapData = new CValueMap();
	*_mapData = std::move(v);
	return *this;
}

CValue& CValue::operator= (const CValueMapIntKey& v)
{
	clear();
	_type = Type::INT_KEY_MAP;
	_intKeyMapData = new CValueMapIntKey();
	*_intKeyMapData = v;
	return *this;
}

CValue& CValue::operator= (CValueMapIntKey&& v)
{
	clear();
	_type = Type::INT_KEY_MAP;
	_intKeyMapData = new CValueMapIntKey();
	*_intKeyMapData = std::move(v);
	return *this;
}

///
unsigned char CValue::asByte() const
{
	//CCASSERT(_type != Type::VECTOR && _type != Type::MAP, "");

	if (_type == Type::BYTE)
	{
		return _baseData.byteVal;
	}

	if (_type == Type::INTEGER)
	{
		return static_cast<unsigned char>(_baseData.intVal);
	}

	if (_type == Type::STRING)
	{
		return static_cast<unsigned char>(atoi(_strData.c_str()));
	}

	if (_type == Type::FLOAT)
	{
		return static_cast<unsigned char>(_baseData.floatVal);
	}

	if (_type == Type::DOUBLE)
	{
		return static_cast<unsigned char>(_baseData.doubleVal);
	}

	if (_type == Type::BOOLEAN)
	{
		return _baseData.boolVal ? 1 : 0;
	}

	return 0;
}

int CValue::asInt() const
{
	//CCASSERT(_type != Type::VECTOR && _type != Type::MAP, "");
	if (_type == Type::INTEGER)
	{
		return _baseData.intVal;
	}

	if (_type == Type::BYTE)
	{
		return _baseData.byteVal;
	}

	if (_type == Type::STRING)
	{
		return atoi(_strData.c_str());
	}

	if (_type == Type::FLOAT)
	{
		return static_cast<int>(_baseData.floatVal);
	}

	if (_type == Type::DOUBLE)
	{
		return static_cast<int>(_baseData.doubleVal);
	}

	if (_type == Type::BOOLEAN)
	{
		return _baseData.boolVal ? 1 : 0;
	}

	return 0;
}

float CValue::asFloat() const
{
	//CCASSERT(_type != Type::VECTOR && _type != Type::MAP, "");
	if (_type == Type::FLOAT)
	{
		return _baseData.floatVal;
	}

	if (_type == Type::BYTE)
	{
		return static_cast<float>(_baseData.byteVal);
	}

	if (_type == Type::STRING)
	{
		return atof(_strData.c_str());
	}

	if (_type == Type::INTEGER)
	{
		return static_cast<float>(_baseData.intVal);
	}

	if (_type == Type::DOUBLE)
	{
		return static_cast<float>(_baseData.doubleVal);
	}

	if (_type == Type::BOOLEAN)
	{
		return _baseData.boolVal ? 1.0f : 0.0f;
	}

	return 0.0f;
}

double CValue::asDouble() const
{
	//CCASSERT(_type != Type::VECTOR && _type != Type::MAP, "");
	if (_type == Type::DOUBLE)
	{
		return _baseData.doubleVal;
	}

	if (_type == Type::BYTE)
	{
		return static_cast<double>(_baseData.byteVal);
	}

	if (_type == Type::STRING)
	{
		return static_cast<double>(atof(_strData.c_str()));
	}

	if (_type == Type::INTEGER)
	{
		return static_cast<double>(_baseData.intVal);
	}

	if (_type == Type::FLOAT)
	{
		return static_cast<double>(_baseData.floatVal);
	}

	if (_type == Type::BOOLEAN)
	{
		return _baseData.boolVal ? 1.0 : 0.0;
	}

	return 0.0;
}

bool CValue::asBool() const
{
	//CCASSERT(_type != Type::VECTOR && _type != Type::MAP, "");
	if (_type == Type::BOOLEAN)
	{
		return _baseData.boolVal;
	}

	if (_type == Type::BYTE)
	{
		return _baseData.byteVal == 0 ? false : true;
	}

	if (_type == Type::STRING)
	{
		return (_strData == "0" || _strData == "false") ? false : true;
	}

	if (_type == Type::INTEGER)
	{
		return _baseData.intVal == 0 ? false : true;
	}

	if (_type == Type::FLOAT)
	{
		return _baseData.floatVal == 0.0f ? false : true;
	}

	if (_type == Type::DOUBLE)
	{
		return _baseData.doubleVal == 0.0 ? false : true;
	}

	return true;
}

std::string CValue::asString() const
{
	//CCASSERT(_type != Type::VECTOR && _type != Type::MAP, "");

	if (_type == Type::STRING)
	{
		return _strData;
	}

	std::stringstream ret;


	switch (_type) {
	case Type::BYTE:
		ret << _baseData.byteVal;
		break;
	case Type::INTEGER:
		ret << _baseData.intVal;
		break;
	case Type::FLOAT:
		ret << std::fixed << std::setprecision(7) << _baseData.floatVal;
		break;
	case Type::DOUBLE:
		ret << std::fixed << std::setprecision(16) << _baseData.doubleVal;
		break;
	case Type::BOOLEAN:
		ret << (_baseData.boolVal ? "true" : "false");
		break;
	default:
		break;
	}
	return ret.str();
}

CValueVector& CValue::asCValueVector()
{
	if (nullptr == _vectorData)
		_vectorData = new CValueVector();
	return *_vectorData;
}

const CValueVector& CValue::asCValueVector() const
{
	static const CValueVector EMPTY_CValueVECTOR;
	if (nullptr == _vectorData)
		return EMPTY_CValueVECTOR;
	return *_vectorData;
}

CValueMap& CValue::asCValueMap()
{
	if (nullptr == _mapData)
		_mapData = new CValueMap();
	return *_mapData;
}

const CValueMap& CValue::asCValueMap() const
{
	static const CValueMap EMPTY_CValueMAP;
	if (nullptr == _mapData)
		return EMPTY_CValueMAP;
	return *_mapData;
}

CValueMapIntKey& CValue::asIntKeyMap()
{
	if (nullptr == _intKeyMapData)
		_intKeyMapData = new CValueMapIntKey();
	return *_intKeyMapData;
}

const CValueMapIntKey& CValue::asIntKeyMap() const
{
	static const CValueMapIntKey EMPTY_CValueMAP_INT_KEY;
	if (nullptr == _intKeyMapData)
		return EMPTY_CValueMAP_INT_KEY;
	return *_intKeyMapData;
}

static std::string getTabs(int depth)
{
	std::string tabWidth;

	for (int i = 0; i < depth; ++i)
	{
		tabWidth += "\t";
	}

	return tabWidth;
}

static std::string visit(const CValue& v, int depth);

static std::string visitVector(const CValueVector& v, int depth)
{
	std::stringstream ret;

	if (depth > 0)
		ret << "\n";

	ret << getTabs(depth) << "[\n";

	int i = 0;
	for (const auto& child : v)
	{
		ret << getTabs(depth + 1) << i << ": " << visit(child, depth + 1);
		++i;
	}

	ret << getTabs(depth) << "]\n";

	return ret.str();
}

template <class T>
static std::string visitMap(const T& v, int depth)
{
	std::stringstream ret;

	if (depth > 0)
		ret << "\n";

	ret << getTabs(depth) << "{\n";

	for (auto iter = v.begin(); iter != v.end(); ++iter)
	{
		ret << getTabs(depth + 1) << iter->first << ": ";
		ret << visit(iter->second, depth + 1);
	}

	ret << getTabs(depth) << "}\n";

	return ret.str();
}

static std::string visit(const CValue& v, int depth)
{
	std::stringstream ret;

	switch (v.getType())
	{
	case CValue::Type::NONE:
	case CValue::Type::BYTE:
	case CValue::Type::INTEGER:
	case CValue::Type::FLOAT:
	case CValue::Type::DOUBLE:
	case CValue::Type::BOOLEAN:
	case CValue::Type::STRING:
		ret << v.asString() << "\n";
		break;
	case CValue::Type::VECTOR:
		ret << visitVector(v.asCValueVector(), depth);
		break;
	case CValue::Type::MAP:
		ret << visitMap(v.asCValueMap(), depth);
		break;
	case CValue::Type::INT_KEY_MAP:
		ret << visitMap(v.asIntKeyMap(), depth);
		break;
	default:
		//CCASSERT(false, "Invalid type!");
		break;
	}

	return ret.str();
}

std::string CValue::getDescription()
{
	std::string ret("\n");
	ret += visit(*this, 0);
	return ret;
}

void CValue::clear()
{
	_type = Type::NONE;
	_baseData.doubleVal = 0.0;
	_strData.clear();
	CC_SAFE_DELETE(_vectorData);
	CC_SAFE_DELETE(_mapData);
	CC_SAFE_DELETE(_intKeyMapData);
}
