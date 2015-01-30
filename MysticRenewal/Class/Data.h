#pragma once
#define ssize_t long _w64

class CData
{
public:
	static const CData Null;

	CData();
	CData(const CData& other);
	CData(CData&& other);
	~CData();

	// Assignment operator
	CData& operator= (const CData& other);
	CData& operator= (CData&& other);

	unsigned char* getBytes() const;

	ssize_t getSize() const;

	/** Copies the buffer pointer and its size.
	*  @note This method will copy the whole buffer.
	*        Developer should free the pointer after invoking this method.
	*  @see CData::fastSet
	*/
	void copy(unsigned char* bytes, const ssize_t size);

	void fastSet(unsigned char* bytes, const ssize_t size);

	/** Clears CData, free buffer and reset CData size */
	void clear();

	/** Check whether the CData is null. */
	bool isNull() const;

private:
	void move(CData& other);

private:
	unsigned char* _bytes;
	ssize_t _size;
};

