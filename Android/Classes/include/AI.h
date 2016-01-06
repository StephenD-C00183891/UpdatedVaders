#pragma once

#include "cocos2d.h"
#include "GameData.h"
#include "GameStates.h"

class AI 
{
private:

	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames;
	cocos2d::Vector<cocos2d::FiniteTimeAction *> m_wayPoints;
	float m_elapsedTime;
	int m_indexOfNextAI;
	GameStates & m_gameState;
	void createAnimatedSprites(GameStates & gameState, int maxAI);
	cocos2d::Vec2 m_Position;
	cocos2d::Vec2 m_Velocity;
	cocos2d::Layer * currentLayer;
public:
	cocos2d::Vector<cocos2d::Sprite *> m_aiSprites;
	AI(GameStates & gameState, cocos2d::Layer &currentLayer, int maxAI);
	AI();
	void update(float dt, float speed);
	cocos2d::Vector<cocos2d::Sprite *> & getAISpriteList();
};