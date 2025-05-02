#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 800

#include <windows.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

#include "Objects/PaintTool.h"
#include "Objects/Circle.h"
#include "Objects/Player.h"
#include "Objects/Bullet.h"
#include "Objects/BulletManager.h"
#include "Objects/Enemy.h"

#include "Framework/GameManager.h"

extern HWND hWnd;
extern POINT mousePos;