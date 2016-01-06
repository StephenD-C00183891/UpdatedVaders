#include "Bullet.h"
USING_NS_CC;




Bullet::Bullet(cocos2d::Vec2 pos)
{
	m_Position = cocos2d::Vec2(pos.x, pos.y);
	vel = cocos2d::Vec2(0, 10);
	bulletSprite = cocos2d::Sprite::create("GameScreen /bullet.png");

}

void Bullet::update(){

	m_Position += vel;


}