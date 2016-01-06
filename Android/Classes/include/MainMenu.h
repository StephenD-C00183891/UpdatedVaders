#pragma once
#include "GameScene.h"
#include "cocos2d.h"
#include "OptionsMenu.h"


class MainMenu : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void activateGameScene(Ref * pSender);
	void activateOptionsScene(Ref * pSender);
	CREATE_FUNC(MainMenu);
};