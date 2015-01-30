#include "Stdafx.h"



const CData CData::Null;

CData::CData() :
_bytes(nullptr),
_size(0)
{
	Log("In the empty constructor of CData.");
}

CData::CData(CData&& other) :
_bytes(nullptr),
_size(0)
{
	Log("In the move constructor of CData.");
	move(other);
}

CData::CData(const CData& other) :
_bytes(nullptr),
_size(0)
{
	Log("In the copy constructor of CData.");
	copy(other._bytes, other._size);
}

CData::~CData()
{
	Log("deallocing CData: %p", this);
	clear();
}

CData& CData::operator= (const CData& other)
{
	Log("In the copy assignment of CData.");
	copy(other._bytes, other._size);
	return *this;
}

CData& CData::operator= (CData&& other)
{
	Log("In the move assignment of CData.");
	move(other);
	return *this;
}

void CData::move(CData& other)
{
	_bytes = other._bytes;
	_size = other._size;

	other._bytes = nullptr;
	other._size = 0;
}

bool CData::isNull() const
{
	return (_bytes == nullptr || _size == 0);
}

unsigned char* CData::getBytes() const
{
	return _bytes;
}

ssize_t CData::getSize() const
{
	return _size;
}

void CData::copy(unsigned char* bytes, const ssize_t size)
{
	clear();

	if (size > 0)
	{
		_size = size;
		_bytes = (unsigned char*)malloc(sizeof(unsigned char)* _size);
		memcpy(_bytes, bytes, _size);
	}
}

void CData::fastSet(unsigned char* bytes, const ssize_t size)
{
	_bytes = bytes;
	_size = size;
}

void CData::clear()
{
	free(_bytes);
	_bytes = nullptr;
	_size = 0;
}
