#pragma once
#include <utility>
#include "cocos2d.h"
#include "GameData.h"
#include "GameStates.h"
#include "Projectile.h"
#include "cocos2d.h"


class Player
{
private:
	GameStates & m_gameState;
	bool m_touched;
	cocos2d::Vec2 vel;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames;
	
public:
	bool isPlayer1;
	cocos2d::Sprite* m_Sprite;
	std::vector<Projectile *> m_projectiles;	// A list of active projectiles.
	std::vector<Projectile *> m_projectiles2;
	Projectile * projectile;
	Projectile * projectile2;
	Player(cocos2d::Vec2 pos,GameStates & gameState);
	bool m_fireRequest;
	bool m_fireRequest2;
	void initOptions(cocos2d::Vec2 position, bool rotate);
	void createAnimation(cocos2d::Vec2 pos);
	void update(float dt);
	cocos2d::Sprite *& spritereturn();
	float timer;
	float timer2;
	const float DELAY = 0.5f;
	void moveLeft();
	void openFire();
	void openFire2();
	void moveRight();
	void handleTouchEvent(cocos2d::Touch* touch);
	bool isTouched() const;

	std::vector<Projectile> const & getProjectileList();
};