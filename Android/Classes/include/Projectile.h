#pragma once

#include <utility>
#include "cocos2d.h"
#include "GameData.h"

class Projectile : public cocos2d::Sprite
{
private:
	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames;
public:
	float m_ttl;
	cocos2d::Vec2 m_dirVec;
	
	Projectile(cocos2d::Vec2 pos);
	cocos2d::Sprite *& spritereturn();
	static Projectile * create(cocos2d::Vec2 position);

	void initOptions(cocos2d::Vec2 position);
	cocos2d::Sprite* m_Sprite;
	void update();
	void createAnimation(cocos2d::Vec2 pos);
	void setTTL(int ttl);
	//cocos2d::Vec2 getPosition();
	cocos2d::Vector<cocos2d::Sprite *> & getBulletSpriteList();
	cocos2d::Vector<cocos2d::Sprite *> m_LaserSprites;
};