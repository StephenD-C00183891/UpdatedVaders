#pragma once
#include "GameScene.h"
#include "cocos2d.h"
#include "Mute.h"


class OptionsMenu : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void activateMainMenuScene(Ref * pSender);
	void mutesound(Ref *pSender);
	bool muted;

	CREATE_FUNC(OptionsMenu);
};