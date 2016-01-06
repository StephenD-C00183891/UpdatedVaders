#pragma once

#include "cocos2d.h"

class Bullet : public cocos2d::Sprite
{
private:
	bool m_touched;
	cocos2d::Vec2 m_Position;
	cocos2d::Vec2 vel;
public:
	Bullet(cocos2d::Vec2 pos);
	void update();
	cocos2d::Sprite* bulletSprite;
};