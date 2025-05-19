#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define CENTER_X (SCREEN_WIDTH >> 1)
#define CENTER_Y (SCREEN_HEIGHT >> 1)

#define CENTER Vector2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f)

#define PI 3.141592f

#define DELTA Timer::Get()->GetElapsedTime()
#define SCENE SceneManager::Get()

#include <windows.h>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <functional>
#include <fstream>

#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace std;

#include "Framework/Utilities/Utility.h"
#include "Framework/Utilities/Singleton.h"
#include "Framework/Utilities/Timer.h"
#include "Framework/Utilities/Input.h"

#include "Framework/Math/Vector2.h"

#include "Objects/Basic/GameObject.h"
#include "Objects/Basic/Circle.h"
#include "Objects/Basic/Rect.h"

#include "Objects/UI/Button.h"
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

#include "Scenes/Scene.h"
#include "Framework/Manager/SceneManager.h"
#include "Framework/Manager/GameManager.h"

extern HWND hWnd;
extern Vector2 mousePos;