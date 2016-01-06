#include "Shield.h"

USING_NS_CC;

Shield::Shield() 
{
	health = 100;

}

Shield * Shield::create(Vec2 position)
{
	
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();

	auto spritecache = SpriteFrameCache::getInstance();
	Shield * pShield = new Shield();
	
	spritecache->addSpriteFramesWithFile(ptr->m_ShieldPlistFile);
   	pShield->initWithSpriteFrameName("shield.png");
	//pShield->setTexture("shield.png");
	pShield->autorelease();
	pShield->initOptions(position);
	return pShield;
	
	
	CC_SAFE_DELETE(pShield);
	return NULL;
	
}
void Shield::Update(){
	if (health < 80)
	{
		this->setSpriteFrame("shield1.png");
	}
	if (health < 60)
	{
		this->setSpriteFrame("shield2.png");
	}
	if (health < 40)
	{
		this->setSpriteFrame("shield3.png");
	}
}
void Shield::setHealth(int temp){
	health = health - temp;
}
int Shield::getHealth(){
   return health;
}


void Shield::initOptions(Vec2 position)
{
	Point origin = Director::getInstance()->getVisibleOrigin();
	this->setPosition(position.x + origin.x, position.y + origin.y);
}