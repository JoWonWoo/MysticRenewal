#pragma once

#include <stdio.h>
#include <Windows.h>

#define PTM_RATIO 180.0f

#define MAX_LEN 255

//#define OnePlayer_TEST

#define MAX_KEY 256

#define CC_DEGREES_TO_RADIANS(__ANGLE__) ((__ANGLE__) * 0.01745329252f) // PI / 180

#define CC_RADIANS_TO_DEGREES(__ANGLE__) ((__ANGLE__) * 57.29577951f) // PI * 180

//DirectInput °´Ã¼.
extern LPDIRECTINPUT8        m_pDX8;
//Device °´Ã¼.
extern LPDIRECTINPUTDEVICE8  m_pKeyboard;
extern BYTE                  m_Key[256];


static void CCLog(const char * pszFormat, ...)
{
	//	if (DEBUG)
	{
		char szBuf[MAX_LEN];
		va_list ap;
		va_start(ap, pszFormat);
		vsnprintf_s(szBuf, MAX_LEN, MAX_LEN, pszFormat, ap);
		va_end(ap);
		WCHAR wszBuf[MAX_LEN] = { 0 };
		//	MultiByteToWideChar(CP_UTF8, 0, szBuf, -1, wszBuf, sizeof(wszBuf));
		MultiByteToWideChar(CP_ACP, 0, szBuf, -1, wszBuf, sizeof(wszBuf));
		OutputDebugStringW(wszBuf);
		OutputDebugStringA("\n");
	}
}
static void Log(const char * pszFormat, ...)
{
	//	if (DEBUG)
	{
		char szBuf[MAX_LEN];
		va_list ap;
		va_start(ap, pszFormat);
		vsnprintf_s(szBuf, MAX_LEN, MAX_LEN, pszFormat, ap);
		va_end(ap);
		WCHAR wszBuf[MAX_LEN] = { 0 };
		//	MultiByteToWideChar(CP_UTF8, 0, szBuf, -1, wszBuf, sizeof(wszBuf));
		MultiByteToWideChar(CP_ACP, 0, szBuf, -1, wszBuf, sizeof(wszBuf));
		OutputDebugStringW(wszBuf);
		OutputDebugStringA("\n");
	}
}

#define CC_SAFE_DELETE(p)   { if((p != NULL)) { delete (p); (p) = NULL; } }
#define CC_SAFE_RELEASE(p) if (p != NULL) { (p)->Release(); (p)=NULL; }
#define CC_SAFE_DELETE_ARRAY(p)  { if((p != NULL)) { delete[] (p); (p) = NULL; } }


//#define MALLOC(TYPE,COUNT) ((TYPE*)_malloc(sizeof(TYPE) * COUNT, __FILE__, __LINE__))
//#define CALLOC(TYPE,COUNT) ((TYPE*)_calloc(COUNT, sizeof(TYPE), __FILE__, __LINE__))
