#pragma once

#include "cocos2d.h"
#include "GameScene.h"
#include "MainMenu.h"
#include "GameData.h"


class HighScore : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	std::vector<int> m_ScoreBoard;
	cocos2d::Label* first;
	cocos2d::Label* second;
	cocos2d::Label* third;
	cocos2d::Label* fourth;
	cocos2d::Label* fifth;
	void activateMainMenuScene(Ref *pSender);
	void fillScoreBoard(int p1Score, int p2Score);
	void addBackGroundSprite(cocos2d::Size const & visibleSize, cocos2d::Point const & origin);
	CREATE_FUNC(HighScore);
};