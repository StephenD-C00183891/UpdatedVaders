#pragma once

#include "cocos2d.h"
#include "MainMenu.h"
#include "GameData.h"
#include "GameScene.h"
#include "HighScore.h"


class GameOver : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	// Called when retry is selected 
	void activateGameScene(Ref *pSender);
	// Called when main menu is selected 
	void activateMainMenuScene(Ref *pSender);
	void activateHighScoreScene(Ref *pSender);
	//GameScene* gscene;
	//HighScore*  m_Score;
	CREATE_FUNC(GameOver);
};