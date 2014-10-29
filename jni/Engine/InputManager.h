#pragma once
#include "FastDelegate.h"
#include "htype.h"
#include <stdio.h>
using namespace fastdelegate;
enum MouseType
{
	MouseDown,
	MouseUp,
	MouseDClick,
	MouseMove,
	MouseWheel
};

class  MousePos
{
public:
	int X;
	int Y;
	MousePos()
	{
		X =0;
		Y = 0;
	}
	MousePos(int x, int y)
	{
		X = x;
		Y = y;
	}
};

typedef FastDelegate2<MouseType, MousePos> MouseEvenHandle;

class GRAPHIC_API InputManager
{

public:
	static InputManager& GetInstance();
	void MouseEven(MouseType nType, MousePos pos);
	MouseEvenHandle _handle;
private:
	InputManager();
	~InputManager();

private:
	MousePos mouseLast;
	
};
#define g_ojbInputManager InputManager::GetInstance()
