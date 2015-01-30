#pragma once
////메인으로이동
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

//warning 무시
#pragma warning(disable:4244)
#pragma warning(disable:4996)
#pragma warning(disable:4018)
#pragma warning(disable:4305)
#pragma warning(disable:4005)
#pragma warning(disable:4316)

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "lib/spine-c.lib")
#pragma comment(lib, "lib/live2d_directX_mtd.lib")
#pragma comment(lib, "imm32.lib")

#define DIRECTINPUT_VERSION 0x0800

//////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>
#include <map>
#include <stack>
#include <vector>
#include <list>
#include <unordered_map>
#include <dinput.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <string>
#include <set>
#include <comutil.h>
#include <float.h>
#include <math.h>
#include <io.h>
#include <string>




//////////////////////////////////////////////////////////////////////////
//DataType Model
//////////////////////////////////////////////////////////////////////////
#include "Interface/Datatype/Size.h"
#include "Interface/Datatype/Point.h"
#include "Interface/Datatype/Rect.h"
#include "Interface/Datatype/Value.h"
#include "system.h"

//////////////////////////////////////////////////////////////////////////
#include "Main/Direct3dx.h"
#include "Main/DirectXInput.h"
#include "Main/Director.h"

//////////////////////////////////////////////////////////////////////////
//InterfaceClass
//////////////////////////////////////////////////////////////////////////
#include "Interface/Node.h"
#include "Interface/Texture.h"
#include "Interface/Sprite.h"
#include "Interface/Layer.h"
#include "Interface/Scene.h"


typedef std::unordered_map<std::string, CValue> CValueMap;
//////////////////////////////////////////////////////////////////////////
//Class
//////////////////////////////////////////////////////////////////////////
#include "Class/Camera.h"
#include "Class/Sprite3D.h"
#include "Class/Data.h"


//////////////////////////////////////////////////////////////////////////
//Manager
//////////////////////////////////////////////////////////////////////////
#include "Manager/SceneManager.h"
#include "Manager/TextureManager.h"
#include "Manager/FileManager.h"

//////////////////////////////////////////////////////////////////////////
//Include
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//Scene
//////////////////////////////////////////////////////////////////////////
#include "Scene/LogoScene.h"
#include "Scene/IngameScene.h"

#include "Scene/Utill/MaptoolScene.h"
//////////////////////////////////////////////////////////////////////////
//Example Scene
//////////////////////////////////////////////////////////////////////////
