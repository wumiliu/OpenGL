#pragma once
#include "htype.h"
#include "InputManager.h"
#include "ScrolRect.h"
class GRAPHIC_API  GameManager
{
public:
	static GameManager& GetInstance();
	void Process();
	void MouseEven(MouseType nType, MousePos pos);
public:
	GameManager();
	~GameManager();
	ScrolRect* pScrolRect;
};

#define  g_objGameManager GameManager::GetInstance()
