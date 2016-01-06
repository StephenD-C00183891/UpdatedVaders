#include "Projectile.h"


USING_NS_CC;


Projectile::Projectile(Vec2 pos)
{
	//createAnimation(pos);
}

Projectile * Projectile::create(Vec2 position)
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();

	auto spritecache = SpriteFrameCache::getInstance();
	//spritecache->addSpriteFramesWithFile(ptr->m_projectileFile);
	//SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_projectileFile);
	spritecache->addSpriteFramesWithFile(ptr->m_textureAtlasPlistFile);
	Projectile * pSprite = new Projectile(position);
	pSprite->initWithSpriteFrameName("bullet.png");

	pSprite->autorelease();

		pSprite->initOptions(position);
   //spritebatch->addChild(pSprite, 1);

   //this->addChild(spritebatch, 1);
		return pSprite;
	

	CC_SAFE_DELETE(pSprite);
}

void Projectile::initOptions(Vec2 position)
{
	Point origin = Director::getInstance()->getVisibleOrigin();
	this->setPosition(position.x + origin.x, position.y + origin.y); // +this->getContentSize().height / 2);
}
void Projectile::createAnimation(Vec2 pos){

	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile(ptr->m_laserPlistFile);
	int frames = 4;
	for (int i = 0; i < frames; i++)
	{
		m_animFrames.pushBack(spritecache->getSpriteFrameByName(std::to_string(i) + ".png"));
	}
	Animation* animation = Animation::createWithSpriteFrames(m_animFrames, 0.05f);
	Animate* animate = Animate::create(animation);

	m_Sprite = Sprite::createWithSpriteFrame(m_animFrames.at(0));
	m_Sprite->setPosition(Vec2(pos));
	m_Sprite->setScale(1);
	m_Sprite->runAction(RepeatForever::create(animate));
	m_LaserSprites.pushBack(m_Sprite);

}
cocos2d::Vector<cocos2d::Sprite *> & Projectile::getBulletSpriteList()
{
	return m_LaserSprites;
}

void Projectile::update()
{
	
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	Vec2 nextPosition(m_dirVec.x * ptr->m_velocity, m_dirVec.y * ptr->m_velocity);
	this->setPosition(this->getPosition().x + nextPosition.x, this->getPosition().y + nextPosition.y);
}

void Projectile::setTTL(int ttl)
{
	m_ttl = ttl;
}

/*cocos2d::Vec2 Projectile::getPosition()
{
	return m_Sprite->getPosition();
}*/


cocos2d::Sprite *& Projectile::spritereturn(){

	return m_Sprite;
}