#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
<<<<<<< HEAD
=======

#define CENTER_X (SCREEN_WIDTH >> 1)
#define CENTER_Y (SCREEN_HEIGHT >> 1)

#define CENTER Vector2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f)
>>>>>>> upstream/main

#define CENTER_X (SCREEN_WIDTH >> 1)
#define CENTER_Y (SCREEN_HEIGHT >> 1)

#define CENTER Vector2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f)

#define DELTA Timer::Get()->GetElapsedTime()
#define SCENE SceneManager::Get()
<<<<<<< HEAD
=======

#define DEVICE Device::Get()->GetDevice()
#define DC Device::Get()->GetDeviceContext()
>>>>>>> upstream/main

#include <windows.h>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <functional>
#include <fstream>
<<<<<<< HEAD

#include <d3d11.h>
#include <d3dcompiler.h>
=======
#include <assert.h>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
>>>>>>> upstream/main

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace std;
using namespace DirectX;

<<<<<<< HEAD
=======
typedef XMFLOAT4 Float4;
typedef XMFLOAT3 Float3;
typedef XMFLOAT2 Float2;
typedef XMMATRIX Matrix;
typedef XMVECTOR Vector4;
typedef XMFLOAT4X4 Float4x4;


>>>>>>> upstream/main
#include "Framework/Utilities/Utility.h"
#include "Framework/Utilities/Singleton.h"
#include "Framework/Utilities/Timer.h"
#include "Framework/Utilities/Input.h"

#include "Framework/Math/Vector2.h"

<<<<<<< HEAD
=======
#include "Framework/Device/Device.h"

#include "Framework/Shader/Shader.h"
#include "Framework/Shader/VertexShader.h"
#include "Framework/Shader/PixelShader.h"

#include "Framework/Buffer/VertexLayouts.h"
#include "Framework/Buffer/VertexBuffer.h"
#include "Framework/Buffer/IndexBuffer.h"
#include "Framework/Buffer/ConstBuffer.h"
#include "Framework/Buffer/GlobalBffer.h"

>>>>>>> upstream/main
#include "Objects/Basic/GameObject.h"
#include "Objects/Basic/Circle.h"
#include "Objects/Basic/Rect.h"

#include "Objects/UI/Button.h"
<<<<<<< HEAD
#include "Objects/UI/Panel.h"

#include "Objects/Manger/DataManager.h"
#include "Objects/Manger/EventManager.h"

#include "Objects/Inventory/Good.h"
#include "Objects/Inventory/StorePanel.h"
#include "Objects/Inventory/InventoryItem.h"
#include "Objects/Inventory/InventoryPanel.h"
#include "Objects/Inventory/InventoryPlayer.h"
#include "Objects/Inventory/EquipPanel.h"

#include "Objects/Etc/PaintTool.h"
#include "Objects/Shooting/Player.h"
#include "Objects/Shooting/Bullet.h"
#include "Objects/Shooting/BulletManager.h"
#include "Objects/Shooting/Enemy.h"
#include "Objects/Shooting/EnemyManager.h"
=======
#include "Objects/Manger/DataManager.h"
#include "Objects/Manger/EventManager.h"
>>>>>>> upstream/main

#include "Scenes/Scene.h"
#include "Framework/Manager/SceneManager.h"
#include "Framework/Manager/GameManager.h"

extern HWND hWnd;
extern Vector2 mousePos;